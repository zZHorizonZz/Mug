cmake_minimum_required(VERSION 3.0.0)
project(Mug VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE UTILITIES_GLOBAL src/util/native/global/*.h)
file(GLOB_RECURSE UTILITIES_WINDOWS src/util/native/windows/*.c)
file(GLOB_RECURSE UTILITIES_SHARED src/util/native/shared/*.c)

file(GLOB_RECURSE BINARY_DATA_GLOBAL src/binary_data/native/global/*.h)
file(GLOB_RECURSE BINARY_DATA_WINDOWS src/binary_data/native/windows/*.c)

file(GLOB_RECURSE COMPILER_GLOBAL src/compiler/native/global/*.h)
file(GLOB_RECURSE COMPILER_WINDOWS src/compiler/native/windows/*.c)

file(GLOB_RECURSE LANGUAGE_GLOBAL src/language/native/global/*.h)
file(GLOB_RECURSE LANGUAGE_WINDOWS src/language/native/windows/*.c)
file(GLOB_RECURSE LANGUAGE_SHARED_H src/language/native/shared/*.h)
file(GLOB_RECURSE LANGUAGE_SHARED_C src/language/native/shared/*.c)

file(GLOB_RECURSE PARSER_GLOBAL src/build/native/global/*.h)
file(GLOB_RECURSE PARSER_WINDOWS src/build/native/windows/*.c)

file(GLOB_RECURSE MACHINE_GLOBAL src/machine/native/global/*.h)
file(GLOB_RECURSE MACHINE_WINDOWS src/machine/native/windows/*.c)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(Mug src/main.c ${UTILITIES_GLOBAL}
                              ${UTILITIES_WINDOWS}
                              ${UTILITIES_SHARED}
                              ${BINARY_DATA_WINDOWS}
                              ${BINARY_DATA_GLOBAL}
                              ${COMPILER_GLOBAL}
                              ${COMPILER_WINDOWS}
                              ${MACHINE_GLOBAL}
                              ${MACHINE_WINDOWS}
                              ${LANGUAGE_GLOBAL}
                              ${LANGUAGE_WINDOWS}
                              ${LANGUAGE_SHARED_H}
                              ${LANGUAGE_SHARED_C}
                              ${PARSER_GLOBAL}
                              ${PARSER_WINDOWS})

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/util/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/util/native/windows)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/util/native/SHARED)
                              
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_data/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_data/native/windows)

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/compiler/native/windows)

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/language/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/language/native/windows)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/language/native/shared)

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/build/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/build/native/windows)

target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/machine/native/global)
target_include_directories(Mug PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/machine/native/windows)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
