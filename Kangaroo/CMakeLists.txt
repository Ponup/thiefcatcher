
find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)

file(GLOB_RECURSE KANGAROO_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(kangaroo STATIC ${KANGAROO_SOURCES})

target_compile_features(kangaroo PUBLIC cxx_std_23)

target_include_directories(kangaroo
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(kangaroo
	PRIVATE
		SDL3::SDL3
		SDL3_ttf::SDL3_ttf
		SDL3_image::SDL3_image
		SDL3_mixer::SDL3_mixer
)

target_compile_options(kangaroo PRIVATE
	$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Werror -pedantic -pedantic-errors>
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)



