#include "ttile.h"
#include <QPainter>
#include <QDebug>

TTile::TTile(int xPos, int yPos, bool ispassable):QGraphicsTextItem()
{
    setPlainText(" ");
    setPos(QPointF(20*xPos,20*yPos));
    setPassable(ispassable);
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
    painter->setBrush(QBrush(QColor(100,100,100,pollutedLevel)));
    if(!getPassable()){
        painter->setBrush(Qt::SolidPattern);
    }
    painter->drawRect(boundingRect());
    delete mPen;
    QGraphicsTextItem::paint(painter,option,widget);
}

bool TTile::getPassable() const
{
    return passable;
}

void TTile::setPassable(bool value)
{
    passable = value;
}

void TTile::getPolluted(int poisonLevel)
{
    //QPainter painter;
    pollutedLevel=poisonLevel;
    update(boundingRect());
}

void TTile::clean()
{
    pollutedLevel=0;
    update(boundingRect());
}
