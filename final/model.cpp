#include "model.h"
#include<QDebug>
#include <QTimer>
#include "config.h"

Model::Model(QString fileName):QObject()
{
    world = std::make_unique<World>();
    world->createWorld(":/images/"+fileName+".png",20,20,0.4);
    numOfEnemies=21;
    readData();
}

bool Model::readData()
{
    //Read data from world lib and store it into our vectors
    row=world->getRows();
    col=world->getCols();
    protagonist = world->getProtagonist();
    maxEH = protagonist->getEnergy();

//    std::vector<std::unique_ptr<Tile>> tempTiles = world->getTiles();
//    for(unsigned int i=0; i<tempTiles.size(); i++){
//        tiles.emplace_back(std::move(tempTiles[i]));
//    }

    std::vector<std::unique_ptr<Enemy>> tempEnemies = world->getEnemies();
    int indexOfEnermy =0;
    int indexOfPEnermy =0;

    for(unsigned int i=0; i<tempEnemies.size(); i++){
        std::shared_ptr<Enemy> e = std::move(tempEnemies[i]);
        connect(e.get(),&Enemy::dead,[=]{
            numOfEnemies--;
            qDebug()<<"numOfEnemies = "<<numOfEnemies;
            emit numOfEnemiesChanged(numOfEnemies);
        });
        if(dynamic_cast<PEnemy*>(e.get())){
            pEnemies.emplace_back(std::dynamic_pointer_cast<PEnemy>(e));
            connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                if(x==e->getXPos()&&y==e->getYPos()){
                    qDebug()<< "there is an posional enermy";
                    this->enemyType = PENEMY;
                    emit detectedSignal(PENEMY,indexOfPEnermy);
                }
            });


            connect(pEnemies[indexOfPEnermy].get(),&PEnemy::poisonLevelUpdated,[=](int poisonLevel){
                   int pEXPosion = pEnemies[indexOfPEnermy].get()->getXPos();
                   int pEYPosion = pEnemies[indexOfPEnermy].get()->getYPos(); //here can be used to modify born place
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
                            emit protagonistGetPoisoned();
                        }
                    }
            });
            indexOfPEnermy++;
        }else{
            normalEnemies.emplace_back(e);
            connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
                if(x==e->getXPos()&&y==e->getYPos()){
                    qDebug()<< "there is an normal enermy";
                    this->enemyType = ENEMY;
                    emit detectedSignal(ENEMY,indexOfEnermy);
                }
            });
            indexOfEnermy++;
        }
    }

    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_index(0, indexOfEnermy-1);
    int index = uniform_index(e1);

    qDebug()<<indexOfEnermy;
    qDebug()<<index;

    qDebug()<< "starting x position is"<< normalEnemies[index].get()->getXPos();
    qDebug()<< "starting y position is"<< normalEnemies[index].get()->getYPos();

    //The X enemy will show up, doing settings then
    connect(normalEnemies[index].get(),&Enemy::dead,[=]{
        qDebug()<< "the chosen enemy is dead now";
        emit xEnemyShown();

        connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
            if(x==xEnemy->getXPos()&&y==xEnemy->getYPos()){
                qDebug()<< "there is an X enermy";
                this->enemyType = XENEMY;
                emit detectedSignal(XENEMY,index);
            }
        });
        qDebug()<< "the Xenemy xpos is"<<xEnemy->getXPos();

    });

    int speed =2;
    xEnemy = std::make_shared<XEnemy>(normalEnemies[index].get()->getXPos(),normalEnemies[index].get()->getYPos(),
                                                   normalEnemies[index].get()->getValue(),speed,col,row);

    connect(xEnemy.get(),&Enemy::dead,[=]{
        numOfEnemies--;
        qDebug()<<"numOfEnemies = "<<numOfEnemies;
        emit numOfEnemiesChanged(numOfEnemies);
    });

    std::vector<std::unique_ptr<Tile>> tempTiles = world->getTiles();
    for(unsigned int i=0; i<tempTiles.size(); i++){
        tiles.emplace_back(std::move(tempTiles[i]));
        connect(xEnemy.get(),&XEnemy::posChanged,[=](int x,int y){
            if(x==tiles[i]->getXPos()&&y==tiles[i]->getYPos()){
//                    qDebug()<< "poison the tile permanently";
                qDebug()<< "Is changable state is"<< getIsChangable();
                emit poisonTilesPermanent(i);
                tiles[i]->setValue(-1);
            }
        });
        //get poisoned on poisoned tile
        connect(getProtagonist().get(),&Protagonist::posChanged,[=](int x,int y){
            if(x==tiles[i]->getXPos()&&y==tiles[i]->getYPos()){
                float tileValue = tiles[i]->getValue();
                if(tileValue<0){
                    float currentHealth = protagonist->getHealth();
                    protagonist->setHealth(currentHealth-2);
                }

            }


        });
    } 
    pathfinder=std::make_shared<Pathfinder>(row,col,tiles);

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
std::vector<std::shared_ptr<Tile>> Model::getNearestHealthpack()
{
    std::vector<std::shared_ptr<Node>> nearNodetHealthpacks;
    std::vector<std::shared_ptr<Tile>> nearTileHealthpacks;
    auto protagonistNode=std::make_shared<Node>(protagonist);
    for(auto i = healthpacks.begin();i != healthpacks.end();++i)
    {
        //check if the healthpack is still useful(value > 0) or useless(value==0)
        if((*i)->getValue() != 0)
        {
            auto healthpack = std::make_shared<Node>(*i,protagonistNode);
            healthpack->calculateDistance();
            healthpack->setTileType(HEALTHPACK);
            nearNodetHealthpacks.push_back(healthpack);
        }
    }
    //here I call the compare function from the Pathinder Class
    sort(nearNodetHealthpacks.begin(), nearNodetHealthpacks.end(),pathfinder->distanncecomp);
    for(auto i = nearNodetHealthpacks.cbegin();i != nearNodetHealthpacks.cend();++i)
    {
        nearTileHealthpacks.push_back((*i)->getTile());
    }
    nearNodetHealthpacks.clear();
    return nearTileHealthpacks;
}

