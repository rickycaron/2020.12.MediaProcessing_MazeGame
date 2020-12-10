#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H
#include <QString>
#include <QLabel>
#include "command.h"

class CommandController:public QObject
{
    Q_OBJECT
public:
    CommandController(std::shared_ptr<Controller> con, QLabel *hint, QObject *parent = nullptr);
    void checkString(QString &s);
private:
    std::shared_ptr<Controller> controller;
    std::map<QString,std::shared_ptr<Command>> commandList;
    QLabel *hint;
private slots:
    void checkCommand(QString commandtext);
};

#endif // COMMANDCONTROLLER_H
