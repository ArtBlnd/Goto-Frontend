#include "basic/Engine.h"

namespace Goto
{
    namespace Basic
    {
        std::unique_ptr<Engine> EngineBuilder::BuildEngine()
        {
            std::unique_ptr<Engine> engine;

            return std::move(engine);
        }

        //
        // Engine Implements
        //

        Engine::Engine()
        {

        }

        EnginePhase Engine::GetEnginePhase() const
        {
            return m_egStage;
        }

        EnginePhase Engine::SetEnginePhase(EnginePhase newStage)
        {
            std::swap(m_egStage, newStage);
            return newStage;
        }

        EngineOptLevel Engine::GetEngineOptLevel() const
        {
            return m_egOpts;
        }

        bool Engine::StartCompile()
        {
            return false;
        }
    }
}