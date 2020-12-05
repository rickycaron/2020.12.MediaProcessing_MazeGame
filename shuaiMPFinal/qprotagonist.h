#ifndef QPROTAGONIST_H
#define QPROTAGONIST_H
#include "config.h"

#include<QGraphicsPixmapItem>

class QProtagonist : public QGraphicsPixmapItem
{
public:
     QProtagonist(int xPos,int yPos,int scale,QObject *parent);
     void reSetPos(int xPos,int yPos);
     void reSetImg(int);
private:
     int scale;

};

#endif // QPROTAGONIST_H
