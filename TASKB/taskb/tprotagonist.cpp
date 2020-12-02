#include "tprotagonist.h"
#include <QDebug>
#include <QGraphicsScene>

TProtagonist::TProtagonist(int xPos, int yPos)
{
    QFont myfont;
    myfont.setBold(true);
    setFont(myfont);
    setPlainText("P");
    setPos(QPointF(20*xPos,20*yPos));
}

QRectF TProtagonist::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void TProtagonist::getPoisoned(float poisonLevel)
{
    if(poisonLevel>0){
        setDefaultTextColor(QColorConstants::Blue);
        qDebug()<<"get poisoned, poisonlevel "<<poisonLevel;
    }else{
        setDefaultTextColor(QColorConstants::Black);
    }
}

void TProtagonist::checkState(int value)
{
    if(value<=0){
        setDefaultTextColor(QColorConstants::Red);
    }
}
