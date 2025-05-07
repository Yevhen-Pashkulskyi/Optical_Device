cmake_minimum_required(VERSION 3.30)
project(Optical_Device)

set(CMAKE_CXX_STANDARD 20)

add_executable(Optical_Device src/org/example/app.cpp
        src/org/example/entity/device.cpp
        src/org/example/entity/device.h
)
