#include "pathfinder.h"

Pathfinder::Pathfinder(int row, int column, std::vector<std::shared_ptr<Tile>> newtiles)
{
    this->row=row;
    this->column=column;
    tiles=newtiles;
    Point startponit=Point();
    Point endponit=Point();
    currentNode=std::make_shared<Node>();
    successorNode=currentNode;
    rootNode=currentNode;
}

void Pathfinder::showsolutionpath()
{
    while (!solution.isEmpty()) {
        auto tile=solution.pop();
        std::cout<<solution.size()<<". Point is ("<<tile->getXPos()<<", "<<tile->getYPos()<<"). "<<std::endl;
    }
}

void Pathfinder::initialze(const std::shared_ptr<Tile> &p, const std::shared_ptr<Tile> goal)
{
    initializePathfinder(p->getXPos(), p->getYPos(), goal->getXPos(), goal->getYPos());
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

void Pathfinder::initializePathfinder(int startx, int starty, int endx, int endy)
{
    clearAllContainer();
    startPoint.setPoint(startx,starty);
    goalPoint.setPoint(endx,endy);
    rootNode=std::make_shared<Node>(move(tiles[startx+row*starty]),nullptr);
    currentNode=rootNode;
    openlist.push_back(rootNode);
    moveCost=0;
    int index = (column)*starty + startx;
    createdNoteIndex.insert(index);
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

double Pathfinder::calEuclideanDistance(double x1, double y1, double x2, double y2)
{
    double xDistance = x1-x2;
    double yDistance = y1-y2;
    double distance=sqrt( pow( xDistance ,2) + pow( yDistance ,2) );
    return distance;
}




std::shared_ptr<Node> Pathfinder::findMinDistanceNode()
{
    //find the node closest to the destinaon from the openlist, get it out and remve it
    auto minDistanceNode = std::min_element(openlist.begin(),openlist.end(), distanncecomp );
    auto minNode = (*minDistanceNode);
    openlist.erase(minDistanceNode);
    return minNode;
}

// The following three medthos are or the breath-first algorithum
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
        //auto pos = std::make_shared<Tile>(std::move(*tiles[index]));
        auto pos = std::make_shared<Tile>((*tiles[index]));
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


//The following three methods are for the best-first algorihum
bool Pathfinder::bestfirstalorithum()
{
    while (openlist.size()!=0)
    {
        //1.pop the node that has the best heuristicCost
        //??maybe bug, it returned the reference in th list, will it be deleted after nest line execution?, maybe dequeue is better here
        currentNode = findMinDistanceNode();
        auto tile=currentNode->getTile();
        auto parent =currentNode;
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

void Pathfinder::bestfirstAddNode(int index, std::shared_ptr<Node> parent)
{
    if(!createdNoteIndex.contains(index))
    {
        // the node hasn't been created yet
        if(!(std::isinf(tiles[index]->getValue())))
        {   //the value of the tile is not inf, it is walkable
            auto pos = std::make_shared<Tile>((*tiles[index]));
            auto newNode = std::make_shared<Node>(pos,parent);
            //set its distance from this node to the goal point
            double distance = calEuclideanDistance(pos->getXPos() , goalPoint.getXpos() , pos->getYPos() , goalPoint.getYpos());
            newNode->setDistance(distance);
            openlist.push_back(newNode);
            createdNoteIndex.insert(index);
        }
    }
}

bool Pathfinder::calcPath_BestFirst()
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










