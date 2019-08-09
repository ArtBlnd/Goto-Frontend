#include "language/transform.h"


namespace Goto
{

bool Language::tfStr2BoolTransform(const std::string& str)
{
    if (str.length() == 1)
    {
        return str[0] == '1';
    }

    if (str == "true")
    {
        return true;
    }
    if (str == "false")
    {
        return false;
    }

    // Unknown token for boolean transformation
    // emit exeception.
    return false;
}

int Language::tfStr2IntegerTransform(const std::string& str)
{
    // TODO : self-implements.
    return std::atoi(str.c_str());
}

} // namespace Goto