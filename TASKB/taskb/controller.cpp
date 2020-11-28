#include "controller.h"
#include <QDebug>

Controller::Controller(std::shared_ptr<Protagonist> newProtagonist):protagonist{newProtagonist}
{
}

void Controller::moveRight()
{
    protagonist->setXPos(protagonist->getXPos()+1);
    qDebug()<<"move right";
}

void Controller::moveLeft()
{
    protagonist->setXPos(protagonist->getXPos()-1);
    qDebug()<<"move left";
}

void Controller::moveUp()
{
    protagonist->setYPos(protagonist->getYPos()-1);
    qDebug()<<"move up";
}

void Controller::moveDown()
{
    protagonist->setYPos(protagonist->getYPos()+1);
    qDebug()<<"move down";
}
