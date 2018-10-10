#pragma once

#include <QObject>

class ReadMessage : public QObject
{
	Q_OBJECT
public:
	ReadMessage(QObject* parent = Q_NULLPTR);
	ReadMessage(const void* message, std::size_t size,QObject* parent = Q_NULLPTR);
	~ReadMessage();

	uchar* message=nullptr;
	std::size_t size=0;

	ReadMessage(const ReadMessage& other);
	ReadMessage(ReadMessage&& other);
	ReadMessage& operator=(const ReadMessage& other);
	ReadMessage& operator=(ReadMessage&& other);
};
