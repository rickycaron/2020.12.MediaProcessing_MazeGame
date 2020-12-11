#ifndef TTILE_H
#define TTILE_H

#include <QGraphicsRectItem>

class TTile : public QGraphicsRectItem
{
public:
    TTile(int xPos, int yPos, int value, int scale, QObject *parent);
    void draw();
    void poisonTile();
private:
    int xPos;
    int yPos;
    float value;
    int scale;
};

#endif // TTILE_H
