#include "qprotagonist.h"



QProtagonist::QProtagonist(int xPos, int yPos,int scale)
{
    QPixmap image(":/images/protagonist.png");
    setPixmap(image.scaled(scale, scale));
    setPos(xPos*scale,yPos*scale);
    setFlags(QGraphicsItem::ItemIsMovable);
}