std::vector<std::shared_ptr<Node>> Model::getNearestEnemy()
{
    std::vector<std::shared_ptr<Node>> nearNodeEnemy;
    //std::vector<std::shared_ptr<Tile>> nearTileEnemy;
    auto protagonistNode=std::make_shared<Node>(protagonist);
    for(auto i = normalEnemies.cbegin();i != normalEnemies.cend();++i)
    {
        if(!(*i)->getDefeated())
        {
            auto enemy = std::make_shared<Node>((*i),protagonistNode);
            enemy->calculateDistance();
            enemy->setTileType(ENEMY);
            nearNodeEnemy.push_back(enemy);
        }
    }
    for(auto i = pEnemies.cbegin();i != pEnemies.cend();++i)
    {
        if(!(*i)->getDefeated())
        {
            auto penemy = std::make_shared<Node>(*i,protagonistNode);
            penemy->calculateDistance();
            penemy->setTileType(PENEMY);
            nearNodeEnemy.push_back(penemy);
        }
    }
    //this is for Xenemy
//    for(auto i = pEnemies.cbegin();i != pEnemies.cend();++i)
//    {
//        if(!(*i)->getDefeated())
//        {
//            auto penemy = std::make_shared<Node>(*i,protagonistNode);
//            penemy->calculateDistance();
//            nearNodeEnemy.push_back(penemy);
//        }
//    }
    //here I call the compare function from the Pathinder Class
    sort(nearNodeEnemy.begin(), nearNodeEnemy.end(),pathfinder->distanncecomp);
//    for(auto i = nearNodeEnemy.cbegin();i != nearNodeEnemy.cend();++i)
//    {
//        nearTileEnemy.push_back((*i)->getTile());
//    }
//    nearNodeEnemy.clear();
    return nearNodeEnemy;
}

