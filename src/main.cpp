#include "driver/CommandLine.h"

#define EXIT_FAILURE 0xFFFFFFFF
#define EXIT_SUCCESS 0x00000001

namespace GTFW
{
    int EntryPoint(int args, char** argv, char** envp)
    {
        int ExitCode = EXIT_SUCCESS;

        Driver::CommandLineContext* CLIContext = nullptr;
        if(!Driver::CreateCommandLineContextWith(&CLIContext, args, argv, envp))
        {
            ExitCode = EXIT_FAILURE;
            goto EXIT;
        }

        Driver::InitalizeOptions(CLIContext);

    EXIT:
        Driver::FreeCommandLineContext(CLIContext);
        return ExitCode;
    }
}

int main(int args, char** argv, char** envp)
{
    try 
    {
        return GTFW::EntryPoint(args, argv, envp);
    }
    catch(std::exception e)
    {
        return EXIT_FAILURE;
    }

    // Unreachable
}