#include "gamewinscene.h"
#include <QGraphicsPixmapItem>

GamewinScene::GamewinScene(QObject *parent):QGraphicsScene(parent)
{
    QPixmap image(":/images/gamewin.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(image.scaled(100, 100));
    addItem(item);
}
