#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<QObject>
#include<memory>
#include<QList>
#include<QDebug>
#include"model.h"
#include"myqview.h"
#include<QMetaType>
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
    int detectEnemy();
    int detectHealthPack();

private:std::shared_ptr<Model> model;
        MyQView* view;

public slots:
        void on_keyPressSlot(int index);

};

#endif // CONTROLLER_H
