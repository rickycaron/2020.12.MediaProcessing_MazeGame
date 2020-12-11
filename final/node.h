#ifndef NODE_H
#define NODE_H
#include "world.h"
#include "world_global.h"
#include <memory>
#include <cmath>
class Node
{
public:
    //because the tiles is a vector of unique_ptr, we create a class Node to solve the pointer problem
    Node();
    Node(std::shared_ptr<Tile> tile);
    Node(std::shared_ptr<Tile> tile,std::shared_ptr<Node> pre);
    std::shared_ptr<Node> getPre() const;
    void setPre(const std::shared_ptr<Node> &value);

    std::shared_ptr<Tile> getTile() const;
    void setTile(const std::shared_ptr<Tile> &value);

    double getDistance() const;
    void setDistance(double value);
    void calculateDistance();

    double getGivenCost() const;
    void setGivenCost(double value);

    double getHeuristicCost() const;
    void setHeuristicCost(double value);

    void updateGivenCost(double newGivenCost);//update the givenCost and final Cost

    double getFinalCost() const;

private:
    std::shared_ptr<Tile> tile;
    std::shared_ptr<Node> pre;
    //double distance = std::numeric_limits<double>::infinity();
    double distance = 0;//it is the final cost in Dijkstra and A* algorithum
    double givenCost = 0.0;//the cost from the start point
    double heuristicCost = 0.0;// the distance to the goal
    double finalCost = 0.0;//the sum pf givenCost and finalCost
};

#endif // NODE_H
