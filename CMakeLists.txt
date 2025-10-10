cmake_minimum_required(VERSION 3.16)
project(app)

set(CMAKE_CXX_STANDARD 17)

# Automatically get all cpp files in source/
file(GLOB SOURCES "source/*.cpp")

# Include main.cpp manually if it’s outside source/
add_executable(app main.cpp ${SOURCES})
