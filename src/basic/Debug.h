#ifndef __GOTO_C_FRONTNED_DEBUG_H__
#define __GOTO_C_FRONTNED_DEBUG_H__

#define noway_assert(cond, message)
#define debug_assert(cond, message)
#define assert(cond, message)

namespace Goto
{

namespace Debug
{
void Assert(char* reason);
void Assert();

} // namespace Debug
} // namespace Goto


#endif