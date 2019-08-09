#ifndef __GOTO_FRONTEND_BASIC_ERROR_TRACE_H__
#define __GOTO_FRONTEND_BASIC_ERROR_TRACE_H__

#include <string>

namespace Goto
{
namespace Basic
{

class ISourceTraceData
{
};

class ISourceErrorData : ISourceTraceData
{
};

class ISourceInfoData : ISourceTraceData
{
};

class ISourceWarningData : ISourceTraceData
{
};

class SourceTrace
{
};

} // namespace Basic
} // namespace Goto


#endif