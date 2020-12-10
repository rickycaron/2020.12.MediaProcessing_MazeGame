#include "take.h"

Take::Take(std::shared_ptr<Controller> con):Command(con)
{

}

void Take::excute() const
{
    getController()->take();
}
