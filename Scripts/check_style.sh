#! /bin/bash

if command -v clang-format >/dev/null 2>&1; then
    echo "clang-format exist"
else
    echo "please install clang-format first"
    exit
fi

for file in $(git status | grep -E "modified|new file" | awk -F ":" '{print $2}' |  grep -E ".*\.h$|.*\.cpp$|.*\.hpp$")
do
   echo "format file: $file"
   clang-format -i -style=file $file
done

for file in $(git status | grep -E "../" | awk -F "：" '{print $2}' |  grep -E ".*\.h$|.*\.cpp$|.*\.hpp$")
do
   echo "format file: $file"
   clang-format -i -style=file $file
done
