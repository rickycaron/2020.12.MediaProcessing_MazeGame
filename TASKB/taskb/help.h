#ifndef HELP_H
#define HELP_H

#include "command.h"
#include <QLabel>

class Help : public Command
{
public:
    explicit Help(std::shared_ptr<Controller> con, QStringList &commandList, QLabel *hint);
    void excute() const override;
private:
    QString hintText;
    QLabel *myhint;
};

#endif // HELP_H
