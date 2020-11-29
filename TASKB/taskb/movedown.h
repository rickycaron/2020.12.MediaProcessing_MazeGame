#ifndef MOVEDOWN_H
#define MOVEDOWN_H

#include "command.h"

class MoveDown : public Command
{
public:
    explicit MoveDown(Controller *con);
    void excute() const override;
};

#endif // MOVEDOWN_H
