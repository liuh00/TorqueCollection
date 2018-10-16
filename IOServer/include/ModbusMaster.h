#pragma once

#include <QObject>
#include <QTimer>
#include <QThread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/shared_array.hpp>
#include <log4qt/logger.h>
#include <modbusdevice.h>
#include <mqueue.h>
#include <modbusrequest.h>
#include <modbusreply.h>

using namespace boost::asio;


class ModbusMaster : public ModbusDevice
{
	Q_OBJECT
	LOG4QT_DECLARE_QCLASS_LOGGER
public:
	ModbusMaster(QObject* parent = nullptr);
	~ModbusMaster();
	void connectServer();
	void disconnectServer();
	
	ModbusReply * sendRequest(ModbusRequest request);

private:
	io_service m_ioserver; //io管理器
	io_service::work m_work; //保持ioserver运行任务
	ip::tcp::endpoint m_ep; //目标服务器
	ip::tcp::socket m_socket;
	deadline_timer m_timer;

	bool m_connect = false;
	int m_responseTime = 200; //响应超时ms
	int m_numberOfRetries = 3; //重试次数

	boost::shared_array<unsigned char> m_readBuff;
	boost::shared_array<unsigned char> m_sendBuff;
	std::size_t m_readBufferSize = 1024 * 1024;
	std::size_t m_sendBufferSize = 1024 * 1024;

	QTimer testTimer;

	QTimer m_overseeTimer;

	MQueue m_readqueue;
	MQueue m_sendqueue;

	ushort m_transactionIdentifier=0;
	QMutex m_tidMutex;



private:
	void socketConnect();
	void socketRead();
	void socketWite(QString eventName, std::size_t size);
	void on_connect(const boost::system::error_code& ec);
	void on_read(const boost::system::error_code& ec, std::size_t sz);
	void on_send(const boost::system::error_code& ec, std::size_t sz, std::string eventName);
	void startThread();
	void addTransactionIdentifier();
	ushort transactionIdentifier();

signals:
	void readMessage();
protected slots:
	void on_timer();
	void on_connectStatusChanged(State state);
	void connectDevice();
	void disconnectDevice();
	void on_readMessage();
};
