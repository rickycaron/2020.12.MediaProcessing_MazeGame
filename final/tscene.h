#ifndef TSCENE_H
#define TSCENE_H
#include <QGraphicsScene>
#include <QList>
#include "world.h"
#include "ttile.h"
#include "tprotagonist.h"
#include "tenemy.h"
#include "thealthpack.h"
#include "xenemy.h"

class TScene : public QGraphicsScene
{
    Q_OBJECT
public:
    TScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies,
              const std::vector<std::shared_ptr<Tile>> &healthpacks, int scale, int row, int col);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies);
    void printXEnemy(const std::shared_ptr<XEnemy> &xEnemy);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectHealthpack();
    void redrawHealthpack(int index);
    void redrawPoisonedState();
    void setTilePoison(int index);

signals:
    void poisonTile(int,int,int);

public slots:
    void redrawPosition(int xPos, int yPos);
    //void collideEnemy(int i, int enemyType);
private:
    int row;
    int col;
    int scale{1};
    QList<TTile *> tileQlist;
    TProtagonist *protagonistView;
    TEnemy* tXEnemyView;
    QList<TEnemy *> normalEnemyQlist;
    QList<TEnemy *> pEnemyQlist;
    QList<THealthpack *> healthpackQlist;
};

#endif // TSCENE_H
