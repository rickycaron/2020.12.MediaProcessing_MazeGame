#include "tenemy.h"

TEnemy::TEnemy(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("E");
    setPos(20*xPos, 20*yPos);
}

QRectF TEnemy::boundingRect() const
{
    return QRectF(0,0,20,20);
}
