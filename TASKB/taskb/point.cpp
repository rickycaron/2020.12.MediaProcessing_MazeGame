#include "point.h"

Point::Point(int x, int y)
{
   xpos=x;
   ypos=y;
}

Point::Point()
{
    xpos=0;
    ypos=0;
}

int Point::getXpos() const
{
    return xpos;
}

int Point::getYpos() const
{
    return ypos;
}

void Point::setPoint(int x, int y)
{
    xpos=x;
    ypos=y;
}
