#include "mqueue.h"

MQueue::MQueue(QObject* parent)
{
	m_list.clear();
}

MQueue::~MQueue()
{
	while(m_list.isEmpty())
	{
		delete m_list.takeFirst().message;
	}
}

const int MQueue::size()
{
	QMutexLocker loker(&m_mutex);
	return m_list.size();
}

bool MQueue::isEmpty()
{
	QMutexLocker loker(&m_mutex);
	return m_list.isEmpty();
}

void MQueue::enqueue(ReadMessage value)
{
	QMutexLocker loker(&m_mutex);
	m_list.append(value);
}

ReadMessage MQueue::dequeue()
{
	QMutexLocker loker(&m_mutex);
	if (!m_list.isEmpty())
	{
		return m_list.takeFirst();
	}
	else
	{
		return ReadMessage();
	}
		
}

ReadMessage MQueue::head()
{
	QMutexLocker loker(&m_mutex);
	return m_list.first();
}
