#include "help.h"

Help::Help(std::shared_ptr<Controller> con, QStringList &commandList, QLabel *hint):Command(con)
{
    hintText = "Hint: ";
    for (int i=0; i<commandList.size()-1; i++) {
        hintText.append(commandList[i]);
        hintText.append(", ");
    }
    hintText.append(commandList[commandList.size()-1]);
    myhint = hint;
}

void Help::excute() const
{
    myhint->setText(hintText);
}
