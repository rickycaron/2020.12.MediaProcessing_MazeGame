#ifndef THEALTHPACK_H
#define THEALTHPACK_H

#include <QWidget>
#include <QGraphicsTextItem>

class THealthpack : public QGraphicsTextItem
{
public:
    THealthpack(int xPos, int yPos, int scale);
    QRectF boundingRect() const;
    bool getIsEmpty() const;
    void setIsEmpty(bool value);
public slots:
    void emptyContent();
private:
    bool isEmpty;
    int scale{1};
};

#endif // THEALTHPACK_H
