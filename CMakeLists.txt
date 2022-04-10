cmake_minimum_required(VERSION 3.16)
project(rigel
    VERSION 0.1.0
    DESCRIPTION "programming language"
    LANGUAGES CXX
)
# set(CMAKE_CXX_COMPILER "/usr/local/bin/clang-12" CACHE STRING "clang++ compiler" FORCE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O1 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_SOURCE_DIR /rigel)

find_package(LLVM REQUIRED CONFIG)
add_definitions(${LLVM_DEFINITIONS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR})

add_subdirectory(lib)
add_executable(rigel lib/rigel.cpp)
llvm_map_components_to_libnames(llvm_libs support core irreader ScalarOpts
        ExecutionEngine OrcJIT native Analysis RuntimeDyld Object InstCombine mcjit)

target_link_libraries(rigel ${llvm_libs})
target_link_libraries(rigel Lib)

add_subdirectory(test)