#include "mappliction.h"
#include <QWidget>
#include <mlogmag.h>
#include <logger.h>
#include <databasemanager.h>
#include <configmanager.h>
#include <ParameterManager.h>


MAppliction::MAppliction(int& argc, char** argv)
	: QApplication(argc, argv)
{
	setWindowIcon(QIcon(":/image/icon"));
	systemTray.setIcon(QIcon(":/image/icon"));
	systemTray.show();
	connect(&systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayActivat(QSystemTrayIcon::ActivationReason)));
}

MAppliction::~MAppliction()
{
	
	systemTray.hide();

}

// ReSharper disable once CppMemberFunctionMayBeStatic
bool MAppliction::Init()
{

	bool result = true;
	//启动日志
	mLogMag::initLogger(applicationDirPath(), applicationName());
	Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	logger->info(QObject::tr("Appliction Init!"));

	ConfigManager &cfManager = ConfigManager::instance();
	cfManager.init();
	
	DatabaseManager &dm = DatabaseManager::instance();
	result = dm.CreateDatabaseConnecttion();


	ParameterManager &parManager = ParameterManager::instance();
	parManager.init();



	return result;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MAppliction::Uninit()
{
	ParameterManager &parManager = ParameterManager::instance();
	parManager.Uninit();
	//关闭日志
	Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	logger->info(QObject::tr("Appliction Uninit!"));
	mLogMag::exitLogger();
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MAppliction::onSystemTrayActivat(QSystemTrayIcon::ActivationReason reason)
{
	if (reason == QSystemTrayIcon::DoubleClick)
	{
		QWidgetList widgetList= QApplication::allWidgets();
		for (int i = 0; i < widgetList.size(); i++)
		{
			QWidget *widget = widgetList.at(i); 
			QString objectName = widget->objectName();
			if (objectName == "mainWindow")
			{
				widget->activateWindow();
				break;
			}
		}
	}
	

}
