#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "myqview.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qView  = new MyQView(this);


    ui->verticalLayout1->addWidget(qView);
     model = std::make_shared<Model>(QString("worldmap"),2);
     myController = std::make_shared<Controller>(model,qView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

