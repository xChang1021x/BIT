cmake_minimum_required(VERSION 3.16)
project(lab01)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-pedantic)
include_directories(include)

add_executable(Compilerlab1
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
    src/codegen.cpp
)

target_compile_features(Compilerlab1 PRIVATE cxx_std_14)
