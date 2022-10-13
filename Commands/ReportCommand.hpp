#ifndef REPORTCOMMAND_H
#define REPORTCOMMAND_H

#include <vector>
#include "ICommand.hpp"

class ReportCommand : public ICommand
{
public:
    ReportCommand()
    {
        Name = "REPORT";
    }

    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) override
    {
        toyRobot.ReportCurrentPosition();
    };
};

#endif