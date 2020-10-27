cmake_minimum_required(VERSION 3.16)
project(treePrinter)

set(CMAKE_CXX_STANDARD 11)

add_executable(treePrinter main.cpp TreeInfo.h TreePrinter.cpp TreePrinter.h)
