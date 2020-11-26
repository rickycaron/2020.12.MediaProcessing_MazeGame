#ifndef MOVEUP_H
#define MOVEUP_H

#include "command.h"

class MoveUp : public Command
{
public:
    MoveUp();
    void excute() const override;
};

#endif // MOVEUP_H
