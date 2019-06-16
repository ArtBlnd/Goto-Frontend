#include "pch.h"

#include "driver/Driver.h"
#include "driver/CommandLine.h"
#include "basic/Engine.h"

namespace GTFW
{
    bool Driver::ExecuteCompilerEngine(CommandLineContext* CLIContext)
    {
        Basic::EngineBuilder engineBuilder;


        //
        // Initialize Options
        //
        if (std::any_cast<bool>(CLIContext->doOptLevel1.GetValOf()))
        {
            // Optimization level 1
            engineBuilder.ebOptimziationLevel = Basic::EngineOptLevel::MINIMIZED_OPT;
        }
        else if (std::any_cast<bool>(CLIContext->doOptLevel2.GetValOf()))
        {
            // Optimization level 2
            engineBuilder.ebOptimziationLevel = Basic::EngineOptLevel::SMALL_CODE_OPT;
        }
        else if (std::any_cast<bool>(CLIContext->doOptLevel3.GetValOf()))
        {
            // Optimization level 3
            engineBuilder.ebOptimziationLevel = Basic::EngineOptLevel::FULL_OPT;
        }
        else
        {
            // No optimization
            engineBuilder.ebOptimziationLevel = Basic::EngineOptLevel::NO_OPT;
        }
        
        std::unique_ptr<Basic::Engine> engine = engineBuilder.BuildEngine();
        engine->SetEnginePhase(Basic::EnginePhase::STAGE_INIT);

        return engine->StartCompile();
    }
}