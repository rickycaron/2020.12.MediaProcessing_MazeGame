#ifndef ATTACK_H
#define ATTACK_H

#include "command.h"

class Attack : public Command
{
public:
    explicit Attack(Controller *con);
    void excute() const override;
};

#endif // ATTACK_H
