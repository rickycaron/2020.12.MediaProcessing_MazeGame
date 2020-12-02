#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myqview.h"
#include "controller.h"
#include"model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyQView* qView;
    QGraphicsView* tview;
    std::shared_ptr<Controller> myController;
    std::shared_ptr<Model> model;

};
#endif // MAINWINDOW_H
