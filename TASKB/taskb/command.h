#ifndef COMMAND_H
#define COMMAND_H


class Command
{
public:
    Command();
    virtual void excute() const = 0;
};

#endif // COMMAND_H
