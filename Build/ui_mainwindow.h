/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QProgressBar *energyBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QProgressBar *healthBar;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *changeSceneButton;
    QPushButton *autoplayButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        energyBar = new QProgressBar(centralwidget);
        energyBar->setObjectName(QString::fromUtf8("energyBar"));
        energyBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"}\n"
"QProgressBar::chunk{\n"
"	background-color: rgb(112, 158, 218);\n"
"}"));
        energyBar->setValue(24);

        horizontalLayout->addWidget(energyBar);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        healthBar = new QProgressBar(centralwidget);
        healthBar->setObjectName(QString::fromUtf8("healthBar"));
        healthBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"}\n"
"QProgressBar::chunk{\n"
"background-color: rgb(141, 161, 98);\n"
"}\n"
""));
        healthBar->setValue(24);

        horizontalLayout_2->addWidget(healthBar);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        changeSceneButton = new QPushButton(centralwidget);
        changeSceneButton->setObjectName(QString::fromUtf8("changeSceneButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(changeSceneButton->sizePolicy().hasHeightForWidth());
        changeSceneButton->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(changeSceneButton);

        autoplayButton = new QPushButton(centralwidget);
        autoplayButton->setObjectName(QString::fromUtf8("autoplayButton"));

        verticalLayout_3->addWidget(autoplayButton);


        horizontalLayout_3->addLayout(verticalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Energy", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Health", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        changeSceneButton->setText(QCoreApplication::translate("MainWindow", "changeScene", nullptr));
        autoplayButton->setText(QCoreApplication::translate("MainWindow", "Autoplay", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
