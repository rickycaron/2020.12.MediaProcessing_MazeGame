#ifndef KEYPRESSCONTROLLER_H
#define KEYPRESSCONTROLLER_H

#include <QObject>
#include <memory>
#include "controller.h"
#include "config.h"

class KeypressController : public QObject
{
    Q_OBJECT
public:
    KeypressController(std::shared_ptr<Controller> con, QObject *parent = nullptr);
private:
    std::shared_ptr<Controller> controller;
private slots:
    void on_keyPressSlot(int index);
};

#endif // KEYPRESSCONTROLLER_H
