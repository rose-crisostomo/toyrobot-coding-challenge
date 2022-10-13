#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <regex>
#include "../ToyRobot.hpp"

class ICommand
{
public:
    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) = 0;
    std::string Name;
    std::string ArgsPattern;
};

#endif