#include "genemy.h"
#include "config.h"

GEnemy::GEnemy(int xPos, int yPos, int scale, QObject *parent)
{
    x=xPos;
    y=yPos;     //unit of position is folowiing value from model without scale effect
    this->scale = scale;
    QPixmap image(ENEMY_IMAGE);
    setPixmap(image.scaled(scale, scale));
    setPos(x*scale,y*scale);
}

void GEnemy::setGrave()
{
    QPixmap image(GRAVE_IMAGE);
    setPixmap(image.scaled(scale, scale));
}

bool GEnemy::collideDetecction(int xPos,int yPos )
{
    if(x==xPos && y==yPos){
        return true;
    }else{
        return false;
    }
}
