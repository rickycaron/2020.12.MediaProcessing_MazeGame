#include "movedown.h"

MoveDown::MoveDown(std::shared_ptr<Controller> con):Command(con)
{
    setName("move down");
}

void MoveDown::excute() const
{
    getController()->moveDown();
}
