#ifndef QENEMY_H
#define QENEMY_H

#include<QGraphicsPixmapItem>
class QEnemy : public QGraphicsPixmapItem
{

public:
     QEnemy(int,int,int);
private:
     int x;
     int y;
private slots:
 bool collideDetecction(int,int);

};
#endif // QENEMY_H
