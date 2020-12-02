#ifndef TTILE_H
#define TTILE_H

#include <QWidget>
#include <QGraphicsTextItem>

class TTile : public QGraphicsTextItem
{
    Q_OBJECT
public:
    TTile(int xPos, int yPos, bool ispassable);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool getPassable() const;
    void setPassable(bool value);
public slots:
    void getPolluted(int poisonLevel);
private:
    bool passable;

};

#endif // TTILE_H
