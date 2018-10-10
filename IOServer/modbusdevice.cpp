#include "modbusdevice.h"

ModbusDevice::ModbusDevice(QObject* parent)
	: QObject(parent)
{
	qRegisterMetaType<ModbusDevice::FunctionCode>();
	qRegisterMetaType<ModbusDevice::State>();
	qRegisterMetaType<ModbusDevice::Error>();
	qRegisterMetaType<ModbusDevice::ConnectionParameter>();
	qRegisterMetaType<ModbusDevice::BaudRate>();
	qRegisterMetaType<ModbusDevice::DataBits>();
	qRegisterMetaType<ModbusDevice::Parity>();
	qRegisterMetaType<ModbusDevice::StopBits>();
	qRegisterMetaType<ModbusDevice::FlowControl>();
}

ModbusDevice::~ModbusDevice()
{
}

ModbusDevice::State ModbusDevice::state() const
{
	return this->m_state;
}

ModbusDevice::Error ModbusDevice::error() const
{
	return this->m_error;
}

QString ModbusDevice::errorString() const
{
	return this->m_errorString;
}

QVariant ModbusDevice::connectionParameter(ConnectionParameter parameter) const
{
	switch (parameter)
	{
	case ModbusDevice::SerialPortNameParameter:
		return m_comPort;
		break;
	case ModbusDevice::SerialParityParameter:
		return m_parity;
		break;
	case ModbusDevice::SerialBaudRateParameter:
		return m_baudRate;
		break;
	case ModbusDevice::SerialDataBitsParameter:
		return m_dataBits;
		break;
	case ModbusDevice::SerialStopBitsParameter:
		return m_stopBits;
		break;
	case ModbusDevice::NetworkPortParameter:
		return m_networkPort;
		break;
	case ModbusDevice::NetworkAddressParameter:
		return m_networkAddress;
		break;
	default:
		return m_userConnectionParams.value(parameter);
		break;
	}
}

void ModbusDevice::setConnectionParameter(ConnectionParameter parameter, const QVariant& value)
{
	switch (parameter)
	{
	case ModbusDevice::SerialPortNameParameter:
		m_comPort = value.toString();
		break;
	case ModbusDevice::SerialParityParameter:
		m_parity = ModbusDevice::Parity(value.toInt());
		break;
	case ModbusDevice::SerialBaudRateParameter:
		m_baudRate = ModbusDevice::BaudRate(value.toInt());
		break;
	case ModbusDevice::SerialDataBitsParameter:
		m_dataBits = ModbusDevice::DataBits(value.toInt());
		break;
	case ModbusDevice::SerialStopBitsParameter:
		m_stopBits = ModbusDevice::StopBits(value.toInt());
		break;
	case ModbusDevice::NetworkPortParameter:
		m_networkPort = value.toInt();
		break;
	case ModbusDevice::NetworkAddressParameter:
		m_networkAddress = value.toString();
		break;
	default:
		m_userConnectionParams.insert(parameter, value);
		break;
	}
}

void ModbusDevice::setState(ModbusDevice::State newState)
{
	if (newState == this->m_state)
		return;
	this->m_state = newState;
	emit stateChanged(newState);
}

void ModbusDevice::setError(const QString& errorText, ModbusDevice::Error error)
{
	this->m_error = error;
	this->m_errorString = errorText;
	emit errorOccurred(error);
}
