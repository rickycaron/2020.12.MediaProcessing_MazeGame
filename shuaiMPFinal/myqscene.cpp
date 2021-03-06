#include "myqscene.h"
#include<QtDebug>
#include<QTimer>
MyQScene::MyQScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                   const std::vector<std::shared_ptr<Enemy>> &enemies,const std::vector<std::shared_ptr<PEnemy>> &penemies ,const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale)
    :QGraphicsScene(parent)
{
    this->scale = scale;
    printTiles(tiles);
    printEnemies(enemies);
    printPEnemies(penemies);
    printProtagonist(protagonist);
    printHealthpacks(healthpacks);
//    parent->connect(protagonist.get(),&Protagonist::posChanged,this,&TextScene::redrawProtagonist);
//    for (unsigned int i=0; i<enemies.size(); i++) {
//        parent->connect(enemies[i].get(),&Enemy::dead,enemyQlist[i],&TEnemy::indicateDead);
//    }
}

void MyQScene::printTiles(const std::vector<std::shared_ptr<Tile> > &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        QTile *tile = new QTile(tiles[i]->getXPos(),tiles[i]->getYPos(),tiles[i]->getValue(),scale,this);
        tileQlist.append(tile);
        this->addItem(tile);
        connect(this,&MyQScene::poisonTile,[=](int xPEPos,int yPEPos,int poisonLevel){
            int tileXPos =tiles[i]->getXPos();
            int tileYPos =tiles[i]->getYPos();

            if(std::abs(xPEPos-tileXPos)<2 && std::abs(yPEPos-tileYPos)<2){
                if(poisonLevel==0){
                    tile->draw();
                }
                else{
                  tile->poisonTile();
                  QTimer::singleShot(400,this,[=]{
                      //to achieve animation
                      tile->draw();
                  });
                }

            }


        });
    }
}

void MyQScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{

    protagonistView = new QProtagonist(protagonist->getXPos(),protagonist->getYPos(),scale,this);

    connect(protagonist.get(),&Protagonist::posChanged,[=](int x,int y){
        protagonistView->reSetPos(x,y);
});


    this->addItem(protagonistView);
}

void MyQScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        QEnemy * enemy = new QEnemy(enemies[i]->getXPos(),enemies[i]->getYPos(),scale,this);
        enemyQlist.append(enemy);
        this->addItem(enemy);

    }
}

void MyQScene::printPEnemies(const std::vector<std::shared_ptr<PEnemy> > &penemies)
{
    for(unsigned int i=0;i<penemies.size();i++){
        QPEnemy * enemy = new QPEnemy(penemies[i]->getXPos(),penemies[i]->getYPos(),scale,this);
        penemyQlist.append(enemy);
        this->addItem(enemy);
        //Timer setting
        auto animationPEnemyTimer = new QTimer(this);
        connect(animationPEnemyTimer,&QTimer::timeout,[=]{
           enemy->animationPEnemy();
        });
        connect(penemies[i].get(),&PEnemy::dead,[=]{
           animationPEnemyTimer->stop();
           enemy->setGrave();
        });
        connect(penemies[i].get(),&PEnemy::poisonLevelUpdated,[=]{
           emit poisonTile(penemies[i]->getXPos(),penemies[i]->getYPos(),penemies[i].get()->getPoisonLevel());
        });
        animationPEnemyTimer->start(300);

    }
}

void MyQScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        QHealthPack * healthpack = new QHealthPack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos(),scale,this);
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}


void MyQScene::redrawHealthpack(int index)
{
    healthpackQlist[index]->usedHealthPack();
}

void MyQScene::changeProtagonistImage(int dir)
{
    switch (dir) {
    case UP:{
        protagonistView->reSetImg(UP);
        break;
    }

    case DOWN:{
        protagonistView->reSetImg(DOWN);
        break;
    }

    case LEFT:{
        protagonistView->reSetImg(LEFT);
        break;
    }

    case RIGHT:{
        protagonistView->reSetImg(RIGHT);
        break;
    }

    }
}

void MyQScene::setDeath(int type,int index)
{
    switch (type) {
    case ENEMY:{
        enemyQlist[index]->setGrave();
        break;
    }
    case PENEMY:{
        penemyQlist[index]->setGrave();
        break;
    }

    }
}





void MyQScene::redrawProtagonist(int xPos, int yPos)
{

}
