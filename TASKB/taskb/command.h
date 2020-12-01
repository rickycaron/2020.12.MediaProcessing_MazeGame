#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <memory>
#include "controller.h"

class Command
{
public:
    //explicit Command(Controller *con);
    explicit Command(std::shared_ptr<Controller> con);
    virtual void excute() const = 0;
    virtual void setDestination(int x, int y);
    //Controller *getController() const;
    std::shared_ptr<Controller> getController() const;

    QString getName() const;
    void setName(const QString &value);

private:
    QString name;
    //Controller *controller;
    std::shared_ptr<Controller> controller;
};

#endif // COMMAND_H
