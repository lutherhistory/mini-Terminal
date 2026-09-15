cmake_minimum_required(VERSION 3.16)
project(mish)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-g -Wall -Wextra -pedantic)

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