std::shared_ptr<Tile> Model::gotoNearestThing()
{
    float healthpackcost=0.0f;
    float enemycost=0.0f;   
    auto nearhealthpack=getNearestHealthpack();
    auto nearenemy=getNearestEnemy();
    QStack<std::shared_ptr<Tile>> healthpackpath;
    QStack<std::shared_ptr<Tile>> enemypath;
    std::shared_ptr<Tile> enemygoalTile=nullptr;
    std::shared_ptr<Tile> healthpackgoalTile=nullptr;
    //find the nearest enemy
    for(auto i = nearenemy.cbegin();i != nearenemy.cend();++i)
    {
        enemypath=pathfinder->findpath(protagonist,(*i)->getTile()->getXPos() ,(*i)->getTile()->getYPos());
        enemycost=pathfinder->getMoveCost();
        if( enemycost < protagonist->getEnergy() && (*i)->getTile()->getValue() < protagonist->getHealth())
        {
            this->enemyType=(*i)->getTileType();
            enemygoalTile=(*i)->getTile();
            break;
        }
    }
    //find the nearest healthpack
    for(auto i = nearhealthpack.cbegin();i != nearhealthpack.cend();++i)
    {
        //find the path from the nearest healthpack
        healthpackpath=pathfinder->findpath(protagonist,(*i)->getXPos(),(*i)->getYPos());
        healthpackcost=pathfinder->getMoveCost();
        if(healthpackcost < protagonist->getEnergy()){
            healthpackgoalTile=(*i);
            break;
        }
    }
    //compare which one is better
    if (enemycost < healthpackcost || protagonist->getHealth())
    {
        //goto the enemy
        path = enemypath;
        return healthpackgoalTile;
    }
    else
    {
        //goto the healthpack
        //autonextThing=1;
        this->enemyType=HEALTHPACK;
        path = healthpackpath;
        return enemygoalTile;
    }
}

std::shared_ptr<XEnemy> Model::getXEnemy() const
{
    return xEnemy;
}

type Model::getEnemyType() const
{
    return enemyType;
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
    //1.update energy //2.detect enemy //3.detectpack
    if(!isChangable){return false;}
    if(!isOutside(protagonist->getXPos()+1,protagonist->getYPos())){
        emit detectedSignal(NONE,-1);
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
        emit detectedSignal(NONE,-1);
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
        emit detectedSignal(NONE,-1);
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
        emit detectedSignal(NONE,-1);
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
        emit detectedSignal(NONE,-1);
        protagonist->setPos(nextTile->getXPos(),nextTile->getYPos());
        consumeEnergy();
        QTimer::singleShot(1000, this, &Model::move);
    }else{
        emit moveFinished();
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
            //qDebug()<<"go to "<<x<<","<<y;
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
    float tileValue = tiles[index]->getValue();
    if(tileValue<0){
        protagonist->setEnergy(protagonist->getEnergy()+tileValue);
    }
    else{
        protagonist->setEnergy(protagonist->getEnergy()-tileValue);
    }
//    protagonist->setEnergy(protagonist->getEnergy()-tiles[index]->getValue());
    qDebug()<<"Energy: "<<protagonist->getEnergy()<<",Health: "<<protagonist->getHealth();
}

//These two function will excute if checking success in controller
void Model::attack(int index)
{
    if(index==-1){
        qDebug()<<"No enemy.";
    }else{
        switch (enemyType) {
        case ENEMY:
            if(normalEnemies[index]->getDefeated()){
                qDebug()<<"The enemy is already dead";
            }else{
                normalEnemies[index]->setDefeated(true);
                emit updateScoreBoard(baseScore);
                float currentHealth = protagonist->getHealth()-difficulty*(normalEnemies[index]->getValue());
                float currentEnergy = protagonist->getEnergy()-difficulty*(normalEnemies[index]->getValue());
                if(currentHealth<0){currentHealth=0;}
                if(currentEnergy<0){currentEnergy=0;}
                protagonist->setHealth(currentHealth);
                protagonist->setEnergy(currentEnergy);
    //            protagonist->setEnergy(maxEH); //return back
                qDebug("1111111111111111111111111111111111111111111111!");
                qDebug()<<"Attack an enemy, enemy strength:"<<normalEnemies[index]->getValue();
                qDebug()<<"Energy:"<<protagonist->getEnergy()<<", health:"<<protagonist->getHealth();
            }
            break;
        case PENEMY:
            qDebug()<<"attacking p enemy.";
            emit updateScoreBoard(2*baseScore);
            if(pEnemies[index]->getPoisonLevel()!=0){
                pEnemies[index]->poison();
//                animation part
            }
            else{
                qDebug()<<"This enemy is already dead.";
            }
            break;
        case XENEMY:
            qDebug()<<"attacking x enemy.";
            int currentLife =xEnemy->useLives();
            if(currentLife>-1){
                qDebug()<<"This x enemy is attacked once."<<currentLife;
//                animation part
            }
            else if(currentLife==-1){
                qDebug()<<"This x enemy is killed by you.";
                xEnemy->setDefeated(true);
                emit updateScoreBoard(3*baseScore);

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
        return index;
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
    }
}

