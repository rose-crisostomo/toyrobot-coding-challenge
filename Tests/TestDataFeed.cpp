#include <iostream>
#include <sstream>
#include "catch.hpp"
#include "../CommandProcessor.hpp"
#include "../ParserUtil.hpp"
#include "../Constants.hpp"

std::string RemoveNewline(std::string const& s)
{
    std::string::size_type pos = s.find('\n');
    if (pos != std::string::npos)
    {
        return s.substr(0, pos);
    }

    return s;
}

TEST_CASE("Validate robot position based on test data", "[TestData]")
{
    ParserUtil parserUtil;
    CommandProcessor cmdProc;
    ToyRobot toyRobot;

    std::ostringstream strCout;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    for (auto line : parserUtil.ParseFileIntoList("../Tests/test-data.txt"))
    {
        if (line.find("Output") != std::string::npos)
        {
            std::cout.rdbuf(oldCoutStreamBuf);

            auto actual = RemoveNewline(strCout.str());
            if (line.find(':') == (line.size() - 1))
            {
                CHECK_THAT(actual, Catch::Matchers::Contains("ERROR"));
            }
            else
            {
                auto expected = line.substr(line.find(':') + 1);
                CHECK(actual == expected);
            }

            toyRobot.Reset();
        }
        else
        {
            if (line.find(CommandConstants::REPORT) != std::string::npos)
            {
                std::cout.rdbuf(strCout.rdbuf());
                strCout.str("");
            }

            cmdProc.ExecuteCommand(toyRobot, line);
        }
    }
}