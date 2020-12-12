#include "gscene.h"
#include<QtDebug>
#include<QTimer>
#include <QGraphicsSceneMouseEvent>

GScene::GScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                   const std::vector<std::shared_ptr<Enemy>> &enemies,const std::vector<std::shared_ptr<PEnemy>> &penemies ,const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale, int row, int col)
    :QGraphicsScene(parent)
{
    this->scale = scale;
    printTiles(tiles,row, col);
    printEnemies(enemies);
    printPEnemies(penemies);
    printProtagonist(protagonist);
    printHealthpacks(healthpacks);
}

void GScene::printTiles(const std::vector<std::shared_ptr<Tile> > &tiles, int row, int col)
{
    for(unsigned int i=0;i<tiles.size();i++){
        GTile *tile = new GTile(tiles[i]->getXPos(),tiles[i]->getYPos(),tiles[i]->getValue(),scale,this);
        tileQlist.append(tile);
        this->addItem(tile);
    }

    connect(this,&GScene::poisonTile,[=](int xPEPos,int yPEPos,int poisonLevel){
        for(int n=xPEPos-1;n<=xPEPos+1;n++){
            for(int m=yPEPos-1;m<=yPEPos+1;m++){
                if(n>=0&&n<col&&m>=0&&m<row){
                    if(poisonLevel==0){
                        tileQlist[m*col+n]->draw();
                    }
                    else{
                        tileQlist[m*col+n]->poisonTile();
                        QTimer::singleShot(400,this,[=]{
                            //to achieve animation
                            tileQlist[m*col+n]->draw();
                        });
                    }
                }
            }
        }
    });
}

void GScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    protagonistView = new GProtagonist(protagonist->getXPos(),protagonist->getYPos(),scale,this);

    connect(protagonist.get(),&Protagonist::posChanged,[=](int x,int y){
        protagonistView->reSetPos(x,y);
});
    this->addItem(protagonistView);
}

void GScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        GEnemy * enemy = new GEnemy(enemies[i]->getXPos(),enemies[i]->getYPos(),scale,this);
        enemyQlist.append(enemy);
        this->addItem(enemy);
        connect(enemies[i].get(),&Enemy::dead,[=]{
            enemy->setGrave();
        });
    }
}

void GScene::printPEnemies(const std::vector<std::shared_ptr<PEnemy> > &penemies)
{
    for(unsigned int i=0;i<penemies.size();i++){
        GPEnemy * enemy = new GPEnemy(penemies[i]->getXPos(),penemies[i]->getYPos(),scale,this);
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

void GScene::printXEnemy(const std::shared_ptr<XEnemy> &xEnemy)
{
    gXEnemyView  =  new GXEnemy(xEnemy->getXPos(),xEnemy->getYPos(),scale,this);
    this->addItem(gXEnemyView);
    parent()->connect(xEnemy.get(),&XEnemy::posChanged,[=](int x,int y){
        gXEnemyView->resetPos(x,y);
    });
    parent()->connect(xEnemy.get(),&XEnemy::dead,[=](){
        gXEnemyView->setGrave();
    });
}

void GScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        GHealthpack * healthpack = new GHealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos(),scale,this);
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}


void GScene::redrawHealthpack(int index)
{
    healthpackQlist[index]->usedHealthPack();
}

void GScene::changeProtagonistImage(int dir)
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

void GScene::setTilePoison(int index)
{
    tileQlist[index]->poisonTile();
}

void GScene::protagonistAttack()
{
    protagonistView->attack();
}

