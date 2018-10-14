#include "readmessage.h"

ReadMessage::ReadMessage(QObject* parent)
	: QObject(parent)
{
}

ReadMessage::ReadMessage(const void* message, std::size_t size, QObject* parent) : QObject(parent)
{
	this->message.clear();
	this->size = size;
	char* m = (char *) message;
	for (size_t i = 0; i < size; i++)
	{
		this->message.append(*(m + i));
	}
}

ReadMessage::~ReadMessage()
{
}

ReadMessage::ReadMessage(const ReadMessage& other): message(other.message),
                                                    size(other.size)
{
}

ReadMessage::ReadMessage(ReadMessage&& other): message(other.message),
                                               size(other.size)
{
}

ReadMessage& ReadMessage::operator=(const ReadMessage& other)
{
	if (this == &other)
		return *this;
	message = other.message;
	size = other.size;
	return *this;
}

ReadMessage& ReadMessage::operator=(ReadMessage&& other)
{
	if (this == &other)
		return *this;
	message = other.message;
	size = other.size;
	return *this;
}
