cmake_minimum_required(VERSION 3.9.1)

project(VioletEngine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Violet ${SOURCES})

add_subdirectory(libs/SFML)

target_link_libraries(Violet sfml-system sfml-window sfml-graphics)
