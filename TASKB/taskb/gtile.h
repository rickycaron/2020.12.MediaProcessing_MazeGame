#ifndef GTILE_H
#define GTILE_H

#include <QWidget>
#include <QGraphicsTextItem>

class GTile : public QGraphicsTextItem
{

public:
    GTile();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

};

#endif // GTILE_H
