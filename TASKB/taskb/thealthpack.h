#ifndef THEALTHPACK_H
#define THEALTHPACK_H

#include <QWidget>
#include <QGraphicsTextItem>

class THealthpack : public QGraphicsTextItem
{
public:
    THealthpack(int xPos, int yPos);
    QRectF boundingRect() const;

signals:

};

#endif // THEALTHPACK_H
