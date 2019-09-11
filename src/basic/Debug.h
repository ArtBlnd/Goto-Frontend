#ifndef __GOTO_C_FRONTNED_DEBUG_H__
#define __GOTO_C_FRONTNED_DEBUG_H__


#ifdef DEBUG_ASSERT
#define noway_assert(cond, message) assert(cond, message)
#define debug_assert(cond, message) assert(cond, message)
#define assert(cond, message)                                                                                          \
    if (!cond)                                                                                                         \
        Goto::Debug::Assert(message)
#else
#define noway_assert(cond, message) assert(cond, message)
#define debug_assert(cond, message)
#define assert(cond, message)                                                                                          \
    if (!cond)                                                                                                         \
        Goto::Debug::Assert(message)
#endif

namespace Goto
{

namespace Debug
{
void Assert(char* reason);
void Assert();

} // namespace Debug
} // namespace Goto


#endif