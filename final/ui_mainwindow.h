/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QProgressBar *healthBar;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QProgressBar *energyBar;
    QVBoxLayout *verticalLayout_gameW;
    QLabel *label;
    QLineEdit *lineEditCommand;
    QVBoxLayout *verticalLayout_2;
    QLCDNumber *scoreBoard;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEditChangeMap;
    QPushButton *changeSceneButton;
    QPushButton *autoplayButton;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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


        verticalLayout->addLayout(horizontalLayout_2);

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


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout_gameW = new QVBoxLayout();
        verticalLayout_gameW->setObjectName(QString::fromUtf8("verticalLayout_gameW"));

        verticalLayout->addLayout(verticalLayout_gameW);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        lineEditCommand = new QLineEdit(centralwidget);
        lineEditCommand->setObjectName(QString::fromUtf8("lineEditCommand"));

        verticalLayout->addWidget(lineEditCommand);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scoreBoard = new QLCDNumber(centralwidget);
        scoreBoard->setObjectName(QString::fromUtf8("scoreBoard"));
        scoreBoard->setFrameShape(QFrame::Box);
        scoreBoard->setLineWidth(1);
        scoreBoard->setSegmentStyle(QLCDNumber::Flat);

        verticalLayout_2->addWidget(scoreBoard);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        lineEditChangeMap = new QLineEdit(centralwidget);
        lineEditChangeMap->setObjectName(QString::fromUtf8("lineEditChangeMap"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditChangeMap->sizePolicy().hasHeightForWidth());
        lineEditChangeMap->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(lineEditChangeMap);

        changeSceneButton = new QPushButton(centralwidget);
        changeSceneButton->setObjectName(QString::fromUtf8("changeSceneButton"));

        verticalLayout_2->addWidget(changeSceneButton);

        autoplayButton = new QPushButton(centralwidget);
        autoplayButton->setObjectName(QString::fromUtf8("autoplayButton"));

        verticalLayout_2->addWidget(autoplayButton);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        horizontalLayout_3->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 26));
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
        label_3->setText(QCoreApplication::translate("MainWindow", "Health", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Energy", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        changeSceneButton->setText(QCoreApplication::translate("MainWindow", "ChangeScene", nullptr));
        autoplayButton->setText(QCoreApplication::translate("MainWindow", "Autoplay", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
