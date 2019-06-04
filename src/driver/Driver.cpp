#include "pch.h"

#include "driver/Driver.h"
#include "driver/CommandLine.h"
#include "basic/Engine.h"

namespace GTFW
{
    bool Driver::ExecuteCompilerEngine(CommandLineContext* CLIContext)
    {
        Basic::Engine engine(Basic::EngineOpts::NO_OPT);

        engine.SetEngineStage(Basic::EngineStage::STAGE_INIT);

        return engine.StartCompile();
    }
}