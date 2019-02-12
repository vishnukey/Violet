cmake_minimum_required(VERSION 3.9.1)

project(VioletEngine)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_SOURCE_DIR ${CMAKE_HOME_DIR}/src)
#set(CMAKE_INCLUDE_PATH ${CMAKE_HOME_DIR}/include)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Violet ${SOURCES})

find_package(SFML REQUIRED COMPONENTS system window graphics)

if (SFML_FOUND)
        message("SFML Found")
        include_directories(${SFML_INCLUDE_DIRS})
        message("${SFML_INCLUDE_DIRS}")
        message("${SFML_LIBRARIES}")
        target_link_libraries(Violet sfml-system sfml-window sfml-graphics)
elseif(NOT SFML_FOUND)
        error("SFML not found")
endif()
