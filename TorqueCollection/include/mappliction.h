#pragma once

#include <QApplication>
#include <QSystemTrayIcon>
#include <mainwindow.h>
#include <usermanager.h>
#include "mydata.h"
#include <QThread>
#include <qttest.h>

class MAppliction : public QApplication
{
	Q_OBJECT
	

private:
	int kk;

public:
	MAppliction(int &argc, char **argv);
	~MAppliction();
	bool Init();
	void Uninit();

private:
	QSystemTrayIcon systemTray;
	MainWindow mainWindow;
	UserManager userManager;
	MyData data;
	QtTest *test1;
	QtTest *test2;
	QThread *thread1;
	QThread *thread2;
public slots:
	void onSystemTrayActivat(QSystemTrayIcon::ActivationReason reason);

};
