#include <gtest/gtest.h>
#include "../headers/Lox.hpp"

TEST(InitialTest, TestingLoxClass) {
    TWI::Lox lox;
    lox.run("Hello, World!");
    SUCCEED();
}