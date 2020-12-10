#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <memory>
#include "controller.h"

class Command
{
public:
    explicit Command(std::shared_ptr<Controller> con);
    virtual void excute() const = 0;
    virtual void setDestination(int x, int y);
    std::shared_ptr<Controller> getController() const;

private:
    std::shared_ptr<Controller> controller;
};

#endif // COMMAND_H
