#pragma once

#include <QObject>
#include <QMap>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{

	Q_OBJECT
private:
	DatabaseManager(QObject *parent = Q_NULLPTR);
	DatabaseManager(DatabaseManager const&);
public:
	static DatabaseManager &instance();
	~DatabaseManager();

	bool CreateDatabaseConnecttion();

	void DisconnectDatabase(const QStringList devs);

private:
	DatabaseManager& operator=(DatabaseManager const&);



};
