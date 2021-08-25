cmake_minimum_required(VERSION 3.19)

project(rusty-cpp)

add_library(rusty-cpp INTERFACE)
target_include_directories(rusty-cpp INTERFACE include)
target_compile_features(rusty-cpp INTERFACE cxx_std_20)
