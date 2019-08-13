#ifndef __GOTO_FRONTEND_BASIC_SOURCE_LOCATION_H__
#define __GOTO_FRONTEND_BASIC_SOURCE_LOCATION_H__

namespace Goto
{
namespace Basic
{

class SourceLocation
{
    size_t m_tkSize   = 0;
    size_t m_tkLine   = 0;
    size_t m_tkColumn = 0;
};

} // namespace Basic
} // namespace Goto

#endif