#include "model.h"
#include<QDebug>


Model::Model(QString fileName,int scale,QObject *parent)
{

    world = std::make_unique<World>();
//    world->createWorld("://images/" +fileName+".png",10,10,0.25);
    world->createWorld("/home/shuai/Desktop/libfinal/" + fileName + ".png",22,22,0.25);

    this->scale= scale;
    readData();

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

        std::vector<std::unique_ptr<Enemy>> tempEnemies = world->getEnemies();
        int indexOfEnermy =0;
        int indexOfPEnermy =0;
        for(unsigned int i=0; i<tempEnemies.size(); i++){
            std::shared_ptr<Enemy> e = std::move(tempEnemies[i]);
            if(dynamic_cast<PEnemy*>(e.get())){
//                 qDebug()<< "P:"<<indexOfPEnermy;

                pEnemies.emplace_back(std::dynamic_pointer_cast<PEnemy>(e));
//                qDebug()<< "list of pisonal enermy strength is"<<pEnemies[indexOfPEnermy]->getValue();
                connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                    if(x==e->getXPos()&&y==e->getYPos()){
                        qDebug()<< "there is an posional enermy";
                        this->isPosional = true;
                        emit detectedSignal(PENEMY,indexOfPEnermy);
                    }
            });

                connect(pEnemies[indexOfPEnermy].get(),&PEnemy::poisonLevelUpdated,[=](int poisonLevel){
                   int pEXPosion =  pEnemies[indexOfPEnermy].get()->getXPos();
                   int pEYPosion =  pEnemies[indexOfPEnermy].get()->getYPos();
                   int xPos = protagonist.get()->getXPos();
                   int yPos=protagonist.get()->getYPos();

                    if(std::abs(pEXPosion-xPos)<2 && std::abs(pEYPosion-yPos)<2){
                        qDebug()<< "protagonist x"<<xPos;
                        qDebug()<< "penemy x"<<pEXPosion;

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
//                  qDebug()<< indexOfEnermy;
                normalEnemies.emplace_back(e);
//                 qDebug()<< "list of normal enermy strength is"<<normalEnemies[indexOfEnermy]->getValue();
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

void Model::moveRight()
{
    //After a movement,three things needed:
    //1.update energy //2.detect energy //3.detectpack
    protagonist->setXPos(protagonist->getXPos()+1);
    consumeEnergy();

}

void Model::moveLeft()
{
    protagonist->setXPos(protagonist->getXPos()-1);
//    qDebug()<<"Move left";
    consumeEnergy();
}

void Model::moveUp()
{
    protagonist->setYPos(protagonist->getYPos()-1);
//    qDebug()<< "position now is" << xPos <<yPos;
//    qDebug()<<"Move up";
    consumeEnergy();
}

void Model::moveDown()
{
    protagonist->setYPos(protagonist->getYPos()+1);
//    qDebug()<<"Move down";
    consumeEnergy();
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
//        healthpacks[index]->setValue(0);
          healthpacks[index]->setValue(0);
          return index;
//        scene->redrawHealthpack(index);
    }
    return index;
}




