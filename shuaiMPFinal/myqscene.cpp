#include "myqscene.h"
#include<QtDebug>

MyQScene::MyQScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                   const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks)
    :QGraphicsScene(parent)
{

    printTiles(tiles);
    qDebug()<< "successfully 44444444444";

    printEnemies(enemies);
    qDebug()<< "successfully 5555555555";

//    printProtagonist(protagonist);

    qDebug()<< "successfully 666666";

    printHealthpacks(healthpacks);
//    parent->connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);
//    for (unsigned int i=0; i<enemies.size(); i++) {
//        parent->connect(enemies[i].get(),&Enemy::dead,enemyQlist[i],&TEnemy::indicateDead);
//    }
}

void MyQScene::printTiles(const std::vector<std::shared_ptr<Tile> > &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        QTile *tile = new QTile(tiles[i]->getXPos(),tiles[i]->getYPos());
        tileQlist.append(tile);
        this->addItem(tile);
    }
}

void MyQScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    qDebug()<< protagonist->getEnergy();
    qDebug()<< "successfully 888ss8888";
    qDebug()<< "successfully "<<protagonist->getXPos()<<protagonist->getYPos();

    protagonistView = new QProtagonist(protagonist->getXPos(),protagonist->getYPos());
    qDebug()<< "successfully 777777777777777";

    this->addItem(protagonistView);
}

void MyQScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        QEnemy * enemy = new QEnemy(enemies[i]->getXPos(),enemies[i]->getYPos());
        enemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void MyQScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        QHealthPack * healthpack = new QHealthPack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos());
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}

int MyQScene::detectEnemy()
{

}

int MyQScene::detectHealthpack()
{

}

void MyQScene::redrawHealthpack(int index)
{

}

void MyQScene::redrawProtagonist(int xPos, int yPos)
{

}
