#include "mappliction.h"
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

	mainWindow.setContextProperty("userManager", &userManager);
	mainWindow.setContextProperty("mydata", &data);
	mainWindow.createUI();
	mainWindow.setObjectName("mainWindow");
	mainWindow.show();

	data.setCount(25);

	test1 = new QtTest();
	test2 = new QtTest();

	thread1 = new QThread();
	thread2 = new QThread();

	connect(&data, &MyData::add, test1, &QtTest::addCount);
	connect(&data, &MyData::add, test2, &QtTest::addCount);

	test1->date = &data;
	test2->date = &data;
	test1->moveToThread(thread1);
	test2->moveToThread(thread2);
	thread1->start();
	thread2->start();
	qDebug()<< "Current Thread ID:" << QThread::currentThreadId();
	test1->addCount();
	test2->addCount();


}

MAppliction::~MAppliction()
{
	thread1->quit();
	thread2->quit();
	thread1->wait();
	thread2->wait();

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
