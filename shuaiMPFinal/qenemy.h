#ifndef QENEMY_H
#define QENEMY_H

#include<QGraphicsPixmapItem>
class QEnemy : public QGraphicsPixmapItem
{

public:
     QEnemy(int,int,int,QObject*);
     void setGrave();
private:
     int x;
     int y;
     int scale;

private slots:
 bool collideDetecction(int,int);

};
#endif // QENEMY_H
