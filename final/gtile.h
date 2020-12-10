#ifndef GTILE_H
#define GTILE_H

#include<QGraphicsRectItem>

class GTile : public QGraphicsRectItem
{
public:
     GTile(int xPos, int ypos, float value, int scale, QObject *parent);
     void poisonTile();
     void draw();
private:
     int xPos;
     int yPos;
     float value;
     int scale;
};

#endif // GTILE_H
