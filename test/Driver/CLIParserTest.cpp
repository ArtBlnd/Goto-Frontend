#include <gtest/gtest.h>
#include <driver/CommandLine.h>

TEST(DriverTest, CLIParseTestArgs1)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "gtfw-exec.exe",
        "source.cpp",
        "-key1=val",
        "-key2=val",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, argv, nullptr);
    EXPECT_TRUE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    EXPECT_TRUE(KV1->m_Key == "key1");
    EXPECT_TRUE(KV1->m_Val[0] == "val");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    EXPECT_TRUE(KV2->m_Key == "key2");
    EXPECT_TRUE(KV2->m_Val[0] == "val");
    
    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST(DriverTest, CLIParseTestArgs2)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "source.cpp",
        "-key1=val1,val2",
        "-key2=val1,val2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, (char**)argv, nullptr);
    EXPECT_TRUE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    EXPECT_TRUE(KV1->m_Key == "key1");
    EXPECT_TRUE(KV1->m_Val[0] == "val1");
    EXPECT_TRUE(KV1->m_Val[1] == "val2");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    EXPECT_TRUE(KV2->m_Key == "key2");
    EXPECT_TRUE(KV2->m_Val[0] == "val1");
    EXPECT_TRUE(KV2->m_Val[1] == "val2");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST(DriverTest, CLIParseTestArgs3)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "source.cpp",
        "-key1=val1,val2,\"val3\"",
        "-key2=val1,\"val2\",val3",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, (char**)argv, nullptr);
    EXPECT_TRUE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    EXPECT_TRUE(KV1->m_Key == "key1");
    EXPECT_TRUE(KV1->m_Val[0] == "val1");
    EXPECT_TRUE(KV1->m_Val[1] == "val2");
    EXPECT_TRUE(KV1->m_Val[2] == "val3");

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    EXPECT_TRUE(KV2->m_Key == "key2");
    EXPECT_TRUE(KV2->m_Val[0] == "val1");
    EXPECT_TRUE(KV2->m_Val[1] == "val2");
    EXPECT_TRUE(KV2->m_Val[2] == "val3");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST(DriverTest, CLIParseTestArgs4)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "source.cpp",
        "-key1",
        "-key2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, (char**)argv, nullptr);
    EXPECT_TRUE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    EXPECT_TRUE(KV1->m_Key == "key1");
    EXPECT_TRUE(KV1->m_Val.empty());

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    EXPECT_TRUE(KV2->m_Key == "key2");
    EXPECT_TRUE(KV2->m_Val.empty());

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST(DriverTest, CLIParseTestArgs5)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "source.cpp",
        "-key-1",
        "-key-2",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 4, (char**)argv, nullptr);
    EXPECT_TRUE(isCreated);

    GTFW::Driver::KVInfo* KV1 = CLIContext->m_clcArgs[0];
    EXPECT_TRUE(KV1->m_Key == "key-1");
    EXPECT_TRUE(KV1->m_Val.empty());

    GTFW::Driver::KVInfo* KV2 = CLIContext->m_clcArgs[1];
    EXPECT_TRUE(KV2->m_Key == "key-2");
    EXPECT_TRUE(KV2->m_Val.empty());

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

TEST(DriverTest, CLIParseTestSourceFile)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    const char* argv[] = {
        "program",
        "source.cpp",
    };

    bool isCreated = GTFW::Driver::InitCommandLineContext(&CLIContext, 2, (char**)argv, nullptr);
    EXPECT_TRUE(isCreated);
    EXPECT_TRUE(CLIContext->m_clcTargetSourceFile == "source.cpp");

    GTFW::Driver::FreeCommandLineContext(CLIContext);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
}