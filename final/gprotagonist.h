#ifndef GPROTAGONIST_H
#define GPROTAGONIST_H

#include "config.h"
#include<QGraphicsPixmapItem>

class GProtagonist : public QGraphicsPixmapItem
{
public:
     GProtagonist(int xPos,int yPos,int scale,QObject *parent);
     void reSetPos(int xPos,int yPos);
     void reSetImg(int);
     void attack();
private:
     int scale;
};

#endif // GPROTAGONIST_H
