#include "gtile.h"
#include <QPainter>

GTile::GTile():QGraphicsTextItem()
{
    setPlainText(" ");
}

QRectF GTile::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void GTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen * mPen = new QPen();
    mPen->setWidth(1);
    mPen->setStyle(Qt::DashLine);
    painter->setPen(*mPen);
    painter->drawRect(boundingRect());
    QGraphicsTextItem::paint(painter,option,widget);
}
