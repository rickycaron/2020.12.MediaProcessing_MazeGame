#include "qpenemy.h"
#include<QDebug>
QPEnemy::QPEnemy(int xPos, int yPos,int scale,QObject *parent):QEnemy(xPos,yPos,scale,parent)
{
    this->scale = scale;

    //set up animation image array
    for(int i =1;i <=5;i++){
        QString str = QString(PENEMY_IMAGE).arg(i);
        img_arr.push_back(QPixmap(str));
    }
    setPixmap(img_arr[0].scaled(scale, scale));
}

void QPEnemy::animationPEnemy()
{
    if(imgCurrentIndex<3){
        setPixmap(img_arr[imgCurrentIndex].scaled(scale, scale));
        imgCurrentIndex++;
    }
    else{
//        qDebug()<< "test ";
        setPixmap(img_arr[imgCurrentIndex].scaled(scale, scale));
        imgCurrentIndex=0;
    }
}

void QPEnemy::setGrave()
{
    QPixmap image(GRAVE_IMAGE);
    setPixmap(image.scaled(scale, scale));
}
