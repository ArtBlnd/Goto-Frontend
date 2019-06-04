#ifndef __GTFW_C_FRONTEND_DRIVER_DRIVER_H__
#define __GTFW_C_FRONTEND_DRIVER_DRIVER_H__

namespace GTFW
{
    namespace Driver
    {
        struct CommandLineContext;

        bool ExecuteCompilerDriver(CommandLineContext* CLIContext);
    }
}

#endif