#pragma once

#include <QObject>


class mLogMag : public QObject
{
	Q_OBJECT

public:
	mLogMag(QObject *parent);
	static void initLogger(const QString &dirPath, const QString &appName);
	static void exitLogger();
	~mLogMag();
};
