#include "pch.h"

#include "driver/Driver.h"
#include "driver/CommandLine.h"
#include "basic/Engine.h"

namespace GTFW
{
    bool Driver::ExecuteCompilerEngine(CommandLineContext* CLIContext)
    {
        Basic::EngineBuilder           engineBuilder;
        std::unique_ptr<Basic::Engine> engine = engineBuilder.BuildEngine();

        engine->SetEnginePhase(Basic::EnginePhase::STAGE_INIT);

        return engine->StartCompile();
    }
}