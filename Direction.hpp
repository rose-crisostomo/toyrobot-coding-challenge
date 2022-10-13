#ifndef DIRECTION_H
#define DIRECTION_H

#include <functional>
#include <memory>
#include <string>
#include "Coordinates.hpp"

struct Direction
{
    std::shared_ptr<Direction> left;
    std::shared_ptr<Direction> right;
    std::function<void(Coordinates*)> move;
    std::string name;
};

#endif