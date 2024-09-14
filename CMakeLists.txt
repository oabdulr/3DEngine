cmake_minimum_required(VERSION 3.22.1)

project(3DEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "-g")


# Recursively find all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

# Add the directory containing pch.h to the include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2_ttf)
