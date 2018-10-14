#pragma once

#include <QObject>
#include <QVector>
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
		//ReadExceptionStatus = 0x07,
		//Diagnostics = 0x08,
		//GetCommEventCounter = 0x0B,
		//GetCommEventLog = 0x0C,
		WriteMultipleCoils = 0x0F,
		WriteMultipleRegisters = 0x10,
		//ReportServerId = 0x11,
		//ReadFileRecord = 0x14,
		//WriteFileRecord = 0x15,
		//MaskWriteRegister = 0x16,
		ReadWriteMultipleRegisters = 0x17,
		//ReadFifoQueue = 0x18,
		//EncapsulatedInterfaceTransport = 0x2B,
		UndefinedFunctionCode = 0x100
	};
	Q_ENUM(FunctionCode)

public:
	ModbusRequest(QObject *parent=Q_NULLPTR);
	~ModbusRequest();


	ModbusRequest( FunctionCode m_function_code, quint8 m_server_id, ushort m_start_address, ushort m_value_length,QObject* parent=Q_NULLPTR);

	FunctionCode functionCode() const;
	void setFunctionCode(const FunctionCode m_function_code);
	quint8 serverId() const;
	void setServerId(const quint8  m_server_id);

	ushort readAddress() const;
	void setReadAddress(const ushort m_read_address);
	ushort writeAddress() const;
	void setWriteAddress(const ushort m_write_address);
	ushort readLength() const;
	void setReadLength(const ushort m_read_length);
	ushort writeLength() const;
	void setWriteLength(const ushort m_write_length);
	quint16 value(int index);
	void setValue(int index, quint16 value);
	bool isValid() const;
	QVector<quint8> getPDU();


	ModbusRequest(const ModbusRequest& other)
		: m_functionCode(other.m_functionCode),
		  m_serverId(other.m_serverId),
		  m_readAddress(other.m_readAddress),
		  m_writeAddress(other.m_writeAddress),
		  m_readLength(other.m_readLength),
		  m_writeLength(other.m_writeLength),
		  m_values(other.m_values)
	{
	}

	ModbusRequest(ModbusRequest&& other)
		: m_functionCode(other.m_functionCode),
		  m_serverId(other.m_serverId),
		  m_readAddress(other.m_readAddress),
		  m_writeAddress(other.m_writeAddress),
		  m_readLength(other.m_readLength),
		  m_writeLength(other.m_writeLength),
		  m_values(std::move(other.m_values))
	{
	}

	ModbusRequest& operator=(const ModbusRequest& other)
	{
		if (this == &other)
			return *this;
		m_functionCode = other.m_functionCode;
		m_serverId = other.m_serverId;
		m_readAddress = other.m_readAddress;
		m_writeAddress = other.m_writeAddress;
		m_readLength = other.m_readLength;
		m_writeLength = other.m_writeLength;
		m_values = other.m_values;
		return *this;
	}

	ModbusRequest& operator=(ModbusRequest&& other)
	{
		if (this == &other)
			return *this;
		m_functionCode = other.m_functionCode;
		m_serverId = other.m_serverId;
		m_readAddress = other.m_readAddress;
		m_writeAddress = other.m_writeAddress;
		m_readLength = other.m_readLength;
		m_writeLength = other.m_writeLength;
		m_values = std::move(other.m_values);
		return *this;
	}

private: 
	void setDataToVector(qint16 data, QVector<quint8> &vector);
private:
	FunctionCode m_functionCode= Invalid;
	quint8 m_serverId=1;

	ushort m_readAddress = -1;
	ushort m_writeAddress = -1;
	ushort m_readLength = 0;
	ushort m_writeLength = 0;

	QVector<quint16> m_values;
	
};
