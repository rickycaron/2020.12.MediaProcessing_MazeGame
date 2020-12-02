#include "qenemy.h"


QEnemy::QEnemy(int xPos, int yPos,int scale)
{
    QPixmap image(":/images/enemy.png");
    setPixmap(image.scaled(scale, scale));
     setPos(xPos*scale,yPos*scale);
}

