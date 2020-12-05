#include "qenemy.h"


QEnemy::QEnemy(int xPos, int yPos,int scale,QObject *parent)
{
    x=xPos;
    y=yPos;     //unit of position is folowiing value from model without scale effect
    QPixmap image(":/images/enemy.png");
    setPixmap(image.scaled(scale, scale));
    setPos(x*scale,y*scale);
}

bool QEnemy::collideDetecction(int xPos,int yPos )
{
    if(x==xPos && y==yPos){
        return true;
    }
}
