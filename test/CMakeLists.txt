cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
find_package(LLVM REQUIRED CONFIG)
include(GoogleTest)

add_executable(test_rigel testToken.cpp testLexer.cpp)
target_link_libraries(test_rigel GTest::GTest GTest::Main Lib ${llvm_libs})
include_directories(${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
