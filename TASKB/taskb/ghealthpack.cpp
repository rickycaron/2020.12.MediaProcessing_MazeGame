#include "ghealthpack.h"

GHealthpack::GHealthpack() : QGraphicsTextItem()
{
    setPlainText("H");
}

QRectF GHealthpack::boundingRect() const
{
    return QRectF(0,0,20,20);
}

