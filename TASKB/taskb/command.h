#ifndef COMMAND_H
#define COMMAND_H
#include "controller.h"

class Command
{
public:
    explicit Command(Controller *con);
    virtual void excute() const = 0;
    Controller *getController() const;

private:
    Controller *controller;
};

#endif // COMMAND_H
