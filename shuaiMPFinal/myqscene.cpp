#include "myqscene.h"
#include<QtDebug>

MyQScene::MyQScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                   const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale)
    :QGraphicsScene(parent)
{
    this->scale = scale;
    printTiles(tiles);
    printEnemies(enemies);
    printProtagonist(protagonist);
    printHealthpacks(healthpacks);
//    parent->connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);
//    for (unsigned int i=0; i<enemies.size(); i++) {
//        parent->connect(enemies[i].get(),&Enemy::dead,enemyQlist[i],&TEnemy::indicateDead);
//    }
}

void MyQScene::printTiles(const std::vector<std::shared_ptr<Tile> > &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        QTile *tile = new QTile(tiles[i]->getXPos(),tiles[i]->getYPos(),tiles[i]->getValue(),scale);
        tileQlist.append(tile);
        this->addItem(tile);
    }
}

void MyQScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{

    protagonistView = new QProtagonist(protagonist->getXPos(),protagonist->getYPos(),scale);

    this->addItem(protagonistView);
}

void MyQScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        QEnemy * enemy = new QEnemy(enemies[i]->getXPos(),enemies[i]->getYPos(),scale);
        enemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void MyQScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        QHealthPack * healthpack = new QHealthPack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos(),scale);
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
