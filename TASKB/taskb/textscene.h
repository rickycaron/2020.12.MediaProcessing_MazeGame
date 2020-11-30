#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QGraphicsScene>
#include <QList>
#include "world.h"
#include "ttile.h"
#include "tprotagonist.h"
#include "tenemy.h"
#include "thealthpack.h"

class TextScene : public QGraphicsScene
{
public:
    TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &enemies);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectEnemy();
    int detectHealthpack();
    void redrawHealthpack(int index);
public slots:
    void redrawProtagonist(int xPos, int yPos);
private:
    QList<TTile *> tileQlist;
    TProtagonist *protagonistView;
    QList<TEnemy *> enemyQlist;
    QList<THealthpack *> healthpackQlist;
};

#endif // TEXTSCENE_H
