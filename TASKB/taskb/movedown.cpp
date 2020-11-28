#include "movedown.h"

MoveDown::MoveDown(Controller *con):Command(con)
{
    setName("move down");
}

void MoveDown::excute() const
{
    getController()->moveDown();
}
