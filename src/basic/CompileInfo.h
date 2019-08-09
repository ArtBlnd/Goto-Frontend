#ifndef __GOTO_BASIC_COMPILE_INFO_H__
#define __GOTO_BASIC_COMPILE_INFO_H__

#include <string>

namespace Goto
{
struct CompileInfo
{
    std::string m_ciSourceFile;
    std::string m_ciSourcePath;

    std::string m_ciEntryPoint;

    bool m_ciVerbose = false;
    bool m_ciDumpAst = false;
};
} // namespace Goto

#endif