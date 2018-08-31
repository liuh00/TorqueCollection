#pragma once

#include <QObject>
#include <QSqlDatabase>

class ParameterManager : public QObject
{
	Q_OBJECT
public:
	static ParameterManager &instance();
public:
	bool init();
	void Uninit();
	QSqlDatabase &getDatabase();
	bool uploadParameterFileToDatabase(QString paramentName, QString  paramentFile ,QString imageDir,QString templateFile);
public:
	~ParameterManager();
private:
	ParameterManager(QObject *parent = Q_NULLPTR);
	ParameterManager(ParameterManager const&);
	ParameterManager& operator=(ParameterManager const&);
};
