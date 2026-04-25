#!/bin/bash
# 获取文件总行数
total=$(wc -l < README.md)
# 生成 1~总行数 的随机数
rand=$((RANDOM % total + 1))
# 读取随机行
sed -n "${rand}p" README.md