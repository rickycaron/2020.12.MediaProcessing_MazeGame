#include "qtile.h"
#include<cmath>
#include<QBrush>
#include<QPen>

QTile::QTile(int xPos, int yPos,float value,int scale):QGraphicsRectItem(xPos*scale,yPos*scale,scale,scale)
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

    QColor color(value*255,value*255,value*255);

    QBrush* brush = new QBrush(color);
    setBrush(*brush);
    QPen pen;
    pen.setColor(color);     //set border color for each item same as its color
    setPen(pen);

}
