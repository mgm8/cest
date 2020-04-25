cmake_minimum_required(VERSION 2.8)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

set(CMAKE_CXX_STANDARD 11)
project(cest)

find_package(OpenCV 4.0.0 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(cest STATIC ${CMAKE_SOURCE_DIR}/src/cdpu.cpp
                        ${CMAKE_SOURCE_DIR}/src/centroider.cpp
                        ${CMAKE_SOURCE_DIR}/src/star_filter.cpp
                        ${CMAKE_SOURCE_DIR}/src/star_filter_sw.cpp
                        ${CMAKE_SOURCE_DIR}/src/star_filter_hw.cpp)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/vhdl/ DESTINATION share)
install(TARGETS cest DESTINATION lib)
