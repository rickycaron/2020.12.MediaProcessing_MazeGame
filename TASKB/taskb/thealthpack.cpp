#include "thealthpack.h"

THealthpack::THealthpack(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("H");
    setPos(20*xPos, 20*yPos);
}

QRectF THealthpack::boundingRect() const
{
    return QRectF(0,0,20,20);
}

