#include "databasemanager.h"
#include <databaseconnectparameter.h>
#include <configmanager.h>
#include <log4qt/logger.h>
#include <QStringList>
DatabaseManager::DatabaseManager(QObject *parent)
	: QObject(parent)
{

}

DatabaseManager& DatabaseManager::instance()
{
	static DatabaseManager thisManager;
	return thisManager;
}

bool DatabaseManager::CreateDatabaseConnecttion()
{

	bool result = true;
	
	ConfigManager &cfManager = ConfigManager::instance();

	QList<DatabaseConnectParameter> databatePars = cfManager.getDatabaseConnecttionParameter();

	for (int i = 0; i < databatePars.size(); i++)
	{
		DatabaseConnectParameter par = databatePars.at(i);

		if(QSqlDatabase::contains(par.getConnectName()))
		{
			QStringList strList;
			strList.append(par.getConnectName());
			DisconnectDatabase(strList);
		}

		QSqlDatabase database = QSqlDatabase::addDatabase(par.getConnectBaseTypeToString(), par.getConnectName());
		database.setHostName(par.getHostName());
		database.setPort(par.getPort());
		database.setDatabaseName(par.getDatabaseName());
		database.setUserName(par.getUserName());
		database.setPassword(par.getUserPassword());
		database.setConnectOptions(par.getOptions());
		if(!database.open())
		{
			Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
			logger->error(QString::fromLocal8Bit("连接为:%1 打开失败！").arg(par.getConnectName()));
			result = false;
		}

	}
	
	return result;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void DatabaseManager::DisconnectDatabase(const QStringList devs)
{
	for (int i = 0; i < devs.size(); i++)
	{
		QSqlDatabase sqldatabase = QSqlDatabase::database(devs.at(i), false);
		if(sqldatabase.isOpen())
		{
			sqldatabase.close();
		}
		QSqlDatabase::removeDatabase(devs.at(i));
	}

}

DatabaseManager & DatabaseManager::operator=(DatabaseManager const &)
{
	return DatabaseManager::instance();
}

DatabaseManager::~DatabaseManager()
{

	DisconnectDatabase(QSqlDatabase::drivers());
}
