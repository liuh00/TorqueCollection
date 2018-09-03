#include "ParameterManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QVariant>
#include <QAxObject>


ParameterManager::ParameterManager(QObject* parent)
	: QObject(parent)
{
}

ParameterManager& ParameterManager::operator=(ParameterManager const&)
{
	return instance();
}

ParameterManager& ParameterManager::instance()
{
	static ParameterManager this_manager;
	return this_manager;
}


bool ParameterManager::init()
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";
	QString fileName = pathName + "/Parameter";
	QDir dir(pathName);

	if (!dir.exists())
	{
		dir.mkpath(pathName);
	}

	if (QSqlDatabase::contains("Parameter"))
	{
		QSqlDatabase::removeDatabase("Parameter");
	}

	QSqlDatabase sql = getDatabase();

	if (sql.open())
	{
		QSqlQuery query(sql);

		//查询参数表是否存在
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//创建参数表
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterTable' ('name' TEXT ,'fileName' TEXT, 'templateData' BLOB)");
				if (!query.isActive())
				{
					//创建parameterTable表失败
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//查询parameterTable表失败
			query.clear();
			sql.close();
			return false;
		}

		//查询参数图片表是否存在
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterImageTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//创建参数表
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterImageTable' ('parameterName'  TEXT, 'fileName'  TEXT,'imageData' BLOB )");
				if (!query.isActive())
				{
					//创建parameterImageTable表失败
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//查询parameterImageTable表失败
			query.clear();
			sql.close();
			return false;
		}

		//查询参数数据表是否存在
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterDataTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//创建参数表
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterDataTable' ('parameterName'  TEXT, 'row'  INTEGER, 'column' INTEGER, 'data' TEXT)");
				if (!query.isActive())
				{
					//创建parameterDataTable表失败
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//查询parameterDataTable表失败
			query.clear();
			sql.close();
			return false;
		}
		query.clear();
		sql.close();
		return true;
	}
	else
	{
		//Parameter数据库打开失败
		return false;
	}
}

void ParameterManager::Uninit()
{
	bool contains = false;
	if (QSqlDatabase::contains("Parameter"))
	{
		QSqlDatabase sql = getDatabase();
		sql.close();
		contains = true;
	}

	if (contains)
	{
		QSqlDatabase::removeDatabase("Parameter");
	}
}

QSqlDatabase& ParameterManager::getDatabase()
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";
	QString fileName = pathName + "/Parameter";

	if (!QSqlDatabase::contains("Parameter"))
	{
		QSqlDatabase sql = QSqlDatabase::addDatabase("QSQLITE", "Parameter");
		sql.setDatabaseName(fileName);
		sql.setUserName("Parameter.");
		sql.setPassword("Parameter.");
		return sql;
	}
	QSqlDatabase sql = QSqlDatabase::database("Parameter");
	return sql;
}

QList<QStringList> ParameterManager::getParameterForExcel(const QString& parameterFile)
{
	QList<QStringList> parameters;

	QAxObject* obj = new QAxObject("Excel.Application", this);

	if (obj == Q_NULLPTR)
	{
		return parameters;
	}


	obj->setProperty("Visible", false);
	obj->setProperty("DisplayAlerts", false);//不显示任何警告信息。

	QAxObject* workbooks = obj->querySubObject("Workbooks");

	if (workbooks == Q_NULLPTR)
	{
		obj->dynamicCall("Quit(void)");
		delete obj;
		return parameters;
	}
	QAxObject* workbook = workbooks->querySubObject("Open(QString)", QDir::toNativeSeparators(parameterFile));

	if (workbook == Q_NULLPTR)
	{
		workbooks->dynamicCall("Close(bool)", true);
		obj->dynamicCall("Quit(void)");
		delete workbooks;
		delete obj;
		return parameters;
	}
	QAxObject* sheets = workbook->querySubObject("Sheets");
	QAxObject* workSheet = sheets->querySubObject("Item(QString)", "List");


	if (workSheet == Q_NULLPTR)
	{
		workbooks->dynamicCall("Close(bool)", true);
		obj->dynamicCall("Quit(void)");
		delete sheets;
		delete workbooks;
		delete obj;
		return parameters;
	}

	QVariant var;
	QAxObject* qcosTableRange = workSheet->querySubObject("Range(QString)", "QCOSTable");
	if (qcosTableRange != Q_NULLPTR)
	{
		var = qcosTableRange->dynamicCall("Value");
		variantTovariantList(var, parameters);
		delete qcosTableRange;
	}

	workbooks->dynamicCall("Close(bool)", true);
	obj->dynamicCall("Quit(void)");


	delete workSheet;
	delete sheets;
	delete workbooks;
	delete obj;

	return parameters;
}

