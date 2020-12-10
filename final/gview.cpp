#include "gview.h"
#include<QtDebug>

GView::GView(QWidget *parent) : QGraphicsView(parent)
{

}

void GView::createScene(const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &enemies,
                          const std::vector<std::shared_ptr<PEnemy> > &penemies,const std::vector<std::shared_ptr<Tile> > &healthpacks,int scale,int row, int col)
{
    this-> scale = scale;
    gScene = new GScene(this, tiles, protagonist, enemies,penemies,healthpacks,scale);
    tScene = new TScene(this, tiles, protagonist, enemies, penemies, healthpacks, row, col);
    setScene(gScene);
    currentScene = 1;
}

void GView::switchScene()
{
    if(currentScene==1){
        setScene(tScene);
        currentScene = 2;
    }else{
        setScene(gScene);
        currentScene = 1;
    }
}

GScene* GView::getGScene()
{
    return gScene;
}

TScene *GView::getTScene()
{
    return tScene;
}

int GView::getCurrentScene() const
{
    return currentScene;
}

void GView::keyPressEvent(QKeyEvent *event)
{
    //    qDebug()<<"key is pressed1";

    switch (event->key()) {
    case Qt::Key_Up:
        emit keyPressSignal(UP);
        break;
    case Qt::Key_Down:
        emit keyPressSignal(DOWN);
        break;
    case Qt::Key_Left:
        emit keyPressSignal(LEFT);
        break;
    case Qt::Key_Right:
        emit keyPressSignal(RIGHT);
        break;
    case Qt::Key_T:
        emit keyPressSignal(TAKE);
        break;
    case Qt::Key_A:
        emit keyPressSignal(ATTACK);
        break;
    case Qt::Key_Enter:
        emit keyPressSignal(ENTER);
        break;
    }
    QGraphicsView::keyPressEvent(event);
}

void GView::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"x="<<event->x()<<", y="<<event->y();
}
