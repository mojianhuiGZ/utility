cmake_minimum_required(VERSION 3.5)

project(utils)

set(utils_VERSION_MAJOR 0)
set(utils_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 11)

option(ENABLE_GCOV "Enable gcov(debug, Linux builds only)" OFF)
if (ENABLE_GCOV)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -lgcov")
endif ()

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GTEST_DIR ${PROJECT_SOURCE_DIR}/gtest)

configure_file(
        "${INCLUDE_DIR}/config.h.in"
        "${INCLUDE_DIR}/config.h"
)

include_directories(${INCLUDE_DIR})

include_directories(${GTEST_DIR}/include)
add_subdirectory(${GTEST_DIR})

#file(GLOB_RECURSE HEADER_FILES ${INCLUDE_DIR}/*.h)
#add_executable(runUnitTests ${HEADER_FILES} test/List_test.cpp)
add_executable(runUnitTests test/List_test.cpp)
target_link_libraries(runUnitTests gtest gtest_main pthread)

enable_testing()
add_test(runUnitTests runUnitTests)



