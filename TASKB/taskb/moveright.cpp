#include "moveright.h"

MoveRight::MoveRight(Controller *con):Command(con)
{

}

void MoveRight::excute() const
{
    getController()->moveRight();
}
