#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QGraphicsView>
#include "textscene.h"
#include "world.h"

class Controller
{
public:
    Controller();
    void createScene(QWidget *parent);
    void addSceneToView(QGraphicsView &view);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack();
    void detectEnemy();
private:
    TextScene *scene;
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;
};

#endif // CONTROLLER_H
