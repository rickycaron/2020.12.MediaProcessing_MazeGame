#include "movedown.h"

MoveDown::MoveDown(Controller *con):Command(con)
{

}

void MoveDown::excute() const
{
    getController()->moveDown();
}
