// Copyright 2021 AutoCore
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package main

import (
	"fmt"
	"io/fs"
	"os"
	"strconv"
	"time"
)

func main() {

	times := 100000
	argc := len(os.Args)

	if argc < 3 {
		fmt.Printf("usage: %v file buffer_size [times]\n", os.Args[0])
		os.Exit(1)
	}

	f, err := os.OpenFile(os.Args[1], os.O_RDONLY, fs.ModePerm)
	if err != nil {
		fmt.Println("error opening input %v: %v", os.Args[1], err)
		os.Exit(1)
	}

	buffer_size, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println("buffer size is not correct number: %v", os.Args[2])
		os.Exit(1)
	}
	buffer := make([]byte, buffer_size)

	if argc > 3 {
		times, err = strconv.Atoi(os.Args[3])
		if err != nil {
			fmt.Println("times is not correct number: %v", os.Args[3])
			os.Exit(1)
		}
	}

	for i := 0; i < 10; i++ {
		n, err := f.Read(buffer)
		if err != nil || n < 1 {
			fmt.Println("reader error: %v", err)
			os.Exit(1)
		}
	}

	start := time.Now()

	for i := 0; i < times; i++ {
		n, err := f.Read(buffer)
		if err != nil || n < 1 {
			fmt.Println("reader error: %v", err)
			os.Exit(1)
		}
	}

	end := time.Now()
	elapsed := end.Sub(start).Microseconds()
	throughput := int64(buffer_size*times*8000) / elapsed

	fmt.Println(elapsed, ",", throughput)
}
