#include <gtest/gtest.h>
#include <driver/CommandLine.h>

TEST(DriverTest, CLIParseTestArgs1)
{
    GTFW::Driver::CommandLineContext* CLIContext = nullptr;

    char* argv[] = {
        "gtfw-exec.exe",
        "-key1=val",
        "-key2=val",
    };

    bool isCreated = GTFW::Driver::CreateCommandLineContextWith(&CLIContext, 3, argv, nullptr);
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

    char* argv[] = {
        "program",
        "-key1=val1,val2",
        "-key2=val1,val2",
    };

    bool isCreated = GTFW::Driver::CreateCommandLineContextWith(&CLIContext, 3, argv, nullptr);
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

    char* argv[] = {
        "program",
        "-key1=val1,val2,\"val3\"",
        "-key2=val1,\"val2\",val3",
    };

    bool isCreated = GTFW::Driver::CreateCommandLineContextWith(&CLIContext, 3, argv, nullptr);
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

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::getchar();
}