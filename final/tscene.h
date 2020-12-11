#ifndef TSCENE_H
#define TSCENE_H
#include <QGraphicsScene>
#include <QList>
#include "world.h"
#include "ttile.h"
#include "tprotagonist.h"
#include "tenemy.h"
#include "thealthpack.h"

class TScene : public QGraphicsScene
{
public:
    TScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies,
              const std::vector<std::shared_ptr<Tile>> &healthpacks, int row, int col);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectHealthpack();
    void redrawHealthpack(int index);
    void redrawState(float poisonLevel);
    int getEnemyIndex() const;
    void setEnemyIndex(int value);

    bool getIsPEnemy() const;
    void setIsPEnemy(bool value);
signals:
    void poisonTile(int,int,int);

public slots:
    void redrawPosition(int xPos, int yPos);
    void collideEnemy(int i, bool isP);
private:
    int row;
    int col;
    QList<TTile *> tileQlist;
    TProtagonist *protagonistView;
    QList<TEnemy *> normalEnemyQlist;
    QList<TEnemy *> pEnemyQlist;
    QList<THealthpack *> healthpackQlist;
    int enemyIndex{-1};
    bool isPEnemy{false};
};

#endif // TSCENE_H
