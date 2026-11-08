cmake_minimum_required(VERSION 3.10)
project(OpenCVDemo)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv_app src/main_opencv.cpp)
target_link_libraries(opencv_app ${OpenCV_LIBS})
