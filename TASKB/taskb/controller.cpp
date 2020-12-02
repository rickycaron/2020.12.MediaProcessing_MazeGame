#include "controller.h"
#include <QDebug>
#include <QTimer>

Controller::Controller(QObject *parent):QObject(parent)
{
    world = std::make_unique<World>();
    world->createWorld(":/images/worldmap.png",15,5,0.5);

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
        std::shared_ptr<Enemy> e = std::move(tempEnemies[i]);
        if(dynamic_cast<PEnemy*>(e.get())){
            pEnemies.emplace_back(std::dynamic_pointer_cast<PEnemy>(e));
        }else{
            normalEnemies.emplace_back(e);
        }
    }

    std::vector<std::unique_ptr<Tile>> tempHealthpacks = world->getHealthPacks();
    for(unsigned int i=0; i<tempHealthpacks.size(); i++){
        healthpacks.emplace_back(std::move(tempHealthpacks[i]));
    }

    pathfinder=std::make_shared<Pathfinder>(row,col,tiles);

    for(unsigned int i=0;i<pEnemies.size();i++){
        connect(pEnemies[i].get(),&PEnemy::poisonLevelUpdated,this,&Controller::getPoisonLevel);
    }
}

void Controller::createScene(QWidget *parent)
{
    scene = new TextScene(parent, tiles, protagonist, normalEnemies, pEnemies, healthpacks, row, col);
}

void Controller::addSceneToView(QGraphicsView &view)
{
    view.setScene(scene);
}

void Controller::moveRight()
{
    if(!checkXBoundary(protagonist->getXPos()+1)){
        protagonist->setXPos(protagonist->getXPos()+1);
        //qDebug()<<"move right";
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
        //qDebug()<<"move left";
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
        //qDebug()<<"move up";
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
        //qDebug()<<"move down";
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
    if(enemyIndex!=-1){
        if(isPEnemy){
            //if(!pEnemies[enemyIndex]->getDefeated()){
            if(pEnemies[enemyIndex]->getPoisonLevel()!=0){
                //pEnemies[enemyIndex]->setDefeated(true);
                pEnemies[enemyIndex]->poison();
                protagonist->setHealth(protagonist->getHealth()-pEnemies[enemyIndex]->getValue());
                qDebug()<<"Attack a poison enemy, enemy strength:"<<pEnemies[enemyIndex]->getValue();
                protagonist->setEnergy(maxEH);
            }
            else{
                qDebug()<<"This enemy is already dead.";
            }
        }
        else{
            if(!normalEnemies[enemyIndex]->getDefeated()){
                normalEnemies[enemyIndex]->setDefeated(true);
                protagonist->setHealth(protagonist->getHealth()-normalEnemies[enemyIndex]->getValue());
                qDebug()<<"Attack a normal enemy, enemy strength:"<<normalEnemies[enemyIndex]->getValue();
                protagonist->setEnergy(maxEH);
            }
            else{
                qDebug()<<"This enemy is already dead.";
            }
        }
    }
    else{
        qDebug()<<"No enemy.";
    }
    qDebug()<<"Energy:"<<protagonist->getEnergy()<<", health:"<<protagonist->getHealth();
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

void Controller::move()
{
    if(!path.isEmpty()){
        std::shared_ptr<Tile> nextTile = path.pop();
        protagonist->setPos(nextTile->getXPos(),nextTile->getYPos());
        consumeEnergy();
        detectEnemy();
        detectHealthpack();
        QTimer::singleShot(1000, this, &Controller::move);
    }else{
        qDebug()<<"Finish!";
    }
}

void Controller::getPoisonLevel(float p)
{
    qDebug()<<"poisonLevel = "<<p;
}

void Controller::gotoXY(int x, int y)
{
    if(checkXBoundary(x)||checkYBoundary(y)){
        qDebug()<<"outside the world!";
    }else{
        path = pathfinder->findpath(protagonist->getXPos(),protagonist->getYPos(),x,y);
        move();
    }
}


void Controller::detectEnemy()
{
    if(scene->getEnemyIndex()!=-1){
        if(scene->getIsPEnemy()){
            qDebug()<<"Here is a poison enemy.";
            isPEnemy = true;
        }else{
            qDebug()<<"Here is a normal enemy.";
        }
        enemyIndex = scene->getEnemyIndex();
    }else{
        //qDebug()<<"No enemy.";
        isPEnemy = false;
        enemyIndex = -1;
    }
    scene->setEnemyIndex(-1);
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
