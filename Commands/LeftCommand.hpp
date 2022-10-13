#ifndef LEFTCOMMAND_H
#define LEFTCOMMAND_H

#include "ICommand.hpp"

class LeftCommand : public ICommand
{
public:
    LeftCommand()
    {
        Name = "LEFT";
    }

    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) override
    {
        toyRobot.RotateLeft();
    };
};

#endif