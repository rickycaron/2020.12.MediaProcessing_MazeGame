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
//    TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
//              const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks);
    TextScene(QObject *parent, const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
              const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies,
              const std::vector<std::shared_ptr<Tile>> &healthpacks);
    void printTiles(const std::vector<std::shared_ptr<Tile>> &tiles);
    void printProtagonist(const std::shared_ptr<Protagonist> &protagonist);
    void printEnemies(const std::vector<std::shared_ptr<Enemy>> &normalEnemies, const std::vector<std::shared_ptr<PEnemy>> &pEnemies);
    void printHealthpacks(const std::vector<std::shared_ptr<Tile>> &healthpacks);
    int detectHealthpack();
    void redrawHealthpack(int index);
    int getEnemyIndex() const;
    void setEnemyIndex(int value);

    bool getIsPEnemy() const;
    void setIsPEnemy(bool value);

public slots:
    void redrawProtagonist(int xPos, int yPos);
    void collideEnemy(int i, bool isP);
private:
    QList<TTile *> tileQlist;
    TProtagonist *protagonistView;
    QList<TEnemy *> normalEnemyQlist;
    QList<TEnemy *> pEnemyQlist;
    QList<THealthpack *> healthpackQlist;
    int enemyIndex{-1};
    bool isPEnemy{false};
};

#endif // TEXTSCENE_H
