#ifndef MODEL_H
#define MODEL_H
#include<QObject>
#include"world.h"
#include<memory>

//This class is used to fetch data from outside(here is lib world)
//into what we can use with view and controller
class Model :public QObject
{
    Q_OBJECT
public:

    Model(QString,int,QObject *parent);
    //Getter for controller using
    int getRow() const;
    int getCol() const;
    std::vector<std::shared_ptr<Tile> > getTiles() const;
    std::shared_ptr<Protagonist> getProtagonist() const;
    std::vector<std::shared_ptr<Tile> > getHealthpacks() const;
    std::vector<std::shared_ptr<Enemy> > getEnemies() const;
    std::vector<std::shared_ptr<PEnemy> > getPEnemies() const;
    //Setter for manapulation from controller
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void consumeEnergy();
    void attack(int);
    int take(int);
    bool setIsChangable(bool);
    bool getIsChangable();



private:
    float difficulty =0.1;
    float maxEH;
    int scale=0;
    int row = 0;
    int col = 0;
    bool isChangable =true;
    bool isPosional =false;
    enum type{NONE=-1,ENEMY=0,PENEMY,HEALTHPACK};
//    float maxEH;
    bool readData();
    std::unique_ptr<World> world;
    std::shared_ptr<Protagonist> protagonist;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Enemy>> normalEnemies;
    std::vector<std::shared_ptr<PEnemy>> pEnemies;
    std::vector<std::shared_ptr<Tile>> healthpacks;

signals:
    void detectedSignal(int type, int index);
//private slots :
//    int detectEnemy(int,int);

};

#endif // MODEL_H
