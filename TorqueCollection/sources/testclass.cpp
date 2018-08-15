#include "testclass.h"

TestClass::TestClass(QObject *parent)
	: QObject(parent)
{
	connect(this, SIGNAL(ageChanged(int)), this, SLOT(info()));
}

TestClass::~TestClass()
{
}

QString TestClass::getName() const
{
	return name;
}

void TestClass::setName(const QString& name)
{
	this->name = name;
	emit nameChanged(name);
}

int TestClass::getAge() const
{
	return age;
}

void TestClass::setAge(const int age)
{
	this->age = age;
	emit ageChanged(age);
}


// ReSharper disable once CppMemberFunctionMayBeStatic
void TestClass::debug(const QString& message)
{
	logger()->info(message);
}

void TestClass::info()
{
	logger()->info(QString::fromLocal8Bit("≤€≤‚ ‘."));
}
