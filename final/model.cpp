#include "model.h"
#include<QDebug>
#include <QTimer>
#include "config.h"

Model::Model(QString fileName):QObject()
{

    world = std::make_unique<World>();
    //qDebug()<<"!!!!";
//    world->createWorld("://images/" +fileName+".png",10,10,0.25);
//    world->createWorld("/home/shuai/Desktop/libfinal/" + fileName + ".png",22,22,0.25);
    world->createWorld(":/images/worldmap4.png",22,22,0.25);
    //qDebug()<<"22222";
    //world->createWorld(":/images/worldmap4.png",22,22,0.25);
    readData();
    //qDebug()<<"3333";
}

bool Model::readData()
{
    //Read data from world lib and store it into our vectors
    row=world->getRows();
    col=world->getCols();
    protagonist = world->getProtagonist();
    maxEH = protagonist->getEnergy();
    std::vector<std::unique_ptr<Tile>> tempTiles = world->getTiles();
    for(unsigned int i=0; i<tempTiles.size(); i++){
        tiles.emplace_back(std::move(tempTiles[i]));
    }

    pathfinder=std::make_shared<Pathfinder>(row,col,tiles);

    std::vector<std::unique_ptr<Enemy>> tempEnemies = world->getEnemies();
    int indexOfEnermy =0;
    int indexOfPEnermy =0;

    for(unsigned int i=0; i<tempEnemies.size(); i++){
        std::shared_ptr<Enemy> e = std::move(tempEnemies[i]);
        if(dynamic_cast<PEnemy*>(e.get())){
            pEnemies.emplace_back(std::dynamic_pointer_cast<PEnemy>(e));
            connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                if(x==e->getXPos()&&y==e->getYPos()){
                    qDebug()<< "there is an posional enermy";
                    this->isPosional = true;
                    emit detectedSignal(PENEMY,indexOfPEnermy);
                }
            });

            connect(pEnemies[indexOfPEnermy].get(),&PEnemy::poisonLevelUpdated,[=](int poisonLevel){
                   int pEXPosion = pEnemies[indexOfPEnermy].get()->getXPos();
                   int pEYPosion = pEnemies[indexOfPEnermy].get()->getYPos();
                   int xPos = protagonist.get()->getXPos();
                   int yPos=protagonist.get()->getYPos();

                   if(std::abs(pEXPosion-xPos)<2 && std::abs(pEYPosion-yPos)<2){
                        qDebug()<< "near around";
                        //get poisoned
                        float currentHealth = protagonist.get()->getHealth();
                        currentHealth = currentHealth -difficulty*poisonLevel;
                        //update apperance around firstly
                        //update protagonist then
                        if(currentHealth<=0){
                            protagonist.get()->setHealth(0);
                        }
                        else{
                            protagonist.get()->setHealth(currentHealth);
                        }
                    }
            });
            indexOfPEnermy++;
        }else{
            normalEnemies.emplace_back(e);
            connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                if(x==e->getXPos()&&y==e->getYPos()){
                    qDebug()<< "there is an normal enermy";
                    this->isPosional = false;
                    emit detectedSignal(ENEMY,indexOfEnermy);
                }
            });
            indexOfEnermy++;
        }
    }

    std::vector<std::unique_ptr<Tile>> tempHealthpacks = world->getHealthPacks();
    for(unsigned int i=0; i<tempHealthpacks.size(); i++){
        std::shared_ptr<Tile> e = std::move(tempHealthpacks[i]);
        healthpacks.emplace_back(e);
        connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
            if(x==e->getXPos()&&y==e->getYPos()){
                qDebug()<< "there is an health pack";
                emit detectedSignal(HEALTHPACK,i);
            }
        });
    }
    if(row==0||col==0||protagonist==NULL||tiles.size()==0||normalEnemies.size()==0||pEnemies.size()==0||healthpacks.size()==0){
        return false;
    }
    return true;
}

bool Model::setIsChangable(bool status)
{
    isChangable = status;
    return isChangable;
}

bool Model::getIsChangable()
{
    return isChangable;
}
//Implementation of getter
int Model::getRow() const
{
    return row;
}

int Model::getCol() const
{
    return col;
}
std::vector<std::shared_ptr<Tile> > Model::getTiles() const
{
    return tiles;
}

std::shared_ptr<Protagonist> Model::getProtagonist() const
{
    return protagonist;
}

std::vector<std::shared_ptr<Tile> > Model::getHealthpacks() const
{
    return healthpacks;
}

std::vector<std::shared_ptr<Enemy> > Model::getEnemies() const
{
    return normalEnemies;
}

std::vector<std::shared_ptr<PEnemy> > Model::getPEnemies() const
{
    return pEnemies;
}

