#include "gxenemy.h"
#include<QDebug>


GXEnemy::GXEnemy(int xPos, int yPos,int scale,QObject *parent):GEnemy(xPos,yPos,scale,parent)
{
    this->scale=scale;
    QPixmap image(XENEMY_IMAGE);
    setPixmap(image.scaled(scale, scale));
    setZValue(3);
    setPos(xPos*scale,yPos*scale);
}

void GXEnemy::resetPos(int newX, int newY)
{
    qDebug()<<"position of enemy is changed";
    setPos(newX*scale,newY*scale);
}
void GXEnemy::setGrave()
{
    QPixmap image(GRAVE_IMAGE);
    setPixmap(image.scaled(scale, scale));
}
