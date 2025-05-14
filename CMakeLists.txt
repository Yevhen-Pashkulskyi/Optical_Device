cmake_minimum_required(VERSION 3.30)
project(Optical_Device)
include_directories(src/org/example)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Optical_Device src/org/example/app.cpp
        src/org/example/entity/DeviceBase.cpp
        src/org/example/entity/DeviceBase.h
        src/org/example/control/CameraController.cpp
        src/org/example/control/CameraController.h
        src/org/example/view/View.cpp
        src/org/example/view/View.h
        src/org/example/entity/OpticalDevice.cpp
        src/org/example/entity/OpticalDevice.h
        src/org/example/entity/PhotoCamera.cpp
        src/org/example/entity/PhotoCamera.h
)
