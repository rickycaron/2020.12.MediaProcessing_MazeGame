#ifndef MYQSCENE_H
#define MYQSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include"model.h"
#include"qtile.h"
#include"qenemy.h"
#include"qpenemy.h"
#include"qprotagonist.h"
#include"qhealthpack.h"


class MyQScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MyQScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &enemies,const std::vector<std::shared_ptr<PEnemy>> &penemies, const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &enemies);
    void printPEnemies(const std::vector<std::shared_ptr<PEnemy>> &penemies);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectEnemy();
    int detectHealthpack();
    void redrawHealthpack(int index);
public slots:
    void redrawProtagonist(int xPos, int yPos);
private:
    int scale=1;
QList<QTile *> tileQlist;
QProtagonist *protagonistView;
QList<QEnemy *> enemyQlist;
QList<QPEnemy *> penemyQlist;
QList<QHealthPack *> healthpackQlist;
};

#endif // MYQSCENE_H




