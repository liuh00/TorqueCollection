#include "qttest.h"
#include  <QDebug>
#include  <QThread>



QtTest::QtTest(QObject *parent)
	: QObject(parent)
{

}

QtTest::~QtTest()
{
}


void QtTest::addCount()
{
	QThread *thread = QThread::currentThread();

	qDebug() << "current Thread ID:" << QThread::currentThreadId();
	date->setCount(date->count()+1);
}
