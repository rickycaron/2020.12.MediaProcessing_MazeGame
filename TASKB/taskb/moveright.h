#ifndef MOVERIGHT_H
#define MOVERIGHT_H

#include "command.h"

class MoveRight : public Command
{
public:
    explicit MoveRight(std::shared_ptr<Controller> con);
    void excute() const override;
};

#endif // MOVERIGHT_H
