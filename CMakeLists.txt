
cmake_minimum_required(VERSION 3.25...4.0)
project(THIEF_CATCHER VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

message(STATUS "Generating project files for '${PROJECT_NAME}' version ${PROJECT_VERSION}")

add_subdirectory(Kangaroo)
add_subdirectory(Core)


