#include "genemy.h"

GEnemy::GEnemy(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("E");
    setPos(20*xPos, 20*yPos);
}

QRectF GEnemy::boundingRect() const
{
    return QRectF(0,0,20,20);
}
