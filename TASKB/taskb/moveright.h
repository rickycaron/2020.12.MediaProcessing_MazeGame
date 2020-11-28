#ifndef MOVERIGHT_H
#define MOVERIGHT_H

#include "command.h"

class MoveRight : public Command
{
public:
    explicit MoveRight(Controller *con);
    void excute() const override;
};

#endif // MOVERIGHT_H
