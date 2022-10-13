#ifndef PARSERUTIL_H
#define PARSERUTIL_H

#include <string>
#include <vector>

class ParserUtil
{
public:
    std::vector<std::string> ParseFileIntoList(std::string const& filename);
    std::vector<std::string> ParseStringWithDelimiter(std::string const& in, char const& delimiter);
};

#endif