#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view  = new GView(this);
    ui->verticalLayout->addWidget(view);

    model = std::make_shared<Model>(QString("worldmap4"));
    controller = std::make_shared<Controller>(model,view,this);
    keypressController = std::make_shared<KeypressController>(controller,this);
    commandController = std::make_shared<CommandController>(controller,ui->label,this);

    ui->energyBar->setValue(100);
    ui->healthBar->setValue(100);
    connect(model->getProtagonist().get(),&Protagonist::energyChanged,ui->energyBar,&QProgressBar::setValue);
    connect(model->getProtagonist().get(),&Protagonist::healthChanged,ui->healthBar,&QProgressBar::setValue);

    //auto completion
    editList<<"right"<<"left"<<"up"<<"down"<<"go to "<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(editList, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEdit->setCompleter(completer);
    ui->lineEdit->setEnabled(false);
    ui->label->setText(" ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changeSceneButton_clicked()
{
    view->switchScene();
    if(view->getCurrentScene()==2){
        ui->lineEdit->setEnabled(true);
    }
    else{
        ui->lineEdit->setText("");
        ui->lineEdit->setEnabled(false);
        ui->label->setText(" ");
    }
}

void MainWindow::on_lineEdit_editingFinished()
{
    emit inputCommand(ui->lineEdit->text());
}

void MainWindow::on_autoplayButton_clicked()
{
    model->autoplay();
}
