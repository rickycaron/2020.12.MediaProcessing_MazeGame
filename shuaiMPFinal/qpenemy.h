#ifndef QPENEMY_H
#define QPENEMY_H

#include "qenemy.h"
#include "config.h"
class QPEnemy : public QEnemy
{
public:
    QPEnemy(int,int,int,QObject *);
    void animationPEnemy();
private:
    int scale;
    int imgCurrentIndex =0;
   QVector<QPixmap> img_arr;
};

#endif // QPENEMY_H
