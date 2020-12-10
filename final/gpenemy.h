#ifndef GPENEMY_H
#define GPENEMY_H
#include "config.h"
#include "genemy.h"

class GPEnemy : public GEnemy
{
public:
    GPEnemy(int,int,int,QObject *);
    void animationPEnemy();
    void setGrave();

private:
    int scale;
    int imgCurrentIndex =0;
    QVector<QPixmap> img_arr;
};
#endif // GPENEMY_H
