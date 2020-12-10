#ifndef GENEMY_H
#define GENEMY_H

#include<QGraphicsPixmapItem>

class GEnemy : public QGraphicsPixmapItem
{
public:
     GEnemy(int,int,int,QObject *parent);
     void setGrave();
private:
     int x;
     int y;
     int scale;

private slots:
 bool collideDetecction(int,int);
};

#endif // GENEMY_H
