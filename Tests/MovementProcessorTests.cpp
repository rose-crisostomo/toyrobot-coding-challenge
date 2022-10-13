#include "catch.hpp"
#include "../Constants.hpp"
#include "../MovementProcessor.hpp"

TEST_CASE("Robot should move forward based on direction", "[MovementProcessor]")
{
    MovementProcessor moveProc;
    Coordinates c { 1,1 };

    SECTION("Position should increase on the y-axis from North")
    {
        int expectedX = c.x, expectedY = c.y + 1;
        auto dir = moveProc.GetDirectionObj(DirectionConstants::NORTH);
        dir->move(&c);

        CHECK(c.x == expectedX);
        CHECK(c.y == expectedY);
    }

    SECTION("Position should increase on the x-axis from East")
    {
        int expectedX = c.x + 1, expectedY = c.y;
        auto dir = moveProc.GetDirectionObj(DirectionConstants::EAST);
        dir->move(&c);

        CHECK(c.x == expectedX);
        CHECK(c.y == expectedY);
    }

    SECTION("Position should decrease on the y-axis from South")
    {
        int expectedX = c.x, expectedY = c.y - 1;
        auto dir = moveProc.GetDirectionObj(DirectionConstants::SOUTH);
        dir->move(&c);

        CHECK(c.x == expectedX);
        CHECK(c.y == expectedY);
    }

    SECTION("Position should decrease on the x-axis from West")
    {
        int expectedX = c.x - 1, expectedY = c.y;
        auto dir = moveProc.GetDirectionObj(DirectionConstants::WEST);
        dir->move(&c);

        CHECK(c.x == expectedX);
        CHECK(c.y == expectedY);
    }
}