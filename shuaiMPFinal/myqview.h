#ifndef MYQVIEW_H
#define MYQVIEW_H

#include <QGraphicsView>
#include <QObject>
#include"myqscene.h"
#include<QKeyEvent>
class MyQView : public QGraphicsView
{

    Q_OBJECT
public:
     MyQView(QWidget *parent = nullptr);
     void createScene( const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                       const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale);
     int detectEnemy();
     int detectHealthPack();
     //function of view only
 signals:
    void mouseClickSignal(QPoint point);
    void keyPressSignal(int index);

private:
    int scale;
    MyQScene* qScene;


    // QWidget interface


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MYQVIEW_H


