#include "attack.h"

Attack::Attack(std::shared_ptr<Controller> con):Command(con)
{

}

void Attack::excute() const
{
    getController()->attack();
}
