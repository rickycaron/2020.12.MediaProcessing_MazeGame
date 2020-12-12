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

    connect(model.get(),&Model::protagonistGetPoisoned,[=]{
        view->getTScene()->redrawPoisonedState();
    });

    connect(model.get(),&Model::numOfEnemiesChanged,[=](int numOfEnemies){
        if(numOfEnemies==0){
            qDebug()<<"You win!";
            gameState=1;
        }
    });

    connect(model->getProtagonist().get(),&Protagonist::healthChanged,[=](int health){
        if(health<1){
         model->setIsChangable (false);
         qDebug()<<"Game Over";
         gameState=-1;
         updateEnergyTimer->stop();
         model->getProtagonist()->setEnergy(0);
         view->gameover();
        }
        else{
            qDebug()<<"Game Continue";
            if(!xEnemyShown){
                model->setIsChangable (true);
            }
        }
    });

    connect(model->getProtagonist().get(),&Protagonist::energyChanged,[=](int energy){
        if(energy<1){
            model->setIsChangable (false);
            if(energy<0){
                updateEnergyTimer->stop();
            }
            else{
               qDebug()<<"Energy is not enough now, please take a rest ";
            }
        }
        else{
//            qDebug()<<"Game Continue from energychanged slot";
            if(!xEnemyShown){
                model->setIsChangable (true);                
            }
        }
    });

    QObject::connect(model.get(),SIGNAL(detectedSignal(int,int)),this,SLOT(detected(int,int)));

    QObject::connect(model.get(),&Model::poisonTilesPermanent,[=](int index){
        view->getGScene()->setTilePoison(index);
        view->getTScene()->setTilePoison(index);
    });

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

    xEnemyExcuteSkillTimer = new QTimer(this);
    QObject::connect(xEnemyExcuteSkillTimer,&QTimer::timeout,[=]{
        model->getXEnemy()->moving();
    });
    QObject::connect(model.get(),&Model::xEnemyShown,[=]{
        //can not move when x enemy come out
        updateEnergyTimer->stop();
        model->setIsChangable(false);
        qDebug()<<"the prota is stoped and the state of is changeble is"<<model->getIsChangable() ;
        xEnemyShown =true;
        //can not move for 8 second
        QTimer::singleShot(8000,this,[=]{
            //to achieve animation
            model->setIsChangable(true);
            updateEnergyTimer->start(1000);
            xEnemyShown=false;
        });


        view->getGScene()->printXEnemy(model->getXEnemy());
        view->getTScene()->printXEnemy(model->getXEnemy());

        xEnemyExcuteSkillTimer->start(4000);
        connect(model->getXEnemy().get() ,&XEnemy::dead,[=](){
            xEnemyExcuteSkillTimer->stop();
        });
    });

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
}

void Controller::moveUp()
{
    if(model->moveUp()){
        view->getGScene()->changeProtagonistImage(UP);
    }
    else{
        qDebug()<<"can't move!";
    }
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
    qDebug()<<"5555555555555555555555";
    if(this->detectedType==ENEMY){
        int index = this->detectedEnemyIndex;
           model->attack(index);
    }
    if(this->detectedType==PENEMY){
        int index = this->detectedPEnemyIndex;
           model->attack(index);
    }
    if(this->detectedType==XENEMY){
        qDebug()<<"66666666666666666666";
//        int index = this->detectedXEnemyIndex;
//           model->attack(index);
    }
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
    view->createScene(model->getTiles(),model->getProtagonist(),
                      model->getEnemies(),model->getPEnemies(),model->getHealthpacks(),scale,model->getRow(),model->getCol());
}

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
    case XENEMY:
        detectedType = XENEMY;
        detectedXEnemyIndex =index;
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

void Controller::autoplay()
{
    auto goalTile = model->gotoNearestThing();
    qDebug()<<"222222222222222222222222";
    model->move();

//    gotoXY(goalTile->getXPos(),goalTile->getYPos());
//    connect(model.get(),&Model::moveFinished,[=](){
        take();
//        qDebug()<<"3333333333333333333333333";
        attack();
//    });
    qDebug()<<"444444444444444444444444";
    QTimer::singleShot(1000, this, [=]{
        if(gameState==0){
            if(xEnemyShown)
            {
                QTimer::singleShot(8000, this,[=]{
                    autoplay();
                });
            }
            else
            {
                autoplay();
            }
        }
    });
}

