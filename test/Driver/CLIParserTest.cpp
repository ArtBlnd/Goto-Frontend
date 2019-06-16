#define CATCH_CONFIG_MAIN

#include "pch.h"
#include "catch2/catch.hpp"
#include "driver/CommandLine.h"

TEST_CASE("CLIParserTestArgs1", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "gtfw-exec.exe",
        "dummy_source.cpp",
        "-O2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 3, argv, nullptr);
    REQUIRE(isCreated);

    REQUIRE(std::any_cast<bool>(CLIContext->doOptLevel2.GetValOf()));
    
    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs2", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "gtfw-exec.exe",
        "dummy_source.cpp",
        "-output-path=\"OutputPath\"",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 3, argv, nullptr);
    REQUIRE(isCreated);

    REQUIRE(std::any_cast<std::string>(CLIContext->doOutputPath.GetValOf()) == "OutputPath");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestSourceFile", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 2, argv, nullptr);
    REQUIRE(isCreated);
    REQUIRE(CLIContext->m_clcTargetSourceFile == "dummy_source.cpp");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}
