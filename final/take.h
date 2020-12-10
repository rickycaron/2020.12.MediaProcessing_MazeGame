#ifndef TAKE_H
#define TAKE_H

#include "command.h"

class Take : public Command
{
public:
    explicit Take(std::shared_ptr<Controller> con);
    void excute() const override;
};

#endif // TAKE_H
