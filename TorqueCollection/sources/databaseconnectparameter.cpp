#include "databaseconnectparameter.h"

DatabaseConnectParameter::DatabaseConnectParameter(QObject *parent)
	: QObject(parent)
{
	valid = false;
}

DatabaseConnectParameter::~DatabaseConnectParameter()
{
}

QString DatabaseConnectParameter::getConnectName() const
{
	return connectName;
}

void DatabaseConnectParameter::setConnectName(const QString& connect_name)
{
	connectName = connect_name;
}

DatabaseConnectParameter::ConnecttionType DatabaseConnectParameter::getConnectBaseType() const
{
	return connectBaseType;
}

void DatabaseConnectParameter::setConnectBaseType(const ConnecttionType connect_base_type)
{
	connectBaseType = connect_base_type;
}

QString DatabaseConnectParameter::getHostName() const
{
	return hostName;
}

void DatabaseConnectParameter::setHostName(const QString& host_name)
{
	hostName = host_name;
}

int DatabaseConnectParameter::getPort() const
{
	return port;
}

void DatabaseConnectParameter::setPort(const int port)
{
	this->port = port;
}

QString DatabaseConnectParameter::getDatabaseName() const
{
	return databaseName;
}

void DatabaseConnectParameter::setDatabaseName(const QString& database_name)
{
	databaseName = database_name;
}

QString DatabaseConnectParameter::getUserName() const
{
	return userName;
}

void DatabaseConnectParameter::setUserName(const QString& user_name)
{
	userName = user_name;
}

QString DatabaseConnectParameter::getUserPassword() const
{
	return userPassword;
}

void DatabaseConnectParameter::setUserPassword(const QString& user_password)
{
	userPassword = user_password;
}

QString DatabaseConnectParameter::getOptions() const
{
	return options;
}

void DatabaseConnectParameter::setOptions(const QString& q_char)
{
	options = q_char;
}

bool DatabaseConnectParameter::isValid()
{
	return valid;
}

void DatabaseConnectParameter::setValid(bool valid)
{
	this->valid = valid;
}

QString DatabaseConnectParameter::getConnectBaseTypeToString() const
{
	switch (connectBaseType)
	{
	case DatabaseConnectParameter::QDB2:
		return "QDB2";
		break;
	case DatabaseConnectParameter::QIBASE:
		return "QIBASE";
		break;
	case DatabaseConnectParameter::QMYSQL:
		return "QMYSQL";
		break;
	case DatabaseConnectParameter::QOCI:
		return "QOCI";
		break;
	case DatabaseConnectParameter::QODBC:
		return "QODBC";
		break;
	case DatabaseConnectParameter::QPSQL:
		return "QPSQL";
		break;
	case DatabaseConnectParameter::QSQLITE:
		return "QSQLITE";
		break;
	case DatabaseConnectParameter::QSQLITE2:
		return "QSQLITE2";
		break;
	case DatabaseConnectParameter::QTDS:
		return "QTDS";
		break;
	default:
		return "Unknow";
		break;

	}
}

DatabaseConnectParameter::DatabaseConnectParameter(const DatabaseConnectParameter& other)
	: connectName(other.connectName),
	connectBaseType(other.connectBaseType),
	hostName(other.hostName),
	port(other.port),
	databaseName(other.databaseName),
	userName(other.userName),
	userPassword(other.userPassword),
	options(other.options),
	valid(other.valid)
{
}

DatabaseConnectParameter::DatabaseConnectParameter(DatabaseConnectParameter&& other) : connectName(std::move(other.connectName)),
	connectBaseType(other.connectBaseType),
hostName(std::move(other.hostName)),
port(other.port),
databaseName(std::move(other.databaseName)),
userName(std::move(other.userName)),
userPassword(std::move(other.userPassword)),
options(std::move(other.options)),
valid(other.valid)
{
}

DatabaseConnectParameter& DatabaseConnectParameter::operator=(const DatabaseConnectParameter& other)
{
		if (this == &other)
			return *this;
		connectName = other.connectName;
		connectBaseType = other.connectBaseType;
		port = other.port;
		hostName = other.hostName;
		databaseName = other.databaseName;
		userName = other.userName;
		userPassword = other.userPassword;
		options = other.options;
		valid = other.valid;
		return *this;

}

DatabaseConnectParameter& DatabaseConnectParameter::operator=(DatabaseConnectParameter&& other)
{
		if (this == &other)
			return *this;
		connectName = std::move(other.connectName);
		connectBaseType = other.connectBaseType;
		port = other.port;
		hostName = std::move(other.hostName);
		databaseName = std::move(other.databaseName);
		userName = std::move(other.userName);
		userPassword = std::move(other.userPassword);
		options = std::move(other.options);
		valid = other.valid;
		return *this;
}
