#include "gameoverscene.h"
#include <QGraphicsPixmapItem>

GameoverScene::GameoverScene(QObject *parent):QGraphicsScene(parent)
{
    QPixmap image(":/images/gameover.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    item->setPixmap(image.scaled(100, 100));
    addItem(item);
}
