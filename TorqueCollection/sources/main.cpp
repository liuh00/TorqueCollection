#include <mappliction.h>
#include <QQmlApplicationEngine>
#include <mainwindow.h>
#include <QQuickStyle>
void qmlRegister()
{
	qmlRegisterType<MainWindow>("liu.Items", 1, 0, "MainWindow");
}

int main(int argc, char *argv[])
{

	qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
	QQuickStyle::setStyle("Material");
	//QML×¢²á
	qmlRegister();

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	MAppliction app(argc, argv);
	MainWindow mainWindow;

	mainWindow.setObjectName("mainWindow");
	mainWindow.show();

	
	app.Init();


	int result= app.exec();

	app.Uninit();

	return result;
}

