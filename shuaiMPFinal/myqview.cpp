#include "myqview.h"
#include<QtDebug>
MyQView::MyQView(QWidget *parent) : QGraphicsView(parent)
{

}

void MyQView::createScene(const std::vector<std::shared_ptr<Tile> > &tiles, const std::shared_ptr<Protagonist> &protagonist, const std::vector<std::shared_ptr<Enemy> > &enemies, const std::vector<std::shared_ptr<Tile> > &healthpacks,int scale)
{
    this-> scale = scale;
   qScene = new MyQScene(this, tiles, protagonist, enemies,healthpacks,scale);
   setScene(qScene);
}

int MyQView::detectEnemy()
{

}

int MyQView::detectHealthPack()
{

}
void MyQView::mousePressEvent(QMouseEvent *event)
{

}
