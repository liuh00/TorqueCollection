#pragma once

#include <QObject>
#include "include/mydata.h"





class QtTest : public QObject
{
	Q_OBJECT

public:
	QtTest(QObject *parent=Q_NULLPTR);
	~QtTest();
	MyData *date;
	


public slots:
	void addCount();
};
