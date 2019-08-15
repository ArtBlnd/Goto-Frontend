#include "pch.h"
#include "driver/CommandLine.h"
#include "driver/Driver.h"

#ifdef EXIT_FAILURE
#undef EXIT_FAILURE
#endif
#define EXIT_FAILURE 0xFFFFFFFF

#ifdef EXIT_SUCCESS
#undef EXIT_SUCCESS
#endif
#define EXIT_SUCCESS 0x00000001

namespace Goto
{
    int EntryPoint(int args, char** argv, char** envp)
    {
        int ExitCode = EXIT_SUCCESS;

        Driver::CommandLineContext* CLIContext = nullptr;
        if(!Driver::InitCommandLineContext(&CLIContext, args, argv, envp))
        {
            ExitCode = EXIT_FAILURE;
            goto EXIT;
        }

        ExitCode = Driver::ExecuteCompilerEngine(CLIContext);

    EXIT:
        Driver::FreeCommandLineContext(CLIContext);
        return ExitCode;
    }
}

int main(int args, char** argv, char** envp)
{
    try 
    {
        return Goto::EntryPoint(args, argv, envp);
    }
    catch(std::exception e)
    {
        return EXIT_FAILURE;
    }

    // Unreachable
}