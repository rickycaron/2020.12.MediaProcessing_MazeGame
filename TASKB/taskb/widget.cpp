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
#include "take.h"
#include <memory>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView(this);
    //std::shared_ptr<QGraphicsView> view = std::make_unique<QGraphicsView>(this);
    //Controller *controller = new Controller();
    std::shared_ptr<Controller> controller = std::make_shared<Controller>();
    controller->createScene(this);
    controller->addSceneToView(*view);
    ui->verticalLayout->addWidget(view);

    //auto completion
    QStringList editList;
    editList<<"right"<<"left"<<"up"<<"down"<<"goto"<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(editList, this);
    ui->lineEdit->setCompleter(completer);

    commandList["right"]=std::make_unique<MoveRight>(controller);
    commandList["left"]=std::make_unique<MoveLeft>(controller);
    commandList["up"]=std::make_unique<MoveUp>(controller);
    commandList["down"]=std::make_unique<MoveDown>(controller);
    commandList["attack"]=std::make_unique<Attack>(controller);
    commandList["take"]=std::make_unique<Take>(controller);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_editingFinished()
{
    QString text = ui->lineEdit->text();
    if(commandList.count(text)==1){
        commandList[text]->excute();
    }else{
        qDebug()<<"Can't find command";
    }
}

