#pragma once

#include <QObject>

class ModbusReply : public QObject
{
	Q_OBJECT

public:
	ModbusReply(QObject *parent);
	~ModbusReply();
};
