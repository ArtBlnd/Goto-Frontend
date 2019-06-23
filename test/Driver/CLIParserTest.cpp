#define CATCH_CONFIG_MAIN

#include "pch.h"
#include "catch2/catch.hpp"
#include "driver/CommandLine.h"

TEST_CASE("CLIParserTestArgs1", "DriverTest")
{
    Goto::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "Goto-exec.exe",
        "dummy_source.cpp",
        "-O2",
    };

    bool isCreated = Goto::Driver::InitCommandLineContext(&CLIContext, 3, argv, nullptr);
    REQUIRE(isCreated);

    REQUIRE(std::any_cast<bool>(CLIContext->doOptLevel2.GetValOf()));
    
    Goto::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs2", "DriverTest")
{
    Goto::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "Goto-exec.exe",
        "dummy_source.cpp",
        "-output-path=\"OutputPath\"",
    };

    bool isCreated = Goto::Driver::InitCommandLineContext(&CLIContext, 3, argv, nullptr);
    REQUIRE(isCreated);

    REQUIRE(std::any_cast<std::string>(CLIContext->doOutputPath.GetValOf()) == "OutputPath");

    Goto::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestSourceFile", "DriverTest")
{
    Goto::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
    };

    bool isCreated = Goto::Driver::InitCommandLineContext(&CLIContext, 2, argv, nullptr);
    REQUIRE(isCreated);
    REQUIRE(CLIContext->m_clcTargetSourceFile == "dummy_source.cpp");

    Goto::Driver::FreeCommandLineContext(CLIContext);
}
