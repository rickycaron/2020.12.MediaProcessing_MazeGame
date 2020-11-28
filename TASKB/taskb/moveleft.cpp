#include "moveleft.h"

MoveLeft::MoveLeft(Controller *con):Command(con)
{

}

void MoveLeft::excute() const
{
    getController()->moveLeft();
}
