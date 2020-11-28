#ifndef TEXTSCENE_H
#define TEXTSCENE_H

#include <QGraphicsScene>
#include <QList>
#include "world.h"
#include "gtile.h"
#include "gprotagonist.h"
#include "genemy.h"
#include "ghealthpack.h"

class TextScene : public QGraphicsScene
{
public:
    TextScene(QObject *parent, const std::vector<std::unique_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::unique_ptr<Enemy>> &enemies, const std::vector<std::unique_ptr<Tile>> &healthpacks);
    void printTiles(const std::vector<std::unique_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::unique_ptr<Enemy>> &enemies);
    void printHealthpacks(const std::vector<std::unique_ptr<Tile>> &healthpacks);
public slots:
    void redrawProtagonist(int xPos, int yPos);
private:
    QList<GTile *> tileQlist;
    GProtagonist *protagonistView;
    QList<GEnemy *> enemyQlist;
    QList<GHealthpack *> healthpackQlist;
};

#endif // TEXTSCENE_H
