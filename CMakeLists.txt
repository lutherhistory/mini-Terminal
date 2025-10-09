cmake_minimum_required(VERSION 3.16)
project(app)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SRC "source/*.cpp")

add_executable(app main.cpp ${SRC})
