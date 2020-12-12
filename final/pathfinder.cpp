#include "pathfinder.h"

Pathfinder::Pathfinder(int row, int column, std::vector<std::shared_ptr<Tile>> newtiles)
{
    this->row=row;
    this->column=column;
    tiles=newtiles;
    Point startponit=Point();
    Point endponit=Point();
    currentNode=std::make_shared<Node>();
    //successorNode=currentNode;
    rootNode=currentNode;
}

void Pathfinder::showsolutionpath()
{
    QVectorIterator<std::shared_ptr<Tile>> i(solution);
    int index=0;
    while(i.hasNext())
    {
        auto tile=i.next();
        std::cout<<index++<<". Point is ("<<tile->getXPos()<<", "<<tile->getYPos()<<"). "<<std::endl;
    }
    std::cout<<"move cost: "<<moveCost<<std::endl;
}

void Pathfinder::showAllContainers()
{
    std::cout<<"createdIndex size:"<<createdNoteIndex.size()<<std::endl;
    std::cout<<"closedlist size:"<<closedlist.size()<<std::endl;
    std::cout<<"openlist size:"<<openlist.size()<<std::endl;
    std::cout<<"solution size:"<<solution.size()<<std::endl;
}

void Pathfinder::initialze(const std::shared_ptr<Tile> &p, const std::shared_ptr<Tile> goal)
{
    initializePathfinder(p->getXPos(), p->getYPos(), goal->getXPos(), goal->getYPos());
}

void Pathfinder::initializePathfinder(int startx, int starty, int endx, int endy)
{
    clearAllContainer();
    startPoint.setPoint(startx,starty);
    goalPoint.setPoint(endx,endy);
    //should be the tiles here, the map wasn't initialized
    rootNode=std::make_shared<Node>((tiles[startx+row*starty]));
    rootNode->setDistance(0);
    currentNode=rootNode;
    openlist.push_back(rootNode);
    moveCost=0;
    int index = (column)*starty + startx;
    createdNoteIndex.insert(index);
}

void Pathfinder::clearAllContainer()
{
    createdNoteIndex.clear();
    openlist.clear();
    closedlist.clear();
    solution.clear();
    currentNode=nullptr;
    //successorNode=nullptr;
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

void Pathfinder::generateSolution()
{
    while (currentNode->getPre()!=nullptr)
    {
        moveCost += currentNode->getTile()->getValue();
        solution.push(currentNode->getTile());
        //show the path we have found one by one
        //screen->addPathStep(destination.getTile()->getXPos(),destination.getTile()->getYPos());
        currentNode=currentNode->getPre();
    }
    //moveCost += 1+currentNode->getTile()->getValue();
    //solution.push(currentNode->getTile());
    //now the currentNode is the startPoint node, we are on this node now
}

//find the node that has been created from the openlist
QList<std::shared_ptr<Node>>::iterator Pathfinder::findOldNote(int index)
{
    std::shared_ptr<Tile> theTile =tiles[index];
    //std::shared_ptr<Node> theNodeFound = nullptr;
    for(auto it = openlist.begin(); it !=openlist.end(); it++)
    {
        if((*it)->getTile()==theTile)
        {
           return it;
        }
    }   
    return openlist.begin();
}
QList<std::shared_ptr<Node>>::iterator Pathfinder::findOldNoteinOpenlist(int index, bool & isInOpenlist)
{
    std::shared_ptr<Tile> theTile =tiles[index];
    isInOpenlist=false;
    for(auto it = openlist.begin(); it !=openlist.end(); it++)
    {
        if((*it)->getTile()==theTile)
        {
            isInOpenlist = true;
           return it;
        }
    }
    //the node wasn't found
    isInOpenlist=false;
    return openlist.begin();
}
QList<std::shared_ptr<Node>>::iterator Pathfinder::findOldNoteinClosedlist(int index, bool & isInClosedlist)
{
    std::shared_ptr<Tile> theTile =tiles[index];
    isInClosedlist = false;
    for(auto it = closedlist.begin(); it !=closedlist.end(); it++)
    {
        if((*it)->getTile()==theTile)
        {
            isInClosedlist = true;
           return it;
        }
    }
    isInClosedlist = false;
    return openlist.begin();
}

bool Pathfinder::isNodeInOpenlist(int index)
{
    std::shared_ptr<Tile> theTile =tiles[index];
    for(auto it = openlist.begin(); it !=openlist.end(); it++)
    {
        if((*it)->getTile()==theTile)
        {
           return true;
        }
    }
    return false;
}

bool Pathfinder::isNoteInClosedlist(int index)
{
    std::shared_ptr<Tile> theTile =tiles[index];
    for(auto it = closedlist.begin(); it !=closedlist.end(); it++)
    {
        if((*it)->getTile()==theTile)
        {
           return true;
        }
    }
    return false;
}

std::shared_ptr<Node> Pathfinder::findMinFinalCostNode()
{
    //find the node with te smallest final cost, get it out and remve it
    auto minFinalCostNode = std::min_element(openlist.begin(),openlist.end(), finalCostcomp);
    auto minNode = (*minFinalCostNode);
    openlist.erase(minFinalCostNode);
    return minNode;
}

// The following three medthos are or the breath-first algorithum
bool Pathfinder::calcPath_BreadthFirst()
{
    //stay in while loop, until the goal is found or the openlist is empty
    while (!breadthfirstalorithum() && openlist.size()) {}

    //when there are still nodes left in the op
    if(openlist.size())
    {
        //qDebug("Path is found!!!");
        generateSolution();
    }else
    {
        //qDebug("BreathFirst: Path is not found in the end!!!!");
        return false;
    }
    return true;
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
        auto pos = tiles[index];
        //auto pos = std::make_shared<Tile>(*tiles[index]);
        if(!(std::isinf(tiles[index]->getValue())))
        {   //i the value is not inf, it is walkable
            openlist.push_back(std::make_shared<Node>(pos,parent));
            createdNoteIndex.insert(index);
        }
    }
}


