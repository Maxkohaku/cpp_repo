#!/bin/env sh
current_dir="$(dirname "$(realpath "$0")")"
build_dir=${current_dir}/build
output_dir=${current_dir}/output
app_file=${output_dir}/test
coredump_file=${current_dir}/coredump
passwd="ynh"
compile()
{   
    if [ -d ${build_dir} ]; then
        rm -rf ${build_dir}
    fi  
    mkdir -p ${build_dir}

    if [ -d ${coredump_file} ]; then
        rm -rf ${coredump_file}
    fi  
    mkdir -p ${coredump_file}
    ulimit -c unlimited
    echo "${passwd}" | sudo -S sh -c "echo '${coredump_file}/core-%e-%p-%t' > /proc/sys/kernel/core_pattern"


    cd ${build_dir}
    cmake ..
    make
    if [ $? != 0 ]; then
        cd -
        echo "编译失败!\n"
        exit -1
    else
        cd -
        echo "编译成功!\n--------------------"
    fi
}
run()
{
    echo "本次运行的程序md5sum信息如下:"
    md5sum $app_file
    ${app_file}
    echo "--------------------\n运行结束!"
}
main()
{
    compile
    run
}
main