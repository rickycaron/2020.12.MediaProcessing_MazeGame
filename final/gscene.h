#ifndef GSCENE_H
#define GSCENE_H
#include "config.h"
#include <QGraphicsScene>
#include <QObject>
#include"model.h"
#include"gtile.h"
#include"genemy.h"
#include"gpenemy.h"
#include"gprotagonist.h"
#include"ghealthpack.h"
#include"world.h"

class GScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &enemies,const std::vector<std::shared_ptr<PEnemy>> &penemies, const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &enemies);
    void printPEnemies(const std::vector<std::shared_ptr<PEnemy>> &penemies);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectEnemy();
    int detectHealthpack();
    void redrawHealthpack(int index);
    void changeProtagonistImage(int);
    void setDeath(int,int);

signals:
void poisonTile(int,int,int);

private:
    int scale=1;
    QList<GTile *> tileQlist;
    GProtagonist *protagonistView;
    QList<GEnemy *> enemyQlist;
    QList<GPEnemy *> penemyQlist;
    QList<GHealthpack *> healthpackQlist;
};


#endif // GSCENE_H
