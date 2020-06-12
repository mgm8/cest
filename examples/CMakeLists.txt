cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 11)
project(cest-example)
find_package(OpenCV 4.0.0 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(cest-example ${CMAKE_SOURCE_DIR}/example.cpp)
target_link_libraries(cest-example ${OpenCV_LIBS})
target_link_libraries(cest-example cest)
