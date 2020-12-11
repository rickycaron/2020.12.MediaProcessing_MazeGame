#include "xenemy.h"

XEnemy::XEnemy(int xPosition, int yPosition, float strength,int speed,int cols,int rows): Enemy(xPosition, yPosition, strength)
{
    this->speed = speed;
    this->cols =cols;
    this->rows = rows;
}

bool XEnemy::moving()       //enemy randomly moving to nearby tiles
{
    if(cooldown==0){
        flash();
        cooldown=6;
    }
    cooldown--;

    int axis = rand()%2;    //axis=0 or 1
    int sign = rand()%2;    //0= negative 1=positive
    switch (axis) {
    case X:{
        if(sign ==0){
            if(checkBoundary(xPos-speed,yPos)){
                return false;
            }
            xPos=xPos -speed;
            emit posChanged(xPos,yPos);
        }
        else{
            if(checkBoundary(xPos+speed,yPos)){
                return false;
            }
            xPos=xPos +speed;
            emit posChanged(xPos,yPos);
        }
        break ;
        }
    case Y:{
        if(sign ==0){
            if(checkBoundary(xPos,yPos-speed)){
                return false;
            }
            yPos=yPos -speed;
            emit posChanged(xPos,yPos);
        }
        else{
            if(checkBoundary(xPos,yPos+speed)){
                return false;
            }
            yPos=yPos +speed;
            emit posChanged(xPos,yPos);
        }
        break ;
        }
    }
    return true;
}

void XEnemy::flash()
{
    //generate a random position on the map
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_x(0, cols-1);
    std::uniform_int_distribution<int> uniform_y(0, rows-1);

    xPos = uniform_x(e1);
    yPos = uniform_y(e1);
    emit posChanged(xPos,yPos);

}

int XEnemy::getSpeed() const
{
    return speed;
}

void XEnemy::setSpeed(int value)
{
    speed = value;
}

int XEnemy::getCooldown() const
{
    return cooldown;
}

void XEnemy::setCooldown(int value)
{
    cooldown = value;
}

bool XEnemy::checkBoundary(int x, int y)
{
  if(x>cols-1||x<0||y>rows-1||y<0){return true;}
  return false;
}

int XEnemy::useLives()
{
    lives--;
    return lives;
}
