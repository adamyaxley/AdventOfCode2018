cmake_minimum_required(VERSION 3.0)

project(AdventOfCode2018)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(External/DownloadProject/DownloadProject.cmake)

# Functional test
download_project(PROJ                googletest
                 GIT_REPOSITORY      https://github.com/abseil/googletest.git
                 GIT_TAG             release-1.8.1
                 ${UPDATE_DISCONNECTED_IF_AVAILABLE}
)
# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

add_executable(
	AdventOfCode2018
	External/Unformat/unformat.h
	util.h
	day1.cpp)

target_link_libraries(
	AdventOfCode2018
	gtest
	gtest_main)