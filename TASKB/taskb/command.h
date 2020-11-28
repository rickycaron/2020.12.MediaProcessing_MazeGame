#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include "controller.h"

class Command
{
public:
    explicit Command(Controller *con);
    virtual void excute() const = 0;
    Controller *getController() const;

    QString getName() const;
    void setName(const QString &value);

private:
    QString name;
    Controller *controller;
};

#endif // COMMAND_H
