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
    TEnemy(int x, int y, int i, int scale, bool isP);
    QRectF boundingRect() const;
public slots:
    void indicateDead();
    void checkCollide(int x, int y){if(xPos==x&&yPos==y){emit collide(index, isPEnemy);}}
signals:
    void collide(int index, bool isP);
private:
    int xPos;
    int yPos;
    int index;
    int scale;
    bool isPEnemy;
};

#endif // TENEMY_H