bool ParameterManager::checkParamentExist(const QString& parameterName)
{
	QSqlDatabase sql = getDatabase();

	if (sql.open())
	{
		QSqlQuery query(sql);
		//查询参数文件是否存在
		QString commandtext = QString("select count(*) as count  from parameterTable where name='%1'").arg(parameterName);
		query.exec(commandtext);
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			if (count > 0)
			{
				query.clear();
				sql.close();
				return false;
			}
		}
		else
		{
			query.clear();
			sql.close();
			return false;
		}
		//查询参数模板是否存在该参数
		commandtext = QString("select count(*) as count from parameterImageTable where parameterName='%1'").arg(parameterName);
		query.exec(commandtext);
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			if (count > 0)
			{
				sql.close();
				return false;
			}
		}
		else
		{
			query.clear();
			sql.close();
			return false;
		}
		//查询参数数据是否存在该参数
		commandtext = QString("select count(*) as count from parameterDataTable where parameterName='%1'").arg(parameterName);
		query.exec(commandtext);
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			if (count > 0)
			{
				sql.close();
				return false;
			}
		}
		else
		{
			query.clear();
			sql.close();
			return false;
		}
		query.clear();
		sql.close();
		return true;
	}
	return false;
}


// ReSharper disable once CppMemberFunctionMayBeStatic
void ParameterManager::variantTovariantList(const QVariant& var, QList<QStringList>& res)
{
	QVariantList varRows = var.toList();
	if (varRows.isEmpty())
	{
		return;
	}
	const int rowCount = varRows.size();
	QVariantList rowData;
	for (int i = 0; i < rowCount; ++i)
	{
		rowData = varRows[i].toList();
		QStringList parItems;
		for (int j = 0; j < rowData.count(); j++)
		{
			parItems.append(rowData.at(j).toString());
		}
		res.append(parItems);
	}
}


