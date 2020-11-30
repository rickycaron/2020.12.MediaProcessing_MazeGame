#include "tenemy.h"
#include <QFont>
#include <QColor>

TEnemy::TEnemy(int xPos, int yPos) : QGraphicsTextItem()
{
    setPlainText("E");
    setPos(20*xPos, 20*yPos);
}

QRectF TEnemy::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void TEnemy::indicateDead()
{
    setDefaultTextColor(QColorConstants::Red);
}
