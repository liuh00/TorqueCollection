#pragma once

#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <readmessage.h>

class MQueue: public QObject
{
public:
	MQueue(QObject *parent=nullptr);
	~MQueue();

	const int size();
	bool isEmpty() ;
	void enqueue(ReadMessage value);
	ReadMessage dequeue();
	ReadMessage head();
private:
	QMutex m_mutex;
	QList<ReadMessage> m_list;
};


