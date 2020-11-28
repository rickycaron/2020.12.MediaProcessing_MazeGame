#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <set>
#include "node.h"
#include "point.h"
class pathfinder
{
public:
    pathfinder(int row,int column);

    std::list<std::shared_ptr<Node>> openlist;
    std::list<std::shared_ptr<Node>> closedlist;
    std::list<std::shared_ptr<Node>> solution;
    std::set<int> createdNoteIndex;
    std::shared_ptr<Node> currentNode=nullptr;
    std::shared_ptr<Node> successorNode=nullptr;
    std::shared_ptr<Node> rootNode=nullptr;
    Point startPoint;
    Point goalPoint;
    Point nearbyPoint;
    std::vector<std::unique_ptr<Tile>> tiles;
private:
    int row=0;
    int column=0;

    void initializePathfinder(int startx, int starty, int endx, int endy);
    void clearAllContainer();
    bool reachinGoal();

    bool breadthfirstalorithum();
    bool breadthfirstAddNode(int index,std::shared_ptr<Node>parent);


};

#endif // PATHFINDER_H
