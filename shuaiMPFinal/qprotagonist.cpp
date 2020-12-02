#include "qprotagonist.h"



QProtagonist::QProtagonist(int xPos, int yPos,int scale)
{
    this->scale = scale;
    QPixmap image(":/images/protagonist.png");
    setPixmap(image.scaled(scale, scale));
    setPos(xPos*scale,yPos*scale);
    setFlags(QGraphicsItem::ItemIsMovable);
}

void QProtagonist::reSetPos(int xPos, int yPos)
{
    setPos(xPos*scale,yPos*scale);
}
