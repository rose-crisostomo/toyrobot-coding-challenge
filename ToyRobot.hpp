#ifndef TOYROBOT_H
#define TOYROBOT_H

#include "Coordinates.hpp"
#include "Direction.hpp"
#include <memory>

class ToyRobot
{
public:
    bool IsOnTheBoard();
    void GoTo(uint8_t const& x, uint8_t const& y, std::shared_ptr<Direction> dir);
    void Move();
    void ReportCurrentPosition();
    void Reset();
    void RotateLeft();
    void RotateRight();

    Coordinates currPos;
    std::shared_ptr<Direction> currDir;
};

#endif