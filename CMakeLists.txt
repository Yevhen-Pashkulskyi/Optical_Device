cmake_minimum_required(VERSION 3.30)
project(Optical_Device)
include_directories(src/org/example)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Optical_Device src/org/example/app.cpp
        src/org/example/entity/device.cpp
        src/org/example/entity/device.h
)
