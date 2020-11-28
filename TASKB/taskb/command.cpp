#include "command.h"

Command::Command(Controller *con)
{
    controller = con;
    name="default command";
}

Controller *Command::getController() const
{
    return controller;
}

QString Command::getName() const
{
    return name;
}

void Command::setName(const QString &value)
{
    name = value;
}
