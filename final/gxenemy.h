#ifndef GXENEMY_H
#define GXENEMY_H

#include"config.h"
#include "genemy.h"
#include<QGraphicsPixmapItem>

class GXEnemy : public GEnemy
{

public:
     GXEnemy(int,int,int,QObject*);
    void resetPos(int,int);
    void setGrave();
private:
     int scale;


};
#endif // GXENEMY_H
