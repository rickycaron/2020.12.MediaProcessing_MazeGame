#include "qhealthpack.h"



QHealthPack::QHealthPack(int xPos, int yPos,int scale,QObject *parent)
{
    this->scale = scale;
    QPixmap image(":/images/healthPack.png");
    setPixmap(image.scaled(scale, scale));
    setPos(xPos*scale,yPos*scale);
}

void QHealthPack::usedHealthPack()
{
    //empty bottle will be used later
    QPixmap image(":/images/healthPack.png");
    setPixmap(image.scaled(scale/200, scale/200));
}
