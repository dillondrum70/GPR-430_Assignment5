cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/socklib)
include_directories(socklib/)

project(a5)

add_executable(a5 main.cpp ${PROJECT_SOURCE_DIR}/socklib/socklib_generic.cpp)

target_compile_features(a5 PRIVATE cxx_std_17)

# target_compile_options(a5 PRIVATE -fsanitize=address)
# target_link_options(a5 PRIVATE -fsanitize=address)

set(CMAKE_BUILD_TYPE Debug)

if (UNIX)
	target_sources(a5 PRIVATE ${PROJECT_SOURCE_DIR}/socklib/socklib_posix.cpp)
endif (UNIX)

if (WIN32)
	target_sources(a5 PRIVATE ${PROJECT_SOURCE_DIR}/socklib/socklib_win32.cpp)
endif (WIN32)

target_sources(a5 PRIVATE ${PROJECT_SOURCE_DIR}/socklib/pool.cpp)
