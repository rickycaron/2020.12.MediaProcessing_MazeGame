#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QGraphicsView>
#include "textscene.h"
#include "world.h"
#include "pathfinder.h"

class Controller
{
public:
    Controller();
    void createScene(QWidget *parent);
    //void addSceneToView(std::shared_ptr<QGraphicsView> view);
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

private:
    TextScene *scene;
    float maxEH;
    int row = 0;
    int col = 0;
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;
    std::shared_ptr<Pathfinder> pathfinder;
};

#endif // CONTROLLER_H
