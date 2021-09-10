cmake_minimum_required(VERSION 3.10)
project(rigel_lib
    VERSION 0.1.0
    DESCRIPTION "programming language"
    LANGUAGES CXX
)
add_library(rigel_lib STATIC Lexer.cpp)
target_compile_features(rigel_lib PRIVATE cxx_std_11)
target_include_directories(rigel_lib INTERFACE ../include)
set_target_properties(rigel_lib
    PROPERTIES
    VERSION ${PROJECT_VERSION})