#!/bin/bash

# Copyright 2021 AutoCore
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -e

BUFFER_SIZES=(
  64
  128
  256
  512
  1024
  2048
)

TEST_DIR=/mnt/train
TEST_FILE=${TEST_DIR}/data.tar

function build_all()
{
  pushd wasm
  gcc demo.c -o demo
  popd
}

function test_all()
{
  pushd wasm
  for((i=0;i<"${#BUFFER_SIZES[@]}";i++));
  do
    ./demo ${TEST_FILE} ${BUFFER_SIZES[i]}
  done
  popd
}

build_all

test_all
