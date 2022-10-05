cmake_minimum_required(VERSION 3.23)
project(GetterBeam)

set(CMAKE_CXX_STANDARD 14)

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
add_executable(GetterBeam_Test
        src/GetterBeam.cpp include/GetterBeam.h
        src/Memory/MemoryUtils.cpp src/Memory/MemoryUtils.h src/Memory/MemoryUtils_Test.cpp
        src/Global/GBTypedef.h)
target_link_libraries(
        GetterBeam_Test
        GTest::gtest_main
)



