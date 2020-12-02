#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include"world.h"
#include<memory>

//This class is used to fetch data from outside(here is lib world)
//into what we can use with view and controller
class Model :public QObject
{
public:
    Model(QString,int);
    //Getter for controller using
    int getRow() const;
    int getCol() const;
    std::vector<std::shared_ptr<Tile> > getTiles() const;
    std::shared_ptr<Protagonist> getProtagonist() const;
    std::vector<std::shared_ptr<Tile> > getHealthpacks() const;
    std::vector<std::shared_ptr<Enemy> > getEnemies() const;
    //Setter for manapulation from controller
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack(int);
    void take(int);

private:
    float maxEH;
    int scale=0;
    int row = 0;
    int col = 0;
//    float maxEH;
    bool readData();
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;

};

#endif // MODEL_H
