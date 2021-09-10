cmake_minimum_required(VERSION 3.10)
project(rigel
    VERSION 0.1.0
    DESCRIPTION "programming language"
    LANGUAGES CXX
)

find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
include(ChooseMSVCCRT)

include(AddLLVM)
include(HandleLLVMOptions)

include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
link_directories("${LLVM_LIBRARY_DIR}")

add_subdirectory(./lib)
add_executable(rigel ./lib/rigel.cpp)
target_link_libraries(rigel rigel_lib)

# add_subdirectory(test)

# find_package(LLVM REQUIRED HINTS "${LLVM_CMAKE_PATH}")
# list(APPEND CMAKE_MODULE_PATH ${LLVM_DIR})
# include(ChooseMSVCCRT)

# include(AddLLVM)
# include(HandleLLVMOptions)

# include_directories("${LLVM_BINARY_DIR}/include" "${LLVM_INCLUDE_DIR}")
# link_directories("${LLVM_LIBRARY_DIR}")

# add_executable(${PROJECT_NAME} lib/rigel.cpp )
# add_subdirectory(lib)
# add_subdirectory(test)
