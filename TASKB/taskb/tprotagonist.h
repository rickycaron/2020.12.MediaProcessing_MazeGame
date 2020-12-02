#ifndef TPROTAGONIST_H
#define TPROTAGONIST_H

#include <QWidget>
#include <QObject>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

class TProtagonist : public QGraphicsTextItem
{
    Q_OBJECT
//    Q_PROPERTY(qreal x READ x WRITE setX)
//    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    TProtagonist(int xPos, int yPos);
    QRectF boundingRect() const;
//    void moveRight();
//    void moveLeft();
//    void moveUp();
//    void moveDown();
//    qreal x() const;
//    qreal y() const;

public slots:
    void getPoisoned();
//    void setX(qreal x);
//    void setY(qreal y);

//private:
//    QPropertyAnimation *xAnimation;
//    QPropertyAnimation *yAnimation;
//    qreal m_x;
//    qreal m_y;

};

#endif // TPROTAGONIST_H
