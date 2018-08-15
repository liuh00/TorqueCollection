#include "mlogmag.h"
#include <log4qt/logger.h>
#include <log4qt/ttcclayout.h>
#include <log4qt/fileappender.h>
#include <log4qt/loggerrepository.h>
#include <QDate>
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
	// ����һ�� FileAppender������־����������ļ��У�

	// true �� Append ��ʽ���ļ���false �� Truncate ��ʽ���ļ���
	QDate curDate = QDate::currentDate();
	QString strData = curDate.toString("yyyy-MM-dd");
	QString file = dirPath + "/logs/"+ appName+"."+ strData+".log";
	Log4Qt::FileAppender *appender = new Log4Qt::FileAppender(layout, file, true);
	appender->setName("My Appender");
	appender->activateOptions();

	// �� rootLogger ����� fileAppender
	logger->addAppender(appender);

	// ���ü���Ϊ DEBUG
	logger->setLevel(Log4Qt::Level::INFO_INT);

	// ������ Qt ��Ϣ
	//Log4Qt::LogManager::setHandleQtMessages(true);
}

 void mLogMag::exitLogger()
 {
	 Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	 Log4Qt::AppenderSharedPtr ptr = logger->appender("My Appender");
	 ptr->close();
	 logger->removeAllAppenders();
	 logger->loggerRepository()->shutdown();
 }
