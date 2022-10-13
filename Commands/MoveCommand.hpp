#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "ICommand.hpp"

class MoveCommand : public ICommand
{
public:
    MoveCommand()
    {
        Name = "MOVE";
    }

    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) override
    {
        toyRobot.Move();
    };
};

#endif