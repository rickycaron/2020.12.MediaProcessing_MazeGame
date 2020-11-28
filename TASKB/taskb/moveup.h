#ifndef MOVEUP_H
#define MOVEUP_H

#include "command.h"

class MoveUp : public Command
{
public:
    explicit MoveUp(Controller *con);
    void excute() const override;
};

#endif // MOVEUP_H
