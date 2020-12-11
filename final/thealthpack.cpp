#include "thealthpack.h"

THealthpack::THealthpack(int xPos, int yPos, int scale) : QGraphicsTextItem()
{
    this->scale=scale;
    setPlainText("H");
    setPos(scale*xPos, scale*yPos);
    setIsEmpty(false);
}

QRectF THealthpack::boundingRect() const
{
    return QRectF(0,0,scale,scale);
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


