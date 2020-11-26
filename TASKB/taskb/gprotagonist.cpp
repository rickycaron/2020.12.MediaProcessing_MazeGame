#include "gprotagonist.h"
#include <QDebug>
#include <QGraphicsScene>

GProtagonist::GProtagonist():QGraphicsTextItem()
{
    setPlainText("P");
    xAnimation = new QPropertyAnimation(this,"x",this);
    yAnimation = new QPropertyAnimation(this,"y",this);
}

QRectF GProtagonist::boundingRect() const
{
    return QRectF(0,0,20,20);
}

qreal GProtagonist::x() const
{
    return m_x;
}

void GProtagonist::moveRight()
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    xAnimation->setEndValue(x()+1);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1000);
    xAnimation->start();
}

void GProtagonist::moveLeft()
{
    xAnimation->stop();
    xAnimation->setStartValue(x());
    xAnimation->setEndValue(x()-1);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(1000);
    xAnimation->start();
}

void GProtagonist::moveUp()
{
    xAnimation->stop();
    yAnimation->setStartValue(y());
    yAnimation->setEndValue(y()-1);
    yAnimation->setEasingCurve(QEasingCurve::Linear);
    yAnimation->setDuration(1000);
    yAnimation->start();
}

void GProtagonist::moveDown()
{
    xAnimation->stop();
    yAnimation->setStartValue(y());
    yAnimation->setEndValue(y()+1);
    yAnimation->setEasingCurve(QEasingCurve::Linear);
    yAnimation->setDuration(1000);
    yAnimation->start();
}

qreal GProtagonist::y() const
{
    return m_y;
}

void GProtagonist::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(20*x,pos().y()));
}

void GProtagonist::setY(qreal y)
{
    m_y = y;
    setPos(QPointF(pos().x(),20*y));
}
