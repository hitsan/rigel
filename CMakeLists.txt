cmake_minimum_required(VERSION 3.16)
project(rigel
    VERSION 0.1.0
    DESCRIPTION "programming language"
    LANGUAGES CXX
)
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