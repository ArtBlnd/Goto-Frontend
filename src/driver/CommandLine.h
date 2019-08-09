#ifndef __GTFW_C_FRONTEND_DRIVER_COMMANDLINE_H__
#define __GTFW_C_FRONTEND_DRIVER_COMMANDLINE_H__

#include <vector>
#include <string>
#include "driver/DriverOption.h"

namespace Goto
{
namespace Driver
{

struct CommandLineContext
{
    std::string m_clcTargetSourceFile;

    DriverOptionTable m_clcOptionTable;

    //
    // OPTIONS (OPTIMIZATIONS)
    //
    DEF_DRV_OPTION(
        &m_clcOptionTable, doOptLevel1, "O1", false, "Enable minimal optimziation", DriverOptionLevel::DOL_OPTIONAL);
    DEF_DRV_OPTION(&m_clcOptionTable,
                   doOptLevel2,
                   "O2",
                   false,
                   "Enable size-targeted optimization",
                   DriverOptionLevel::DOL_OPTIONAL);
    DEF_DRV_OPTION(
        &m_clcOptionTable, doOptLevel3, "O3", false, "Eanble full optimziation", DriverOptionLevel::DOL_OPTIONAL);

    //
    // OPTIONS (DEBUG)
    //
    DEF_DRV_OPTION(
        &m_clcOptionTable, doEnableASTDump, "dump-ast", false, "Enable dump for ASTs", DriverOptionLevel::DOL_HIDDEN);
    DEF_DRV_OPTION(&m_clcOptionTable,
                   doEnableVerbose,
                   "verbose",
                   false,
                   "Enable debug informations",
                   DriverOptionLevel::DOL_OPTIONAL);

    //
    // OPTIONS (BUILD)
    //
    DEF_DRV_OPTION(
        &m_clcOptionTable, doOutputPath, "output-path", "", "Set output path", DriverOptionLevel::DOL_OPTIONAL);
};

bool InitCommandLineContext(CommandLineContext** ppContext, size_t args, const char** argv, const char** envp);
void FreeCommandLineContext(CommandLineContext* pContext);

} // namespace Driver
} // namespace Goto

#endif