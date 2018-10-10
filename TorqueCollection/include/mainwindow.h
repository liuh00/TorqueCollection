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


	QMap<QString, QObject *> *m_contextProperty;


public:
	QMap<QString, QObject*> *contextProperty();
	void setContextProperty(const QString objName, QObject *obj);
	void createUI();
protected:
	void closeEvent(QCloseEvent* event);

};
