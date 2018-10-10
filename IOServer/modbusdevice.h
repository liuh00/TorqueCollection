#pragma once

#include <QObject>
#include <QHash>
#include <QVariant>
#include <QQueue>
class ModbusDevice : public QObject
{
	Q_OBJECT
public:
	//Device ∂®“Â
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

	enum State
	{
		UnconnectedState,
		ConnectingState,
		ConnectedState,
		ClosingState
	};

	Q_ENUM(State)

	enum Error
	{
		NoError,
		ReadError,
		WriteError,
		ConnectionError,
		ConfigurationError,
		TimeoutError,
		ProtocolError,
		ReplyAbortedError,
		UnknownError
	};

	Q_ENUM(Error)

	enum ConnectionParameter
	{
		SerialPortNameParameter,
		SerialParityParameter,
		SerialBaudRateParameter,
		SerialDataBitsParameter,
		SerialStopBitsParameter,

		NetworkPortParameter,
		NetworkAddressParameter,

		// Reserved
		UserParameter = 0x100
	};

	Q_ENUM(ConnectionParameter)

	enum BaudRate
	{
		Baud1200 = 1200,
		Baud2400 = 2400,
		Baud4800 = 4800,
		Baud9600 = 9600,
		Baud19200 = 19200,
		Baud38400 = 38400,
		Baud57600 = 57600,
		Baud115200 = 115200,
		UnknownBaud = -1
	};

	Q_ENUM(BaudRate)

	enum DataBits
	{
		Data5 = 5,
		Data6 = 6,
		Data7 = 7,
		Data8 = 8,
		UnknownDataBits = -1
	};

	Q_ENUM(DataBits)

	enum Parity
	{
		NoParity = 0,
		EvenParity = 2,
		OddParity = 3,
		SpaceParity = 4,
		MarkParity = 5,
		UnknownParity = -1
	};

	Q_ENUM(Parity)

	enum StopBits
	{
		OneStop = 1,
		OneAndHalfStop = 3,
		TwoStop = 2,
		UnknownStopBits = -1
	};

	Q_ENUM(StopBits)

	enum FlowControl
	{
		NoFlowControl,
		HardwareControl,
		SoftwareControl,
		UnknownFlowControl = -1
	};

	Q_ENUM(FlowControl)

public:
	ModbusDevice(QObject* parent);
	~ModbusDevice();

	State state() const;
	Error error() const;
	QString errorString() const;

	QVariant connectionParameter(ConnectionParameter parameter) const;
	void setConnectionParameter(ConnectionParameter parameter, const QVariant &value);

protected:
	void setState(ModbusDevice::State newState);
	void setError(const QString& errorText, ModbusDevice::Error error);
private:
	State m_state = ModbusDevice::UnconnectedState;
	Error m_error = ModbusDevice::NoError;
	QString m_errorString;

	QString m_comPort;
	DataBits m_dataBits = ModbusDevice::Data8;
	Parity m_parity = ModbusDevice::EvenParity;
	StopBits m_stopBits = ModbusDevice::OneStop;
	BaudRate m_baudRate = ModbusDevice::Baud19200;

	int m_networkPort = 502;
	QString m_networkAddress = QStringLiteral("127.0.0.1");

	QHash<int, QVariant> m_userConnectionParams;



	Q_SIGNALS:
	void errorOccurred(ModbusDevice::Error error);
	void stateChanged(ModbusDevice::State state);

};

Q_DECLARE_TYPEINFO(ModbusDevice::FunctionCode, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::State, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::Error, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::ConnectionParameter, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::BaudRate, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::DataBits, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::Parity, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::StopBits, Q_PRIMITIVE_TYPE);

Q_DECLARE_TYPEINFO(ModbusDevice::FlowControl, Q_PRIMITIVE_TYPE);
