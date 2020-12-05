#include "qpenemy.h"

QPEnemy::QPEnemy(int xPos, int yPos,int scale,QObject *parent):QEnemy(xPos,yPos,scale,parent)
{
    QPixmap image(":/images/penemy.png");
    setPixmap(image.scaled(scale, scale));
}
