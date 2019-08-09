#include "language/TokenTable.h"

namespace Goto
{
namespace Language
{

bool ttIsInteger(const std::string& str)
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

bool ttIsBoolean(const std::string& str)
{
    if (str == "true" || str == "1" || str == "false" || str == "0")
    {
        return true;
    }

    return false;
}

bool ttIsAlphabet(const std::string& str)
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

bool ttIsAlphabet(const char c)
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

bool ttFastStrCmp16(const std::string& str1, const std::string& str2)
{
    // We are just using normal compare just for now
    // enabling it after using SmallString implementations.
    return str1 == str2;
}

} // namespace Language
} // namespace Goto