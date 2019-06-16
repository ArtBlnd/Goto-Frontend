#include "parser/TokenVerifier.h"

namespace GTFW
{
    bool Parser::tvIsInteger(const std::string& str)
    {
        for (char c : str)
        {
            if (c >= '0' && c <= '9')
            {
                continue;
            }

            return false;
        }

        return true;
    }

    bool Parser::tvIsBoolean(const std::string& str)
    {
        if (str == "true" || str == "1" || str == "false" || str == "0")
        {
            return true;
        }

        return false;
    }

    bool Parser::tvIsAlphabet(const std::string& str)
    {
        for (char c : str)
        {
            if (c >= 'a' && c <= 'z')
            {
                continue;
            }

            if (c >= 'A' && c <= 'Z')
            {
                continue;
            }

            return false;
        }

        return true;
    }
}