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
private:
	QSqlDatabase &getDatabase();
	QList<QStringList> getParameterForExcel(const QString  &parameterFile);
	bool checkParamentExist(const QString &parameterName);
	void variantTovariantList(const QVariant &var, QList<QStringList>& res);
	
private:
	ParameterManager(QObject *parent = Q_NULLPTR);
	ParameterManager(ParameterManager const&);
	ParameterManager& operator=(ParameterManager const&);
};
