#include <fstream>
#include <sstream>
#include "ParserUtil.hpp"

std::vector<std::string> ParserUtil::ParseFileIntoList(std::string const& filename)
{
    std::vector<std::string> ret;

    std::ifstream file(filename);
    std::string line;
    while (getline(file, line))
    {
        std::istringstream iss(line);
        ret.push_back(line);
    }

    return ret;
}