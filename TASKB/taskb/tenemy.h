#ifndef TENEMY_H
#define TENEMY_H

#include <QWidget>
#include <QGraphicsTextItem>

class TEnemy : public QGraphicsTextItem
{
public:
    TEnemy(int xPos, int yPos);
    QRectF boundingRect() const;
    void indicateDead(bool isDead);

};

#endif // TENEMY_H
