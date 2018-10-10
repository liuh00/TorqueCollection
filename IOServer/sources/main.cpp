#include <QtCore/QCoreApplication>
#include <ModbusMaster.h>
#include <mlogmag.h>
#include <log4qt/logger.h>
#include <mqueue.h>

void typeRegister()
{
	
	//qRegisterMetaType<ModbusMaster>("ModbusMaster::Error");
}
int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);
	//typeRegister();


	mLogMag::initLogger(a.applicationDirPath(), a.applicationName());
	Log4Qt::Logger *logger = Log4Qt::Logger::rootLogger();
	logger->info(QObject::tr("Appliction Start!"));
	ModbusMaster master(&a);
	///ModbuMaster master1(&a);
	master.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkAddressParameter, "127.0.0.1");
	master.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkPortParameter,502);
	master.connectServer();
	
	//master1.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkAddressParameter, "127.0.0.1");
	//master1.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkPortParameter, 8080);
	


	int result = a.exec();

	mLogMag::exitLogger();
	
	return result;
}
