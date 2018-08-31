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

		//��ѯ�������Ƿ����
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//����������
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterTable' ('name'  TEXT)");
				if (!query.isActive())
				{
					//����parameterTable��ʧ��
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//��ѯparameterTable��ʧ��
			query.clear();
			sql.close();
			return false;
		}

		//��ѯ����ģ����Ƿ����
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterTemplateTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//����������
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterTemplateTable' ('parameterName'  TEXT, 'fileName'  TEXT,'templateData' BLOB )");
				if (!query.isActive())
				{
					//����parameterTemplateTable��ʧ��
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//��ѯparameterTemplateTable��ʧ��
			query.clear();
			sql.close();
			return false;
		}

		//��ѯ�������ݱ��Ƿ����
		query.exec("SELECT  count(*) as count  FROM sqlite_master WHERE name='parameterDataTable'");
		if (query.isActive() && query.next())
		{
			int count;
			count = query.value("count").toInt();
			//����������
			if (count == 0)
			{
				query.exec("CREATE TABLE 'parameterDataTable' ('parameterName'  TEXT, 'row'  INTEGER,'column' INTEGER, 'data' TEXT");
				if (!query.isActive())
				{
					//����parameterDataTable��ʧ��
					sql.close();
					return false;
				}
			}
		}
		else
		{
			//��ѯparameterDataTable��ʧ��
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
		//Parameter���ݿ��ʧ��
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
		//�����ļ�������
		return false;
	}
	if (!dimage.exists())
	{
		//ͼƬ�ļ�������
		return false;
	}

	if (!ftemplate.exists())
	{
		//ģ���ļ�������
		return false;
	}



	





	return true;

}

ParameterManager::~ParameterManager()
{
}
