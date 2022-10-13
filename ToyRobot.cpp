#include <iostream>
#include <string>
#include "ToyRobot.hpp"

void ToyRobot::Move()
{
    currDir->move(&currPos);
}

void ToyRobot::GoTo(uint8_t const& x, uint8_t const& y, std::shared_ptr<Direction> dir)
{
    currPos.x = x;
    currPos.y = y;
    currDir = dir;
}

void ToyRobot::ReportCurrentPosition()
{
    std::cout << std::to_string(currPos.x) << "," << std::to_string(currPos.y) << "," << currDir->name << std::endl;
}

void ToyRobot::RotateLeft()
{
    currDir = currDir->left;
}

void ToyRobot::RotateRight()
{
    currDir = currDir->right;
}

void ToyRobot::Reset()
{
    currDir = nullptr;
    currPos.x = 0;
    currPos.y = 0;
}

bool ToyRobot::IsOnTheBoard()
{
    return currDir != nullptr;
}