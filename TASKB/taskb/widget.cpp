#include "widget.h"
#include "ui_widget.h"
#include "gtile.h"
#include "genemy.h"
#include "ghealthpack.h"
#include "world.h"
#include <QDebug>
#include <QCompleter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(this);
    view->setScene(scene);
    buildWorld();
    ui->verticalLayout->addWidget(view);
    QStringList commandtList;
    commandtList<<"up"<<"right"<<"down"<<"left"<<"goto"<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(commandtList, this);
    ui->lineEdit->setCompleter(completer);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buildWorld()
{
    World *world = new World();
    world->createWorld("://images/worldmap.png",10,10,0.25);
    int row = world->getRows();
    int col =  world->getCols();

    for (int i=0;i<row ; i++) {
        for (int j=0;j<col;j++ ) {
            //myText * tile = new myText();
            GTile * tile = new GTile();
            //tile->setPlainText(" ");
            tile->setPos(QPointF(20*i,20*j));
            scene->addItem(tile);
        }
    }


    p = new GProtagonist();
    p->setPos(QPointF(20*world->getProtagonist()->getXPos(),20*world->getProtagonist()->getYPos()));
    scene->addItem(p);

    std::vector<std::unique_ptr<Enemy>> enemies = world->getEnemies();
    for(unsigned int i=0;i<enemies.size();i++){
        GEnemy * enemy = new GEnemy();
        int x = enemies[i]->getXPos();
        int y = enemies[i]->getYPos();
        enemy->setPos(QPointF(20*x,20*y));
        scene->addItem(enemy);
        qDebug()<<enemy->pos().x()<<" "<<enemy->pos().y();
    }


    std::vector<std::unique_ptr<Tile>> healthpacks = world->getHealthPacks();
    for(unsigned int i=0;i<healthpacks.size();i++){
        //myText * healthpack = new myText();
        //healthpack->setPlainText("H");
        GHealthpack * healthpack = new GHealthpack();
        int x = healthpacks[i]->getXPos();
        int y = healthpacks[i]->getYPos();
        healthpack->setPos(QPointF(20*x,20*y));
        scene->addItem(healthpack);
    }

}

void Widget::on_lineEdit_editingFinished()
{
    QString command = ui->lineEdit->text();
    qDebug()<<"command: "<<command;
    if(command=="right"){
        p->moveRight();
    }else if (command=="left") {
        p->moveLeft();
        }else if (command=="up") {
        p->moveUp();
    }else {
        p->moveDown();
    }
}
