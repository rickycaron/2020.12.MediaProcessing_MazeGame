#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCompleter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view  = new GView(this);
    ui->verticalLayout_gameW->addWidget(view);
    currentFile = QString("worldmap");
    initializeGame(currentFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeGame(QString fileName)
{

    model = std::make_shared<Model>(fileName);
    controller = std::make_shared<Controller>(model,view,this);
    keypressController = std::make_shared<KeypressController>(controller,this);
    commandController = std::make_shared<CommandController>(controller,ui->label,this);

    ui->energyBar->setValue(100);
    ui->healthBar->setValue(100);
    connect(model->getProtagonist().get(),&Protagonist::energyChanged,ui->energyBar,&QProgressBar::setValue);
    connect(model->getProtagonist().get(),&Protagonist::healthChanged,ui->healthBar,&QProgressBar::setValue);
    connect(model.get(),&Model::updateScoreBoard,[=](int score){
        int currentScore = ui->scoreBoard->value();
        ui->scoreBoard->display(currentScore+score);
    });

    //auto completion
    editList<<"right"<<"left"<<"up"<<"down"<<"go to "<<"attack"<<"take"<<"help";
    QCompleter *completer = new QCompleter(editList, this);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEditCommand->setCompleter(completer);
    ui->lineEditCommand->setEnabled(false);
    ui->label->setText(" ");

    ui->scoreBoard->setDigitCount(6);
    ui->scoreBoard->setSmallDecimalPoint(false);
    ui->scoreBoard->display(0);
}

void MainWindow::on_changeSceneButton_clicked()
{

    view->switchScene();
    if(view->getCurrentScene()==2){
        ui->lineEditCommand->setEnabled(true);
    }
    else{
        ui->lineEditCommand->setText("");
        ui->lineEditCommand->setEnabled(false);
        ui->label->setText(" ");
    }
}


void MainWindow::on_pushButton_clicked()
{
    initializeGame(currentFile);
}


void MainWindow::on_autoplayButton_clicked()
{
    controller->autoplay();
}

void MainWindow::on_lineEditCommand_editingFinished()
{
    emit inputCommand(ui->lineEditCommand->text());

}

void MainWindow::on_lineEditChangeMap_editingFinished()
{
     //there should be a checking function before change file name
     currentFile = QString(ui->lineEditChangeMap->text());
     initializeGame(currentFile);
}


