#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include"world.h"
#include "pathfinder.h"
#include<memory>
#include "xenemy.h"

//This class is used to fetch data from outside(here is lib world)
//into what we can use with view and controller
class Model :public QObject
{
    Q_OBJECT
public:
    Model(QString fileName);
    int getRow() const;
    int getCol() const;
    std::vector<std::shared_ptr<Tile> > getTiles() const;
    std::shared_ptr<Protagonist> getProtagonist() const;
    std::vector<std::shared_ptr<Tile> > getHealthpacks() const;
    std::vector<std::shared_ptr<Enemy> > getEnemies() const;
    std::vector<std::shared_ptr<PEnemy> > getPEnemies() const;
    //Setter for manapulation from controller
    bool moveRight();
    bool moveLeft();
    bool moveUp();
    bool moveDown();
    void attack();
    int take();
    void gotoXY(int x, int y);
    bool isOutside(int x,int y);
    void consumeEnergy();
    bool setIsChangable(bool);
    bool getIsChangable();
    std::shared_ptr<Tile> gotoNearestThing();
    std::shared_ptr<XEnemy> getXEnemy() const;


private:
    float difficulty{0.1};
    float maxEH;
    int row = 0;
    int col = 0;
    bool isChangable =true;
    enum type thingType =NONE;
    int thingIndex=-1;
    int baseScore=1;
    int numOfEnemies;

    bool readData();
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> normalEnemies;
    std::vector<std::shared_ptr<PEnemy>> pEnemies;
    std::shared_ptr<XEnemy> xEnemy;
    std::vector<std::shared_ptr<Tile>> healthpacks;
    std::shared_ptr<Pathfinder> pathfinder;
    QStack<std::shared_ptr<Tile>> path;
    std::vector<std::shared_ptr<Tile>> getNearestHealthpack();
    std::vector<std::shared_ptr<Node>> getNearestEnemy();

signals:
    void poisonTilesPermanent(int);
    void xEnemyShown();
    void updateScoreBoard(int);
    void protagonistGetPoisoned();
    void numOfEnemiesChanged(int);

public slots:
    void move();
};

#endif // MODEL_H
