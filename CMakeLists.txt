cmake_minimum_required(VERSION 3.23)
project(GetterBeam)

set(CMAKE_CXX_STANDARD 14)
if (NOT MSVC)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -pedantic-errors -O2" )
endif ()

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
include_directories("src" "src/Global" "include")

add_library(GetterBeam SHARED
        src/GetterBeam.cpp include/GetterBeam.h
        src/Memory/MemoryUtils.cpp src/Memory/MemoryUtils.h
        src/Global/GBTypedef.h
        )

string(TOLOWER ${CMAKE_BUILD_TYPE} _type)
if(${_type} STREQUAL "debug")
        if (NOT MSVC)
                SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g" )
        endif ()
        add_executable(GetterBeam_Test
                src/GetterBeam.cpp include/GetterBeam.h
                src/Memory/MemoryUtils.cpp src/Memory/MemoryUtils.h src/Memory/MemoryUtils_Test.cpp
                src/Global/GBTypedef.h)
        target_link_libraries(
                GetterBeam_Test
                GTest::gtest_main
        )
        if (NOT MSVC)
                target_link_libraries(
                        GetterBeam_Test
                        gcov
                )
                target_compile_options(GetterBeam_Test PUBLIC
                        -fprofile-arcs -ftest-coverage)
                target_link_options(GetterBeam_Test PUBLIC --coverage)
        endif()
endif()
