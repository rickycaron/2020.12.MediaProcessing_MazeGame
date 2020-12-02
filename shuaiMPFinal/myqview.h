#ifndef MYQVIEW_H
#define MYQVIEW_H

#include <QGraphicsView>
#include <QObject>
#include"myqscene.h"

class MyQView : public QGraphicsView
{

    Q_OBJECT
public:
     MyQView(QWidget *parent = nullptr);
     void createScene( const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                       const std::vector<std::shared_ptr<Enemy>> &enemies, const std::vector<std::shared_ptr<Tile>> &healthpacks);
     int detectEnemy();
     int detectHealthPack();
     //function of view only


protected:
    void mousePressEvent(QMouseEvent * event);
private:
    MyQScene* qScene;
signals:
    void mouseClickSignal(QPoint point);
};

#endif // MYQVIEW_H


