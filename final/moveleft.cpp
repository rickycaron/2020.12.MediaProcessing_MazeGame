#include "moveleft.h"

MoveLeft::MoveLeft(std::shared_ptr<Controller> con):Command(con)
{

}

void MoveLeft::excute() const
{
    getController()->moveLeft();
}
