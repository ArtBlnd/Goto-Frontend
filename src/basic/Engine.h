#ifndef __GFWK_C_FRONTEND_BASIC_ENGINE_H__
#define __GFWK_C_FRONTEND_BASIC_ENGINE_H__

#include <memory>

namespace GTFW
{
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
            STAGE_INIT          = 0x01, 
            STAGE_TOKENLIZE     = 0x02, 
            STAGE_PARSE         = 0x03,
            STAGE_AST_TO_CG     = 0x04, // AST tree to Code-Generation.
        };

        struct EngineBuilder
        {
            EngineOptLevel ebOptimziationLevel;

            std::unique_ptr<Engine> BuildEngine();
        };

        class Engine
        {
            const size_t EngineStageCnt = 4;

        protected:
            EnginePhase m_egStage;
            EngineOptLevel m_egOpts;

            Engine();
            
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