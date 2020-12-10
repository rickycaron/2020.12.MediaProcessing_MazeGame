#ifndef GHEALTHPACK_H
#define GHEALTHPACK_H

#include<QGraphicsPixmapItem>

class GHealthpack : public QGraphicsPixmapItem
{
public:
     GHealthpack(int xPos,int yPos,int scale,QObject *parent);
     void usedHealthPack();
private:
     int scale;
};

#endif // GHEALTHPACK_H
