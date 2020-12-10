#ifndef CONFIG_H
#define CONFIG_H



#define PROTAGONIST_UP_IMAGE  ":/images/protagonistUp.png"
#define PROTAGONIST_DOWN_IMAGE ":/images/protagonistDown.png"
#define PROTAGONIST_LEFT_IMAGE ":/images/protagonistLeft.png"
#define PROTAGONIST_RIGHT_IMAGE ":/images/protagonistRight.png"


#define PENEMY_IMAGE ":/images/penemy%1.png"
#define ENEMY_IMAGE ":/images/enemy.png"

#define GRAVE_IMAGE ":/images/grave.png"


enum axis{X=0,Y=1};
enum type{NONE=-1,ENEMY=0,PENEMY,HEALTHPACK};
enum sign{POSITIVE=1,NEGATIVE=-1};
enum direction{UP=0,DOWN,LEFT,RIGHT,TAKE,ATTACK,ENTER};

#endif // CONFIG_H
