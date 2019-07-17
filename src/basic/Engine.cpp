#include "basic/Engine.h"
#include "language/Lexer.h"
#include "language/Parser.h"

namespace Goto
{
    namespace Basic
    {
        //
        // Engine Builder
        //
        std::unique_ptr<Engine> EngineBuilder::BuildEngine()
        {
            std::unique_ptr<Engine> engine;

            return std::move(engine);
        }

        //
        // Engine Implements
        //
        Engine::Engine(EngineBuilder* builder)
        {
            m_egCompStage = EnginePhase::STAGE_INIT;
            m_egCompOpts = builder->ebOptimziationLevel;
            m_egCompInfo = std::shared_ptr<CompileInfo>(builder->ebCompileInfo);
        }

        EnginePhase Engine::GetEnginePhase() const
        {
            return m_egCompStage;
        }

        EnginePhase Engine::SetEnginePhase(EnginePhase newStage)
        {
            std::swap(m_egCompStage, newStage);
            return newStage;
        }

        EngineOptLevel Engine::GetEngineOptLevel() const
        {
            return m_egCompOpts;
        }

        bool Engine::StartCompile()
        {
            this->SetEnginePhase(EnginePhase::STAGE_INIT);
            void*  srcFileBuf;
            size_t srcFileSize;

            this->SetEnginePhase(EnginePhase::STAGE_TOKENLIZE);
            Language::TokenContext tokenContext;
            if (!Language::lxTokenlizeSourceCode(&tokenContext, srcFileBuf, srcFileSize))
            {
                // TODO : internal exception.
            }

            if (!Language::lxResolveAndApplyMacros(&tokenContext))
            {
                // TODO : internal exception.
            }
            
            return false;
        }
    }
}