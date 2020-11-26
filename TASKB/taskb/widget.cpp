#include "widget.h"
#include "ui_widget.h"
#include "gtile.h"
#include "gprotagonist.h"
#include "genemy.h"
#include "ghealthpack.h"
#include "world.h"
#include <QDebug>

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
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buildWorld()
{
    World* w = new World();
    w->createWorld("://images/worldmap.png",10,10,0.25);
    int row = w->getRows();
    int col =  w->getCols();

    for (int i=0;i<row ; i++) {
        for (int j=0;j<col;j++ ) {
            //myText * tile = new myText();
            GTile * tile = new GTile();
            //tile->setPlainText(" ");
            tile->setPos(QPointF(20*i,20*j));
            scene->addItem(tile);
        }
    }


    GProtagonist *p = new GProtagonist();
    p->setPos(QPointF(20*w->getProtagonist()->getXPos(),20*w->getProtagonist()->getYPos()));
    scene->addItem(p);


    std::vector<std::unique_ptr<Enemy>> enemies = w->getEnemies();
    for(unsigned int i=0;i<enemies.size();i++){
        //myText * enemy = new myText();
        GEnemy * enemy = new GEnemy();
        int x = enemies[i]->getXPos();
        int y = enemies[i]->getYPos();
        enemy->setPos(QPointF(20*x,20*y));
        scene->addItem(enemy);
    }


    std::vector<std::unique_ptr<Tile>> healthpacks = w->getHealthPacks();
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




