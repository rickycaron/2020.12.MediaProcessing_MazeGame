#ifndef GOTOXY_H
#define GOTOXY_H

#include "command.h"

class GotoXY : public Command
{
public:
    explicit GotoXY(std::shared_ptr<Controller> con);
    void excute() const override;
    void setDestination(int x, int y) override;
private:
    int xPos{-1};
    int yPos{-1};
};

#endif // GOTOXY_H
