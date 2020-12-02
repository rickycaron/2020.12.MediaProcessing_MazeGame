#include "qprotagonist.h"
#include<QtDebug>


QProtagonist::QProtagonist(int xPos, int yPos,int scale)
{
    this->scale = scale;
    QPixmap image(":/images/protagonist.png");
    setZValue(1);
    setPixmap(image.scaled(scale, scale));
    setPos(xPos*scale,yPos*scale);
    setFlags(QGraphicsItem::ItemIsMovable);
}

void QProtagonist::reSetPos(int xPos, int yPos)
{
    setPos(xPos*scale,yPos*scale);
    qDebug()<< "position after is" << xPos <<yPos;

}
