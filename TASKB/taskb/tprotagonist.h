#ifndef TPROTAGONIST_H
#define TPROTAGONIST_H

#include <QWidget>
#include <QObject>
#include <QGraphicsTextItem>
#include <QPropertyAnimation>

class TProtagonist : public QGraphicsTextItem
{
    Q_OBJECT
public:
    TProtagonist(int xPos, int yPos);
    QRectF boundingRect() const;
    void getPoisoned(float poisonLevel);
public slots:
    void checkState(int value);
};

#endif // TPROTAGONIST_H
