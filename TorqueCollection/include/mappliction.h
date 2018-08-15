#pragma once

#include <QApplication>
#include <QSystemTrayIcon>

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
	
public slots:
	void onSystemTrayActivat(QSystemTrayIcon::ActivationReason reason);
	
};
