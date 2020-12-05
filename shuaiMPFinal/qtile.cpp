#include "qtile.h"
#include<cmath>
#include<QBrush>
#include<QPen>

QTile::QTile(int xPos, int yPos,float value,int scale,QObject *parent):QGraphicsRectItem(xPos*scale,yPos*scale,scale,scale)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->value = value;
    this->scale = scale;
    draw();
}

void QTile::draw()
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
