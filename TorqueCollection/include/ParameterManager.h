#pragma once

#include <QObject>
#include <QSqlDatabase>

class ParameterManager : public QObject
{
	Q_OBJECT
public:
	static ParameterManager &instance();
	~ParameterManager();
public:
	bool init();
	void Uninit();
	bool uploadParameterFileToDatabase(const QString &parameterName, const QString &parameterFile, const QString &imageDir, const QString &templateFile);
	bool generateTemplateFile(const QString &parameterName);
	bool generateImageFile(const QString &parameterName,const QStringList &images);
	bool printQCOSTable(const QString &parameterName, const QString &no);
	bool printChartTable(const QString &parameterName, const QString &no);
private:
	QSqlDatabase &getDatabase();
	QList<QStringList> getParameterFromExcel(const QString  &parameterFile);
	bool checkParamentExist(const QString &parameterName);
	void variantTovariantList(const QVariant &var, QList<QStringList>& res);
	QString getTemplateFileNameFromSQL(const QString &parameterName);
	QStringList getParameterFromSQL(const QString &parameterName, const QString &no);
private:
	ParameterManager(QObject *parent = Q_NULLPTR);
	ParameterManager(ParameterManager const&);
	ParameterManager& operator=(ParameterManager const&);
};
