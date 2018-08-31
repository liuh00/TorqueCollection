#include "ParameterManager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QVariant>

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
				query.exec("CREATE TABLE 'parameterTable' ('name'  TEXT)");
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

		//查询参数模板表是否存在
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterTemplateTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//创建参数表
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterTemplateTable' ('parameterName'  TEXT, 'fileName'  TEXT,'templateData' BLOB )");
				if (!query.isActive())
				{
					//创建parameterTemplateTable表失败
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//查询parameterTemplateTable表失败
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
				query.exec("CREATE TABLE 'parameterDataTable' ('parameterName'  TEXT, 'row'  INTEGER,'column' INTEGER, 'data' TEXT");
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
	bool contains=false;
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

bool ParameterManager::uploadParameterFileToDatabase(QString parameterName, QString parameterFile, QString imageDir, QString templateFile)
{
	QSqlDatabase sql = getDatabase();

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



	





	return true;

}

ParameterManager::~ParameterManager()
{
}
