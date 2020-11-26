#include "gprotagonist.h"

GProtagonist::GProtagonist() : QGraphicsTextItem()
{
    setPlainText("P");
}

QRectF GProtagonist::boundingRect() const
{
    return QRectF(0,0,20,20);
}
