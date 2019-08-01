#ifndef __GTFW_C_FRONTEND_BASIC_ENGINE_H__
#define __GTFW_C_FRONTEND_BASIC_ENGINE_H__

#include <memory>
#include <basic/CompileInfo.h>

namespace Goto
{
    namespace Driver
    {
        class CommandLineContext;
    }
    
    namespace Basic
    {
        class Engine;

        enum EngineOptLevel
        {
            FULL_OPT            = 0x01, // -O3 Flag
            SMALL_CODE_OPT      = 0x02, // -O2 Flag
            MINIMIZED_OPT       = 0x03, // -O1 Flag
            NO_OPT              = 0x04  // -O0 Flag
        };

        enum EnginePhase
        {
            STAGE_PRE_INIT      = 0x01,
            STAGE_PST_INIT      = 0x02,
            STAGE_TOKENLIZE     = 0x03,
            STAGE_PARSE         = 0x04,
            STAGE_AST_TO_CG     = 0x05, // AST tree to Code-Generation.
        };

        struct EngineBuilder
        {
            EngineOptLevel ebCompOptLevel;
            CompileInfo*   ebCompInfo = nullptr;

            std::unique_ptr<Engine> BuildEngine();

            EngineBuilder();
            ~EngineBuilder() = default;
        };

        class Engine
        {
            friend class EngineBuilder;

            //
            // Major compiler informations
            //
            EngineOptLevel               m_egCompOpts;
            EnginePhase                  m_egCompStage;
            std::shared_ptr<CompileInfo> m_egCompInfo;

            //
            // Indicator informations
            //
            size_t m_egLexerTokens = 0;
            size_t m_egLexerMacros = 0;

        protected:
            //
            // Constructors and Distructors
            //
            explicit Engine() = delete;
            explicit Engine(EngineBuilder* builder);
            ~Engine() = default;
            
        public:
            // Get current compiler engine phase
            // This is useful when you are debugging C-Frontend engine appication
            // by checking what compilation phase is executing right now.
            EnginePhase GetEnginePhase() const;
            EnginePhase SetEnginePhase(EnginePhase newStage);

            // Get global compiler optimziation level
            EngineOptLevel GetEngineOptLevel() const;

            bool StartCompile();
        };
    }
}

#endif