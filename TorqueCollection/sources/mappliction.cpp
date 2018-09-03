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
	setWindowIcon(QIcon(":/image/Services_48px.png"));
	systemTray.setIcon(QIcon(":/image/Services_48px.png"));
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
	//������־
	mLogMag::initLogger(applicationDirPath(), applicationName());
	Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	logger->info(QObject::tr("Appliction Init!"));

	ConfigManager &cfManager = ConfigManager::instance();
	cfManager.init();
	
	DatabaseManager &dm = DatabaseManager::instance();
	result = dm.CreateDatabaseConnecttion();


	ParameterManager &parManager = ParameterManager::instance();
	parManager.init();
	parManager.uploadParameterFileToDatabase("K256", "D:/K256/K256.xls", QString::fromLocal8Bit("D:/K256/QCOSͼƬ"), "D:/K256/QCOSh.xlt");
	

	parManager.generateTemplateFile("K256");
	QStringList imeges;
	imeges << "QWN600b.bmp" << "QWN608.bmp" << "QWN610.bmp" << "QWN622.bmp" << "QWN722.bmp";

	parManager.generateImageFile("K256", imeges);
	return true;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MAppliction::Uninit()
{
	ParameterManager &parManager = ParameterManager::instance();
	parManager.Uninit();
	//�ر���־
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
