cmake_minimum_required(VERSION 3.1)

project(AdventOfCode2018)

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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

add_executable(
	AdventOfCode2018
	External/Unformat/unformat.h
	util.h
	day1.cpp)

target_link_libraries(
	AdventOfCode2018
	gtest
	gtest_main)

target_include_directories(
	AdventOfCode2018 PUBLIC
	"External/range-v3/include")