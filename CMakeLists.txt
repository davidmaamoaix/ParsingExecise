cmake_minimum_required(VERSION 3.13)
project(ParsingExercise C)

set(CMAKE_C_STANDARD 99)

add_executable(ParsingExercise src/main.c src/RecursiveDescent.h src/Token.h src/RecursiveDescent.c src/Token.c src/stack.c src/stack.h src/SimpleJsonParser.h src/SimpleJsonParser.c)