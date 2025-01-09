cmake_minimum_required(VERSION 3.31)

set(This CPP_Lox_TWI_Tests)

set(Sources
    InitialTest.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    CPP_Lox_TWI
    gtest
)

add_test(
    NAME ${This}
    COMMAND ${This}
)