#include "controller.h"
#include <QDebug>

Controller::Controller()
{
    //world = new World();
    world = std::make_unique<World>();
    world->createWorld("://images/worldmap.png",10,10,0.25);

    protagonist = world->getProtagonist();

    row=world->getRows();
    col=world->getCols();

    std::vector<std::unique_ptr<Tile>> tempTiles = world->getTiles();
    for(unsigned int i=0; i<tempTiles.size(); i++){
        tiles.emplace_back(std::move(tempTiles[i]));
    }

    std::vector<std::unique_ptr<Enemy>> tempEnemies = world->getEnemies();
    for(unsigned int i=0; i<tempEnemies.size(); i++){
        enemies.emplace_back(std::move(tempEnemies[i]));
    }

        std::vector<std::unique_ptr<Tile>> tempHealthpacks = world->getHealthPacks();
    for(unsigned int i=0; i<tempHealthpacks.size(); i++){
        healthpacks.emplace_back(std::move(tempHealthpacks[i]));
    }
}

void Controller::createScene(QWidget *parent)
{
    scene = new TextScene(parent, tiles, protagonist, enemies, healthpacks);
    //parent->connect()
}

void Controller::addSceneToView(QGraphicsView &view)
{
    view.setScene(scene);
}

void Controller::moveRight()
{
    protagonist->setXPos(protagonist->getXPos()+1);
    qDebug()<<"move right";
    consumeEnergy();
    detectEnemy();
}

void Controller::moveLeft()
{
    protagonist->setXPos(protagonist->getXPos()-1);
    qDebug()<<"move left";
    consumeEnergy();
    detectEnemy();
}

void Controller::moveUp()
{
    protagonist->setYPos(protagonist->getYPos()-1);
    qDebug()<<"move up";
    consumeEnergy();
    detectEnemy();
}

void Controller::moveDown()
{
    protagonist->setYPos(protagonist->getYPos()+1);
    qDebug()<<"move down";
    consumeEnergy();
    detectEnemy();
}

void Controller::consumeEnergy()
{
    int index = protagonist->getYPos()*world->getCols()+protagonist->getXPos();
    protagonist->setEnergy(protagonist->getEnergy()-tiles[index]->getValue());
    qDebug()<<"Energy: "<<protagonist->getEnergy()<<",Health: "<<protagonist->getHealth();
}

void Controller::attack()
{
    int index = scene->detectEnemy();
    if(index==-1){
        qDebug()<<"No enemy.";
    }else{
        enemies[index]->setDefeated(true);
    }
}

void Controller::detectEnemy()
{
    if(scene->detectEnemy()!=-1){
        qDebug()<<"There is an enemy.";
    }
}

std::vector<std::shared_ptr<Tile> > Controller::getTiles() const
{
    return tiles;
}

int Controller::getRow() const
{
    return row;
}

int Controller::getCol() const
{
    return col;
}
