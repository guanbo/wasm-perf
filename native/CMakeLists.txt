# Copyright 2021 AutoCore
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http:#www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
cmake_minimum_required(VERSION 3.5)
project(native VERSION 0.1.0 LANGUAGES C)
include(GNUInstallDirs)

set(CMAKE_C_STANDARD 11)

add_executable(server_udp server_udp.c)
add_executable(client_udp client_udp.c)
add_executable(agent_udp agent_udp.c)