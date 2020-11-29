#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <iostream>
#include <memory>
#include <list>
#include <vector>
#include <QSet>
#include <QStack>
#include <cmath>
#include <cfloat>
#include "node.h"
#include "point.h"
class Pathfinder
{
public:
    Pathfinder(int row,int column, std::vector<std::shared_ptr<Tile>> tiles);
    std::vector<std::shared_ptr<Tile>> tiles;//this should be initialized when the pathfinder is created


    std::list<std::shared_ptr<Node>> openlist;
    std::list<std::shared_ptr<Node>> closedlist;
    QStack<std::shared_ptr<Tile>> solution;
    QSet<int> createdNoteIndex;//all the indexcs that have been created
    std::shared_ptr<Node> currentNode;
    std::shared_ptr<Node> successorNode;
    std::shared_ptr<Node> rootNode;
    Point startPoint;
    Point goalPoint;
    Point nearbyPoint;


    bool calcPath_BreadthFirst();
private:
    int row=0;
    int column=0;
    float moveCost=0;

    void initializePathfinder(int startx, int starty, int endx, int endy);
    void clearAllContainer();
    bool reachingGoal();

    bool breadthfirstalorithum();
    void breadthfirstAddNode(int index,std::shared_ptr<Node>parent);


};

#endif // PATHFINDER_H
