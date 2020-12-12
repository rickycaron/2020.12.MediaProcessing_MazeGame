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
    //Getter for controller using
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
    void attack(int);
    int take(int);
    void gotoXY(int x, int y);
    bool isOutside(int x,int y);
    void consumeEnergy();
    bool setIsChangable(bool);
    bool getIsChangable();
    void autoplay();


    std::shared_ptr<XEnemy> getXEnemy() const;

private:
    float difficulty{0.1};
    float maxEH;
    int row = 0;
    int col = 0;
    bool isChangable =true;
    //bool isPosional =false;
    int enemyType =NONE;
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
    int autonextThing =0;//(0,normal;1 healthpack;2,enemy)

    std::vector<std::shared_ptr<Tile>> getNearestHealthpack();
    std::vector<std::shared_ptr<Tile>> getNearestEnemy();  
    std::shared_ptr<Tile> gotoNearestThing();
signals:
    void detectedSignal(int type, int index);
    void poisonTilesPermanent(int);
    void xEnemyShown();
private slots:
    void move();
};

#endif // MODEL_H
