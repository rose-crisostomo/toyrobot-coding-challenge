#include "MovementProcessor.hpp"
#include "Constants.hpp"

MovementProcessor::MovementProcessor()
{
    InitializeDirectionMap();
    InitializeDirections();
}

void MovementProcessor::InitializeDirectionMap()
{
    directionMap[DirectionConstants::NORTH] = std::make_shared<Direction>();
    directionMap[DirectionConstants::EAST] = std::make_shared<Direction>();
    directionMap[DirectionConstants::SOUTH] = std::make_shared<Direction>();
    directionMap[DirectionConstants::WEST] = std::make_shared<Direction>();
}

void MovementProcessor::InitializeDirections()
{
    auto const& north = directionMap[DirectionConstants::NORTH];
    auto const& east = directionMap[DirectionConstants::EAST];
    auto const& south = directionMap[DirectionConstants::SOUTH];
    auto const& west = directionMap[DirectionConstants::WEST];

    north->left = west;
    north->right = east;
    north->name = DirectionConstants::NORTH;
    north->move = [this](Coordinates* c)
        {
            if (c->y != boundary.high)
            {
                ++(c->y);
            }
        };

    east->left = north;
    east->right = south;
    east->name = DirectionConstants::EAST;
    east->move = [this](Coordinates* c)
        {
            if (c->x != boundary.high)
            {
                ++(c->x);
            }
        };

    south->left = east;
    south->right = west;
    south->name = DirectionConstants::SOUTH;
    south->move = [this](Coordinates* c)
        {
            if (c->y != boundary.low)
            {
                --(c->y);
            }
        };

    west->left = south;
    west->right = north;
    west->name = DirectionConstants::WEST;
    west->move = [this](Coordinates* c)
        {
            if (c->x != boundary.low)
            {
                --(c->x);
            }
        };
}

std::shared_ptr<Direction> MovementProcessor::GetDirectionObj(std::string const& dir)
{
    try
    {
        return directionMap.at(dir);
    }
    catch(const std::exception& e)
    {
        return nullptr;
    }
}

Boundary const& MovementProcessor::GetBoundary()
{
    return boundary;
}