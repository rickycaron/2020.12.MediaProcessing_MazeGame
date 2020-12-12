#include "gview.h"
#include <QtDebug>
#include <QGraphicsPixmapItem>

GView::GView(QWidget *parent) : QGraphicsView(parent)
{

}

void GView::createScene(const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &enemies,
                          const std::vector<std::shared_ptr<PEnemy> > &penemies,const std::vector<std::shared_ptr<Tile> > &healthpacks,int scale,int row, int col)
{
    this-> scale = scale;
    gScene = new GScene(this, tiles, protagonist, enemies, penemies, healthpacks, scale, row, col);
    tScene = new TScene(this, tiles, protagonist, enemies, penemies, healthpacks, scale, row, col);

    gameoverScene = new GameoverScene(this);
    gamewinScene = new GamewinScene(this);

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

void GView::gameover()
{
    setScene(gameoverScene);
}

void GView::win()
{
    setScene(gamewinScene);
}

void GView::keyPressEvent(QKeyEvent *event)
{
    //    qDebug()<<"key is pressed";
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
    if(event->button() == Qt::LeftButton){
        int x;
        int y;
        if(mapToScene(event->pos()).x()>0){
            x = static_cast<int>(mapToScene(event->pos()).x()/scale);
        }
        else{
            x = static_cast<int>(mapToScene(event->pos()).x()/scale)-1;
        }

        if(mapToScene(event->pos()).y()>0){
            y = static_cast<int>(mapToScene(event->pos()).y()/scale);
        }
        else{
            y = static_cast<int>(mapToScene(event->pos()).y()/scale)-1;
        }
        emit mouseClickSignal(x,y);
        qDebug()<<"x="<<x<<", y="<<y;
    }
}
