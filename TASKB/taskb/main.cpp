#include "widget.h"
#include "pathfinder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();


    //World *world->createWorld("://images/worldmap.png",10,10,0.25);
    std::shared_ptr<World> world=std::make_shared<World>();
    world->createWorld("://images/worldmap.png",10,10,0.25);
    world->getCols();
    std::cout<<"rows"<<world->getCols()<<"columns"<<world->getRows()<<std::endl;
    std::vector<std::unique_ptr<Tile>> tiles = world->getTiles();

    std::shared_ptr<Pathfinder> pathfinder=std::make_shared<Pathfinder>(world->getRows(),world->getCols(),tiles);


//    std::vector<std::unique_ptr<Tile>> tiles = world->getTiles();
//    function(const std::vector<std::unique<Tile>> &tiles)
//    tiles[index]
    return a.exec();
}
