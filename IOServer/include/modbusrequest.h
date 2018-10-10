#pragma once

#include <QObject>

class ModbusRequest : public QObject
{
	Q_OBJECT
public:
	enum FunctionCode
	{
		Invalid = 0x00,
		ReadCoils = 0x01,
		ReadDiscreteInputs = 0x02,
		ReadHoldingRegisters = 0x03,
		ReadInputRegisters = 0x04,
		WriteSingleCoil = 0x05,
		WriteSingleRegister = 0x06,
		ReadExceptionStatus = 0x07,
		Diagnostics = 0x08,
		GetCommEventCounter = 0x0B,
		GetCommEventLog = 0x0C,
		WriteMultipleCoils = 0x0F,
		WriteMultipleRegisters = 0x10,
		ReportServerId = 0x11,
		ReadFileRecord = 0x14,
		WriteFileRecord = 0x15,
		MaskWriteRegister = 0x16,
		ReadWriteMultipleRegisters = 0x17,
		ReadFifoQueue = 0x18,
		EncapsulatedInterfaceTransport = 0x2B,
		UndefinedFunctionCode = 0x100
	};
	Q_ENUM(FunctionCode)

public:
	ModbusRequest(QObject *parent=Q_NULLPTR);
	~ModbusRequest();

	
private:
	FunctionCode m_functionCode= Invalid;
	ushort m_serverId=1;
	ushort m_startAddress=-1;
	ushort m_valueLength=0;
};
