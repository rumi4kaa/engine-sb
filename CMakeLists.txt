cmake_minimum_required(VERSION 3.10)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(SearchEngine main.cpp ConverterJSON.cpp InvertedIndex.cpp SearchServer.cpp)