#pragma once

#include <QObject>
#include <log4qt/logger.h>
class mLogMag : public QObject
{
	Q_OBJECT

public:
	mLogMag(QObject *parent);
	~mLogMag();
	static void initLogger(const QString &dirPath, const QString &appName);
	static void exitLogger();
private:
	static  Log4Qt::Level::Value getLevel(const QString level);
};
