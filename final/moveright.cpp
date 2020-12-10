#include "moveright.h"

MoveRight::MoveRight(std::shared_ptr<Controller> con):Command(con)
{

}

void MoveRight::excute() const
{
    getController()->moveRight();
}
