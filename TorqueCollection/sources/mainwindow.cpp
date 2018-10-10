#include "mainwindow.h"
#include <QQmlContext>
#include <QApplication>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	m_contextProperty = new QMap<QString, QObject *>();
}

MainWindow::~MainWindow()
{

}

// ReSharper disable once CppMemberFunctionMayBeStatic
void MainWindow::closeApp()
{
	QApplication::quit();
}

void MainWindow::showMax()
{
	this->showMaximized();
}


void MainWindow::createUI()
{
	this->setWindowModality(Qt::NonModal);
	this->setContextMenuPolicy(Qt::NoContextMenu);
	this->resize(1000, 600);

	gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(0);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName(QStringLiteral("gridLayout"));
	gridLayout->setContentsMargins(0, 0, 0, 0);

	quickWidget = new QQuickWidget(this);
	quickWidget->setObjectName(QStringLiteral("quickWidget"));
	quickWidget->setFocusPolicy(Qt::StrongFocus);
	quickWidget->setContextMenuPolicy(Qt::NoContextMenu);
	quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
	quickWidget->setMinimumSize(1000, 600);

	this->setWindowFlags(Qt::FramelessWindowHint);
	this->showMaximized();
	gridLayout->addWidget(quickWidget, 0, 0, 1, 1);

	setContextProperty("mainWindow", this);

	QMapIterator<QString, QObject *> i(*m_contextProperty);
	
	while (i.hasNext())
	{
		i.next();
		quickWidget->rootContext()->setContextProperty(i.key(), i.value());
	}

	quickWidget->setSource(QUrl(QString("qrc:/TorqueCollection.qml")));

	
}

QMap<QString, QObject*> *MainWindow::contextProperty() 
{
	return m_contextProperty;
}

void MainWindow::setContextProperty(const QString objName, QObject* obj)
{
	m_contextProperty->insert(objName, obj);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	event->ignore();
}
