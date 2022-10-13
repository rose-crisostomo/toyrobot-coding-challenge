#ifndef RIGHTCOMMAND_H
#define RIGHTCOMMAND_H

#include <vector>
#include "ICommand.hpp"

class RightCommand : public ICommand
{
public:
    RightCommand()
    {
        Name = "RIGHT";
    }

    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) override
    {
        toyRobot.RotateRight();
    };
};

#endif