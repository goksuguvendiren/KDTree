cmake_minimum_required(VERSION 2.8)
project(kd_tree)

message(STATUS "Building kd_tree")

set(CMAKE_CXX_FLAGS                "-std=c++17")
set(CMAKE_CXX_FLAGS_DEBUG          "-g")
set(CMAKE_CXX_FLAGS_RELEASE        "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_AR      "/usr/bin/gcc-ar")
set(CMAKE_LINKER  "/usr/bin/ld")
set(CMAKE_NM      "/usr/bin/gcc-nm")
set(CMAKE_OBJDUMP "/usr/bin/objdump")
set(CMAKE_RANLIB  "/usr/bin/gcc-ranlib")

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(third_party)

add_library(kd_tree_lib include/kd_tree.hpp src/kd_tree.cpp)

target_include_directories(kd_tree_lib PUBLIC include)

add_executable(kd_tree main.cpp include/node.hpp include/utils.hpp include/vecd.hpp)
target_link_libraries(kd_tree PUBLIC kd_tree_lib)
target_link_libraries(kd_tree PUBLIC spdlog::spdlog)

#add_executable(test_kdtree "test_kdtree.cpp")
#target_link_libraries(test_kdtree KDTree)

