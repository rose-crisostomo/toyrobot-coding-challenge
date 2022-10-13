#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "catch.hpp"
#include "../Constants.hpp"
#include "../CommandProcessor.hpp"
#include "../ToyRobot.hpp"

std::string CreatePlaceCommand(int const& x, int const& y, std::string const& dir)
{
    return "PLACE " + std::to_string(x) + "," + std::to_string(y) + "," + dir;
}

TEST_CASE("Robot should be placed at a valid position facing a valid direction", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    std::string const directions[] = { DirectionConstants::NORTH, DirectionConstants::EAST, DirectionConstants::WEST, DirectionConstants::SOUTH };
    int x = 0, y = 0;

    for (auto dir : directions)
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, dir));

        CHECK(toyRobot.currDir->name == dir);
        CHECK(toyRobot.currPos.x == x);
        CHECK(toyRobot.currPos.y == y);
    }
}

TEST_CASE("Robot should not be placed when an invalid direction is provided", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    std::string const directions[] = { "invalid", "", " ", "123", "!@#", "NORTHEAST" };
    int x = 0, y = 0;

    for (auto dir : directions)
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, dir));

        CHECK(toyRobot.currDir == nullptr);
    }
}

TEST_CASE("Toy Robot should not be placed outside the board", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;
    MovementProcessor moveProc;
    auto const& limits = moveProc.GetLimits();

    cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(limits.low - 1, limits.low - 1, DirectionConstants::NORTH));
    CHECK(toyRobot.currDir == nullptr);

    cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(limits.high + 1, limits.high + 1, DirectionConstants::NORTH));
    CHECK(toyRobot.currDir == nullptr);
}

TEST_CASE("First command should be PLACE", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    std::string dir = DirectionConstants::NORTH;
    int x = 0, y = 0;

    SECTION("Other commands are ignored until the robot is placed")
    {
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currDir == nullptr);

        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currDir == nullptr);

        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currDir == nullptr);

        cmdProc.ExecuteCommand(toyRobot, CommandConstants::REPORT);
        CHECK(toyRobot.currDir == nullptr);
    }

    cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, dir));
    CHECK(toyRobot.currDir->name == dir);

    SECTION("Subsequent commands should be processed")
    {
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currPos.y == (y + 1));
    }

    SECTION("Another PLACE command should be processed")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, dir));
        CHECK(toyRobot.currPos.y == y);
    }
}

TEST_CASE("MOVE should move the robot one unit forward", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;
    MovementProcessor moveProc;
    auto const& limits = moveProc.GetLimits();

    int x = 0, y = 0;

    cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::NORTH));
    cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
    CHECK(toyRobot.currPos.y == (y + 1));

    SECTION("Robot should not fall off the board facing NORTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, limits.high, DirectionConstants::NORTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currPos.y == limits.high);
    }

    SECTION("Robot should not fall off the board facing EAST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(limits.high, y, DirectionConstants::EAST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currPos.x == limits.high);
    }

    SECTION("Robot should not fall off the board facing SOUTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, limits.low, DirectionConstants::SOUTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currPos.y == limits.low);
    }

    SECTION("Robot should not fall off the board facing WEST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(limits.low, y, DirectionConstants::WEST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::MOVE);
        CHECK(toyRobot.currPos.x == limits.low);
    }
}

TEST_CASE("LEFT should rotate the robot", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    int x = 0, y = 0;

    SECTION("LEFT should rotate the robot facing WEST from NORTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::NORTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currDir->name == DirectionConstants::WEST);
    }

    SECTION("LEFT should rotate the robot facing SOUTH from WEST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::WEST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currDir->name == DirectionConstants::SOUTH);
    }

    SECTION("LEFT should rotate the robot facing EAST from SOUTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::SOUTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currDir->name == DirectionConstants::EAST);
    }

    SECTION("LEFT should rotate the robot facing NORTH from EAST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::EAST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currDir->name == DirectionConstants::NORTH);
    }

    SECTION("LEFT should not move the robot")
    {
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::LEFT);
        CHECK(toyRobot.currPos.x == x);
        CHECK(toyRobot.currPos.y == y);
    }
}

TEST_CASE("RIGHT should rotate the robot", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    int x = 0, y = 0;

    SECTION("RIGHT should rotate the robot facing EAST from NORTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::NORTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currDir->name == DirectionConstants::EAST);
    }

    SECTION("RIGHT should rotate the robot facing SOUTH from EAST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::EAST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currDir->name == DirectionConstants::SOUTH);
    }

    SECTION("RIGHT should rotate the robot facing WEST from SOUTH")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::SOUTH));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currDir->name == DirectionConstants::WEST);
    }

    SECTION("RIGHT should rotate the robot facing NORTH from WEST")
    {
        cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::WEST));
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currDir->name == DirectionConstants::NORTH);
    }

    SECTION("RIGHT should not move the robot")
    {
        cmdProc.ExecuteCommand(toyRobot, CommandConstants::RIGHT);
        CHECK(toyRobot.currPos.x == x);
        CHECK(toyRobot.currPos.y == y);
    }
}

TEST_CASE("REPORT should print the current position and direction to console", "[CommandProcessor]")
{
    ToyRobot toyRobot;
    CommandProcessor cmdProc;

    int x = 0, y = 0;
    std::string expectedOutput = std::to_string(x) + "," + std::to_string(y) + "," + DirectionConstants::NORTH + "\n";

    cmdProc.ExecuteCommand(toyRobot, CreatePlaceCommand(x, y, DirectionConstants::NORTH));

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf(strCout.rdbuf());

    cmdProc.ExecuteCommand(toyRobot, CommandConstants::REPORT);

    std::cout.rdbuf(oldCoutStreamBuf);

    REQUIRE(!strCout.str().empty());
    CHECK(strCout.str() == expectedOutput);
}