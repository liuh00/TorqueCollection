#pragma once

#include <QObject>

class DatabaseConnectParameter : public QObject
{
	Q_OBJECT

public:
		enum ConnecttionType {
		QDB2 = 0x0,
		QIBASE = 0x1,
		QMYSQL = 0x2,
		QOCI = 0x3,
		QODBC = 0x4,
		QPSQL = 0x5,
		QSQLITE = 0x6,
		QSQLITE2 = 0x7,
		QTDS = 0x8
	};

public:
	DatabaseConnectParameter(QObject *parent=Q_NULLPTR);
	~DatabaseConnectParameter();

	QString getConnectName() const;
	void setConnectName(const QString& connect_name);
	ConnecttionType getConnectBaseType() const;
	void setConnectBaseType(const ConnecttionType connect_base_type);
	QString getHostName() const;
	void setHostName(const QString& host_name);

	int getPort() const;
	void setPort(const int port);
	QString getDatabaseName() const;
	void setDatabaseName(const QString& database_name);
	QString getUserName() const;
	void setUserName(const QString& user_name);
	QString getUserPassword() const;
	void setUserPassword(const QString& user_password);

	QString getOptions() const;
	void setOptions(const QString& q_char);
	bool isValid();
	void setValid(bool valid);
	QString getConnectBaseTypeToString()const;


	DatabaseConnectParameter(const DatabaseConnectParameter& other);

	DatabaseConnectParameter(DatabaseConnectParameter&& other);


	DatabaseConnectParameter& operator=(const DatabaseConnectParameter& other);

	DatabaseConnectParameter& operator=(DatabaseConnectParameter&& other);


private:
	QString connectName;
	ConnecttionType connectBaseType;
	QString hostName;
	int port;
	QString databaseName;
	QString userName;
	QString userPassword;
	QString options;
	bool valid;
};
