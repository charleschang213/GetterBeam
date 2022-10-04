cmake_minimum_required(VERSION 3.23)
project(GetterBeam)

set(CMAKE_CXX_STANDARD 14)

add_library(GetterBeam SHARED src/GetterBeam.cpp include/GetterBeam.h)
