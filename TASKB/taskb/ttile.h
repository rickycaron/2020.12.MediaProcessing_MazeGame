#ifndef TTILE_H
#define TTILE_H

#include <QWidget>
#include <QGraphicsTextItem>

class TTile : public QGraphicsTextItem
{

public:
    TTile(int xPos, int yPos);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

};

#endif // TTILE_H
