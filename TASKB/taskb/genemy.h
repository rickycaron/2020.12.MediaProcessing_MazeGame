#ifndef GENEMY_H
#define GENEMY_H

#include <QWidget>
#include <QGraphicsTextItem>

class GEnemy : public QGraphicsTextItem
{
public:
    GEnemy(int xPos, int yPos);
    QRectF boundingRect() const;

signals:

};

#endif // GENEMY_H
