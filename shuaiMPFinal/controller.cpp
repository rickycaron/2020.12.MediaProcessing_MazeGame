#include "controller.h"

//control flow: controller->model->view
Controller::Controller(std::shared_ptr<Model> model, QGraphicsView* view)
{

}

Controller::Controller(std::shared_ptr<Model> model, MyQView* view)
{

    this->model = model;
    this->view = view;
    createScene();
    qDebug()<< "successfully 222222222222222";

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

void Controller::createScene()
{
    view->createScene(model->getTiles(),model->getProtagonist()
                      ,model->getEnemies(),model->getHealthpacks());
    qDebug()<< "successfully 66666666666666";

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
