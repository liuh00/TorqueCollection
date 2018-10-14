#include <QtCore/QCoreApplication>
#include <ModbusMaster.h>
#include <mlogmag.h>
#include <log4qt/logger.h>
#include <mqueue.h>
#include <modbusrequest.h>
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
/*	ModbusMaster master(&a);
	///ModbuMaster master1(&a);
	master.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkAddressParameter, "127.0.0.1");
	master.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkPortParameter,502);
	master.connectServer();
	
	//master1.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkAddressParameter, "127.0.0.1");
	//master1.setConnectionParameter(ModbusDevice::ConnectionParameter::NetworkPortParameter, 8080);
	
	*/

	ModbusRequest req(ModbusRequest::ReadCoils,1,10,50);
	QVector<quint8> rs = req.getPDU();

	ModbusRequest req1(ModbusRequest::ReadDiscreteInputs, 1, 10, 50);
	QVector<quint8> rs1 = req1.getPDU();


	ModbusRequest req2(ModbusRequest::WriteMultipleCoils, 1, 10, 28);
	for (size_t i = 0; i < 28; i++)
	{
		req2.setValue(i, (i+1)%2);
	}
	QVector<quint8> rs2 = req2.getPDU();


	ModbusRequest req3(ModbusRequest::WriteMultipleRegisters, 1, 10, 28);
	for (size_t i = 0; i < 28; i++)
	{
		req3.setValue(i, 300+i);
	}
	QVector<quint8> rs3 = req3.getPDU();

	int result = a.exec();

	mLogMag::exitLogger();
	
	return result;
}
