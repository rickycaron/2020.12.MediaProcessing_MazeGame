#ifndef QPROTAGONIST_H
#define QPROTAGONIST_H

#include<QGraphicsPixmapItem>

class QProtagonist : public QGraphicsPixmapItem
{
public:
     QProtagonist(int xPos,int yPos,int scale,QObject *parent);
     void reSetPos(int xPos,int yPos);
private:
     int scale;

};

#endif // QPROTAGONIST_H
