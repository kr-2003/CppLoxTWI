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

#exclude AstPrinter.cpp from the main executable
list(FILTER Sources EXCLUDE REGEX "AstPrinter.cpp")

add_executable(${This}_Executable ${Sources} ${Headers})

#exclude main.cpp from the library but include AstPrinter.cpp

# list(FILTER Sources EXCLUDE REGEX "main.cpp")
# list(APPEND Sources "${CMAKE_SOURCE_DIR}/AstPrinter.cpp")

# add_executable(${This}_Executable_AstPrinter ${Sources} ${Headers})

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)
