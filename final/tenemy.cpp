#include "tenemy.h"
#include <QFont>
#include <QColor>
#include <QDebug>

TEnemy::TEnemy(int xPos, int yPos, int scale, int enemyType) : QGraphicsTextItem()
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->scale=scale;
    setPlainText("E");
    setPos(scale*xPos, scale*yPos);
    this->enemyType = enemyType;

    QFont myfont;
    switch (this->enemyType) {
    case 1:
        myfont.setBold(true);
        setFont(myfont);
        setDefaultTextColor(QColorConstants::Blue);
        break;
    case 2:
        myfont.setBold(true);
        setFont(myfont);
        setDefaultTextColor(QColorConstants::Green);
        setPlainText("X");
        break;
    }
}

void TEnemy::resetPos(int newX, int newY)
{
    setPos(newX*scale,newY*scale);
}

QRectF TEnemy::boundingRect() const
{
    return QRectF(0,0,scale,scale);
}

void TEnemy::indicateDead()
{
    setDefaultTextColor(QColorConstants::Red);
}
