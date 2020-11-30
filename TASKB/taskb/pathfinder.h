#ifndef PATHFINDER_H
#define PATHFINDER_H

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
    Pathfinder(int row,int column, std::vector<std::shared_ptr<Tile>> newtiles);
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
    void showsolutionpath();

    void initialze(const std::shared_ptr<Tile> &p,const std::shared_ptr<Tile> goal);

    bool calcPath_BreadthFirst();
    bool calcPath_BestFirst();

private:
    int row=0;
    int column=0;
    float moveCost=0;

    void initializePathfinder(int startx, int starty, int endx, int endy);
    void clearAllContainer();
    bool reachingGoal();
    double calEuclideanDistance(double x1, double y1, double x2, double y2);
    //static bool distanncecomp(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);
    static bool distanncecomp(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
    {
        return node1->getDistance() < node2->getDistance();
    }

    std::shared_ptr<Node> findMinDistanceNode();

    bool breadthfirstalorithum();
    void breadthfirstAddNode(int index,std::shared_ptr<Node>parent);

    bool bestfirstalorithum();
    void bestfirstAddNode(int index,std::shared_ptr<Node>parent);
    
};

#endif // PATHFINDER_H
