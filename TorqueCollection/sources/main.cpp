#include <mappliction.h>
#include <QQmlApplicationEngine>
#include <mlogmag.h>
#include <logger.h>
#include <QQmlContext>
#include <mainwindow.h>



int main(int argc, char *argv[])
{

	qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
	
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	MAppliction app(argc, argv);
	MainWindow mainWindow;
	mainWindow.setObjectName("mainWindow");
	mainWindow.show();

	
	app.Init();








	int result= app.exec();

	app.Uninit();

	return result;
}

