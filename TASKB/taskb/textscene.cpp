#include "textscene.h"
#include <QDebug>

TextScene::TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                     const std::vector<std::shared_ptr<Enemy> > &enemies, const std::vector<std::shared_ptr<Tile> > &healthpacks): QGraphicsScene(parent)
{
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(enemies);
    printHealthpacks(healthpacks);
    parent->connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);
    for (unsigned int i=0; i<enemies.size(); i++) {
        parent->connect(enemies[i].get(),&Enemy::dead,enemyQlist[i],&TEnemy::indicateDead);
    }
}

void TextScene::printTiles(const std::vector<std::shared_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        TTile *tile = new TTile(tiles[i]->getXPos(),tiles[i]->getYPos());
        tileQlist.append(tile);
        this->addItem(tile);
    }
}

void TextScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    protagonistView = new TProtagonist(protagonist->getXPos(),protagonist->getYPos());
    this->addItem(protagonistView);
}

void TextScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        TEnemy * enemy = new TEnemy(enemies[i]->getXPos(),enemies[i]->getYPos());
        enemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void TextScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        THealthpack * healthpack = new THealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos());
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}

int TextScene::detectEnemy()
{
    int index = -1;
    for (int i=0; i<enemyQlist.size(); i++) {
        if(protagonistView->collidesWithItem(enemyQlist[i],Qt::IntersectsItemShape)){
            index = i;
            break;
        }
    }
    return index;
}

void TextScene::redrawProtagonist(int xPos, int yPos)
{
    protagonistView->setPos(20*xPos,20*yPos);
}
