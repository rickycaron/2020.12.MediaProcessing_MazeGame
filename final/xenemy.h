#ifndef XENEMY_H
#define XENEMY_H

#include"world.h"
#include <random>
#include"config.h"
class XEnemy : public Enemy
{
    Q_OBJECT
public:
    XEnemy(int,int,float,int,int,int);
    ~XEnemy() override = default;
    bool moving();  //Automatically moving based on speed
    void flash();   //Excuting flash skill after cd
    int getSpeed() const;
    void setSpeed(int value);
    int getCooldown() const;
    void setCooldown(int value);
    bool checkBoundary(int,int);
    int useLives();
signals:
    void posChanged(int,int);

private:
    int cols;
    int rows;
    int speed;  // how many tiles for each step
    int cooldown=6; //cd time in default
    int lives =5;

};

#endif // XENEMY_H
