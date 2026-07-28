
set(KANGAROO_LIB_NAME kangaroo)

project(${KANGAROO_LIB_NAME} VERSION 0.9.9 LANGUAGES CXX)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)

file(GLOB_RECURSE KANGAROO_SOURCES "src/*.cpp")
add_library(${KANGAROO_LIB_NAME} STATIC ${KANGAROO_SOURCES})

target_include_directories(
	${KANGAROO_LIB_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${KANGAROO_LIB_NAME} PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image SDL3_mixer::SDL3_mixer)
set_property(TARGET ${KANGAROO_LIB_NAME} PROPERTY CXX_STANDARD 17)

if(UNIX)
	add_definitions(-pedantic -pedantic-errors -Wall -Werror)
else()
	add_definitions(-Wall)
endif()


