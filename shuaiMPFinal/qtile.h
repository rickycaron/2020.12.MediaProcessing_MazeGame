#ifndef QTILE_H
#define QTILE_H

#include<QGraphicsRectItem>

class QTile : public QGraphicsRectItem
{

public:
     QTile(int xPos,int ypos,float value,int scale,QObject *parent);
     void poisonTile();
     void draw();
private:
     int xPos;
     int yPos;
     float value;
     int scale;


};

#endif // QTILE_H
