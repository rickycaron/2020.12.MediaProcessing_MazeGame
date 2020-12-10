#include "tscene.h"
#include <QDebug>

TScene::TScene(QObject *parent, const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &normalEnemies, const std::vector<std::shared_ptr<PEnemy> > &pEnemies, const std::vector<std::shared_ptr<Tile> > &healthpacks, int row, int col)
    :QGraphicsScene(parent)
{
    printTiles(tiles);
    printProtagonist(protagonist);
    printEnemies(normalEnemies,pEnemies);
    printHealthpacks(healthpacks);
    connect(protagonist.get(),&Protagonist::posChanged,this,&TScene::redrawPosition);

    for(int i=0; i<normalEnemyQlist.size(); i++){
        connect(normalEnemies[i].get(),&Enemy::dead,normalEnemyQlist[i],&TEnemy::indicateDead);
        connect(protagonist.get(),&Protagonist::posChanged,normalEnemyQlist[i],&TEnemy::checkCollide);
        connect(normalEnemyQlist[i],&TEnemy::collide,this,&TScene::collideEnemy);
    }
    for (int i=0; i<pEnemyQlist.size(); i++) {
        connect(pEnemies[i].get(),&Enemy::dead,pEnemyQlist[i],&TEnemy::indicateDead);
        connect(protagonist.get(),&Protagonist::posChanged,pEnemyQlist[i],&TEnemy::checkCollide);
        connect(pEnemyQlist[i],&TEnemy::collide,this,&TScene::collideEnemy);
        int x = pEnemies[i]->getXPos();
        int y = pEnemies[i]->getYPos();
        for(int n=x-1;n<=x+1;n++){
            for(int m=y-1;m<=y+1;m++){
                if(n>=0&&n<col&&m>=0&&m<row){
                    connect(pEnemies[i].get(),&PEnemy::poisonLevelUpdated,tileQlist[m*col+n],&TTile::getPolluted);
                    connect(pEnemies[i].get(),&PEnemy::dead,tileQlist[m*col+n],&TTile::clean);
                }
            }
        }
    }
}

void TScene::printTiles(const std::vector<std::shared_ptr<Tile>> &tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        TTile *tile;
        if(tiles[i]->getValue()>100){
            tile = new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),false);
        }else{
            tile = new TTile(tiles[i]->getXPos(),tiles[i]->getYPos(),true);
        }
        tileQlist.append(tile);
        this->addItem(tile);
    }
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
        normalEnemyQlist.append(enemy);
        this->addItem(enemy);
    }
    for(unsigned int i=0;i<pEnemies.size();i++){
        TEnemy * enemy = new TEnemy(pEnemies[i]->getXPos(),pEnemies[i]->getYPos(),i,true);
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
