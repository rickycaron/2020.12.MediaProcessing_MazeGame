#include "widget.h"
#include "ui_widget.h"
#include "ttile.h"
#include "tenemy.h"
#include "thealthpack.h"
#include "world.h"
#include <QDebug>
#include <QCompleter>
#include "textscene.h"
#include "controller.h"
#include "moveright.h"
#include "moveleft.h"
#include "moveup.h"
#include "movedown.h"
#include "attack.h"
#include "take.h"
#include "gotoxy.h"
#include "help.h"
#include <memory>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsView *view = new QGraphicsView(this);
    hint = new QLabel(this);
    hint->setText(" ");
//    std::shared_ptr<QGraphicsView> view = std::make_unique<QGraphicsView>(this);
//    Controller *controller = new Controller();

    std::shared_ptr<Controller> controller = std::make_shared<Controller>(this);
    controller->createScene(this);
    controller->addSceneToView(*view);
    ui->verticalLayout->addWidget(view);
    ui->verticalLayout->addWidget(hint);

    //auto completion
    editList<<"right"<<"left"<<"up"<<"down"<<"go to "<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(editList, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEdit->setCompleter(completer);

    commandList["right"]=std::make_unique<MoveRight>(controller);
    commandList["left"]=std::make_unique<MoveLeft>(controller);
    commandList["up"]=std::make_unique<MoveUp>(controller);
    commandList["down"]=std::make_unique<MoveDown>(controller);
    commandList["attack"]=std::make_unique<Attack>(controller);
    commandList["take"]=std::make_unique<Take>(controller);
    commandList["goto"]=std::make_unique<GotoXY>(controller);
    commandList["help"]=std::make_unique<Help>(controller,editList,hint);

    ui->energyBar->setValue(100);
    ui->healthBar->setValue(100);
    connect(controller->getProtagonist().get(),&Protagonist::energyChanged,ui->energyBar,&QProgressBar::setValue);
    connect(controller->getProtagonist().get(),&Protagonist::healthChanged,ui->healthBar,&QProgressBar::setValue);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::checkString(QString &s)
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
            qDebug()<<"x="<<x<<", y="<<y;
            commandList["goto"]->setDestination(x,y);
            commandList["goto"]->excute();
        }else{
            hint->setText("invalid input");
        }
    }
}

void Widget::on_lineEdit_editingFinished()
{
    QString text = ui->lineEdit->text();
    if(text.contains("go to ",Qt::CaseSensitive)){
        checkString(text);
    }else{
        if(commandList.count(text)==1){
            hint->setText(" ");
            commandList[text]->excute();
        }
        else{
            hint->setText("Can't find this command.");
        }
    }
}
