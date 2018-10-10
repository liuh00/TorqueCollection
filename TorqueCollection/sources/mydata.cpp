#include "mydata.h"

MyData::MyData(QObject *parent)
	: QObject(parent)
{
}

MyData::~MyData()
{
}

int MyData::count() const
{
	return m_count;
}

void MyData::setCount(const int m_count)
{
	this->m_count = m_count;
	emit countChanged();
}
