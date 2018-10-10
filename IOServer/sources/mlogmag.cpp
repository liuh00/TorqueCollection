#include "mlogmag.h"
#include <log4qt/ttcclayout.h>
#include <log4qt/fileappender.h>
#include <log4qt/loggerrepository.h>
#include <QDate>
#include <QCoreApplication>
mLogMag::mLogMag(QObject *parent)
	: QObject(parent)
{
}



mLogMag::~mLogMag()
{
}

 void mLogMag::initLogger(const QString &dirPath, const QString &appName)
{
	Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	Log4Qt::TTCCLayout *layout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601);
	layout->setName("My Layout");

	layout->activateOptions();
	// 创建一个 FileAppender（将日志内容输出到文件中）

	// true 以 Append 方式打开文件，false 以 Truncate 方式打开文件。
	QDate curDate = QDate::currentDate();
	QString strData = curDate.toString("yyyy-MM-dd");
	QString file = dirPath + "/logs/"+ appName+"."+ strData+".log";
	Log4Qt::FileAppender *appender = new Log4Qt::FileAppender(layout, file, true);
	appender->setName("My Appender");
	appender->activateOptions();

	// 在 rootLogger 上添加 fileAppender
	logger->addAppender(appender);


	// 设置Level级别
	QString level = "";
	QStringList pars = QCoreApplication::arguments();

	if (pars.length() > 1)
	{
		level = pars.at(1);
	}
	Log4Qt::Level::Value lev = getLevel(level);
	logger->setLevel(lev);
	logger->log(lev, QString("--------------->").append(level));

	// 允许处理 Qt 消息
	//Log4Qt::LogManager::setHandleQtMessages(true);
}

Log4Qt::Level::Value mLogMag::getLevel(const QString level)
{	
	if(level.compare("OFF_INT")==0)
	{
		return Log4Qt::Level::OFF_INT;
	}
	if (level.compare("FATAL_INT") == 0)
	{
		return Log4Qt::Level::FATAL_INT;
	}
	if (level.compare("ERROR_INT") == 0)
	{
		return Log4Qt::Level::ERROR_INT;
	}
	if (level.compare("WARN_INT") == 0)
	{
		return Log4Qt::Level::WARN_INT;
	}
	if (level.compare("INFO_INT") == 0)
	{
		return Log4Qt::Level::INFO_INT;
	}
	if (level.compare("DEBUG_INT") == 0)
	{
		return Log4Qt::Level::DEBUG_INT;
	}
	if (level.compare("TRACE_INT") == 0)
	{
		return Log4Qt::Level::TRACE_INT;
	}
	if (level.compare("ALL_INT") == 0)
	{
		return Log4Qt::Level::ALL_INT;
	}
	if (level.compare("NULL_INT") == 0)
	{
		return Log4Qt::Level::NULL_INT;
	}
	return Log4Qt::Level::WARN_INT;
}

void mLogMag::exitLogger()
 {
	 Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	 Log4Qt::AppenderSharedPtr ptr = logger->appender("My Appender");
	 ptr->close();
	 logger->removeAllAppenders();
	 logger->loggerRepository()->shutdown();
 }
