#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "world.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
#include "gprotagonist.h"
#include "command.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void buildWorld();

private slots:
    void on_lineEdit_editingFinished();
private:
    Ui::Widget *ui;
    std::shared_ptr<Protagonist> protagonist;
    //std::vector<std::unique_ptr<Command>> clist;
    std::map<QString,std::shared_ptr<Command>> clist;
};
#endif // WIDGET_H
