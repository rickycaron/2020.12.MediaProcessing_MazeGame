#include "command.h"
#include <QDebug>

//Command::Command(Controller *con)
Command::Command(std::shared_ptr<Controller> con)
{
    controller = con;
}

void Command::setDestination(int x, int y)
{
    qDebug()<<x<<y;
}

//Controller *Command::getController() const
std::shared_ptr<Controller> Command::getController() const
{
    return controller;
}
