#include "command.h"
#include <QDebug>

//Command::Command(Controller *con)
Command::Command(std::shared_ptr<Controller> con)
{
    controller = con;
    name="default command";
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

QString Command::getName() const
{
    return name;
}

void Command::setName(const QString &value)
{
    name = value;
}
