#include "moveup.h"

MoveUp::MoveUp(std::shared_ptr<Controller> con):Command(con)
{

}

void MoveUp::excute() const
{
    getController()->moveUp();
}
