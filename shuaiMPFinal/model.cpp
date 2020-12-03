#include "model.h"
#include<QDebug>


Model::Model(QString fileName,int scale)
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
        for(unsigned int i=0; i<tempEnemies.size(); i++){
            std::shared_ptr<Enemy> e = std::move(tempEnemies[i]);
            if(dynamic_cast<PEnemy*>(e.get())){
                pEnemies.emplace_back(std::dynamic_pointer_cast<PEnemy>(e));
                connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                    if(x==e->getXPos()&&y==e->getYPos()){
                        qDebug()<< "there is an posional enermy";
                        emit detectedSignal(PENEMY,i);
                    }
                    emit detectedSignal(-1,i);
            });

            }else{
                normalEnemies.emplace_back(e);
                connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                    if(x==e->getXPos()&&y==e->getYPos()){
                        qDebug()<< "there is an normal enermy";
                        emit detectedSignal(ENEMY,i);
                    }
                    emit detectedSignal(NONE,i);

            });
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
                emit detectedSignal(NONE,i);

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
    qDebug()<<"Move right";
    consumeEnergy();
//  detectEnemy();  //implementation in controller, cause it is detected by view
//  detectHealthpack(); //implementation in controller, cause it is detected by view
}

void Model::moveLeft()
{
    protagonist->setXPos(protagonist->getXPos()-1);
    qDebug()<<"Move left";
    consumeEnergy();
}

void Model::moveUp()
{
    protagonist->setYPos(protagonist->getYPos()-1);
//    qDebug()<< "position now is" << xPos <<yPos;
    qDebug()<<"Move up";
    consumeEnergy();
}

void Model::moveDown()
{
    protagonist->setYPos(protagonist->getYPos()+1);
    qDebug()<<"Move down";
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

    if(index==-1){
        qDebug()<<"No enemy.";
    }else{
        if(normalEnemies[index]->getDefeated()){
            qDebug()<<"The enemy is already dead";
        }else{
            normalEnemies[index]->setDefeated(true);
            protagonist->setHealth(protagonist->getHealth()-normalEnemies[index]->getValue());
            protagonist->setEnergy(maxEH); //return back
            qDebug()<<"Attack an enemy, enemy strength:"<<normalEnemies[index]->getValue();
            qDebug()<<"Energy:"<<protagonist->getEnergy()<<", health:"<<protagonist->getHealth();
        }
    }
}

void Model::take(int index)
{
    if(index==-1){
        qDebug()<<"No healthpack.";
    }else{
        protagonist->setHealth(protagonist->getHealth()+healthpacks[index]->getValue());
        qDebug()<<"Take a healthpack, content:"<<healthpacks[index]->getValue()<<", health:"<<protagonist->getHealth();
        healthpacks[index]->setValue(0);
//        scene->redrawHealthpack(index);
    }
}




