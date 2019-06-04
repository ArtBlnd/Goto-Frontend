#include "basic/Engine.h"

namespace GTFW
{
    namespace Basic
    {
        std::unique_ptr<Engine> EngineBuilder::BuildEngine()
        {
            std::unique_ptr<Engine> engine;

            return std::move(engine);
        }
    }
}