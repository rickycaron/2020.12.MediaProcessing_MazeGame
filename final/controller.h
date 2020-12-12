#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <memory>
#include <QList>
#include <QDebug>
#include <QMetaType>
#include <QTimer>
#include "model.h"
#include "gview.h"
#include "pathfinder.h"

class Controller :public QObject
{
    Q_OBJECT
public:
    Controller(std::shared_ptr<Model> model, GView *view, QObject *parent = nullptr);
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack();
    void take();
    void createScene(int);
    bool checkModel();
    GView *getView() const;
    void autoplay();
private:
    std::shared_ptr<Model> model;
    GView* view;
    QTimer * updateEnergyTimer;
    QTimer * xEnemyExcuteSkillTimer;
    bool xEnemyShown=false;
    type detectedType=NONE;
    int detectedEnemyIndex=-1;
    int detectedPEnemyIndex=-1;
    int detectedHealthPack=-1;
signals:
    void gameOver();

public slots:
    void detected(int type, int index);
    void gotoXY(int x, int y);
};

#endif // CONTROLLER_H
