#ifndef THEALTHPACK_H
#define THEALTHPACK_H

#include <QWidget>
#include <QGraphicsTextItem>

class THealthpack : public QGraphicsTextItem
{
public:
    THealthpack(int xPos, int yPos);
    QRectF boundingRect() const;
    bool getIsEmpty() const;
    void setIsEmpty(bool value);
public slots:
    void emptyContent();
private:
    bool isEmpty;

};

#endif // THEALTHPACK_H
