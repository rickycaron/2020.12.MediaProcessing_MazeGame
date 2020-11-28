#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QGraphicsScene>
#include "world.h"

class Controller
{
public:
    Controller(std::shared_ptr<Protagonist> newProtagonist);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
private:
    std::shared_ptr<Protagonist> protagonist;
};

#endif // CONTROLLER_H
