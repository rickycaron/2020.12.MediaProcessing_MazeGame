#ifndef NODE_H
#define NODE_H
#include "world.h"
#include "world_global.h"
#include <memory>

class Node
{
public:
    //because the tiles is a vector of unique_ptr, we create a class Node to solve the pointer problem
    Node();
    Node(std::shared_ptr<Tile> tile,std::shared_ptr<Node> pre);
    std::shared_ptr<Node> getPre() const;
    void setPre(const std::shared_ptr<Node> &value);

    std::shared_ptr<Tile> getTile() const;
    void setTile(const std::shared_ptr<Tile> &value);

    double getDistance() const;
    void setDistance(double value);
    void calculateDistance();

private:
    std::shared_ptr<Tile> tile;
    std::shared_ptr<Node> pre;
    double distance = std::numeric_limits<double>::infinity();
};

#endif // NODE_H
