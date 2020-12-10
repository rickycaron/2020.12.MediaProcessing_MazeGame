#include "gpenemy.h"
#include<QDebug>

GPEnemy::GPEnemy(int xPos, int yPos, int scale, QObject *parent):GEnemy(xPos,yPos,scale,parent)
{
    this->scale = scale;

    //set up animation image array
    for(int i =1;i <=5;i++){
        QString str = QString(PENEMY_IMAGE).arg(i);
        img_arr.push_back(QPixmap(str));
    }
    setPixmap(img_arr[0].scaled(scale, scale));
}

void GPEnemy::animationPEnemy()
{
    if(imgCurrentIndex<3){
        setPixmap(img_arr[imgCurrentIndex].scaled(scale, scale));
        imgCurrentIndex++;
    }
    else{
        setPixmap(img_arr[imgCurrentIndex].scaled(scale, scale));
        imgCurrentIndex=0;
    }
}

void GPEnemy::setGrave()
{
    QPixmap image(GRAVE_IMAGE);
    setPixmap(image.scaled(scale, scale));
}
