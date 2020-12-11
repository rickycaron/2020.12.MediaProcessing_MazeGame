#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <QVectorIterator>
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
    void showAllContainers();
    static bool distanncecomp(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
    {
        return node1->getDistance() < node2->getDistance();
    }
    void initialze(const std::shared_ptr<Tile> &p,const std::shared_ptr<Tile> goal);
    bool calcPath_BreadthFirst();
    bool calcPath_BestFirst();
    bool calcPath_Dijkstra();
    bool calcPath_Astar();

    QStack<std::shared_ptr<Tile>> findpath(const std::shared_ptr<Tile> &p,int x, int y);
    QStack<std::shared_ptr<Tile>> findpath(int sx,int sy,int x, int y);
    float getMoveCost() const;

private:
    int row=0;
    int column=0;
    float moveCost=0;
    void initializePathfinder(int startx, int starty, int endx, int endy);
    void clearAllContainer();
    bool reachingGoal();
    double calEuclideanDistance(double x1, double y1, double x2, double y2);
    //static bool distanncecomp(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2);

    std::shared_ptr<Node> findMinDistanceNode();
    void generateSolution();
    std::list<std::shared_ptr<Node>>::iterator findOldNote(int index);
    std::list<std::shared_ptr<Node>>::iterator findOldNoteinOpenlist(int index, bool & isInOpenlist);
    std::list<std::shared_ptr<Node>>::iterator findOldNoteinClosedlist(int index, bool & isInClosedlist);
    bool isNodeInOpenlist(int index);
    bool isNoteInClosedlist(int index);
    std::shared_ptr<Node> findMinFinalCostNode();
    static bool finalCostcomp(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
    {
        return node1->getFinalCost() < node2->getFinalCost();
    }

    bool breadthfirstalorithum();
    void breadthfirstAddNode(int index,std::shared_ptr<Node>parent);

    bool bestfirstalorithum();
    void bestfirstAddNode(int index,std::shared_ptr<Node>parent);

    bool dijkstraalorithum();
    void dijkstraAddNode(int index,std::shared_ptr<Node>parent);

    bool aStaralorithum();
    void aStarAddNode(int index,std::shared_ptr<Node>parent);
    
};

#endif // PATHFINDER_H
