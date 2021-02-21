cmake_minimum_required(VERSION "3.0")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

if(DEFINED CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
	message(STATUS "Debug configuration detected: CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
	add_compile_definitions("DEBUG")
endif()

if(DEFINED BOOST_PATH)
	message(STATUS "boost library located: ${BOOST_PATH}")
	list(APPEND CMAKE_PREFIX_PATH "${BOOST_PATH}")
endif()

project("dna-not-ascii")

include(FindPkgConfig)
set(requiredlibs)

include_directories("/usr/local/lib")

cmake_policy(SET CMP0074 OLD)
find_package(Boost 1.40 COMPONENTS program_options system filesystem REQUIRED)
find_package(ZLIB)

file(GLOB_RECURSE TARGET_SOURCES src/*.cpp lib/cpp-stopwatch/*.cpp lib/cpp_progress_bar/progress_bar.cpp)
add_executable("${PROJECT_NAME}" ${TARGET_SOURCES})
include_directories("${Boost_INCLUDE_DIR}")
target_link_libraries("${PROJECT_NAME}" "stdc++fs")
target_link_libraries("${PROJECT_NAME}" "${Boost_LIBRARIES}")
target_link_libraries("${PROJECT_NAME}" "ZLIB::ZLIB")

target_include_directories("${PROJECT_NAME}" PRIVATE "include" PRIVATE "lib/cpp-stopwatch" PRIVATE "lib/cpp_progress_bar")
install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
install(FILES "src/dna.cpp" DESTINATION src)
