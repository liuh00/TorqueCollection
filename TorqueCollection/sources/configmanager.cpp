#include "configmanager.h"

#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

ConfigManager::ConfigManager(QObject* parent)
	: QObject(parent)
{
}

bool ConfigManager::init()
{
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";
	QString fileName = pathName + "/AppConfig";
	QDir dir(pathName);
	if (!dir.exists())
	{
		dir.mkpath(pathName);
	}

	QSqlDatabase sql = QSqlDatabase::addDatabase("QSQLITE", "AppConfig");
	sql.setDatabaseName(fileName);
	sql.setUserName("AppConfig.");
	sql.setPassword("AppConfig.");
	if (sql.open())
	{
		QSqlQuery query(sql);
		//查询数据库配置表是否存在
		query.exec("SELECT count(*) as count  FROM sqlite_master WHERE name=\"databaseConfig\"");
		int count = 0;
		if (query.next() && query.isActive())
		{
			count = query.value("count").toInt();
		}

		if (count == 0)
		{
			//创建数据库配置表
			QString createTable = "CREATE TABLE \"databaseConfig\" (\"ConnectName\"  TEXT,\"DatabaseType\"  TEXT,\"HostName\"  TEXT,\"Port\" INTEGER,\"DatabaseName\"  TEXT,\"UserName\"  TEXT,\"UserPassword\"  TEXT,\"Options\"  TEXT)";
			query.exec(createTable);
			if(!query.isActive())
			{
				QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("databaseConfig配置文件创建错误."));
				sql.close();
				return false;
			}
		}
		
	}
	else
	{
		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("AppConfig配置文件打开错误."));
		return false;
	}

	sql.close();
	return true;

}

ConfigManager& ConfigManager::instance()
{
	static ConfigManager thisConfigManager;
	return thisConfigManager;
}

ConfigManager& ConfigManager::operator=(ConfigManager const&)
{
	return ConfigManager::instance();
}

ConfigManager::~ConfigManager()
{
	QSqlDatabase::removeDatabase("AppConfig");
}


QList<DatabaseConnectParameter> ConfigManager::getDatabaseConnecttionParameter()
{
	
	QString pathName = QCoreApplication::applicationDirPath() + "/Configuration";
	QString fileName = pathName + "/AppConfig";
	if(!QSqlDatabase::contains("AppConfig"))
	{
		QSqlDatabase sql = QSqlDatabase::addDatabase("QSQLITE", "AppConfig");
		sql.setDatabaseName(fileName);
		sql.setUserName("AppConfig.");
		sql.setPassword("AppConfig.");
	}

	QSqlDatabase sql = QSqlDatabase::database("AppConfig", true);

	if(!sql.isValid())
	{

		QMessageBox::warning(Q_NULLPTR, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("数据库打开错误."));
		return QList<DatabaseConnectParameter>();
	}

	QSqlQuery sqlQuery(sql);

	sqlQuery.exec("SELECT * FROM databaseConfig");
	QList<DatabaseConnectParameter> pars;
	while(sqlQuery.next())
	{
		
		DatabaseConnectParameter par;
		QString connectName = sqlQuery.value("ConnectName").toString();
		QString hostName = sqlQuery.value("HostName").toString();
		QString databaseName = sqlQuery.value("DatabaseName").toString();
		QString userName = sqlQuery.value("UserName").toString();
		QString userPassword = sqlQuery.value("UserPassword").toString();
		QString options = sqlQuery.value("Options").toString();
		int port= sqlQuery.value("Port").toInt();
		par.setConnectName(connectName);
		par.setHostName(hostName);
		par.setPort(port);
		par.setDatabaseName(databaseName);
		par.setUserName(userName);
		par.setUserPassword(userPassword);
		par.setOptions(options);
		pars.append(par);
		
	}
	sqlQuery.clear();
	sql.close();
	return pars;
	
}
