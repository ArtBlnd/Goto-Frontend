#include "basic/Engine.h"
#include "basic/FileUtils.h"

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


        //
        // Compile Section
        //

        bool Engine::StartCompile()
        {
            //
            // Initializing stage
            //
            this->SetEnginePhase(EnginePhase::STAGE_INIT);
            const CompileInfo* compileInfo = LookupCompileInfo();

            // 
            // Source finding stage
            //
            std::string filePath;

            if (fuFileExists(compileInfo->m_ciSourceFile))
            {
                // Check that file exists on current path
                // Or we are finding on path included file path

                filePath = compileInfo->m_ciSourceFile;
            }

            if (fuFileExists(compileInfo->m_ciSourcePath, compileInfo->m_ciSourcePath))
            {
                // We are getting full path of file.

                filePath = fuGetFullFilePath(compileInfo->m_ciSourceFile, compileInfo->m_ciSourcePath);
            }

            if (filePath.empty())
            {
                // We couldn't find source file even we tried to find on absolute path
                // TODO : internal exception.

                return false;
            }

            // 
            // Source reading stage
            //
            FileReader sourceFileReader = FileReader(filePath);


            //
            // Source tokenize and lexing stage.
            //
            this->SetEnginePhase(EnginePhase::STAGE_TOKENLIZE);
            Language::TokenContext tokenContext;

            // Read source code and tokenlize it (includes macros)
            // We are resolving macros after tokenlize it.
            if (!Language::lxTokenlizeSourceCode(
                &tokenContext, 
                sourceFileReader.GetBuffer(), 
                sourceFileReader.GetFileSize()))
            {
                // TODO : internal exception.

                return false;
            }

            if (!Language::lxResolveAndApplyMacros(&tokenContext))
            {
                // TODO : internal exception.

                return false;
            }
            
            return false;
        }
    }
}