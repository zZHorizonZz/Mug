cmake_minimum_required(VERSION 3.0.0)
project(Mug VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE BINARY_DATA_GLOBAL binary_data/native/global/*.h)
file(GLOB_RECURSE BINARY_DATA_WINDOWS binary_data/native/windows/*.c)

file(GLOB_RECURSE COMPILER_GLOBAL compiler/native/global/*.h)
file(GLOB_RECURSE COMPILER_WINDOWS compiler/native/windows/*.c)

file(GLOB_RECURSE LANGUAGE_GLOBAL language/native/global/*.h)
file(GLOB_RECURSE LANGUAGE_WINDOWS language/native/windows/*.c)

file(GLOB_RECURSE PARSER_GLOBAL parser/native/global/*.h)
file(GLOB_RECURSE PARSER_WINDOWS parser/native/windows/*.c)

add_executable(Mug main.c ${BINARY_DATA_WINDOWS} ${BINARY_DATA_GLOBAL} ${COMPILER_GLOBAL} ${COMPILER_WINDOWS} ${LANGUAGE_GLOBAL} ${LANGUAGE_WINDOWS} ${PARSER_GLOBAL} ${PARSER_WINDOWS})

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/binary_data/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/binary_data/native/windows)

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compiler/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/compiler/native/windows)


target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/language/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/language/native/windows)


target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/parser/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/parser/native/windows)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
