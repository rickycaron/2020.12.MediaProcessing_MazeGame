#ifndef TENEMY_H
#define TENEMY_H

#include <QWidget>
#include <QGraphicsTextItem>
#include <type_traits>
#include "world.h"

class TEnemy : public QGraphicsTextItem
{
    Q_OBJECT
public:
    TEnemy(int xPos, int yPos, int scale, int enemyType);
    void resetPos(int newX, int newY);
    QRectF boundingRect() const;
public slots:
    void indicateDead();
private:
    int xPos{-1};
    int yPos{-1};
    int scale{1};
    int enemyType{0};
};

#endif // TENEMY_H
