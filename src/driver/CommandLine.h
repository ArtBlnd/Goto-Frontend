#ifndef __GFWK_C_FRONTEND_DRIVER_COMMANDLINE_H__
#define __GFWK_C_FRONTEND_DRIVER_COMMANDLINE_H__

#include <vector>
#include <string>

namespace GTFW
{
    namespace Driver
    {
        struct KVInfo
        {
            std::string              m_Key;
            std::vector<std::string> m_Val;
        };

        struct CommandLineContext
        {
            // clcArgs and clcEnvs contains parsed program execution informations
            // clcArgs contains program argument informations, and clcEvns contains program execution envionrment informations.
            std::vector<KVInfo*> m_clcArgs;
            std::vector<KVInfo*> m_clcEnvs;

            std::string m_clcTargetSourceFile;

            bool LookUpArgs(std::string Key, std::vector<std::string>* Val = nullptr) const;
        };

        bool InitCommandLineContext(CommandLineContext** ppContext, size_t args, const char** argv, const char** envp);
        void FreeCommandLineContext(CommandLineContext* pContext);
    }
}

#endif