#include "textscene.h"
#include <QDebug>

TextScene::TextScene(QObject *parent, const std::vector<std::unique_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                     const std::vector<std::unique_ptr<Enemy> > &enemies, const std::vector<std::unique_ptr<Tile> > &healthpacks): QGraphicsScene(parent)
{
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(enemies);
    printHealthpacks(healthpacks);
}

void TextScene::printTiles(const std::vector<std::unique_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        GTile *tile = new GTile(tiles[i]->getXPos(),tiles[i]->getYPos());
        tileQlist.append(tile);
        this->addItem(tile);
    }
}

void TextScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    protagonistView = new GProtagonist(protagonist->getXPos(),protagonist->getYPos());
    this->addItem(protagonistView);
}

void TextScene::printEnemies(const std::vector<std::unique_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        GEnemy * enemy = new GEnemy(enemies[i]->getXPos(),enemies[i]->getYPos());
        enemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void TextScene::printHealthpacks(const std::vector<std::unique_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        GHealthpack * healthpack = new GHealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos());
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}

void TextScene::redrawProtagonist(int xPos, int yPos)
{
    protagonistView->setPos(20*xPos,20*yPos);
}
