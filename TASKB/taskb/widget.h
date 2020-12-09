#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include "world.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
#include "tprotagonist.h"
#include "command.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void checkString(QString &s);

private slots:
    void on_lineEdit_editingFinished();
    void getEnegyValue(int enegy);
    void getHealthValue(int health);
signals:
    void energyChanged(int enegy);
    void healthChanged(int health);
private:
    Ui::Widget *ui;
    QLabel *hint;
    QStringList editList;
    std::map<QString,std::shared_ptr<Command>> commandList;
};
#endif // WIDGET_H
