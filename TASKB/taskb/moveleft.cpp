#include "moveleft.h"

MoveLeft::MoveLeft(std::shared_ptr<Controller> con):Command(con)
{
    setName("move left");
}

void MoveLeft::excute() const
{
    getController()->moveLeft();
}
