#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QGraphicsView>
#include <QObject>
#include "textscene.h"
#include "world.h"
#include "pathfinder.h"

class Controller:public QObject
{
    Q_OBJECT
public:
    Controller(QObject *parent);
    void createScene(QWidget *parent);
    void addSceneToView(QGraphicsView &view);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void attack();
    void take();
    void gotoXY(int x, int y);
    void consumeEnergy();
    void detectEnemy();
    void detectHealthpack();
    bool checkXBoundary(int xPos);
    bool checkYBoundary(int yPos);

    int getRow() const;
    int getCol() const;
    std::shared_ptr<Protagonist> getProtagonist() const;
    std::vector<std::shared_ptr<Tile> > getTiles() const;
    std::vector<std::shared_ptr<Tile> > getHealthpacks() const;
private slots:
    void move();
private:
    TextScene *scene;
    float maxEH;
    int row = 0;
    int col = 0;
    int enemyIndex{-1};
    bool isPEnemy{false};
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> normalEnemies;
    std::vector<std::shared_ptr<PEnemy>> pEnemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;
    std::shared_ptr<Pathfinder> pathfinder;
    QStack<std::shared_ptr<Tile>> path;
};

#endif // CONTROLLER_H
