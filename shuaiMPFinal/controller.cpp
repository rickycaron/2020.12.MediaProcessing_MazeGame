#include "controller.h"
#include<QtDebug>
#include<QKeyEvent>
#include<QTimer>
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
    connect(model->getProtagonist().get(),&Protagonist::healthChanged,[=](int health){
        if(health<1){
         model->setIsChangable (false);
        }
        else{
            model->setIsChangable (true);
        }
});
    connect(model->getProtagonist().get(),&Protagonist::energyChanged,[=](int energy){
        if(energy<1){
         model->setIsChangable (false);
         qDebug()<<"Energy is not enough now, please take a rest ";
        }
        else{
            model->setIsChangable (true);
        }
});

    QObject::connect(model.get(),SIGNAL(detectedSignal(int,int)),this,SLOT(detected(int,int)));

    updateEnergyTimer = new QTimer(this);
    connect(updateEnergyTimer,&QTimer::timeout,[=]{
        float currentEnergy = model->getProtagonist()->getEnergy();
        if(currentEnergy<30){
            currentEnergy += 0.5;
            model->getProtagonist()->setEnergy(currentEnergy);
        }
    });
    updateEnergyTimer->start(1000);

}

void Controller::moveRight()
{
    if(!checkModel()) {return;}
    if(!checkBoundary(X,POSITIVE)){
     model->moveRight();
    }
   else{
        qDebug()<<"at boundary!";
    }
    //it depends on if you want to explore around when you come
    //or explore when taking action("TAKE","ATTACK")
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveLeft()
{
    if(!checkModel()) {return;}
    if(!checkBoundary(X,NEGATIVE)){
        model->moveLeft();
    }
   else{
        qDebug()<<"at boundary!";
    }
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveUp()
{
    if(!checkModel()) {return;}
    if(!checkBoundary(Y,NEGATIVE)){
        model->moveUp();
    }
   else{
        qDebug()<<"at boundary!";
    }
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveDown()
{
    if(!checkModel()) {return;}
    if(!checkBoundary(Y,POSITIVE)){
        model->moveDown();
    }
   else{
        qDebug()<<"at boundary!";
    }
//    detectEnemy();
//    detectHealthPack();
}

//void Controller::consumeEnergy()
//{
//    model->consumeEnergy();
//}

void Controller::attack()
{
    int index =-1;
    //query firstly
    switch (detectedType) {
        case NONE:
             index = -1 ;
        case ENEMY:
             index = detectedEnemyIndex ;
        case PENEMY:
             index = detectedPEnemyIndex ;
        case HEALTHPACK:
             index = detectedHealthPack ;

        }
    //send query result to model
    model->attack(index);
}

void Controller::take()
{
//    if(this->detectedType==HEALTHPACK){
//        int index = this->detectedHealthPack;
//            model->take(index);
//             qDebug()<<"model take " ;
//    }
    qDebug()<<"detectedType is(take function) " << detectedType ;
    qDebug()<<"healthpack index is " << detectedHealthPack ;

    qDebug()<<"detectedType is " << HEALTHPACK ;


}

void Controller::createScene(int scale)
{

    view->createScene(model->getTiles(),model->getProtagonist()
                      ,model->getEnemies(),model->getPEnemies(),model->getHealthpacks(),scale);

}

//controller call method from view to query
//int Controller::detectAround()
//{
//    switch (detectedType) {
//    case NONE:
//        return NONE;
//    case ENEMY:
//        return ENEMY;
//    case PENEMY:
//        return PENEMY;
//    case HEALTHPACK:
//        return HEALTHPACK;

//    }

//    return view->detectEnemy();
//}


bool Controller::checkModel()
{
    return model->getIsChangable();
}

bool Controller::checkBoundary(int axis,int sign)
{
    int col = model->getCol();
    int row = model->getRow();
    switch (axis) {
    case X: //X axis
        {
        int xPos =  model->getProtagonist()->getXPos() + sign*1;
        if(xPos>col-1||xPos<0){ return true;}
        return false;
        }
    case Y: //Y axis
        {
        int yPos =  model->getProtagonist()->getYPos() + sign*1;
        if(yPos>row-1||yPos<0){ return true;}
        return false;
        }
    }
}


void Controller::on_keyPressSlot(int index)
{
//    qDebug()<<"key is pressed and the index is" << index;

    switch (index) {
    case UP:
        moveUp();
        break;
    case DOWN:
        moveDown();
        break;
    case LEFT:
        moveLeft();
        break;
    case RIGHT:
        moveRight();
        break;
    case TAKE:
        take();
        break;

    }
    qDebug()<<"detectedType value is(key)  "<< this->detectedType;



}

void Controller::detected(int type,  int index)
{

    switch (type) {
    case ENEMY:
        detectedType =ENEMY;
        this->detectedEnemyIndex =index;
    break;
    case PENEMY:
        detectedType =PENEMY;
        this->detectedPEnemyIndex = index;
        qDebug()<<"pEnemy detected slot triggered ";
        qDebug()<<"detectedType value is(slot)  "<< detectedType;
        break;
    case HEALTHPACK:
        detectedType =HEALTHPACK;
        detectedHealthPack =index;
        qDebug()<<"healthPack detected slot triggered ";
        qDebug()<<"detectedType value is(slot)  "<< detectedType;

    break;
    case NONE:
        detectedType =NONE;

 //        qDebug()<<"detected slot triggered ";

        break;
    }
//    qDebug()<<"detectedType value is(slot2)  "<< detectedType;

}
