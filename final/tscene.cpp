#include "tscene.h"
#include <QDebug>
#include <QTimer>

TScene::TScene(QObject *parent, const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy> > &pEnemies, const std::vector<std::shared_ptr<Tile> > &healthpacks, int row, int col)
    :QGraphicsScene(parent)
{
    this->row=row;
    this->col=col;
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(normalEnemies,pEnemies);
    printHealthpacks(healthpacks);
    connect(protagonist.get(),&Protagonist::posChanged,this,&TScene::redrawPosition);

    //for(int i=0; i<normalEnemyQlist.size(); i++){
        //connect(normalEnemies[i].get(),&Enemy::dead,normalEnemyQlist[i],&TEnemy::indicateDead);
        //connect(protagonist.get(),&Protagonist::posChanged,normalEnemyQlist[i],&TEnemy::checkCollide);
        //connect(normalEnemyQlist[i],&TEnemy::collide,this,&TScene::collideEnemy);
    //}
    //for (int i=0; i<pEnemyQlist.size(); i++) {
        //connect(pEnemies[i].get(),&Enemy::dead,pEnemyQlist[i],&TEnemy::indicateDead);
//        connect(protagonist.get(),&Protagonist::posChanged,pEnemyQlist[i],&TEnemy::checkCollide);
        //connect(pEnemyQlist[i],&TEnemy::collide,this,&TScene::collideEnemy);
    //}
}

void TScene::printTiles(const std::vector<std::shared_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        TTile *tile= new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),tiles[i]->getValue(),20,this);
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
    protagonistView = new TProtagonist(protagonist->getXPos(),protagonist->getYPos());
    connect(protagonist.get(),&Protagonist::energyChanged,protagonistView,&TProtagonist::checkState);
    connect(protagonist.get(),&Protagonist::healthChanged,protagonistView,&TProtagonist::checkState);
    this->addItem(protagonistView);
}

void TScene::printEnemies(const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies)
{
    for(unsigned int i=0;i<normalEnemies.size();i++){
        TEnemy * enemy = new TEnemy(normalEnemies[i]->getXPos(),normalEnemies[i]->getYPos(),i,false);
        connect(normalEnemies[i].get(),&Enemy::dead,enemy,&TEnemy::indicateDead);
        connect(enemy,&TEnemy::collide,this,&TScene::collideEnemy);
        normalEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
    for(unsigned int i=0;i<pEnemies.size();i++){
        connect(pEnemies[i].get(),&PEnemy::poisonLevelUpdated,[=]{
           emit poisonTile(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),pEnemies[i].get()->getPoisonLevel());
        });
        TEnemy * enemy = new TEnemy(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),i,true);
        connect(pEnemies[i].get(),&Enemy::dead,enemy,&TEnemy::indicateDead);
        connect(enemy,&TEnemy::collide,this,&TScene::collideEnemy);
        pEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
}

void TScene::printHealthpacks(const std::vector<std::shared_ptr<Tile> > &healthpacks)
{
    for(unsigned int i=0;i<healthpacks.size();i++){
        THealthpack * healthpack = new THealthpack(healthpacks[i]->getXPos(),healthpacks[i]->getYPos());
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

void TScene::redrawState(float poisonLevel)
{
    protagonistView->getPoisoned(poisonLevel);
}

void TScene::collideEnemy(int i, bool isP)
{
    enemyIndex = i;
    isPEnemy = isP;
}

bool TScene::getIsPEnemy() const
{
    return isPEnemy;
}

void TScene::setIsPEnemy(bool value)
{
    isPEnemy = value;
}

int TScene::getEnemyIndex() const
{
    return enemyIndex;
}

void TScene::setEnemyIndex(int value)
{
    enemyIndex = value;
}
