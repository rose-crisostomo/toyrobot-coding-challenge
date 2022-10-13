#ifndef PARSERUTIL_H
#define PARSERUTIL_H

#include <string>
#include <vector>

class ParserUtil
{
public:
    std::vector<std::string> ParseFileIntoList(std::string const& filename);
};

#endif