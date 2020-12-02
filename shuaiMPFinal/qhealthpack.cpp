#include "qhealthpack.h"



QHealthPack::QHealthPack(int xPos, int yPos,int scale)
{
    QPixmap image(":/images/healthPack.png");
    setPixmap(image.scaled(scale, scale));
     setPos(xPos*scale,yPos*scale);
}
