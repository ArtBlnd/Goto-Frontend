#include "language/TokenVerifier.h"

namespace Goto
{
    bool Language::tvIsInteger(const std::string& str)
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

    bool Language::tvIsBoolean(const std::string& str)
    {
        if (str == "true" || str == "1" || str == "false" || str == "0")
        {
            return true;
        }

        return false;
    }

    bool Language::tvIsAlphabet(const std::string& str)
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

    bool Language::tvIsAlphabet(const char c)
    {
        if (c >= 'a' && c <= 'z')
        {
            return true;
        }

        if (c >= 'A' && c <= 'Z')
        {
            return true;
        }
        
        return false;
    }
}