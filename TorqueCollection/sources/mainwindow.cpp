#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::ForeignWindow | Qt::WindowTitleHint);
	this->showMaximized();
}

MainWindow::~MainWindow()
{
}
