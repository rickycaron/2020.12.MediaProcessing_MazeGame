#include "ttile.h"
#include <QPainter>

TTile::TTile(int xPos, int yPos):QGraphicsTextItem()
{
    setPlainText(" ");
    setPos(QPointF(20*xPos,20*yPos));
}

QRectF TTile::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void TTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen * mPen = new QPen();
    mPen->setWidth(1);
    mPen->setStyle(Qt::DashLine);
    painter->setPen(*mPen);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter,option,widget);
}
