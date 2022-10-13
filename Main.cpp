#include <iostream>
#include <string>
#include <algorithm>
#include "CommandProcessor.hpp"
#include "ParserUtil.hpp"
#include "ToyRobot.hpp"

int main(int argc, char const* argv[])
{
    ToyRobot toyRobot;
    ParserUtil parserUtil;
    CommandProcessor cmdProc;

    std::string inputFile = "input.txt";
    if (argc == 2)
    {
        inputFile = argv[1];
    }

    for (auto line : parserUtil.ParseFileIntoList(inputFile))
    {
        if (line.empty())
        {
            toyRobot.Reset();
            std::cout << std::endl;
            continue;
        }

        cmdProc.ExecuteCommand(toyRobot, line);
    }

    return 0;
}