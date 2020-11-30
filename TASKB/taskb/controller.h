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
    //void addSceneToView(std::shared_ptr<QGraphicsView> view);
    void addSceneToView(QGraphicsView &view);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack();
    void take();
    void detectEnemy();
<<<<<<< HEAD
    void detectHealthpack();
=======

    std::vector<std::shared_ptr<Tile> > getTiles() const;
    int getRow() const;
    int getCol() const;
    std::shared_ptr<Protagonist> getProtagonist() const;
    std::vector<std::shared_ptr<Tile> > getHealthpacks() const;

>>>>>>> c793e2a1da0b28bb50dd3bad3880aa293f89d105
private:
    TextScene *scene;
    //std::shared_ptr<TextScene> scene;
    std::unique_ptr<World> world;
    int row = 0;
    int col = 0;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;
};

#endif // CONTROLLER_H
