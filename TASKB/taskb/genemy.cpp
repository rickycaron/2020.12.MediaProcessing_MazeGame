#include "genemy.h"

GEnemy::GEnemy() : QGraphicsTextItem()
{
    setPlainText("E");
}

QRectF GEnemy::boundingRect() const
{
    return QRectF(0,0,20,20);
}
