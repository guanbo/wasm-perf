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

KINDS=(ssvm wamr native)

WAMRC=~/repo/wasm-micro-runtime/wamr-compiler/build/wamrc
WAMR=~/repo/wasm-micro-runtime/product-mini/platforms/linux/build/iwasm
SSVMC=~/repo/SSVM/build/tools/ssvm/ssvmc
SSVM=~/repo/SSVM/build/tools/ssvm/ssvm
FGROOT=~/repo/FlameGraph

TEST_DIR=/mnt/train
TEST_FILE=${TEST_DIR}/data.tar

BENCHMARK_PATH="$(pwd)/benchmark"

function perpare()
{
  for((i=0;i<"${#KINDS[@]}";i++));
  do
    mkdir -p benchmark/${KINDS[i]}
    # echo "" > benchmark/${KINDS[i]}/result.csv
  done
  
}

function build_all()
{
  pushd wasm
  gcc demo.c -o demo
  /opt/wasi-sdk/bin/clang demo.c -o demo.wasm
  $WAMRC -o demo.aot demo.wasm
  $SSVMC demo.wasm demo.so
  popd
}

function test_all()
{
  pushd wasm
  for((i=0;i<"${#BUFFER_SIZES[@]}";i++));
  do
    RESULT_FILE=${BUFFER_SIZES[i]}.csv
    echo "latency,throughput" > ../benchmark/native/${RESULT_FILE}
    echo "latency,throughput" > ../benchmark/wamr/${RESULT_FILE}
    echo "latency,throughput" > ../benchmark/ssvm/${RESULT_FILE}
    for((j=0;j<10;j++));
    do
      ./demo ${TEST_FILE} ${BUFFER_SIZES[i]} >> ../benchmark/native/${RESULT_FILE}
      $WAMR --dir=${TEST_DIR} demo.aot ${TEST_FILE} ${BUFFER_SIZES[i]} >> ../benchmark/wamr/${RESULT_FILE}
      $SSVM --dir ${TEST_DIR}:${TEST_DIR} demo.so ${TEST_FILE} ${BUFFER_SIZES[i]} >> ../benchmark/ssvm/${RESULT_FILE}
    done    
    # echo "" >> ../benchmark/native/${RESULT_FILE}
    # echo "" >> ../benchmark/wamr/${RESULT_FILE}
    # echo "" >> ../benchmark/ssvm/${RESULT_FILE}
  done
  popd
}

function print_result()
{
  echo > result.csv
  for((i=0;i<"${#KINDS[@]}";i++));
  do
    python3 stat.py ${KINDS[i]} >> result.csv
    # for((j=0;j<${#BUFFER_SIZES};j++));
    # do
    #   echo "${KINDS[i]} - ${BUFFER_SIZES[j]}"
    #   # python3 -c "import pandas as pd; df=pd.read_csv('benchmark/${KINDS[i]}/${BUFFER_SIZES[j]}.csv'); print(df['latency'].mean());"
    # done    
  done  
}

function perf_go()
{
  pushd $2
  sudo perf record -p $1 -F 999 -a -g
  sudo chmod +r *.data
  perf script > out.stack
  $FGROOT/stackcollapse-perf.pl out.stack > out.folded
  $FGROOT/flamegraph.pl out.folded > test.svg
  popd
}

function perf_all()
{
  pushd wasm
  # ./demo ${TEST_FILE} 1024 10000000 &
  # perf_go $! "${BENCHMARK_PATH}/native"
  # $WAMR --dir=${TEST_DIR} demo.aot ${TEST_FILE} 1024 10000000 &
  # perf_go $! "${BENCHMARK_PATH}/wamr"
  $SSVM --dir ${TEST_DIR}:${TEST_DIR} demo.so ${TEST_FILE} 1024 10000000 &
  perf_go $! "${BENCHMARK_PATH}/ssvm"
  popd
}

# perpare
# build_all

# test_all
# print_result

perf_all
# sudo sshfs -o allow_other,cache=no,IdentityFile=/home/ci/.ssh/id_rsa,no_readahead,cache_timeout=0,noauto_cache train@192.168.10.43:/home/train /mnt/train
