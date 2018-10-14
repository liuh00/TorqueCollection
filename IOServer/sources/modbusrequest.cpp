#include "modbusrequest.h"

ModbusRequest::ModbusRequest(QObject* parent)
	: QObject(parent)
{
}

ModbusRequest::~ModbusRequest()
{
}

ModbusRequest::ModbusRequest( FunctionCode m_function_code, quint8 m_server_id, ushort m_start_address, ushort m_value_length,QObject* parent): QObject(parent),
                                                                                                                                                m_functionCode(m_function_code),
                                                                                                                                                m_serverId(m_server_id),
                                                                                                                                                m_readAddress(m_start_address),
                                                                                                                                                m_readLength(m_value_length),
																																				m_writeAddress(m_start_address),
																																				m_writeLength(m_value_length)
{
}

ModbusRequest::FunctionCode ModbusRequest::functionCode() const
{
	return m_functionCode;
}

void ModbusRequest::setFunctionCode(const FunctionCode m_function_code)
{
	m_functionCode = m_function_code;
}

quint8 ModbusRequest::serverId() const
{
	return m_serverId;
}

void ModbusRequest::setServerId(const quint8 m_server_id)
{
	m_serverId = m_server_id;
}

ushort ModbusRequest::readAddress() const
{
	return m_readAddress;
}

void ModbusRequest::setReadAddress(const ushort m_read_address)
{
	m_readAddress = m_read_address;
}

ushort ModbusRequest::writeAddress() const
{
	return m_writeAddress;
}

void ModbusRequest::setWriteAddress(const ushort m_write_address)
{
	m_writeAddress = m_write_address;
}

ushort ModbusRequest::readLength() const
{
	return m_readLength;
}

void ModbusRequest::setReadLength(const ushort m_read_length)
{
	m_readLength = m_read_length;
}

ushort ModbusRequest::writeLength() const
{
	return m_writeLength;
}

void ModbusRequest::setWriteLength(const ushort m_write_length)
{
	m_writeLength = m_write_length;
}



quint16 ModbusRequest::value(int index)
{
	return m_values.value(index);
}

void ModbusRequest::setValue(int index, quint16 value)
{
	m_values.insert(index, value);
}

bool ModbusRequest::isValid() const
{
	return m_functionCode != Invalid && m_readAddress != -1 ;
}

QVector<quint8> ModbusRequest::getPDU()
{
	QVector<quint8> m_pud;
	m_pud.clear();
	if (!isValid())
	{
		return m_pud;
	}
	m_pud << m_serverId;
	m_pud << m_functionCode;


	switch (m_functionCode)
	{
	case ModbusRequest::ReadCoils:
	case ModbusRequest::ReadDiscreteInputs:
	case ModbusRequest::ReadHoldingRegisters:
	case ModbusRequest::ReadInputRegisters:
		setDataToVector(m_readAddress, m_pud);
		setDataToVector(m_readLength, m_pud);
		break;
	case ModbusRequest::WriteMultipleCoils:
	case ModbusRequest::WriteMultipleRegisters:
		setDataToVector(m_writeAddress, m_pud);
		setDataToVector(m_writeLength, m_pud);
		break;
	case ModbusRequest::ReadWriteMultipleRegisters:
		setDataToVector(m_readAddress, m_pud);
		setDataToVector(m_readLength, m_pud);
		setDataToVector(m_writeAddress, m_pud);
		setDataToVector(m_writeLength, m_pud);
		break;
	case ModbusRequest::WriteSingleCoil:
	case ModbusRequest::WriteSingleRegister:
		setDataToVector(m_writeAddress, m_pud);
		break;
	case ModbusRequest::UndefinedFunctionCode:
		break;
	default:
		return m_pud;
		break;
	}

	quint8 colis_count = 0;
	quint8 data_temp = 0;
	qint32 mvaluesSize = m_values.size();
	quint8 registers_count = m_writeLength * 2;
	switch (m_functionCode)
	{
	case ModbusRequest::ReadCoils:
	case ModbusRequest::ReadDiscreteInputs:
	case ModbusRequest::ReadHoldingRegisters:
	case ModbusRequest::ReadInputRegisters:
		return m_pud;
		break;
	case ModbusRequest::WriteSingleCoil:
		if (m_values.size() > 0)
		{
			if (m_values.at(0) > 0)
			{
				m_pud << 0xff;
				m_pud << 0x00;
			}
			else
			{
				m_pud << 0xff;
				m_pud << 0x00;
			}
		}
		break;
	case ModbusRequest::WriteSingleRegister:
		if (m_values.size() > 0)
		{
			setDataToVector(m_values.at(0), m_pud);
		}
		break;
	case ModbusRequest::WriteMultipleCoils:
		data_temp = 0;
		colis_count = m_writeLength / 8;
		if ((m_writeLength % 8) > 0)
		{
			++colis_count;
		}
		m_pud << colis_count;
		for (size_t i = 0; i < mvaluesSize; i++)
		{
			quint8 data_bit = i % 8;

			if (data_bit == 0)
			{
				if (i > 7)
				{
					m_pud << data_temp;
				}
				data_temp = 0;
			}
			if (m_values.at(i) > 0)
			{
				data_temp = data_temp | (1 << data_bit);
			}
			if (i == (mvaluesSize - 1))
			{
				m_pud << data_temp;
			}
		}
		break;
	case ModbusRequest::WriteMultipleRegisters:
	case ModbusRequest::ReadWriteMultipleRegisters:
		m_pud << registers_count;
		for (size_t i = 0; i < m_values.size(); i++)
		{
			setDataToVector(m_values.at(i), m_pud);
		}
		break;
	case ModbusRequest::UndefinedFunctionCode:
		break;
	default:
		break;
	}
	return m_pud;
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ModbusRequest::setDataToVector(qint16 data, QVector<quint8>& vector)
{
	uchar hightByte = 0x0;
	uchar lowByte = 0x0;
	lowByte = data & 0x00ff;
	hightByte = data >> 8;
	vector << hightByte;
	vector << lowByte;
}
