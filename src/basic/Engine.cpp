#include "basic/Engine.h"

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
            this->SetEnginePhase(EnginePhase::STAGE_TOKENLIZE);

            return false;
        }
    }
}