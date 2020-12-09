#ifndef POINT_H
#define POINT_H
#include <iostream>

class Point
{
public:
    Point(int,int);
    Point();
    int getXpos() const;
    int getYpos() const;
    void setPoint(const int x, const int y);
    void show();

private:
    int xpos;
    int ypos;
};

#endif // POINT_H
