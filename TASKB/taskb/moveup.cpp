#include "moveup.h"

MoveUp::MoveUp(std::shared_ptr<Controller> con):Command(con)
{
    setName("move up");
}

void MoveUp::excute() const
{
    getController()->moveUp();
}
