#include <iostream>
#include "CommandProcessor.hpp"
#include "Constants.hpp"
#include <regex>
#include "StringUtil.hpp"

CommandProcessor::CommandProcessor()
{
    InitializeCommandMap();
    BuildCommandListString();

    cmdPattern = "^(" + cmdList + ")\\s?(.*)";
}

void CommandProcessor::InitializeCommandMap()
{
    commandMap[CommandConstants::PLACE] = std::make_unique<PlaceCommand>();
    commandMap[CommandConstants::MOVE] = std::make_unique<MoveCommand>();
    commandMap[CommandConstants::REPORT] = std::make_unique<ReportCommand>();
    commandMap[CommandConstants::LEFT] = std::make_unique<LeftCommand>();
    commandMap[CommandConstants::RIGHT] = std::make_unique<RightCommand>();
}

void CommandProcessor::BuildCommandListString()
{
    for (auto const& cmd : commandMap)
    {
        cmdList += cmd.first + "|";
    }

    cmdList = cmdList.substr(0, cmdList.size() - 1);
}

void CommandProcessor::ExecuteCommand(ToyRobot& toyRobot, std::string const& input)
{
    if (input.empty()) return;

    std::string command = input;

    transform(command.begin(), command.end(), command.begin(), ::toupper);
    StringUtil::trim(command);

    auto parsedCmd = ExtractCommandAndArgs(command, cmdPattern);
    if (parsedCmd.empty()) return;

    auto const& cmd = commandMap.at(parsedCmd[1]);
    if (!CanExecuteCommand(cmd, toyRobot.IsOnTheBoard(), parsedCmd[1])) return;

    auto args = ExtractArgs(parsedCmd[2], cmd->ArgsPattern);
    if (args.empty()) return;

    cmd->Execute(toyRobot, args);
}

std::smatch CommandProcessor::ExtractCommandAndArgs(std::string const& command, std::string const& argsPattern)
{
    auto parsedCmd = GetMatches(command, argsPattern);
    if (parsedCmd.empty())
    {
        std::cerr << "ERROR: Invalid command [" + command + "] provided. Expecting {" + cmdList + "}" << std::endl;
    };

    return parsedCmd;
}

bool CommandProcessor::CanExecuteCommand(std::unique_ptr<ICommand> const& cmd, bool const& toyHasBeenPlaced, std::string const& command)
{
    if (!toyHasBeenPlaced && (dynamic_cast<PlaceCommand*>(cmd.get()) == nullptr))
    {
        std::cout << "ERROR: Ignoring command [" << command << "]. PLACE should be done first." << std::endl;
        return false;
    }
    return true;
}

std::smatch CommandProcessor::ExtractArgs(std::string const& args, std::string const& argsPattern)
{
    auto parsedArgs = GetMatches(args, argsPattern);
    if (parsedArgs.empty())
    {
        std::cerr << "ERROR: Invalid arguments [" + args + "] provided. " +
        "Expecting <number>,<number>," +
        "{" + DirectionConstants::NORTH + "|" + DirectionConstants::EAST + "|" +
        DirectionConstants::WEST + "|" + DirectionConstants::SOUTH + "}" << std::endl;
    };

    return parsedArgs;
}

std::smatch CommandProcessor::GetMatches(std::string const& in, std::string const& pattern)
{
    std::regex rgx(pattern);
    std::smatch matches;
    std::regex_search(in, matches, rgx);

    return matches;
}