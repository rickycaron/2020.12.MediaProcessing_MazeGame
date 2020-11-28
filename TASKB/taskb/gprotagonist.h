#ifndef GPROTAGONIST_H
#define GPROTAGONIST_H

#include <QWidget>
#include <QObject>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

class GProtagonist : public QGraphicsTextItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    GProtagonist(int xPos, int yPos);
    QRectF boundingRect() const;
    qreal x() const;
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    qreal y() const;

public slots:
    void setX(qreal x);

    void setY(qreal y);

private:
    QPropertyAnimation *xAnimation;
    QPropertyAnimation *yAnimation;
    qreal m_x;

    qreal m_y;

signals:

};

#endif // GPROTAGONIST_H
