#include "controller.h"
#include<QtDebug>
#include<QKeyEvent>
#include<QTimer>
#include<cmath>

Controller::Controller(std::shared_ptr<Model> model, GView* view, QObject *parent):QObject(parent)
{
    this->model = model;
    this->view = view;
    createScene(20);

//    QObject::connect(this->view,SIGNAL(keyPressSignal(int)),this,SLOT(on_keyPressSlot(int)));
    connect(model->getProtagonist().get(),&Protagonist::healthChanged,[=](int health){
        if(health<1){
         model->setIsChangable (false);
         qDebug()<<"Game Over";
         updateEnergyTimer->stop();
        }
        else{
            qDebug()<<"Game Continue";

            model->setIsChangable (true);
        }
    });

    connect(model->getProtagonist().get(),&Protagonist::energyChanged,[=](int energy){
        if(energy<1){
            model->setIsChangable (false);
            if(energy<0){
                updateEnergyTimer->stop();
                qDebug()<<"Game Over";
            }

            else{
               qDebug()<<"Energy is not enough now, please take a rest ";
            }
        }
        else{
            model->setIsChangable (true);
        }
    });

    QObject::connect(model.get(),SIGNAL(detectedSignal(int,int)),this,SLOT(detected(int,int)));

    //Qtimer setting
    updateEnergyTimer = new QTimer(this);
    connect(updateEnergyTimer,&QTimer::timeout,[=]{
        float currentEnergy = model->getProtagonist()->getEnergy();
        if(currentEnergy<30){
            currentEnergy += 0.5;
            model->getProtagonist()->setEnergy(currentEnergy);
        }
    });
    updateEnergyTimer->start(1000);
    connect(view,SIGNAL(mouseClickSignal(int,int)),this,SLOT(gotoXY(int,int)));
}

void Controller::moveRight()
{
    if(model->moveRight()){
        view->getGScene()->changeProtagonistImage(RIGHT);
    }
    else{
        qDebug()<<"can't move!";
    }
    //it depends on if you want to explore around when you come
    //or explore when taking action("TAKE","ATTACK")
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveLeft()
{
    if(model->moveLeft()){
        view->getGScene()->changeProtagonistImage(LEFT);
    }
    else{
        qDebug()<<"can't move!";
    }
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveUp()
{
    if(model->moveUp()){
        view->getGScene()->changeProtagonistImage(UP);
    }
    else{
        qDebug()<<"can't move!";
    }
//    detectEnemy();
//    detectHealthPack();
}

void Controller::moveDown()
{
    if(model->moveDown()){
        view->getGScene()->changeProtagonistImage(DOWN);
    }
    else{
        qDebug()<<"can't move!";
    }
}


void Controller::attack()
{
    if(this->detectedType==ENEMY){
        int index = this->detectedEnemyIndex;
           model->attack(index);
           view ->getGScene()->setDeath(ENEMY,index);

    }
    if(this->detectedType==PENEMY){
        int index = this->detectedPEnemyIndex;
           model->attack(index);
//           view ->getCurrentScene()->setDeath(PENEMY,index);

    }
//    if(this->detectedType==PENEMY){
//        int index = this->detectedPEnemyIndex;
//          int outcome = model->take(index);
//            if(outcome!=-1){
//                view ->getCurrentScene()->redrawHealthpack(index);
//            }
//    }


}

void Controller::take()
{
    if(this->detectedType==HEALTHPACK){
        int index = this->detectedHealthPack;
        //Model part
          model->take(index);
            if(index!=-1){
                //view part
                view ->getGScene()->redrawHealthpack(index);
                view->getTScene()->redrawHealthpack(index);
            }
    }

}

void Controller::createScene(int scale)
{

    view->createScene(model->getTiles(),model->getProtagonist()
                      ,model->getEnemies(),model->getPEnemies(),model->getHealthpacks(),scale,model->getRow(),model->getCol());

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

GView *Controller::getView() const
{
    return view;
}

void Controller::detected(int type,  int index)
{

    switch (type) {
    case ENEMY:
        detectedType = ENEMY;
        this->detectedEnemyIndex =index;
    break;
    case PENEMY:
        detectedType = PENEMY;
        this->detectedPEnemyIndex = index;
        break;
    case HEALTHPACK:
        detectedType = HEALTHPACK;
        detectedHealthPack =index;

    break;
    case NONE:
        detectedType = NONE;
        break;
    }
}

void Controller::gotoXY(int x, int y)
{
    model->gotoXY(x,y);
}


