#include "controller.h"
#include<QtDebug>
#include<QKeyEvent>
//control flow: controller->model->view
Controller::Controller(std::shared_ptr<Model> model, QGraphicsView* view)
{

}

Controller::Controller(std::shared_ptr<Model> model, MyQView* view)
{

    this->model = model;
    this->view = view;
    createScene(20);
    QObject::connect(this->view,SIGNAL(keyPressSignal(int)),this,SLOT(on_keyPressSlot(int)));

}

void Controller::moveRight()
{
    model->moveRight();
    //it depends on if you want to explore around when you come
    //or explore when taking action("TAKE","ATTACK")
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveLeft()
{
    model->moveLeft();
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveUp()
{
    model->moveUp();
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveDown()
{
    model->moveDown();
//    detectEnemy();
//    detectHealthPack();
}

void Controller::consumeEnergy()
{
    model->consumeEnergy();
}

void Controller::attack()
{
    //query firstly
    int index = detectEnemy();
    //send query result to model
    model->attack(index);
}

void Controller::take()
{
    int index = detectHealthPack();
    model->take(index);
}

void Controller::createScene(int scale)
{

    view->createScene(model->getTiles(),model->getProtagonist()
                      ,model->getEnemies(),model->getHealthpacks(),scale);

}

//controller call method from view to query
int Controller::detectEnemy()
{
    return view->detectEnemy();
}

int Controller::detectHealthPack()
{
    return view->detectHealthPack();
}

void Controller::on_keyPressSlot(int index)
{
    qDebug()<<"key is pressed and the index is" << index;
}
