#include "ttile.h"
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <cmath>

TTile::TTile(int xPos, int yPos, int value, int scale, QObject *parent):QGraphicsRectItem(xPos*scale,yPos*scale,scale,scale)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->value = value;
    this->scale = scale;
    draw();
}

void TTile::draw()
{
    if(std::isinf(value)) //fix inf value
    {
        value=0;
    }
    setPen(QPen(Qt::DashLine));
}

void TTile::poisonTile()
{
    setBrush(QBrush(QColor(100,100,200)));
}

//void TTile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    painter->setPen(QPen(Qt::DashLine));
//    painter->setBrush(QBrush(QColor(100,100,200,pollutedLevel)));

//    if(std::isinf(value)) //fix inf value
//    {
//        //value=0;
//        painter->setBrush(Qt::SolidPattern);
//    }
//    if(!getPassable()){
//        painter->setBrush(Qt::SolidPattern);
//    }
//    painter->drawRect(boundingRect());
//    QGraphicsTextItem::paint(painter,option,widget);
//}

//bool TTile::getPassable() const
//{
//    return passable;
//}

//void TTile::setPassable(bool value)
//{
//    passable = value;
//}

//void TTile::getPolluted(int poisonLevel)
//{
    //QPainter painter;
//    pollutedLevel=poisonLevel;
//    update(boundingRect());
//    QTimer::singleShot(400,this,[=]{
//        to achieve animation
//        clean();
//    });
//}