bool ParameterManager::uploadParameterFileToDatabase(const QString& parameterName, const QString& parameterFile, const QString& imageDir, const QString& templateFile)
{
	QFile fparameter(parameterFile);
	QDir dimage(imageDir);
	QFile ftemplate(templateFile);
	if (!fparameter.exists())
	{
		//参数文件不存在
		return false;
	}
	if (!dimage.exists())
	{
		//图片文件不存在
		return false;
	}

	if (!ftemplate.exists())
	{
		//模板文件不存在
		return false;
	}

	if (!checkParamentExist(parameterName))
	{
		//参数文件已存在
		return false;
	}


	QStringList nameFilters;
	nameFilters << "*.bmp";
	nameFilters << "*.BMP";

	QStringList imageFiles = dimage.entryList(nameFilters, QDir::Files, QDir::Name);

	QList<QStringList> parameters = getParameterForExcel(parameterFile);


	QSqlDatabase sql = getDatabase();
	if (sql.open())
	{
		sql.transaction();
		QSqlQuery query(sql);
		QString commandText;


		//插入参数名parameterTable
		if (!ftemplate.open(QIODevice::ReadOnly))
		{
			query.finish();
			sql.rollback();
			sql.close();
			return false;
		}
		QByteArray fdata = ftemplate.readAll();

		commandText = "INSERT INTO parameterTable (name,fileName,templateData) VALUES (:name,:fileName,:templateData)";
		query.prepare(commandText);
		query.bindValue(":name", parameterName);
		query.bindValue(":fileName", templateFile.section("/",-1));
		query.bindValue(":templateData", fdata);
		query.exec();
		if (!query.isActive())
		{
			fdata.clear();
			ftemplate.close();
			query.finish();
			sql.rollback();
			sql.close();
			return false;
		}
		fdata.clear();
		ftemplate.close();
		query.finish();

		//插入参数
		commandText = "INSERT INTO parameterDataTable (parameterName,row,column,data) VALUES (:parameterName,:row,:column,:data)";
		for (int i = 0; i < parameters.count(); i++)
		{
			QStringList rowData = parameters.at(i);
			for (int j = 0; j < rowData.count(); j++)
			{
				query.prepare(commandText);
				query.bindValue(":parameterName", parameterName);
				query.bindValue(":row", i + 1);
				query.bindValue(":column", j + 1);
				query.bindValue(":data", rowData.at(j));
				query.exec();
				if (!query.isActive())
				{
					query.finish();
					sql.rollback();
					sql.close();
					return false;
				}
				query.finish();
			}
		}
		//插入图片文件
		for (int i = 0; i < imageFiles.size(); i++)
		{
			QString path = imageDir + "/" + imageFiles.at(i);
			path.replace("//", "/");
			QFile file(path);
			if (!file.open(QIODevice::ReadOnly))
			{
				query.finish();
				sql.rollback();
				sql.close();
				return false;
			}
			QByteArray data = file.readAll();
			commandText = "INSERT INTO parameterImageTable (parameterName,fileName,imageData) VALUES (:parameterName,:fileName,:imageData)";
			query.prepare(commandText);
			query.bindValue(":parameterName", parameterName);
			query.bindValue(":fileName", imageFiles.at(i));
			query.bindValue(":imageData", data);
			query.exec();
			if (!query.isActive())
			{
				query.finish();
				file.close();
				data.clear();
				sql.rollback();
				sql.close();
				return false;
			}
			query.finish();
			file.close();
			data.clear();
		}

		//提交
		bool result = sql.commit();
		sql.close();
		if (!result)
		{
			return false;
		}
	}
	else
	{
		return false;
	}


	return true;
}

bool ParameterManager::generateTemplateFile(const QString& parameterName)
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Temporary";
	QDir dir(pathName);

	if (!dir.exists(pathName))
	{
		dir.mkdir(pathName);
	}

	QSqlDatabase sql = getDatabase();
	QString fileName;
	QByteArray data;
	if (sql.open())
	{
		QSqlQuery query(sql);
		QString commandText;
		commandText = QString("select * from parameterTable where name='%1'").arg(parameterName);
		query.exec(commandText);
		if (query.isActive() && query.next())
		{
			fileName = query.value("fileName").toString();
			data = query.value("templateData").toByteArray();
			query.clear();
			sql.close();
		}
		else
		{
			query.clear();
			sql.close();
			return false;
		}
	}
	else
	{
		return false;
	}

	if(fileName.isEmpty() || data.count() <= 0)
	{
		return false;
	}

	QString path = pathName + "/" + fileName;
	
	QFile file(path);

	if(file.open(QIODevice::ReadWrite))
	{
		file.write(data);
		file.close();
	}
	else
	{
		return false;
	}


	return true;
}

bool ParameterManager::generateImageFile(const QString &parameterName, const QStringList &images)
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Temporary";
	QDir dir(pathName);

	if (!dir.exists(pathName))
	{
		dir.mkdir(pathName);
	}

	QSqlDatabase sql = getDatabase();
	
	if (sql.open())
	{
		QSqlQuery query(sql);
		QString commandText;
		for (int i = 0; i < images.size(); i++)
		{
			commandText = QString("select * from parameterImageTable where parameterName='%1' and fileName= '%2'").arg(parameterName).arg(images.at(i));
			query.exec(commandText);
			if (query.isActive() && query.next())
			{
				QString fileName = query.value("fileName").toString();
				QByteArray data = query.value("imageData").toByteArray();
				if (fileName.isEmpty() || data.count() <= 0)
				{
					return false;
				}

				QString path = pathName + "/" + fileName;

				QFile file(path);

				if (file.open(QIODevice::ReadWrite))
				{
					file.write(data);
					file.close();
				}
				else
				{
					return false;
				}
				query.clear();
			}
			else
			{
				query.clear();
				sql.close();
				return false;
			}

		}
		sql.close();
	}
	else
	{
		return false;
	}

	



	return true;

}

ParameterManager::~ParameterManager()
{
}
