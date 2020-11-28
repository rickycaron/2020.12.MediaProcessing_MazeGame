#include "ghealthpack.h"

GHealthpack::GHealthpack(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("H");
    setPos(20*xPos, 20*yPos);
}

QRectF GHealthpack::boundingRect() const
{
    return QRectF(0,0,20,20);
}

