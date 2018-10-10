#include "ModbusMaster.h"
#include <iostream>

ModbusMaster::ModbusMaster(QObject* parent)
	: ModbusDevice(parent),
	  m_work(m_ioserver),
	  m_socket(m_ioserver),
	  m_timer(m_ioserver)
{
	//…Ë÷√∂¡–¥ª∫≥Â«¯
	m_readBuff.reset(new unsigned char[m_readBufferSize]());
	m_sendBuff.reset(new unsigned char[m_sendBufferSize]());
	boost::thread(boost::bind(&ModbusMaster::startThread, this));
	connect(&testTimer, &QTimer::timeout, this, &ModbusMaster::on_timer);
	connect(this, &ModbusMaster::stateChanged, this, &ModbusMaster::on_connectStatusChanged);
	connect(this, &ModbusMaster::readMessage, this, &ModbusMaster::on_readMessage);
	testTimer.setInterval(2000);
	testTimer.start();
	
	connect(&m_overseeTimer, &QTimer::timeout, this, &ModbusMaster::connectDevice);
	
}

ModbusMaster::~ModbusMaster()
{
	testTimer.stop();
	if (m_socket.is_open())
	{
		m_socket.cancel();
	}
	m_socket.close();
	m_ioserver.stop();
}

void ModbusMaster::connectServer()
{
	m_connect = true;
	connectDevice();
}

void ModbusMaster::on_readMessage()
{
	ReadMessage rm;
	while (!m_readqueue.isEmpty())
	{
		rm = m_readqueue.dequeue();
	}
	std::string st((char *)rm.message, rm.size);
	std::cout << st << std::endl;
	delete rm.message;

}

void ModbusMaster::connectDevice()
{
	if(state()==State::UnconnectedState)
	{
		socketConnect();
	}
}

void ModbusMaster::socketConnect()
{
	setState(State::ConnectingState);
	if (m_socket.is_open())
	{
		m_socket.cancel();
	}
	m_socket.close();
	QString ip = connectionParameter(ConnectionParameter::NetworkAddressParameter).toString();
	int port = connectionParameter(ConnectionParameter::NetworkPortParameter).toInt();
	m_ep = ip::tcp::endpoint(ip::address_v4::from_string(ip.toStdString()), port);
	m_socket.async_connect(m_ep, boost::bind(&ModbusMaster::on_connect, this, _1));
}

void ModbusMaster::socketRead()
{
	if (state() == State::ConnectedState)
	{
		m_socket.async_receive(buffer(m_readBuff.get(), m_readBufferSize), boost::bind(&ModbusMaster::on_read, this, _1, _2));
	}
}

void ModbusMaster::socketWite(QString eventName, std::size_t size)
{
	if (state() == State::ConnectedState)
	{
		ReadMessage sm;
		sm = m_sendqueue.dequeue();
		if(sm.size > 0 && sm.message !=nullptr )
		{
			memcpy(m_sendBuff.get(), sm.message, sm.size);
			delete sm.message;
			m_socket.async_send(buffer(m_sendBuff.get(), sm.size), boost::bind(&ModbusMaster::on_send, this, _1, _2, eventName.toStdString()));
		}
		
		
	}
}

void ModbusMaster::on_connect(const boost::system::error_code& ec)
{
	if (ec == boost::system::errc::success)
	{
		setState(State::ConnectedState);
		setError(QString::fromStdString(ec.message()), Error::NoError);
		logger()->info("connect success");
		socketRead();
	}
	else
	{
		setState(State::UnconnectedState);
		setError(QString::fromStdString(ec.message()), Error::ConnectionError);
		QString message("Connect ID:");
		message.append(QString("%1 ").arg(ec.value()));
		message.append(QString::fromLocal8Bit(ec.message().c_str(), ec.message().size()));
		logger()->error(message);
	}
}

void ModbusMaster::on_read(const boost::system::error_code& ec, std::size_t sz)
{
	if (ec == boost::system::errc::success)
	{
		logger()->info(QString("Received data:%1").arg(sz));
		if(sz > 0)
		{
			m_readqueue.enqueue(ReadMessage(m_readBuff.get(),sz));
			emit readMessage();
		}
		m_socket.async_receive(buffer(m_readBuff.get(), m_readBufferSize), boost::bind(&ModbusMaster::on_read, this, _1, _2));
	}
	else
	{
		setState(State::UnconnectedState);
		setError(QString::fromStdString(ec.message()), Error::ConnectionError);
		QString message("READ ID:");
		message.append(QString("%1 ").arg(ec.value()));
		message.append(QString::fromLocal8Bit(ec.message().c_str(), ec.message().size()));
		logger()->error(message);
	}
}

void ModbusMaster::on_send(const boost::system::error_code& ec, std::size_t sz, std::string eventName)
{
	if (ec == boost::system::errc::success)
	{
		logger()->info(QString("Send data:%1").arg(sz));
	}
	else
	{
		setState(State::UnconnectedState);
		setError(QString::fromStdString(ec.message()), Error::ConnectionError);
		QString message("SEND ID:");
		message.append(QString("%1 ").arg(ec.value()));
		message.append(QString::fromLocal8Bit(ec.message().c_str(), ec.message().size()));
		logger()->error(message);
	}
}

void ModbusMaster::on_timer()
{
	uchar * message = (uchar *)"this is a message.";
	
	size_t sz = strlen((char *)message);

	m_sendqueue.enqueue(ReadMessage(message, sz));
	socketWite("this is test.", sz);
}

void ModbusMaster::on_connectStatusChanged(State state)
{
	if((state==UnconnectedState) && m_connect)
	{
		m_overseeTimer.setInterval(3000);
		if(!m_overseeTimer.isActive())
		{
			m_overseeTimer.start();
		}	
	}
	else
	{
		m_overseeTimer.stop();
	}
}

void ModbusMaster::startThread()
{
	m_ioserver.run();
}
