#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QObject>
#include<memory>
#include<QList>
#include<QDebug>
#include"model.h"
#include"myqview.h"
#include<QMetaType>
#include<QTimer>
class Controller :public QObject
{
    Q_OBJECT
public:
    Controller(std::shared_ptr<Model>,QGraphicsView*);
    Controller(std::shared_ptr<Model>,MyQView*);
    //controller+model
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack();
    void take();
    //controller+view
    void createScene(int);
//    int detectAround();
    bool checkModel();
    bool checkBoundary(int,int);


private:std::shared_ptr<Model> model;
        MyQView* view;
        enum axis{X=0,Y=1};
        enum type{NONE=-1,ENEMY=0,PENEMY,HEALTHPACK};
        enum sign{POSITIVE=1,NEGATIVE=-1};
        enum direction{UP=0,DOWN,LEFT,RIGHT,TAKE,ATTACK};
        QTimer * updateEnergyTimer;
        type detectedType=NONE;
        int detectedEnemyIndex=-1;
        int detectedPEnemyIndex=-1;
        int detectedHealthPack=-1;
signals:
        void gameOver();
public slots:
        void on_keyPressSlot(int index);
        void detected(int type, int index);


};

#endif // CONTROLLER_H
