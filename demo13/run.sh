#!/usr/bin/env sh
current_dir="$(dirname "$(realpath "$0")")"
build_dir=${current_dir}/build
output_dir=${current_dir}/output
app_file=${output_dir}/test
compile()
{   
    if [ -d ${build_dir} ]; then
        rm -rf ${build_dir}
    fi  
    mkdir -p ${build_dir}
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