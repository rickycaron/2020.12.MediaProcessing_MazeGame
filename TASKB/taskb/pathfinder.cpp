#include "pathfinder.h"

pathfinder::pathfinder(int row, int column)
{
    this->row=row;
    this->column=column;
    Point startponit=Point();
    Point endponit=Point();
}

void pathfinder::initializePathfinder(int startx, int starty, int endx, int endy)
{
    clearAllContainer();
    startPoint.setPoint(startx,starty);
    goalPoint.setPoint(endx,endy);
    rootNode=std::make_shared<Node>(move(tiles[startx+row*starty]),nullptr);
    currentNode=rootNode;
    openlist.push_back(rootNode);
}

void pathfinder::clearAllContainer()
{
    openlist.clear();
    closedlist.clear();
    solution.clear();
    currentNode=nullptr;
    successorNode=nullptr;
    rootNode=nullptr;
}

bool pathfinder::reachinGoal()
{
    if(currentNode==nullptr)
    {
        return false;
    }
    if(currentNode->getTile()->getXPos()==goalPoint.getXpos()&&currentNode->getTile()->getYPos()==goalPoint.getYpos()){
        return true;
    }
    else
    {
        return false;
    }
}

bool pathfinder::breadthfirstalorithum()
{
    while (openlist.size()!=0)
    {
        //1.pop the node that has been waiting the longest
        //??maybe bug, it returned the reference in th list, will it be deleted after nest line execution?, maybe dequeue is better here
        currentNode=openlist.front();
        auto tile=currentNode->getTile();
        auto parent =std::make_shared<Node>(currentNode);
        openlist.erase(openlist.begin());
        //2.check if reached in goal
        if(reachinGoal())
        {
            solution.push_back(currentNode);
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

bool pathfinder::breadthfirstAddNode(int index, std::shared_ptr<Node> parent)
{

}
