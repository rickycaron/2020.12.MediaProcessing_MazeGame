#include <QApplication>
#include "widget.h"
#include "pathfinder.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    std::shared_ptr<Controller> controller=std::make_shared<Controller>();
    std::cout<<"rows"<<controller->getCol()<<"columns"<<controller->getRow()<<std::endl;
    std::shared_ptr<Pathfinder> pathfinder=std::make_shared<Pathfinder>(controller->getRow(),controller->getCol(),controller->getTiles());

    return a.exec();
}
