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
        "-key1=val",
        "-key2=val",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    REQUIRE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    REQUIRE(KV1->m_Key == "key1");
    REQUIRE(KV1->m_Val[0] == "val");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    REQUIRE(KV2->m_Key == "key2");
    REQUIRE(KV2->m_Val[0] == "val");
    
    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs2", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
        "-key1=val1,val2",
        "-key2=val1,val2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    REQUIRE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    REQUIRE(KV1->m_Key == "key1");
    REQUIRE(KV1->m_Val[0] == "val1");
    REQUIRE(KV1->m_Val[1] == "val2");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    REQUIRE(KV2->m_Key == "key2");
    REQUIRE(KV2->m_Val[0] == "val1");
    REQUIRE(KV2->m_Val[1] == "val2");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs3", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
        "-key1=val1,val2,\"val3\"",
        "-key2=val1,\"val2\",val3",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    REQUIRE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    REQUIRE(KV1->m_Key == "key1");
    REQUIRE(KV1->m_Val[0] == "val1");
    REQUIRE(KV1->m_Val[1] == "val2");
    REQUIRE(KV1->m_Val[2] == "val3");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    REQUIRE(KV2->m_Key == "key2");
    REQUIRE(KV2->m_Val[0] == "val1");
    REQUIRE(KV2->m_Val[1] == "val2");
    REQUIRE(KV2->m_Val[2] == "val3");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs4", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
        "-key1",
        "-key2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    REQUIRE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    REQUIRE(KV1->m_Key == "key1");
    REQUIRE(KV1->m_Val.empty());

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    REQUIRE(KV2->m_Key == "key2");
    REQUIRE(KV2->m_Val.empty());

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST_CASE("CLIParserTestArgs5", "DriverTest")
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "dummy_source.cpp",
        "-key-1",
        "-key-2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    REQUIRE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    REQUIRE(KV1->m_Key == "key-1");
    REQUIRE(KV1->m_Val.empty());

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    REQUIRE(KV2->m_Key == "key-2");
    REQUIRE(KV2->m_Val.empty());

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
