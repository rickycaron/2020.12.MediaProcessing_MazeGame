#ifndef GVIEW_H
#define GVIEW_H
#include <QGraphicsView>
#include <QObject>
#include<QKeyEvent>
#include "gscene.h"

class GView : public QGraphicsView
{
    Q_OBJECT
public:
     GView(QWidget *parent);
     void createScene( const std::vector<std::shared_ptr<Tile>> &tiles, const std::shared_ptr<Protagonist> &protagonist,
                       const std::vector<std::shared_ptr<Enemy>> &enemies,const std::vector<std::shared_ptr<PEnemy>> &penemies, const std::vector<std::shared_ptr<Tile>> &healthpacks,int scale);
     int detectEnemy();
     GScene* getCurrentScene();
//     int detectHealthPack();
//     function of view only
 signals:
    void mouseClickSignal(QPoint point);
    void keyPressSignal(int index);

private:
    int scale;
    GScene* qScene;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // GVIEW_H
