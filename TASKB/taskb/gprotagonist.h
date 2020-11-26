#ifndef GPROTAGONIST_H
#define GPROTAGONIST_H

#include <QWidget>
#include <QGraphicsTextItem>

class GProtagonist : public QGraphicsTextItem
{
public:
    GProtagonist();
    QRectF boundingRect() const;

signals:

};

#endif // GPROTAGONIST_H
