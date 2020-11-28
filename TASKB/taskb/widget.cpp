#include "widget.h"
#include "ui_widget.h"
#include "gtile.h"
#include "genemy.h"
#include "ghealthpack.h"
#include "world.h"
#include <QDebug>
#include <QCompleter>
#include "textscene.h"
#include "command.h"
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

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_editingFinished()
{
    QString command = ui->lineEdit->text();
    Controller *c = new Controller(protagonist);
    MoveRight *right = new MoveRight(c);
    MoveLeft *left = new MoveLeft(c);
    MoveUp *up = new MoveUp(c);
    MoveDown *down = new MoveDown(c);


    if(command=="right"){
        //p->moveRight();
        right->excute();

    }else if (command=="left") {
        //p->moveLeft();
        left->excute();
        }else if (command=="up") {
        //p->moveUp();
        up->excute();
    }else {
        down->excute();
        //p->moveDown();
    }
}

