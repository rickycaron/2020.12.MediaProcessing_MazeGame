#include "gprotagonist.h"
#include<QtDebug>

GProtagonist::GProtagonist(int xPos, int yPos, int scale, QObject *parent)
{
    this->scale = scale;
    QPixmap image(PROTAGONIST_DOWN_IMAGE);
    setZValue(1);
    setPixmap(image.scaled(scale, scale));
    setPos(xPos*scale,yPos*scale);
    setFlags(QGraphicsItem::ItemIsMovable);
}

void GProtagonist::reSetPos(int xPos, int yPos)
{
    setPos(xPos*scale,yPos*scale);
//    qDebug()<< "position after is" << xPos <<yPos;

}

void GProtagonist::reSetImg(int index)
{

    switch (index) {
    case UP:{
        QPixmap image(PROTAGONIST_UP_IMAGE);
        setPixmap(image.scaled(scale, scale));
        break;
    }
    case DOWN:{
        QPixmap image(PROTAGONIST_DOWN_IMAGE);
        setPixmap(image.scaled(scale, scale));
        break;
    }
    case LEFT:{ QPixmap image(PROTAGONIST_LEFT_IMAGE);
        setPixmap(image.scaled(scale, scale));
        break;
    }
    case RIGHT:{
        QPixmap image(PROTAGONIST_RIGHT_IMAGE);
        setPixmap(image.scaled(scale, scale));
        break;
    }

   }

}
