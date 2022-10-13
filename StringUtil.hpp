#ifndef STRINGUTIL_H
#define STRINGUTIL_H

#include <algorithm>
#include <string>

class StringUtil
{
public:
    static inline void ltrim(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }));
    }

    static inline void rtrim(std::string& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
        {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    static inline void trim(std::string& s)
    {
        ltrim(s);
        rtrim(s);
    }

    static inline void to_upper(std::string& s)
    {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
    }
};

#endif