#!/bin/bash
if [ "$1" = "clean" ]; then
    bazel clean
    exit 0
fi
bazel build //app:app
bazel run //app:app