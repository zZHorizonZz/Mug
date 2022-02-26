cmake_minimum_required(VERSION 3.0.0)
project(Mug VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE BINARY_DATA_GLOBAL binary_data/native/global/*.h)
file(GLOB_RECURSE BINARY_DATA_WINDOWS binary_data/native/windows/*.c)

add_executable(Mug main.c ${BINARY_DATA_WINDOWS} ${BINARY_DATA_GLOBAL})

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/binary_data/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/binary_data/native/windows)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
