#include "movedown.h"

MoveDown::MoveDown(std::shared_ptr<Controller> con):Command(con)
{

}

void MoveDown::excute() const
{
    getController()->moveDown();
}
