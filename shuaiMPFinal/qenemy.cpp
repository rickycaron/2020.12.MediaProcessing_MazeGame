#include "qenemy.h"
#include "config.h"

QEnemy::QEnemy(int xPos, int yPos,int scale,QObject *parent)
{
    x=xPos;
    y=yPos;     //unit of position is folowiing value from model without scale effect
    this->scale = scale;
    QPixmap image(ENEMY_IMAGE);
    setPixmap(image.scaled(scale, scale));
    setPos(x*scale,y*scale);
}

void QEnemy::setGrave()
{
    QPixmap image(GRAVE_IMAGE);
    setPixmap(image.scaled(scale, scale));
}

bool QEnemy::collideDetecction(int xPos,int yPos )
{
    if(x==xPos && y==yPos){
        return true;
    }
}
