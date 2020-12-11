#include "tenemy.h"
#include <QFont>
#include <QColor>
#include <QDebug>

TEnemy::TEnemy(int x, int y, int i, int scale, bool isP) : QGraphicsTextItem()
{
    xPos = x;
    yPos = y;
    index = i;
    this->scale=scale;
    setPlainText("E");
    setPos(scale*xPos, scale*yPos);
    isPEnemy = isP;
    if(isP){
        QFont myfont;
        myfont.setBold(true);
        setFont(myfont);
        setDefaultTextColor(QColorConstants::Blue);
    }
}

QRectF TEnemy::boundingRect() const
{
    return QRectF(0,0,scale,scale);
}

void TEnemy::indicateDead()
{
    setDefaultTextColor(QColorConstants::Red);
}
