#!/bin/bash

_target=${1:-'all'}

rm -rf build
mkdir build

_workspaceFolder=$(pwd)

cd build

# For non-conda users:
# cmake ..   -G Ninja \
#   -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
#   -DCMAKE_BUILD_TYPE:STRING=Debug \
#   -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
#   -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
#   -DMLIR_DIR=${_workspaceFolder}/third_party/lib/cmake/mlir \
#   -DLLVM_DIR=${_workspaceFolder}/third_party/lib/cmake/llvm \
#   -DCMAKE_MODULE_PATH="${_workspaceFolder}/third_party/lib/cmake/mlir;${_workspaceFolder}/third_party/lib/cmake/llvm" \
#   -DMLIR_TABLEGEN_EXE=${_workspaceFolder}/third_party/bin/mlir-tblgen
#   # -DLibEdit_DIR=/root/miniconda3/envs/mlir/lib

cmake ..  -G Ninja --no-warn-unused-cli \
  -Wno-dev \
  -DCMAKE_MODULE_PATH="/root/miniconda3/envs/llvm-tutor/lib/cmake/mlir;/root/miniconda3/envs/llvm-tutor/lib/cmake/llvm" \
  -DLT_LLVM_INSTALL_DIR=/root/miniconda3/envs/llvm-tutor/ \
  -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
  -DCMAKE_BUILD_TYPE:STRING=Debug \
  -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
  -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++

# ninja
cmake \
  --build `pwd` \
  --config Debug --target ${_target}
