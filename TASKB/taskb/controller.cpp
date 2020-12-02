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
    connect(protagonist.get(),&Protagonist::energyChanged,this,&Controller::gameover);
    connect(protagonist.get(),&Protagonist::healthChanged,this,&Controller::gameover);

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
        connect(pEnemies[i].get(),&PEnemy::dead,this,&Controller::resetPoisonLevel);
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
    if(!isOutside(protagonist->getXPos()+1,protagonist->getYPos())){
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
    if(!isOutside(protagonist->getXPos()-1,protagonist->getYPos())){
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
    if(!isOutside(protagonist->getXPos(),protagonist->getYPos()-1)){
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
    if(!isOutside(protagonist->getXPos(),protagonist->getYPos()+1)){
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

void Controller::getPoisoned()
{
    if(xposP-1<=protagonist->getXPos()&&protagonist->getXPos()<=xposP+1&&yposP-1<=protagonist->getYPos()&&protagonist->getYPos()<=yposP+1&&poisonLevel>0){
        //qDebug()<<"get poisoned "<<poisonLevel;
        protagonist->setHealth(protagonist->getHealth()-poisonLevel);
        scene->redrawState(poisonLevel);
        QTimer::singleShot(3000, this, &Controller::getPoisoned);
    }else{
        scene->redrawState(0);
    }
}

void Controller::gameover(int checkvalue)
{
    if(checkvalue<=0){
        qDebug()<<"Game over!";
    }
}

void Controller::attack()
{
    if(enemyIndex!=-1){
        if(isPEnemy){
            //if(!pEnemies[enemyIndex]->getDefeated()){
            if(pEnemies[enemyIndex]->getPoisonLevel()!=0){
                //pEnemies[enemyIndex]->setDefeated(true);
                xposP=pEnemies[enemyIndex]->getXPos();
                yposP=pEnemies[enemyIndex]->getYPos();
                pEnemies[enemyIndex]->poison();
                protagonist->setHealth(protagonist->getHealth()-pEnemies[enemyIndex]->getValue());
                qDebug()<<"Attack a poison enemy, enemy strength:"<<pEnemies[enemyIndex]->getValue();
                protagonist->setEnergy(maxEH);
                getPoisoned();
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
    poisonLevel=p;
}

void Controller::resetPoisonLevel()
{
    poisonLevel=0;
    xposP=-1;
    yposP=-1;
}

void Controller::gotoXY(int x, int y)
{
    if(isOutside(x,y)){
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

bool Controller::isOutside(int x, int y)
{
    bool isoutside=false;
    if(x>col-1||x<0||y>row-1||y<0){
        isoutside=true;
    }
    return isoutside;
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
