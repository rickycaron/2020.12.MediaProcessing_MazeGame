#include "widget.h"
#include "ui_widget.h"
#include "gtile.h"
#include "genemy.h"
#include "ghealthpack.h"
#include "world.h"
#include <QDebug>
#include <QCompleter>
#include "textscene.h"

#include "moveright.h"
#include "moveleft.h"
#include "moveup.h"
#include "movedown.h"
#include "controller.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView(this);
    World *world = new World();
    world->createWorld("://images/worldmap.png",10,10,0.25);

    std::vector<std::unique_ptr<Tile>> tiles = world->getTiles();
    //std::unique_ptr<Protagonist> protagonist = world->getProtagonist();
    protagonist = world->getProtagonist();
    std::vector<std::unique_ptr<Enemy>> enemies = world->getEnemies();
    std::vector<std::unique_ptr<Tile>> healthpacks = world->getHealthPacks();

    TextScene *scene = new TextScene(this, tiles,protagonist, enemies, healthpacks);
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);
    connect(protagonist.get(),&Protagonist::posChanged,scene,&TextScene::redrawProtagonist);

    QStringList commandtList;
    commandtList<<"up"<<"right"<<"down"<<"left"<<"goto"<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(commandtList, this);
    ui->lineEdit->setCompleter(completer);

    Controller *c = new Controller(protagonist);
    clist["right"]=std::make_unique<MoveRight>(c);
    clist["left"]=std::make_unique<MoveLeft>(c);
    clist["up"]=std::make_unique<MoveUp>(c);
    clist["down"]=std::make_unique<MoveDown>(c);
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