bool Model::isOutside(int x, int y)
{
    if(x>col-1||x<0||y>row-1||y<0){
        return true;
    }else{
        return false;
    }
}

bool Model::moveRight()
{
    //After a movement,three things needed:
    //1.update energy //2.detect energy //3.detectpack
    if(!isChangable){return false;}
    if(!isOutside(protagonist->getXPos()+1,protagonist->getYPos())){
        protagonist->setXPos(protagonist->getXPos()+1);
        consumeEnergy();
        return true;
    }
    else{
        return false;
    }
}

bool Model::moveLeft()
{
    if(!isChangable){return false;}
    if(!isOutside(protagonist->getXPos()-1,protagonist->getYPos())){
        protagonist->setXPos(protagonist->getXPos()-1);
        consumeEnergy();
        return true;
    }
    else{
        return false;
    }
}

bool Model::moveUp()
{
    if(!isChangable){return false;}
    if(!isOutside(protagonist->getXPos(),protagonist->getYPos()-1)){
        protagonist->setYPos(protagonist->getYPos()-1);
        consumeEnergy();
        return true;
    }
    else{
        return false;
    }
}

bool Model::moveDown()
{
    if(!isChangable){return false;}
    if(!isOutside(protagonist->getXPos(),protagonist->getYPos()+1)){
        protagonist->setYPos(protagonist->getYPos()+1);
        consumeEnergy();
        return true;
    }
    else{
        return false;
    }
}

void Model::move()
{
    if(!path.isEmpty()){
        std::shared_ptr<Tile> nextTile = path.pop();
        protagonist->setPos(nextTile->getXPos(),nextTile->getYPos());
        consumeEnergy();
        QTimer::singleShot(1000, this, &Model::move);
    }else{
        qDebug()<<"Finish!";
    }
}

void Model::gotoXY(int x, int y)
{
    if(isChangable){
        if(isOutside(x,y)){
            qDebug()<<"outside the world!";
        }
        else
        {
            path = pathfinder->findpath(protagonist->getXPos(),protagonist->getYPos(),x,y);
            move();
        }
    }else{
        qDebug()<<"can't move!";
    }
}

void Model::consumeEnergy()
{
    int index = protagonist->getYPos()*world->getCols()+protagonist->getXPos();
    protagonist->setEnergy(protagonist->getEnergy()-tiles[index]->getValue());
    qDebug()<<"Energy: "<<protagonist->getEnergy()<<",Health: "<<protagonist->getHealth();
}

//These two function will excute if checking success in controller
void Model::attack(int index)
{
qDebug()<<isPosional;
    if(index==-1){
        qDebug()<<"No enemy.";
    }else{
        switch (isPosional) {
        case false:
            if(normalEnemies[index]->getDefeated()){
                qDebug()<<"The enemy is already dead";
            }else{
                normalEnemies[index]->setDefeated(true);
                float currentHealth = protagonist->getHealth()-difficulty*(normalEnemies[index]->getValue());
                float currentEnergy = protagonist->getEnergy()-difficulty*(normalEnemies[index]->getValue());
                if(currentHealth<0){currentHealth=0;}
                if(currentEnergy<0){currentEnergy=0;}
                protagonist->setHealth(currentHealth);
                protagonist->setEnergy(currentEnergy);
    //            protagonist->setEnergy(maxEH); //return back
                qDebug()<<"Attack an enemy, enemy strength:"<<normalEnemies[index]->getValue();
                qDebug()<<"Energy:"<<protagonist->getEnergy()<<", health:"<<protagonist->getHealth();
            }
            break;
        case true:
            qDebug()<<"attacking p enemy.";
            if(pEnemies[index]->getPoisonLevel()!=0){
                pEnemies[index]->poison();
//                animation part
            }
            else{
                qDebug()<<"This enemy is already dead.";
            }
            break;
        }

    }
}

int Model::take(int index)
{
    if(index==-1){
        qDebug()<<"No healthpack.";
    }else{
        if(healthpacks[index]->getValue()==0){qDebug()<< "this is a empty healthpacks"; return -1;}
        float currentHealth = protagonist->getHealth()+healthpacks[index]->getValue();
        float currentEnergy = protagonist->getEnergy()+healthpacks[index]->getValue();
        if(currentHealth>100){currentHealth=100;}
        if(currentEnergy>100){currentEnergy=100;}
        protagonist->setHealth(currentHealth);
        protagonist->setEnergy(currentEnergy);
        qDebug()<<"Take a healthpack, content:"<<healthpacks[index]->getValue()<<", health:"<<protagonist->getHealth();
        healthpacks[index]->setValue(0);
        return index;
//        scene->redrawHealthpack(index);
    }
    return index;
}

