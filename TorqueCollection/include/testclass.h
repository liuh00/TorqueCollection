#pragma once

#include <QObject>
#include <log4qt/logger.h>

LOG4QT_DECLARE_STATIC_LOGGER(logger, TestClass)
class TestClass : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
	Q_PROPERTY(int age READ getAge WRITE setAge  NOTIFY ageChanged)

public:
	TestClass(QObject *parent=Q_NULLPTR);
	~TestClass();

	 QString getName() const;
	 void setName(const QString& name);
	 int getAge() const;
	 void setAge(const int age);

	Q_INVOKABLE void debug(const QString &message);

private:
	QString name;
	int age;
signals:
	void nameChanged(const QString&);
	void ageChanged(int);
public slots:
	void info();
};
