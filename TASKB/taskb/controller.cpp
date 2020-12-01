#include "controller.h"
#include <QDebug>

Controller::Controller()
{
    world = std::make_unique<World>();
    world->createWorld(":/images/worldmap.png",10,10,0.25);

    row = world->getRows();
    col = world->getCols();

    protagonist = world->getProtagonist();
    maxEH = protagonist->getEnergy();

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

    pathfinder=std::make_shared<Pathfinder>(row,col,tiles);
}

void Controller::createScene(QWidget *parent)
{
    scene = new TextScene(parent, tiles, protagonist, enemies, healthpacks);
}

void Controller::addSceneToView(QGraphicsView &view)
{
    view.setScene(scene);
}

void Controller::moveRight()
{
    if(!checkXBoundary(protagonist->getXPos()+1)){
        protagonist->setXPos(protagonist->getXPos()+1);
        qDebug()<<"move right";
        consumeEnergy();
        detectEnemy();
        detectHealthpack();
    }else{
        qDebug()<<"at boundary!";
    }
}

void Controller::moveLeft()
{
    if(!checkXBoundary(protagonist->getXPos()-1)){
        protagonist->setXPos(protagonist->getXPos()-1);
        qDebug()<<"move left";
        consumeEnergy();
        detectEnemy();
        detectHealthpack();
    }else{
        qDebug()<<"at boundary!";
    }
}

void Controller::moveUp()
{
    if(!checkYBoundary(protagonist->getYPos()-1)){
        protagonist->setYPos(protagonist->getYPos()-1);
        qDebug()<<"move up";
        consumeEnergy();
        detectEnemy();
        detectHealthpack();
    }else{
        qDebug()<<"at boundary!";
    }
}

void Controller::moveDown()
{
    if(!checkYBoundary(protagonist->getYPos()+1)){
        protagonist->setYPos(protagonist->getYPos()+1);
        qDebug()<<"move down";
        consumeEnergy();
        detectEnemy();
        detectHealthpack();
    }else{
        qDebug()<<"at boundary!";
    }
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
        if(enemies[index]->getDefeated()){
            qDebug()<<"The enemy is already dead";
        }else{
            enemies[index]->setDefeated(true);
            protagonist->setHealth(protagonist->getHealth()-enemies[index]->getValue());
            protagonist->setEnergy(maxEH);
            qDebug()<<"Attack an enemy, enemy strength:"<<enemies[index]->getValue();
            qDebug()<<"Energy:"<<protagonist->getEnergy()<<", health:"<<protagonist->getHealth();
        }
    }
}

void Controller::take()
{
    int index = scene->detectHealthpack();
    if(index==-1){
        qDebug()<<"No healthpack.";
    }else{
        protagonist->setHealth(protagonist->getHealth()+healthpacks[index]->getValue());
        qDebug()<<"Take a healthpack, content:"<<healthpacks[index]->getValue()<<", health:"<<protagonist->getHealth();
        healthpacks[index]->setValue(0);
        scene->redrawHealthpack(index);
    }
}

void Controller::gotoXY(int x, int y)
{
    if(checkXBoundary(x)||checkYBoundary(y)){
        qDebug()<<"outside the world!";
    }else{
        protagonist->setPos(x,y);
        //pathfinder
        auto path = pathfinder->findpath(protagonist->getXPos(),protagonist->getYPos(),x,y);
        while(!path.isEmpty()){
            qDebug()<<path.pop()->getXPos()<<path.pop()->getYPos();
        }
    }
}

void Controller::detectEnemy()
{
    if(scene->detectEnemy()!=-1){
        qDebug()<<"There is an enemy.";
    }
}

void Controller::detectHealthpack()
{
    if(scene->detectHealthpack()!=-1){
        qDebug()<<"There is a healthpack.";
    }
}

bool Controller::checkXBoundary(int xPos)
{
    if(xPos>col-1||xPos<0){
        return true;
    }else{
        return false;
    }
}

bool Controller::checkYBoundary(int yPos)
{
    if(yPos>row-1||yPos<0){
        return true;
    }else{
        return false;
    }
}

int Controller::getRow() const
{
    return row;
}

int Controller::getCol() const
{
    return col;
}

std::shared_ptr<Protagonist> Controller::getProtagonist() const
{
    return protagonist;
}

std::vector<std::shared_ptr<Tile> > Controller::getTiles() const
{
    return tiles;
}

std::vector<std::shared_ptr<Tile> > Controller::getHealthpacks() const
{
    return healthpacks;
}
