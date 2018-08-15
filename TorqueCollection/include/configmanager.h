#pragma once

#include <QObject>
#include <log4qt/logger.h>
#include <databaseconnectparameter.h>

class ConfigManager : public QObject
{
	Q_OBJECT
	LOG4QT_DECLARE_QCLASS_LOGGER

public:
	static ConfigManager &instance();
	~ConfigManager();
public:
	QList<DatabaseConnectParameter> getDatabaseConnecttionParameter();
	bool init();
private:
	ConfigManager(QObject *parent = Q_NULLPTR);
	ConfigManager(ConfigManager const&);
	ConfigManager& operator=(ConfigManager const&);

};
