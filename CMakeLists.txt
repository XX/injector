cmake_minimum_required(VERSION 3.5)
project(injector)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -flto")

set(DEPENDENCY_DIR "${CMAKE_SOURCE_DIR}/ext")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
find_package(Catch)

set(SOURCE_FILES
    )

set(TEST_SOURCE_FILES
        test/unit/src/noogen/injector/injectorTest.cpp
        test/unit/src/noogen/injector/main.cpp)

include_directories(
        "${Catch_INCLUDE_DIR}"
        lib/include
        test/unit/include)

add_executable(injector ${SOURCE_FILES} ${TEST_SOURCE_FILES})