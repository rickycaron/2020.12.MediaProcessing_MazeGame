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
        setBrush(QBrush(QColorConstants::Black));
        qDebug()<<"black";
    }
    setBrush(QBrush(QColorConstants::White));
    setPen(QPen(Qt::DashLine));
}

void TTile::poisonTile()
{
    setBrush(QBrush(QColor(100,100,200)));
}
