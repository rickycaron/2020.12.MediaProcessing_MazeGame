#ifndef GENEMY_H
#define GENEMY_H

#include <QWidget>
#include <QGraphicsTextItem>

class GEnemy : public QGraphicsTextItem
{
public:
    GEnemy();
    QRectF boundingRect() const;

signals:

};

#endif // GENEMY_H
