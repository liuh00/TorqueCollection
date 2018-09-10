#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QQuickWidget>

class MainWindow : public QWidget
{
	Q_OBJECT


public:
	MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();
public slots:
	 void closeApp();
	 void showMax();
	
	
	
private:
	QGridLayout* gridLayout;
	QQuickWidget* quickWidget;
	void createUI();


protected:
	void closeEvent(QCloseEvent* event);
};
