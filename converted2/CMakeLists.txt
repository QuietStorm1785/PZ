cmake_minimum_required(VERSION 3.16)
project(ProjectZomboid)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -fPIC")

# Include directories - only local converted headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add zombie include directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/zombie)

# Compile only core game files that don't depend on external Java wrappers
file(GLOB_RECURSE CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/zombie/core/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/zombie/iso/**/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/zombie/scripting/**/*.cpp"
)

# Exclude problematic files with external dependencies
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/Lua/.*\\.cpp$")
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/fmod/.*\\.cpp$")
list(FILTER CORE_SOURCES EXCLUDE REGEX ".*/worldMap/.*\\.cpp$")

# Create library from core game sources
add_library(projectzomboid OBJECT ${CORE_SOURCES})

message(STATUS "ProjectZomboid C++ Conversion")
message(STATUS "=================================")
message(STATUS "Compiling core zombie sources: ${CMAKE_CURRENT_SOURCE_DIR}/src/zombie")
message(STATUS "Include path: ${CMAKE_CURRENT_SOURCE_DIR}/include/zombie")
message(STATUS "")
message(STATUS "Note: This is a structural conversion")
message(STATUS "      Many method implementations are stubs (returning default values)")
message(STATUS "      External Java wrappers (FMOD, Lua, etc.) are excluded")
message(STATUS "      Next step: Implement critical game systems incrementally")



