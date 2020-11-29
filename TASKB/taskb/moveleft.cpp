#include "moveleft.h"

MoveLeft::MoveLeft(Controller *con):Command(con)
{
    setName("move left");
}

void MoveLeft::excute() const
{
    getController()->moveLeft();
}
