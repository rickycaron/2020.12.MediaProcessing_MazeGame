#include "tprotagonist.h"
#include <QDebug>
#include <QGraphicsScene>

TProtagonist::TProtagonist(int xPos, int yPos)
{
    setPlainText("P");
//    xAnimation = new QPropertyAnimation(this,"x",this);
//    yAnimation = new QPropertyAnimation(this,"y",this);
    setPos(QPointF(20*xPos,20*yPos));
}

QRectF TProtagonist::boundingRect() const
{
    return QRectF(0,0,20,20);
}

void TProtagonist::getPoisoned()
{
    setDefaultTextColor(QColorConstants::Blue);
}

//void TProtagonist::moveRight()
//{
//    xAnimation->stop();
//    xAnimation->setStartValue(x());
//    xAnimation->setEndValue(x()+1);
//    xAnimation->setEasingCurve(QEasingCurve::Linear);
//    xAnimation->setDuration(500);
//    xAnimation->start();
//}

//void TProtagonist::moveLeft()
//{
//    xAnimation->stop();
//    xAnimation->setStartValue(x());
//    xAnimation->setEndValue(x()-1);
//    xAnimation->setEasingCurve(QEasingCurve::Linear);
//    xAnimation->setDuration(500);
//    xAnimation->start();
//}

//void TProtagonist::moveUp()
//{
//    xAnimation->stop();
//    yAnimation->setStartValue(y());
//    yAnimation->setEndValue(y()-1);
//    yAnimation->setEasingCurve(QEasingCurve::Linear);
//    yAnimation->setDuration(500);
//    yAnimation->start();
//}

//void TProtagonist::moveDown()
//{
//    xAnimation->stop();
//    yAnimation->setStartValue(y());
//    yAnimation->setEndValue(y()+1);
//    yAnimation->setEasingCurve(QEasingCurve::Linear);
//    yAnimation->setDuration(500);
//    yAnimation->start();
//}

//qreal TProtagonist::x() const
//{
//    return m_x;
//}

//qreal TProtagonist::y() const
//{
//    return m_y;
//}

//void TProtagonist::setX(qreal x)
//{
//    m_x = x;
//    setPos(QPointF(20*x,pos().y()));
//}

//void TProtagonist::setY(qreal y)
//{
//    m_y = y;
//    setPos(QPointF(pos().x(),20*y));
//}
