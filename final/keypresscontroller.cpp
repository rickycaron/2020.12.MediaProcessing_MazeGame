#include "keypresscontroller.h"

KeypressController::KeypressController(std::shared_ptr<Controller> con, QObject *parent) : QObject(parent)
{
    controller=con;
    connect(controller->getView(),SIGNAL(keyPressSignal(int)),this,SLOT(on_keyPressSlot(int)));
}

void KeypressController::on_keyPressSlot(int index)
{
    switch (index) {
        case UP:
            controller->moveUp();
            break;
        case DOWN:
            controller->moveDown();
            break;
        case LEFT:
            controller->moveLeft();
            break;
        case RIGHT:
            controller->moveRight();
            break;
        case TAKE:
            controller->take();
            break;
        case ATTACK:
            controller->attack();
            break;
    }
}
