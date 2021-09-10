cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
find_package(LLVM REQUIRED CONFIG)
include(GoogleTest)

add_executable(test_rigel testToken.cpp )
target_link_libraries(test_rigel GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS})
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

# Google Testの各テストケースごとにCTestのテストを作成する
# gtest_add_tests(TARGET test_rigel)

# CTestのテストをひとつだけ作成する
#add_test(NAME AllTests COMMAND TestSample1)