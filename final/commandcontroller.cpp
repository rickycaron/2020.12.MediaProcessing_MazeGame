#include "commandcontroller.h"
#include "moveright.h"
#include "moveleft.h"
#include "moveup.h"
#include "movedown.h"
#include "attack.h"
#include "take.h"
#include "gotoxy.h"
#include "help.h"
#include "config.h"
#include <QDebug>

CommandController::CommandController(std::shared_ptr<Controller> con, QLabel *hint, QObject *parent) : QObject(parent)
{
    controller=con;
    this->hint = hint;
    commandList["right"]=std::make_unique<MoveRight>(controller);
    commandList["left"]=std::make_unique<MoveLeft>(controller);
    commandList["up"]=std::make_unique<MoveUp>(controller);
    commandList["down"]=std::make_unique<MoveDown>(controller);
    commandList["attack"]=std::make_unique<Attack>(controller);
    commandList["take"]=std::make_unique<Take>(controller);
    commandList["goto"]=std::make_unique<GotoXY>(controller);
    QStringList editList;
    editList<<"right"<<"left"<<"up"<<"down"<<"go to X Y"<<"attack"<<"take"<<"help";
    commandList["help"]=std::make_unique<Help>(controller,editList,hint);
    connect(parent,SIGNAL(inputCommand(QString)),this,SLOT(checkCommand(QString)));
}

void CommandController::checkString(QString &s)
{
    s.remove("go to ");
    QStringList list = s.split(QLatin1Char(','), Qt::SkipEmptyParts);
    if(list.size()!=2){
        hint->setText("invalid input");
    }else{
        bool ok=true;
        int x=list[0].toInt(&ok);
        int y=list[1].toInt(&ok);
        if(ok){
            hint->setText(" ");
            commandList["goto"]->setDestination(x,y);
            commandList["goto"]->excute();
        }else{
            hint->setText("invalid input");
        }
    }
}

void CommandController::checkCommand(QString commandtext)
{
    if(commandtext.contains("go to ",Qt::CaseSensitive)){
        checkString(commandtext);
    }else{
        if(commandList.count(commandtext)==1){
            hint->setText(" ");
            qDebug()<<commandtext;
            commandList[commandtext]->excute();
        }
        else{
            hint->setText("Can't find this command.");
        }
    }
}

