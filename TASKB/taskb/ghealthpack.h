#ifndef GHEALTHPACK_H
#define GHEALTHPACK_H

#include <QWidget>
#include <QGraphicsTextItem>

class GHealthpack : public QGraphicsTextItem
{
public:
    GHealthpack();
    QRectF boundingRect() const;

signals:

};

#endif // GHEALTHPACK_H
