#ifndef MOVELEFT_H
#define MOVELEFT_H

#include "command.h"

class MoveLeft : public Command
{
public:
    explicit MoveLeft(Controller *con);
    void excute() const override;
};

#endif // MOVELEFT_H
