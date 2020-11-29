#include "pathfinder.h"

Pathfinder::Pathfinder(int row, int column, std::vector<std::shared_ptr<Tile>> newtiles)
{
    this->row=row;
    this->column=column;
    //tiles=newtiles;
    //std::vector<std::unique_ptr<Tile>> tiles=newtiles;
    newtiles[10];
    Point startponit=Point();
    Point endponit=Point();
    currentNode=std::make_shared<Node>();
    successorNode=currentNode;
    rootNode=currentNode;
}

void Pathfinder::initializePathfinder(int startx, int starty, int endx, int endy)
{
    clearAllContainer();
    startPoint.setPoint(startx,starty);
    goalPoint.setPoint(endx,endy);
    rootNode=std::make_shared<Node>(move(tiles[startx+row*starty]),nullptr);
    currentNode=rootNode;
    openlist.push_back(rootNode);
    moveCost=0;
}

void Pathfinder::clearAllContainer()
{
    createdNoteIndex.clear();
    openlist.clear();
    closedlist.clear();
    solution.clear();
    currentNode=nullptr;
    successorNode=nullptr;
    rootNode=nullptr;
}

bool Pathfinder::reachingGoal()
{
    if(currentNode==nullptr)
    {
        return false;
    }
    if(currentNode->getTile()->getXPos()==goalPoint.getXpos()&&currentNode->getTile()->getYPos()==goalPoint.getYpos())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Pathfinder::breadthfirstalorithum()
{
    while (openlist.size()!=0)
    {
        //1.pop the node that has been waiting the longest
        //??maybe bug, it returned the reference in th list, will it be deleted after nest line execution?, maybe dequeue is better here
        currentNode=openlist.front();
        auto tile=currentNode->getTile();
        auto parent =currentNode;
        openlist.erase(openlist.begin());
        //2.check if reached in goal
        if(reachingGoal())
        {
            //solution.push(currentNode->getTile());
            return true;// The path is found!
        }
        else
        {
            //3. for 4 points around it
            //right
            if(tile->getXPos()<column-1){
                int index = (column)*(tile->getYPos()) + tile->getXPos() + 1;
                breadthfirstAddNode(index, parent);
            }//left
            if(tile->getXPos()>0){
                auto index = (column)*(tile->getYPos()) + tile->getXPos() - 1;
                breadthfirstAddNode(index, parent);
            }//down
            if(tile->getYPos()<row-1){
                int index = (tile->getYPos() +1)*(column) + tile->getXPos();
                breadthfirstAddNode(index, parent);
            }//up
            if(tile->getYPos()>0){
                int index = (tile->getYPos() -1)*(column) + tile->getXPos();
                breadthfirstAddNode(index, parent);
            }

            //4.push successorNode in to closed
            closedlist.push_back(currentNode);
        }
    }
    return false;
}

void Pathfinder::breadthfirstAddNode(int index, std::shared_ptr<Node> parent)
{
    if(!createdNoteIndex.contains(index))
    {
        // the node hasn't been created yet
        auto pos = std::make_shared<Tile>(std::move(*tiles[index]));
        if(!(std::isinf(tiles[index]->getValue())))
        {   //i the value is not inf, it is walkable
            openlist.push_back(std::make_shared<Node>(pos,parent));
            createdNoteIndex.insert(index);
        }
    }
}

bool Pathfinder::calcPath_BreadthFirst()
{
    //stay in while loop, until the goal is found or the openlist is empty
    while (!breadthfirstalorithum() && openlist.size()) {}

    //when there are still nodes left in the op
    if(openlist.size())
    {
        qDebug("Path is found!!!");
        while (currentNode->getPre()!=nullptr)
        {
            moveCost += 1+currentNode->getTile()->getValue();
            solution.push(currentNode->getTile());
            //show the path we have found one by one
            //screen->addPathStep(destination.getTile()->getXPos(),destination.getTile()->getYPos());
            currentNode=currentNode->getPre();
        }
        //now the currentNode is the startPoint node, we are on this node now
    }else
    {
        qDebug("BreathFirst: Path is not found in the end!!!!");
        return false;
    }
    return true;
}














