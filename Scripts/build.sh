#!/bin/bash

print_help_and_exit(){
    echo "Usage: ${0} [-release] [-rebuild]"
    echo "-release - build release library"
    echo "-rebuild - rebuild project"
    exit 1
}

BuildConfigName="Debug"
CMakeBuildDir="../cmake-build-debug"
CMakeSourceDir=".."
CMakeTargetName="GetterBeam"
NeedReBuild=false

for var in $*
do
    if [[ $var = "-release" ]]; then
        BuildConfigName="Release"
        CMakeBuildDir="../cmake-build-release"
    elif [[ $var = "-rebuild" ]]; then
        NeedReBuild=true
    else
    	echo "Invalid parameter:${var}"
        print_help_and_exit
    fi
done

if [ $NeedReBuild = true ]; then
    echo "Clean Project"
    if [ -d ${CMakeBuildDir} ]; then
        rm -rf ${CMakeBuildDir}
    fi
fi

echo "Configure CMake"
if [ -z `command -v cmake` ]; then
        echo "need install cmake"
        exit 1
fi
cmake -B ${CMakeBuildDir} -S ${CMakeSourceDir} -DCMAKE_BUILD_TYPE=${BuildConfigName}
if [ ! $? -eq 0 ]; then
        echo "Configure Failed"
        exit 1
fi

echo "Build Project"
cmake --build ${CMakeBuildDir} --config ${BuildConfigName} --target ${CMakeTargetName}
if [ ! $? -eq 0 ]; then
        echo "Build Failed"
        exit 1
fi