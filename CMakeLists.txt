# Compiling using GTest needs at least 3.15 version under
# Windows, as it need set property "MSVC_RUNTIME_LIBRARY"
cmake_minimum_required(VERSION 3.15)

PROJECT(GenericMath)

find_package(GTest REQUIRED)
find_package(Threads)

add_subdirectory(test/TestBasic)