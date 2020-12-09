#include "attack.h"

Attack::Attack(std::shared_ptr<Controller> con):Command(con)
{
    setName("attack");
}

void Attack::excute() const
{
    getController()->attack();
}
