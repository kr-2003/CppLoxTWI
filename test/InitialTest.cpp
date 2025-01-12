#include <gtest/gtest.h>
#include "../headers/Lox.hpp"
#include <fstream>

const std::string TEST_FOLDER_PATH = "../../test/SampleLoxFiles";
const std::string TEST_EXPECTED_OUTPUT_FOLDER_PATH = "../../test/SampleLoxFilesExpectedOutputs";

std::string getExpectedOutput(std::string path)
{
    std::string expected_output;

    // read the file
    std::ifstream file(path, std::ios::in);
    std::string line;
    while (std::getline(file, line))
    {
        expected_output += line + "\n";
    }

    return expected_output;
}

std::string getActualOutput(std::string path)
{
    std::string actual_output;

    // catch the output
    testing::internal::CaptureStdout();
    TWI::Lox lox;
    lox.runFile(path);
    actual_output = testing::internal::GetCapturedStdout();

    return actual_output;
}

TEST(InitialTest, Testing_Lox_1) {
    TWI::Lox lox;
    
    std::string path = TEST_FOLDER_PATH + "/test1.lox";
    std::string expected_output = getExpectedOutput(TEST_EXPECTED_OUTPUT_FOLDER_PATH + "/test1.lox.expected");
    std::string actual_output = getActualOutput(path);

    EXPECT_EQ(expected_output, actual_output);
}

TEST(InitialTest, Testing_Lox_2) {
    TWI::Lox lox;
    
    std::string path = TEST_FOLDER_PATH + "/test2.lox";
    std::string expected_output = getExpectedOutput(TEST_EXPECTED_OUTPUT_FOLDER_PATH + "/test2.lox.expected");
    std::string actual_output = getActualOutput(path);

    EXPECT_EQ(expected_output, actual_output);
}

TEST(InitialTest, TestingLoxClass2) {
    EXPECT_TRUE(true);
}
