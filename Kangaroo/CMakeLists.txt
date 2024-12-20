
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

set(KANGAROO_LIB_NAME kangaroo)

project(${KANGAROO_LIB_NAME} VERSION 0.9.9 LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE KANGAROO_SOURCES "src/*.cpp")
add_library(${KANGAROO_LIB_NAME} STATIC ${KANGAROO_SOURCES})

target_include_directories(
	${KANGAROO_LIB_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS}
)
target_link_libraries(${KANGAROO_LIB_NAME} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
set_property(TARGET ${KANGAROO_LIB_NAME} PROPERTY CXX_STANDARD 14)

if(UNIX)
	add_definitions(-pedantic -pedantic-errors -Wall -Werror -Werror)
else()
	add_definitions(-Wall)
endif()

