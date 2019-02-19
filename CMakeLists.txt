cmake_minimum_required(VERSION 2.8)

# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "FATAL: In-source builds are not allowed. You should create a separate directory for build files.")
endif()

set(CMAKE_CXX_STANDARD 11)
project(centroiding_sim)
find_package(OpenCV 3.0.0 REQUIRED)

add_executable(csim ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(csim ${OpenCV_LIBS})
target_link_libraries(csim ${CMAKE_SOURCE_DIR}/src/cdpu.cpp)
target_link_libraries(csim ${CMAKE_SOURCE_DIR}/src/centroider.cpp)
target_link_libraries(csim ${CMAKE_SOURCE_DIR}/src/star_filter.cpp)
target_link_libraries(csim ${CMAKE_SOURCE_DIR}/src/star_filter_sw.cpp)
target_link_libraries(csim ${CMAKE_SOURCE_DIR}/src/star_filter_hw.cpp)

file(COPY ${CMAKE_SOURCE_DIR}/vhdl DESTINATION ${CMAKE_BINARY_DIR})
