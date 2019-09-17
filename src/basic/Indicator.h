#ifndef __GOTO_FRONTEND_BASIC_INDICATOR_H__
#define __GOTO_FRONTEND_BASIC_INDICATOR_H__

namespace Goto
{
namespace Basic
{

#define TABLE_DEF(Key, Value) const std::string Key = #Value;
#include <Basic/IndicatorTable.h>

class Indicator
{
};

} // namespace Basic
} // namespace Goto

#endif