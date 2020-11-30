#include "gotoxy.h"

GotoXY::GotoXY(std::shared_ptr<Controller> con):Command(con)
{
    setName("go to x y");
}

void GotoXY::excute() const
{
    getController()->gotoXY(xPos,yPos);
}

void GotoXY::setDestination(int x, int y)
{
    xPos = x;
    yPos = y;
}
