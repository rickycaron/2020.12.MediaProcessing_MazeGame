#ifndef QHEALTHPACK_H
#define QHEALTHPACK_H

#include <QObject>
#include<QGraphicsPixmapItem>

class QHealthPack : public QGraphicsPixmapItem
{

public:
     QHealthPack(int xPos,int yPos,int scale,QObject *parent);
     void usedHealthPack();
private:
     int scale;

};

#endif // QHEALTHPACK_H
