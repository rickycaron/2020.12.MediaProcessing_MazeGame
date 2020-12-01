#ifndef TTILE_H
#define TTILE_H

#include <QWidget>
#include <QGraphicsTextItem>

class TTile : public QGraphicsTextItem
{

public:
    TTile(int xPos, int yPos, bool ispassable);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool getPassable() const;
    void setPassable(bool value);

private:
    bool passable;

};

#endif // TTILE_H
