#include "tenemy.h"
#include <QFont>
#include <QColor>
#include <QDebug>

TEnemy::TEnemy(int x, int y, int i, bool isP) : QGraphicsTextItem()
{
    xPos = x;
    yPos = y;
    index = i;
    setPlainText("E");
    setPos(20*xPos, 20*yPos);
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
    return QRectF(0,0,20,20);
}

void TEnemy::indicateDead()
{
    setDefaultTextColor(QColorConstants::Red);
}
