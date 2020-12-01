#include <QApplication>
#include "widget.h"
#include "pathfinder.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    std::shared_ptr<Controller> controller=std::make_shared<Controller>();
//    std::cout<<"rows: "<<controller->getCol()<<", columns: "<<controller->getRow()<<std::endl;


//    //for(unsigned i=0; i< pathfinder->tiles.size();i++){std::cout<<pathfinder->tiles.at(i)->getValue()<<std::endl;}
//    std::cout<<pathfinder->tiles.size()<<std::endl;
//    //std::cout<<pathfinder->tiles[2]->getValue()<<std::endl;
//    pathfinder->initialze(controller->getProtagonist(),controller->getHealthpacks().at(0));
//    pathfinder->goalPoint.show();



//    std::cout<<"closedlist size:"<<pathfinder->closedlist.size()<<std::endl;
//    std::cout<<"openlist size:"<<pathfinder->openlist.size()<<std::endl;
//    std::cout<<"solution size:"<<pathfinder->solution.size()<<std::endl;

//    if(pathfindtaer->calcPath_BreadthFirst())
//    {
//        std::cout<<"Path is found ahaha"<<std::endl;
//        pathfinder->showsolutionpath();
//    }else{
//        std::cout<<"Path is not found..."<<std::endl;
//    }
//    if(pathfinder->calcPath_BestFirst())
//    {
//        std::cout<<"Path best first is found ahaha"<<std::endl;
//        pathfinder->showsolutionpath();
//    }else{
//        std::cout<<"Path best first is not found..."<<std::endl;
//    }

//    std::cout<<"closedlist size:"<<pathfinder->closedlist.size()<<std::endl;
//    std::cout<<"openlist size:"<<pathfinder->openlist.size()<<std::endl;
//    std::cout<<"solution size:"<<pathfinder->solution.size()<<std::endl;

//    std::cout<<"X:"<<pathfinder->tiles.at(1)->getXPos()<<std::endl;
//    std::cout<<"Y:"<<pathfinder->tiles.at(1)->getYPos()<<std::endl;

    return a.exec();
}