//The following three methods are for the best-first algorihum
bool Pathfinder::calcPath_BestFirst()
{
    //stay in while loop, until the goal is found or the openlist is empty
    while (!bestfirstalorithum() && openlist.size()) {}

    //when there are still nodes left in the op
    if(openlist.size())
    {
        qDebug("Path best first is found!!!");
        generateSolution();
    }else
    {
        qDebug("BestFirst: Path is not found in the end!!!!");
        return false;
    }
    return true;
}

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
                bestfirstAddNode(index, parent);
            }//left
            if(tile->getXPos()>0){
                auto index = (column)*(tile->getYPos()) + tile->getXPos() - 1;
                bestfirstAddNode(index, parent);
            }//down
            if(tile->getYPos()<row-1){
                int index = (tile->getYPos() +1)*(column) + tile->getXPos();
                bestfirstAddNode(index, parent);
            }//up
            if(tile->getYPos()>0){
                int index = (tile->getYPos() -1)*(column) + tile->getXPos();
                bestfirstAddNode(index, parent);
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

bool Pathfinder::calcPath_Dijkstra()
{
    //set the distance o the irst node to zero
    //stay in while loop, until the goal is found or the openlist is empty
    while (!dijkstraalorithum() && openlist.size()) {}

    //when there are still nodes left in the op
    if(openlist.size())
    {
        qDebug("Dijkstra: Path  is found!!!");
        generateSolution();
    }else
    {
        qDebug("dijkstra: Path is not found in the end!!!!");
        return false;
    }
    return true;
}

bool Pathfinder::dijkstraalorithum()
{
    while (openlist.size()!=0)
    {
        //1.pop the node that has the smallest givenCost
        //??maybe bug, it returned the reference in the list, will it be deleted after nest line execution?, maybe dequeue is better here
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
                dijkstraAddNode(index, parent);
            }//left
            if(tile->getXPos()>0){
                int index = (column)*(tile->getYPos()) + tile->getXPos() - 1;
                dijkstraAddNode(index, parent);
            }//down
            if(tile->getYPos()<row-1){
                int index = (tile->getYPos() +1)*(column) + tile->getXPos();
                dijkstraAddNode(index, parent);
            }//up
            if(tile->getYPos()>0){
                int index = (tile->getYPos() -1)*(column) + tile->getXPos();
                dijkstraAddNode(index, parent);
            }
            //4.push successorNode in to closed
            closedlist.push_back(currentNode);
        }
    }
    return false;
}

void Pathfinder::dijkstraAddNode(int index, std::shared_ptr<Node> parent)
{
    if(!(std::isinf(tiles[index]->getValue())))
    {
        //the value of the tile is not inf, it is walkable
        //auto pos = std::make_shared<Tile>((*tiles[index]));
        auto pos = tiles[index];
        auto newNode = std::make_shared<Node>(pos,parent);
        //set its distance to the givencost
        double distance = parent->getDistance() + pos->getValue();
        newNode->setDistance(distance);

        if(!createdNoteIndex.contains(index))
        {
        // the node hasn't been created yet
            openlist.push_back(newNode);
            createdNoteIndex.insert(index);
        }
        else//the node has been created before
        {
            //find the node from the openlist that points to the same tile with node
            auto oldNote = findOldNote(index);
            if( newNode->getDistance() < (*oldNote)->getDistance() )
            {
                openlist.erase(oldNote);
                openlist.push_back(newNode);
                //std::cout<<"a new node replaced old note: ("<<newNode->getTile()->getXPos()<<", "<<newNode->getTile()->getYPos()<<std::endl;
            }else{
                newNode=nullptr;
            }
        }
    }
}

