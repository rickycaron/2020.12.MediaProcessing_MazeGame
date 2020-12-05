#ifndef QTILE_H
#define QTILE_H

#include<QGraphicsRectItem>

class QTile : public QGraphicsRectItem
{

public:
     QTile(int xPos,int ypos,float value,int scale,QObject *parent);

private:
     int xPos;
     int yPos;
     float value;
     int scale;
     void draw();

};

#endif // QTILE_H
