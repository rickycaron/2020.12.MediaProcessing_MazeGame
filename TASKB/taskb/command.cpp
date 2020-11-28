#include "command.h"

Command::Command(Controller *con)
{
    controller = con;
}

Controller *Command::getController() const
{
    return controller;
}
