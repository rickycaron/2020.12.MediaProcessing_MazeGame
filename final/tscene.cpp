#include "tscene.h"
#include <QDebug>
#include <QTimer>

TScene::TScene(QObject *parent, const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy> > &pEnemies, const std::vector<std::shared_ptr<Tile> > &healthpacks, int scale, int row, int col)
    :QGraphicsScene(parent)
{
    this->row=row;
    this->col=col;
    this->scale=scale;
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(normalEnemies,pEnemies);
    printHealthpacks(healthpacks);
    connect(protagonist.get(),&Protagonist::posChanged,this,&TScene::redrawPosition);
}

void TScene::printTiles(const std::vector<std::shared_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        TTile *tile= new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),tiles[i]->getValue(),scale,this);
        tileQlist.append(tile);
        this->addItem(tile);
    }
    connect(this,&TScene::poisonTile,[=](int xPEPos,int yPEPos,int poisonLevel){
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

void TScene::printProtagonist(const std::shared_ptr<Protagonist> &protagonist)
{
    protagonistView = new TProtagonist(protagonist->getXPos(),protagonist->getYPos(),scale);
    //connect(protagonist.get(),&Protagonist::energyChanged,protagonistView,&TProtagonist::checkState);
    connect(protagonist.get(),&Protagonist::healthChanged,protagonistView,&TProtagonist::checkState);
    this->addItem(protagonistView);
}

void TScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies)
{
    for(unsigned int i=0;i<normalEnemies.size();i++){
        TEnemy * enemy = new TEnemy(normalEnemies[i]->getXPos(),normalEnemies[i]->getYPos(),scale,0);
        connect(normalEnemies[i].get(),&Enemy::dead,enemy,&TEnemy::indicateDead);
        normalEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
    for(unsigned int i=0;i<pEnemies.size();i++){
        connect(pEnemies[i].get(),&PEnemy::poisonLevelUpdated,[=]{
           emit poisonTile(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),pEnemies[i].get()->getPoisonLevel());
        });
        TEnemy * enemy = new TEnemy(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),scale,1);
        connect(pEnemies[i].get(),&Enemy::dead,enemy,&TEnemy::indicateDead);
        pEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void TScene::printXEnemy(const std::shared_ptr<XEnemy> &xEnemy)
{
    tXEnemyView  =  new TEnemy(xEnemy->getXPos(),xEnemy->getYPos(),scale,2);
    this->addItem(tXEnemyView);
    parent()->connect(xEnemy.get(),&XEnemy::posChanged,[=](int x,int y){
        tXEnemyView->resetPos(x,y);
    });

    connect(xEnemy.get(),&Enemy::dead,tXEnemyView,&TEnemy::indicateDead);
}

void TScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        THealthpack * healthpack = new THealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos(),scale);
        healthpackQlist.append(healthpack);
        this->addItem(healthpack);
    }
}

int TScene::detectHealthpack()
{
    int index = -1;
    for (int i=0; i<healthpackQlist.size(); i++) {
        if(protagonistView->collidesWithItem(healthpackQlist[i],Qt::IntersectsItemShape)&&!healthpackQlist[i]->getIsEmpty()){
            index = i;
            break;
        }
    }
    return index;
}

void TScene::redrawHealthpack(int index)
{
    healthpackQlist[index]->emptyContent();
}

void TScene::redrawPosition(int xPos, int yPos)
{
    protagonistView->setPos(20*xPos,20*yPos);
}

void TScene::redrawPoisonedState()
{
    protagonistView->getPoisoned();
    QTimer::singleShot(400,this,[=]{
        protagonistView->reset();
    });
}

void TScene::setTilePoison(int index)
{
    tileQlist[index]->poisonTile();
}
