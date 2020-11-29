#include "moveright.h"

MoveRight::MoveRight(Controller *con):Command(con)
{
    setName("move right");
}

void MoveRight::excute() const
{
    getController()->moveRight();
}
