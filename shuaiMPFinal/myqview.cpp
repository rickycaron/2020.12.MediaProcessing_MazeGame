#include "myqview.h"
#include<QtDebug>
MyQView::MyQView(QWidget *parent) : QGraphicsView(parent)
{

}

void MyQView::createScene(const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &enemies,
                          const std::vector<std::shared_ptr<PEnemy> > &penemies,const std::vector<std::shared_ptr<Tile> > &healthpacks,int scale)
{
    this-> scale = scale;
   qScene = new MyQScene(this, tiles, protagonist, enemies,penemies,healthpacks,scale);
   setScene(qScene);
}




void MyQView::keyPressEvent(QKeyEvent *event)
{
//    qDebug()<<"key is pressed1";

    switch (event->key()) {
    case Qt::Key_Up:
        emit keyPressSignal(0);
        break;
    case Qt::Key_Down:
        emit keyPressSignal(1);
        break;
    case Qt::Key_Left:
        emit keyPressSignal(2);
        break;
    case Qt::Key_Right:
        emit keyPressSignal(3);
        break;
    case Qt::Key_T:
        emit keyPressSignal(4);
        break;

    }
    QGraphicsView::keyPressEvent(event);
}
