#ifndef GOTOXY_H
#define GOTOXY_H

#include "command.h"

class GotoXY : public Command
{
public:
    explicit GotoXY(std::shared_ptr<Controller> con);
    void excute() const override;
    void setDestination(int x, int y);
private:
    int xPos;
    int yPos;
};

#endif // GOTOXY_H
