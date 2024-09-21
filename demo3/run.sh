#!/bin/sh
current_dir="$(cd "$(dirname "$0")" && pwd)"
build_dir=${current_dir}/build
exe_file=${current_dir}/output/app
if [ -d ${build_dir} ]; then
    rm -rf ${build_dir}
fi
mkdir -p ${build_dir}
cd ${build_dir}
cmake ..
make
if [ $? = 0 ]; then
    echo "-----------------------------"
    md5sum ${exe_file}
    echo "-----------------------------"
    ${exe_file}
fi