bool Pathfinder::calcPath_Astar()
{
    //set the distance o the irst node to zero
    //stay in while loop, until the goal is found or the openlist is empty
    while (!aStaralorithum() && openlist.size()) {}

    //when there are still nodes left in the op
    if(openlist.size())
    {
        //qDebug("A*: Path  is found!!!");
        generateSolution();
    }else
    {
        //qDebug("A*: Path is not found in the end!!!!");
        return false;
    }
    return true;
}

bool Pathfinder::aStaralorithum()
{
    while (openlist.size()!=0)
    {
        //1.pop the node that has the best finalCost from the openlist and assign it to currentNode
        //??maybe bug, it returned the reference in the list, will it be deleted after nest line execution?, maybe dequeue is better here
        currentNode = findMinFinalCostNode();
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
                aStarAddNode(index, parent);
            }//left
            if(tile->getXPos()>0){
                int index = (column)*(tile->getYPos()) + tile->getXPos() - 1;
                aStarAddNode(index, parent);
            }//down
            if(tile->getYPos()<row-1){
                int index = (tile->getYPos() +1)*(column) + tile->getXPos();
                aStarAddNode(index, parent);
            }//up
            if(tile->getYPos()>0){
                int index = (tile->getYPos() -1)*(column) + tile->getXPos();
                aStarAddNode(index, parent);
            }
            //4.push successorNode in to closed
            closedlist.push_back(currentNode);
        }
    }
    return false;
}

void Pathfinder::aStarAddNode(int index, std::shared_ptr<Node> parent)
{
    if(!(std::isinf(tiles[index]->getValue())))
    {
        //the value of the tile is not inf, it is walkable
        double newGivenCost = currentNode->getGivenCost() + tiles[index]->getValue();
        if(createdNoteIndex.contains(index))
        {
            // the node has been created before

            bool findInOpenlist = false;
            auto oldNote = findOldNoteinOpenlist(index,findInOpenlist);
            if(findInOpenlist)
            {
                //the node is found in openlist
                if( newGivenCost < (*oldNote)->getGivenCost() )
                {
                    //update the old Note
                    (*oldNote)->setPre(parent);//parent = currentNode, set its parent to current Node
                    (*oldNote)->updateGivenCost(newGivenCost);
                }
            }
            else
            {
                //the node wasn't found in openlist
               bool findInClosedlist = false;
               oldNote = findOldNoteinClosedlist(index,findInClosedlist);
               if(findInClosedlist)
               {
                   //the node is found in closedlist
                   if( newGivenCost < (*oldNote)->getGivenCost() )
                   {
                       //pop the old node from closedlist and push it to openlist, it needs to be reconsidered
                       openlist.push_back(*oldNote);
                       closedlist.erase(oldNote);
                   }
               }
               else
               {
                   //if it wasn't found either in closelist or openlist, it shouldn't happen
                   qDebug("Can't find the old Node nether in open nor closed list, but its index has been created index");
               }
            }
        }
        else
        {
            //the node wasn't created yes
            auto newTile = tiles[index];
            auto newNode = std::make_shared<Node>(newTile,parent);
            //calcuate heuristic Cost
            double heuristicCost = calEuclideanDistance(newTile->getXPos() , goalPoint.getXpos() , newTile->getYPos() , goalPoint.getYpos());
            newNode->setHeuristicCost(heuristicCost);
            newNode->updateGivenCost(newGivenCost);

            //push the newNode to openlist
            openlist.push_back(newNode);
            createdNoteIndex.insert(index);
        }
    }
}

float Pathfinder::getMoveCost() const
{
    return moveCost;
}

bool Pathfinder::checkReachable(int x, int y)
{
    if(x < column && x>=0 && y < row && y >=0)
    {
        int index=y*column+x;
        if(!std::isinf(tiles[index]->getValue()))
        {
            return true;
        }
    }
    else
    {
        std::cout<<"out of the map"<<std::endl;
    }
    return false;
}

QStack<std::shared_ptr<Tile>> Pathfinder::findpath(const std::shared_ptr<Tile> &p, int x, int y)
{
    return findpath(p->getXPos(), p->getYPos(),x,y);
}

QStack<std::shared_ptr<Tile> > Pathfinder::findpath(int sx, int sy, int x, int y)
{
    initializePathfinder(sx, sy,x,y);
    if(sx == x && sy == y)
    {
       std::cout<<"You are alreay here! No need for pathfinding!"<<std::endl;
       return solution;
    }
    //showAllContainers();
    if(!checkReachable(x,y))
    {
        std::cout<<"The goal is unreachable, it is wall!"<<std::endl;
        return solution;
    }
    if(calcPath_Astar())
    {
        std::cout<<"Path A* is found ahaha"<<std::endl;
        showsolutionpath();
    }else{
        std::cout<<"Oh, no, Path A*  is not found..."<<std::endl;
    }
    showAllContainers();
    return solution;
}















