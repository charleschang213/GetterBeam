print_help_and_exit(){
    echo "Usage: ${0} [-run] [-html] [-rebuild]"
    echo "-run - run all tests"
    echo "-html - generate html report, need -run enabled"
    echo "-rebuild - rebuild project"
    exit 1
}

BuildConfigName="Debug"
CMakeBuildDir="../cmake-build-debug"
TestFileDir="${CMakeBuildDir}/Tests"
TestObjDir="${CMakeBuildDir}/CMakeFiles/GetterBeam_Test.dir/src"
TestExecutivePath="${CMakeBuildDir}/GetterBeam_Test"
TestResultPath="${TestFileDir}/GetterBeamTestCoverage"
CMakeSourceDir="${PWD}/.."
CMakeTargetName="GetterBeam_Test"
CoverageReportDir="${CMakeBuildDir}/Report"
NeedReBuild=false
NeedRun=false
NeedHtml=false

for var in $*
do
    if [[ $var = "-run" ]]; then
        NeedRun=true
    elif [[ $var = "-rebuild" ]]; then
        NeedReBuild=true
    elif [[ $var = "-html" ]]; then
        NeedHtml=true
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

if [ $NeedRun = false ]; then
        exit
fi

echo "Run Project"
if [ ! -d ${TestFileDir} ]; then
        mkdir ${TestFileDir}
fi

if [[ -z `command -v lcov` ]] || [[ -z `command -v gcov` ]] || [[ -z `command -v llvm-cov` ]]; then
        echo "need install lcov, gcov and llvm-gcov to collect coverage"
        exit 1
fi
lcov -d ${TestObjDir}  -b ${CMakeSourceDir}/src \
--initial --no-external -q \
--gcov-tool $PWD/llvm-gcov.sh \
-c -o ${TestResultPath}_init

./${TestExecutivePath}

if [ ! $? -eq 0 ]; then
        echo "Test Failed"
        exit 1
fi

lcov -d ${TestObjDir} -b ${CMakeSourceDir}/src \
--no-external -q \
--gcov-tool $PWD/llvm-gcov.sh \
-c -o ${TestResultPath}_Test

lcov -a ${TestResultPath}_init -a ${TestResultPath}_Test -o ${TestResultPath}_Total -q
lcov -r ${TestResultPath}_Total "*googletest*" "*_Test.cpp" -o ${TestResultPath} -q

if [ $NeedHtml = false ]; then
        exit
fi

echo "Generate Coverage Report"
genhtml ${TestResultPath} --output-directory ${CoverageReportDir}

HEAD_COMMIT=$(git log -n 1 --pretty="%H")
SINCE_COMMIT=$(git log HEAD~2..HEAD~1 --pretty="%H")

if [ -z `command -v python` ]; then
        echo "Need python to generate incremental report"
fi

./ut_incremental_check.py $SINCE_COMMIT".."$HEAD_COMMIT '["${CMakeSourceDir}/src"]' "${CoverageReportDir}" 0.01
