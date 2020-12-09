#include "thealthpack.h"

THealthpack::THealthpack(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("H");
    setPos(20*xPos, 20*yPos);
    setIsEmpty(false);
}

QRectF THealthpack::boundingRect() const
{
    return QRectF(0,0,20,20);
}

bool THealthpack::getIsEmpty() const
{
    return isEmpty;
}

void THealthpack::setIsEmpty(bool value)
{
    isEmpty = value;
}

void THealthpack::emptyContent()
{
    setPlainText(" ");
    setIsEmpty(true);
}


