#ifndef PLACECOMMAND_H
#define PLACECOMMAND_H

#include "ICommand.hpp"
#include "../MovementProcessor.hpp"
#include "../Constants.hpp"

class PlaceCommand : public ICommand, virtual public MovementProcessor
{
public:
    PlaceCommand()
    {
        Name = "PLACE";
        ArgsPattern = "^(\\d+),(\\d+),(" + DirectionConstants::NORTH + "|" + DirectionConstants::EAST + "|" +
            DirectionConstants::WEST + "|" + DirectionConstants::SOUTH + ")$";
    }

    virtual void Execute(ToyRobot& toyRobot, std::smatch const& args = {}) override
    {
        auto x = stoi(args[1]);
        auto y = stoi(args[2]);

        if (!IsCoordinateWithinBoard(x) || !IsCoordinateWithinBoard(y))
        {
            std::cerr << "ERROR: Coordinates (" << args[1] << "," << args[2] << ") are outside of the board" << std::endl;
            return;
        }

        auto dir = GetDirectionObj(args[3]);
        if (dir == nullptr)
        {
            std::cerr << "ERROR: Direction [" << args[3] << "] not recognized" << std::endl;
            return;
        }

        toyRobot.GoTo(x, y, dir);
    }

private:
    bool IsCoordinateWithinBoard(int const& c)
    {
        auto const& boundary = GetBoundary();
        return (c <= boundary.high) && (c >= boundary.low);
    }
};

#endif