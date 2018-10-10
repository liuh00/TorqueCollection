#pragma once

#include <QObject>
#include <QVector>

class ReadMessage : public QObject
{
	Q_OBJECT
public:
	ReadMessage(QObject* parent = Q_NULLPTR);
	ReadMessage(const void* message, std::size_t size,QObject* parent = Q_NULLPTR);
	~ReadMessage();

	QVector<unsigned char> message;
	std::size_t size=0;

	ReadMessage(const ReadMessage& other);
	ReadMessage(ReadMessage&& other);
	ReadMessage& operator=(const ReadMessage& other);
	ReadMessage& operator=(ReadMessage&& other);
};
