/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QProgressBar *healthBar;
    QLabel *healthLabel;
    QProgressBar *energyBar;
    QLabel *energyLabel;
    QLineEdit *lineEdit;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(800, 800);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        healthBar = new QProgressBar(Widget);
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
        healthBar->setMaximum(300);
        healthBar->setValue(24);

        formLayout->setWidget(1, QFormLayout::FieldRole, healthBar);

        healthLabel = new QLabel(Widget);
        healthLabel->setObjectName(QString::fromUtf8("healthLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, healthLabel);

        energyBar = new QProgressBar(Widget);
        energyBar->setObjectName(QString::fromUtf8("energyBar"));
        energyBar->setStyleSheet(QString::fromUtf8("QProgressBar{\n"
"border: 1px solid grey;\n"
"border-radius: 5px;\n"
"text-align: center;\n"
"}\n"
"QProgressBar::chunk{\n"
"	background-color: rgb(112, 158, 218);\n"
"}\n"
""));
        energyBar->setMaximum(100);
        energyBar->setValue(24);

        formLayout->setWidget(0, QFormLayout::FieldRole, energyBar);

        energyLabel = new QLabel(Widget);
        energyLabel->setObjectName(QString::fromUtf8("energyLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, energyLabel);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        lineEdit = new QLineEdit(Widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_2->addWidget(lineEdit);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        healthBar->setFormat(QCoreApplication::translate("Widget", "%v", nullptr));
        healthLabel->setText(QCoreApplication::translate("Widget", "Health", nullptr));
        energyBar->setFormat(QCoreApplication::translate("Widget", "%v", nullptr));
        energyLabel->setText(QCoreApplication::translate("Widget", "Energy", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
