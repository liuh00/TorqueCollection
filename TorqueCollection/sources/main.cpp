#include <mappliction.h>
#include <mainwindow.h>
#include <QQuickStyle>
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>
using namespace boost::asio;

void handler(const boost::system::error_code &ec)
{
	qDebug() << "current Thread ID:" << QThread::currentThreadId() << "5 s.";
}

void qmlRegister()
{
	qmlRegisterType<MainWindow>("liu.Items", 1, 0, "MainWindow");
	qmlRegisterType<UserManager>("liu.Items", 1, 0, "UserManager");
}

int main(int argc, char *argv[])
{
	QQuickStyle::setStyle("Material");
	qputenv("QT_QUICK_CONTROLS_MATERIAL_THEME", "Light");
	//QML×¢²á
	qmlRegister();
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	MAppliction app(argc, argv);


	io_service server;
	deadline_timer timerss(server, boost::posix_time::seconds(30));
	timerss.async_wait(handler);
	server.run();

	app.Init();

	int result= app.exec();

	app.Uninit();

	return result;
}

