cmake_minimum_required(VERSION 3.31)

set(This CPP_Lox_TWI)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

file(GLOB_RECURSE Headers CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/headers/*.hpp")

file(GLOB Sources CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/*.cpp")

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
