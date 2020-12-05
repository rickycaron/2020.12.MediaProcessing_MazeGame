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
    Controller(std::shared_ptr<Model>,MyQView*,QObject *parent);
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
