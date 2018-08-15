/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include "QtQuickWidgets/QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QGridLayout *gridLayout;
    QQuickWidget *quickWidget;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::NonModal);
        MainWindow->resize(588, 469);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        gridLayout = new QGridLayout(MainWindow);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        quickWidget = new QQuickWidget(MainWindow);
        quickWidget->setObjectName(QStringLiteral("quickWidget"));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget->setSource(QUrl(QStringLiteral("qrc:/TorqueCollection.qml")));

        gridLayout->addWidget(quickWidget, 0, 0, 1, 1);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
