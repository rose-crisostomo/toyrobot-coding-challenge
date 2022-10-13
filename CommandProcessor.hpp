#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>
#include "Constants.hpp"
#include "ParserUtil.hpp"
#include "ToyRobot.hpp"

#include "Commands/LeftCommand.hpp"
#include "Commands/MoveCommand.hpp"
#include "Commands/PlaceCommand.hpp"
#include "Commands/ReportCommand.hpp"
#include "Commands/RightCommand.hpp"


class CommandProcessor
{
public:
    CommandProcessor();

    void ExecuteCommand(ToyRobot& toyRobot, std::string const& input);

private:
    bool CanExecuteCommand(std::unique_ptr<ICommand> const& cmd, bool const& toyHasBeenPlaced, std::string const& command);
    bool IsValidCommand(std::string const& command);
    std::smatch ExtractArgs(std::string const& args, std::string const& argsPattern);
    std::smatch ExtractCommandAndArgs(std::string const& command, std::string const& argsPattern);
    std::smatch GetMatches(std::string const& in, std::string const& pattern);
    void BuildCommandListString();
    void InitializeCommandMap();

    ParserUtil parserUtil;

    std::map<std::string, std::unique_ptr<ICommand>> commandMap;
    std::string cmdList = "";
    std::string cmdPattern;
};

#endif