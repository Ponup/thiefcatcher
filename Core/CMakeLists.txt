cmake_policy(SET CMP0003 NEW)

message(STATUS "Compiling under ${CMAKE_SYSTEM_NAME}")

find_package(CURL REQUIRED)
find_package(TinyXML2 REQUIRED)
find_package(SQLITE3 REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_ttf REQUIRED)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/conan_toolchain.cmake")
	include("${CMAKE_CURRENT_SOURCE_DIR}/conan_toolchain.cmake")
endif()

file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "vendor/*.cpp" "vendor/*.cc")

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/src/Version.hpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/generated/Version.hpp"
)

add_executable(ThiefCatcher WIN32 MACOSX_BUNDLE ${GAME_SOURCES})

target_compile_features(ThiefCatcher PRIVATE cxx_std_23)

target_include_directories(ThiefCatcher PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_SOURCE_DIR}/vendor"
	"${CMAKE_CURRENT_BINARY_DIR}/generated"
)

target_compile_options(ThiefCatcher PRIVATE
	$<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Werror -pedantic -pedantic-errors>
	$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

target_link_libraries(ThiefCatcher
	PUBLIC
		kangaroo
	PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
		SDL3_mixer::SDL3_mixer
		SDL3_ttf::SDL3_ttf
		CURL::libcurl
		SQLite::SQLite3
		TinyXML2::TinyXML2
		$<$<PLATFORM_ID:Windows>:libintl>
		$<$<PLATFORM_ID:Darwin>:intl>
)

set(INSTALL_FOLDER ".")
set(CPACK_SOURCE_IGNORE_FILES "/\\.git/;\\.swp$;")

install(
	DIRECTORY data resources DESTINATION "${INSTALL_FOLDER}"
	PATTERN ".git" EXCLUDE
)

install(FILES config.ini ../LICENSE ../README.md ../CREDITS DESTINATION "${INSTALL_FOLDER}")

install(
	TARGETS ThiefCatcher
	RUNTIME DESTINATION "${INSTALL_FOLDER}"
	BUNDLE DESTINATION "${INSTALL_FOLDER}"
)

set(CPACK_PACKAGE_NAME "ThiefCatcher")
set(CPACK_PACKAGE_VENDOR "Ponup Games")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Thief Catcher")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_EXECUTABLES "ThiefCatcher;Thief Catcher")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")

set(CPACK_NSIS_HELP_LINK "http://ponup.com/thief-catcher.html")
set(CPACK_NSIS_URL_INFO_ABOUT "http://ponup.com/thief-catcher.html")
set(CPACK_NSIS_CONTACT "https://docs.google.com/forms/d/1MnEaBXmTZvtJsE-efQpxuSsYSxfHJLLjKVlil7Jb7P8/viewform?c=0&w=1")
set(CPACK_NSIS_MODIFY_PATH ON)

include(CPack)
