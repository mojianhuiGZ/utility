cmake_minimum_required(VERSION 3.5)

project(utility)

set(utils_VERSION_MAJOR 0)
set(utils_VERSION_MINOR 1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall")

option(ENABLE_GCOV "Enable gcov(debug, Linux builds only)" ON)

if (ENABLE_GCOV)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -lgcov")
endif ()

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GTEST_DIR ${PROJECT_SOURCE_DIR}/gtest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
set(MEMORYCHECK_SUPPRESSIONS_FILE "${PROJECT_SOURCE_DIR}/valgrind_suppress.txt")

set(CMAKE_REQUIRED_INCLUDES /usr/include)
include(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)

check_include_file("pthread.h" HAVE_FEATURE_PTHREAD)

configure_file(
        "${INCLUDE_DIR}/config.h.in"
        "${INCLUDE_DIR}/config.h"
)

include_directories(${GTEST_DIR}/include)
add_subdirectory(${GTEST_DIR})

include_directories(${INCLUDE_DIR})
add_library(${PROJECT_NAME} src/utils/Logger.cpp src/utils/Timers.cpp include/utils/DynamicString.h include/utils/String8.h include/utils/RWLock.h include/utils/Unicode.h include/utils/Thread.h include/utils/SocketListener.h include/utils/SocketClient.h src/utils/SocketListener.cpp src/utils/Thread.cpp)

add_executable(UnitTests test/utils/DynamicList_test.cpp test/utils/String_test.cpp
        test/utils/List_test.cpp test/utils/Logger_test.cpp test/utils/Singleton_test.cpp
        test/utils/Mutex_test.cpp test/utils/Timers_test.cpp test/atomic_test.cpp)
target_link_libraries(UnitTests ${PROJECT_NAME} gtest gtest_main pthread)

enable_testing()

add_test(UnitTests UnitTests)

if (ENABLE_GCOV)
    set(PRODUCT_COVERAGE_REPORT_SCRIPT_FILE "${CMAKE_BINARY_DIR}/product_coverage_report.sh")
    file(WRITE ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE} "#!/bin/sh\n")
    file(APPEND ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE} "OUT_DIR=${CMAKE_BINARY_DIR}/coverage\n")
    file(APPEND ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE} "[ -d \$OUT_DIR ] && rm -rf \$OUT_DIR\n")
    file(APPEND ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE} "mkdir -p \$OUT_DIR\n")
    file(APPEND ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE} "gcovr --object-directory=${CMAKE_BINARY_DIR}"
            " -o \$OUT_DIR/coverage.html -r ${CMAKE_SOURCE_DIR}"
            " --html --html-details -b -s -e *gtest*\n")
    add_custom_command(
            TARGET UnitTests POST_BUILD
            COMMAND chmod a+x ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE})
    add_custom_target(productCoverageReport
            COMMAND sh -x ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE}
            DEPENDS ${PRODUCT_COVERAGE_REPORT_SCRIPT_FILE}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif ()
