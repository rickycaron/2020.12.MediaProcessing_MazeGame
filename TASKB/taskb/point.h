#ifndef POINT_H
#define POINT_H


class Point
{
public:
    Point(int,int);
    Point();

    int getXpos() const;
    int getYpos() const;
    void setPoint(const int x, const int y);

private:
    int xpos;
    int ypos;
};

#endif // POINT_H
