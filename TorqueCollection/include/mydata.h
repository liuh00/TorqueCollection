#pragma once

#include <QObject>

class MyData : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)
public:
	MyData(QObject *parent=Q_NULLPTR);
	~MyData();
private:
	int m_count;
public:
	int count() const;
	void setCount(const int m_count);


signals:
	void countChanged();
	void add();
};
