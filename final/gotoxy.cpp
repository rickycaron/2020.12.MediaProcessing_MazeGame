#include "gotoxy.h"
#include <QDebug>

GotoXY::GotoXY(std::shared_ptr<Controller> con):Command(con)
{

}

void GotoXY::excute() const
{
    getController()->gotoXY(xPos,yPos);
    //qDebug()<<"I want to go to ("<<xPos<<","<<yPos<<")";
}

void GotoXY::setDestination(int x, int y)
{
    xPos = x;
    yPos = y;
}
