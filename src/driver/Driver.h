#ifndef __GTFW_C_FRONTEND_DRIVER_DRIVER_H__
#define __GTFW_C_FRONTEND_DRIVER_DRIVER_H__

namespace Goto
{
    namespace Driver
    {
        struct CommandLineContext;

        bool ExecuteCompilerEngine(CommandLineContext* CLIContext);
    }
}

#endif