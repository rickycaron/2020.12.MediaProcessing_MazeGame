#include "widget.h"
#include "ui_widget.h"
#include "ttile.h"
#include "tenemy.h"
#include "thealthpack.h"
#include "world.h"
#include <QDebug>
#include <QCompleter>
#include "textscene.h"
#include "controller.h"
#include "moveright.h"
#include "moveleft.h"
#include "moveup.h"
#include "movedown.h"
#include "attack.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView(this);
    Controller *controller = new Controller();
    controller->createScene(this);
    controller->addSceneToView(*view);
    ui->verticalLayout->addWidget(view);

    //auto completion
    QStringList commandtList;
    commandtList<<"right"<<"left"<<"up"<<"down"<<"goto"<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(commandtList, this);
    ui->lineEdit->setCompleter(completer);

    clist["right"]=std::make_unique<MoveRight>(controller);
    clist["left"]=std::make_unique<MoveLeft>(controller);
    clist["up"]=std::make_unique<MoveUp>(controller);
    clist["down"]=std::make_unique<MoveDown>(controller);
    clist["attack"]=std::make_unique<Attack>(controller);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_editingFinished()
{
    QString command = ui->lineEdit->text();
    if(clist.count(command)==1){
        clist[command]->excute();
    }else{
        qDebug()<<"Can't find command";
    }
}

