#include "moveup.h"

MoveUp::MoveUp(Controller *con):Command(con)
{
    setName("move up");
}

void MoveUp::excute() const
{
    getController()->moveUp();
}
