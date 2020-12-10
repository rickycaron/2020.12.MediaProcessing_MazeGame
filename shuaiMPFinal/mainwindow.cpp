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


     ui->verticalLayout->addWidget(qView);
     model = std::make_shared<Model>(QString("worldmap"),2,this);
     myController = std::make_shared<Controller>(model,qView,this);
     ui->energyBar->setValue(100);
     ui->healthBar->setValue(100);
     connect(model->getProtagonist().get(),&Protagonist::energyChanged,ui->energyBar,&QProgressBar::setValue);
     connect(model->getProtagonist().get(),&Protagonist::healthChanged,ui->healthBar,&QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

