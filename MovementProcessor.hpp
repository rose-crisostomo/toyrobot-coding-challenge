#ifndef MOVEMENTPROCESSOR_H
#define MOVEMENTPROCESSOR_H

#include <map>
#include <memory>
#include <string>
#include "Boundary.hpp"
#include "Direction.hpp"

class MovementProcessor
{
public:
    MovementProcessor();

    std::shared_ptr<Direction> GetDirectionObj(std::string const& dir);
    Boundary const& GetBoundary();

private:
    void InitializeDirections();
    void InitializeDirectionMap();

    Boundary boundary { 0, 4 };
    std::map<std::string, std::shared_ptr<Direction>> directionMap;
};

#endif