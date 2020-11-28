#include "moveup.h"

MoveUp::MoveUp(Controller *con):Command(con)
{

}

void MoveUp::excute() const
{
    getController()->moveUp();
}
