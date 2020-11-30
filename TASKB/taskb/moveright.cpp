#include "moveright.h"

MoveRight::MoveRight(std::shared_ptr<Controller> con):Command(con)
{
    setName("move right");
}

void MoveRight::excute() const
{
    getController()->moveRight();
}
