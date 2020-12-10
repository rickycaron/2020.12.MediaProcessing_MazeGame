#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "controller.h"
#include "commandcontroller.h"
#include "keypresscontroller.h"
#include "gview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void inputCommand(QString commandtext);
private slots:
    void on_changeSceneButton_clicked();
    void on_lineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    GView* view;
    std::shared_ptr<Controller> controller;
    std::shared_ptr<KeypressController> keypressController;
    std::shared_ptr<CommandController> commandController;
    std::shared_ptr<Model> model;
    QStringList editList;
    std::map<QString,std::shared_ptr<Command>> commandList;
};
#endif // MAINWINDOW_H
