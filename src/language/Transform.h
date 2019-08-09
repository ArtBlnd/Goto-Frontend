#ifndef __GOTO_C_FRONTEND_LANGUAGE_TRANSFORM_H__
#define __GOTO_C_FRONTEND_LANGUAGE_TRANSFORM_H__

#include <string>

namespace Goto
{
namespace Language
{

// Transform string to boolean
// "true" | "1" will transform to boolean true
// "false" | "0" will transform to boolean false
bool tfStr2BoolTransform(const std::string& str);

// Transform string to integer
// for example. string "1040" will transform into 1040 int value
// emit exception if its overflow.
int tfStr2IntegerTransform(const std::string& str);

} // namespace Language
} // namespace Goto

#endif