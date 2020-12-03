#include "qpenemy.h"

QPEnemy::QPEnemy(int xPos, int yPos,int scale):QEnemy(xPos,yPos,scale)
{
    QPixmap image(":/images/penemy.png");
    setPixmap(image.scaled(scale, scale));
}
