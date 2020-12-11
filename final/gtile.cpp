#include "gtile.h"
#include<cmath>
#include<QBrush>
#include<QPen>
#include <QDebug>

GTile::GTile(int xPos, int yPos, float value, int scale, QObject *parent):QGraphicsRectItem(xPos*scale,yPos*scale,scale,scale)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->value = value;
    this->scale = scale;
    draw();
}

void GTile::poisonTile()
{
    QColor poisonColor(128,0,128);
    QBrush brush(poisonColor);
    setBrush(brush);
}

void GTile::draw()
{
    if(std::isinf(value)) //fix inf value
    {
        value=0;
    }

//    QColor color(value*255,value*255,value*255);
    QColor color(value*100,value*255,value*100);

//    QBrush* brush = new QBrush(color);
//    setBrush(*brush);
    QBrush brush(color);
    setBrush(brush);
    QPen pen;
    pen.setColor(color);     //set border color for each item same as its color
    setPen(pen);
}
