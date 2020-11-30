#include "node.h"

Node::Node()
{
    tile=nullptr;
    pre=nullptr;
}

Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> pre)
{
    this->tile = tile;
    this->pre = pre;
    //calculateDistance();
}

std::shared_ptr<Node> Node::getPre() const
{
    return pre;
}

void Node::setPre(const std::shared_ptr<Node> &value)
{
    pre = value;
}

std::shared_ptr<Tile> Node::getTile() const
{
    return tile;
}

void Node::setTile(const std::shared_ptr<Tile> &value)
{
    tile = value;
}

double Node::getDistance() const
{
    return distance;
}

void Node::setDistance(double value)
{
    distance = value;
}

void Node::calculateDistance()
{
    if(pre!=nullptr && tile!= nullptr)
    {
        double xDistance = tile->getXPos() - pre->getTile()->getXPos();
        double yDistance = tile->getYPos() - pre->getTile()->getYPos();
        distance=sqrt( pow( xDistance ,2) + pow( yDistance ,2) );
        setDistance(distance);
    }
}
