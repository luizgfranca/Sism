#!/bin/bash
set -e
set -x

PROJECT_DIR=$(pwd)

# BASEDIR=$(dirname "$PROJECT_DIR")
BASEDIR=$(pwd)
pushd "$BASEDIR"

cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=on
cmake --build .
cd ..

mkdir -p .vscode
cp build/compile_commands.json .vscode/compile_commands.json

cd build
./sism