cmake_minimum_required(VERSION 2.8.2)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project(FuseMusepp CXX)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -I../deps")
set(CMAKE_BUILD_TYPE Debug)

# Enable automatic tests via CMake
# Probably will be removed - google test automatically discovers tests
enable_testing()

add_subdirectory(src)
add_subdirectory(tests)

