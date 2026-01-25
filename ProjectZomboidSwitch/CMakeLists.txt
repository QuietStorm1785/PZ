# Only perform Boost include mapping for Nintendo Switch builds
if(NINTENDO_SWITCH)
    file(GLOB_RECURSE NON_ABSEIL_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
        "${CMAKE_SOURCE_DIR}/src/include/**/*.h"
        "${CMAKE_SOURCE_DIR}/src/include/**/*.hpp"
    )
    foreach(SRC ${NON_ABSEIL_SOURCES})
        if(NOT SRC MATCHES "/abseil/")
            file(READ "${SRC}" SRC_CONTENTS)
            # Replace custom BigInteger include with Boost
            string(REPLACE "#include \"java/math/BigInteger.h\"" "#include <boost/multiprecision/cpp_int.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "#include \"../../java/math/BigInteger.h\"" "#include <boost/multiprecision/cpp_int.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "java::math::BigInteger" "boost::multiprecision::cpp_int" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "BigInteger" "boost::multiprecision::cpp_int" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl mappings (already present)
            string(REPLACE "#include \"absl/container/flat_hash_map.h\"" "#include <boost/unordered_map.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::flat_hash_map" "boost::unordered_map" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "#include \"absl/container/flat_hash_set.h\"" "#include <boost/unordered_set.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::flat_hash_set" "boost::unordered_set" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::strings" "boost::algorithm" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::str_format" "boost::format" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::base" "boost/thread.hpp" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::synchronization" "boost/thread.hpp" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::time" "boost::chrono" SRC_CONTENTS "${SRC_CONTENTS}")
            file(WRITE "${SRC}" "${SRC_CONTENTS}")
        endif()
    endforeach()
endif()

# Only perform absl-to-boost mapping for Nintendo Switch builds
if(NINTENDO_SWITCH)
    # Global replacement of absl types/includes with Boost or std equivalents in non-Abseil code
    file(GLOB_RECURSE NON_ABSEIL_SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.h"
        "${CMAKE_SOURCE_DIR}/src/include/**/*.h"
        "${CMAKE_SOURCE_DIR}/src/include/**/*.hpp"
    )
    foreach(SRC ${NON_ABSEIL_SOURCES})
        if(NOT SRC MATCHES "/abseil/")
            file(READ "${SRC}" SRC_CONTENTS)
            # absl::flat_hash_map -> boost::unordered_map
            string(REPLACE "#include \"absl/container/flat_hash_map.h\"" "#include <boost/unordered_map.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::flat_hash_map" "boost::unordered_map" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl::flat_hash_set -> boost::unordered_set
            string(REPLACE "#include \"absl/container/flat_hash_set.h\"" "#include <boost/unordered_set.hpp>" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::flat_hash_set" "boost::unordered_set" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl::strings -> boost::algorithm or std::string
            string(REPLACE "absl::strings" "boost::algorithm" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl::str_format -> boost::format
            string(REPLACE "absl::str_format" "boost::format" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl::base, absl::synchronization -> boost/thread.hpp or boost/sync
            string(REPLACE "absl::base" "boost/thread.hpp" SRC_CONTENTS "${SRC_CONTENTS}")
            string(REPLACE "absl::synchronization" "boost/thread.hpp" SRC_CONTENTS "${SRC_CONTENTS}")
            # absl::time -> boost::chrono
            string(REPLACE "absl::time" "boost::chrono" SRC_CONTENTS "${SRC_CONTENTS}")
            file(WRITE "${SRC}" "${SRC_CONTENTS}")
        endif()
    endforeach()
endif()
cmake_minimum_required(VERSION 3.10)
project(ProjectZomboidSwitch VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
# Abseil requires C++20, use C++20 for all builds
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type

# Build options
option(NINTENDO_SWITCH "Build for Nintendo Switch" OFF)

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
    add_compile_options(/wd4100) # unreferenced formal parameter
    add_compile_options(/wd4101) # unreferenced local variable
else()
    add_compile_options(-Wall -Wextra -pedantic)
    add_compile_options(-Wno-unused-parameter)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
endif()

set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/src/boost")
if(EXISTS ${BOOST_ROOT})
    message(STATUS "Found Boost at: ${BOOST_ROOT}")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    include_directories(${BOOST_ROOT})
    add_definitions(-DBOOST_ALL_NO_LIB) # Disable auto-linking on Windows
else()
    message(WARNING "Boost not found at ${BOOST_ROOT} - some features may not compile")
endif()

# Add Abseil (always, for all platforms)
set(ABSEIL_ROOT "${CMAKE_SOURCE_DIR}/src/abseil")
if(EXISTS ${ABSEIL_ROOT})
    message(STATUS "Found Abseil at: ${ABSEIL_ROOT}")
    if(NINTENDO_SWITCH)
        # For Switch, only use Abseil as header-only: do not add_subdirectory, just add include path
        include_directories(${ABSEIL_ROOT})
    else()
        add_subdirectory(${ABSEIL_ROOT} ${CMAKE_BINARY_DIR}/abseil EXCLUDE_FROM_ALL)
    endif()
else()
    message(WARNING "Abseil not found at ${ABSEIL_ROOT} - some features may not compile")
endif()

# Platform-specific settings
cmake_minimum_required(VERSION 3.10)
project(ProjectZomboidSwitch VERSION 1.0.0 LANGUAGES CXX)

# Qt (QImage) support for image handling
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(NINTENDO_SWITCH)
    message(STATUS "Configuring for Nintendo Switch")
    add_definitions(-D__SWITCH__)
    add_definitions(-DNINTENDO_SWITCH)
    
    # Find SDL2 on Switch
    find_package(SDL2 REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_check_modules(SDL2_NET REQUIRED SDL2_net)
    
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} 
                        ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS})
else()
    # Windows/Linux desktop build
    find_package(SDL2)
    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS})
    else()
        message(WARNING "SDL2 not found - some features may not compile")
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src/boost)
include_directories(${CMAKE_SOURCE_DIR}/src/OpenCV/include)
include_directories(${CMAKE_SOURCE_DIR}/src/OpenCV/modules/highgui/include)
include_directories(${CMAKE_SOURCE_DIR}/src/lua-5.4.7)
include_directories(${CMAKE_SOURCE_DIR}/src/zlib)
include_directories(${CMAKE_SOURCE_DIR}/src/sqlite)
include_directories(${CMAKE_SOURCE_DIR}/src/sqlite)
include_directories(${CMAKE_SOURCE_DIR}/src/abseil)
include_directories(${CMAKE_SOURCE_DIR}/src/include/de/btobastian/javacord)
include_directories(${CMAKE_SOURCE_DIR}/src/fmod/core/inc)
include_directories(${CMAKE_SOURCE_DIR}/src/fmod/studio/inc)
include_directories(${CMAKE_SOURCE_DIR}/src/fmod/fsbank/inc)
include_directories(${CMAKE_SOURCE_DIR}/src/fmod/plugins/fmod_haptics/inc)
include_directories(${CMAKE_SOURCE_DIR}/src/fmod/plugins/resonance_audio/inc)

# Collect all source files

# Exclude Boost example and test files from sources to avoid build errors (e.g., AutoMoc conflicts)
file(GLOB_RECURSE ALL_CONVERT2CPP_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/**/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

set(CONVERT2CPP_SOURCES "")
foreach(SRC ${ALL_CONVERT2CPP_SOURCES})
    if(NOT SRC MATCHES "/boost/tools/build/example/qt/")
        if(NOT SRC MATCHES "/boost/tools/build/test/")
            if(NOT SRC MATCHES "/boost/libs/.*/test/")
                if(NOT SRC MATCHES "/boost/libs/.*/example/")
                    list(APPEND CONVERT2CPP_SOURCES ${SRC})
                endif()
            endif()
        endif()
    endif()
endforeach()

file(GLOB_RECURSE CONVERT2CPP_HEADERS 
    "${CMAKE_SOURCE_DIR}/include/**/*.h"
    "${CMAKE_SOURCE_DIR}/include/*.h"
)

message(STATUS "Found ${CMAKE_MATCH_COUNT} source files")
list(LENGTH CONVERT2CPP_SOURCES SOURCE_COUNT)
message(STATUS "Total source files: ${SOURCE_COUNT}")

# Create main.cpp if it doesn't exist
set(MAIN_CPP "${CMAKE_SOURCE_DIR}/src/main.cpp")
if(NOT EXISTS ${MAIN_CPP})
    file(WRITE ${MAIN_CPP} 
"#include <iostream>
#include <cstdlib>

// Entry point for Project Zomboid converted code
int main(int argc, char* argv[]) {
    std::cout << \"Project Zomboid - Convert2Cpp\" << std::endl;
    std::cout << \"Converted Java-to-C++ codebase\" << std::endl;
    std::cout << \"Version: ${PROJECT_VERSION}\" << std::endl;
    
    // TODO: Initialize game systems here
    
    return EXIT_SUCCESS;
}
")
    message(STATUS "Created main.cpp entry point")
endif()

# Add main.cpp to sources if not already included
list(APPEND CONVERT2CPP_SOURCES ${MAIN_CPP})

# Create executable
add_executable(ProjectZomboidSwitch ${CONVERT2CPP_SOURCES})
message(STATUS "Building executable")

# Set output name
if(NINTENDO_SWITCH)
    set_target_properties(ProjectZomboidSwitch PROPERTIES OUTPUT_NAME "ProjectZomboidSwitch")
else()
    set_target_properties(ProjectZomboidSwitch PROPERTIES OUTPUT_NAME "pz_convert2cpp")
endif()

# Include directories
target_include_directories(ProjectZomboidSwitch PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/include
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
set(LINK_LIBS "")

# FMOD Core, Studio, FSBANK, Haptics, Resonance Audio (x64)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND LINK_LIBS
        ${CMAKE_SOURCE_DIR}/src/fmod/core/lib/x64/fmod_vc.lib
        ${CMAKE_SOURCE_DIR}/src/fmod/studio/lib/x64/fmodstudio_vc.lib
        ${CMAKE_SOURCE_DIR}/src/fmod/fsbank/lib/x64/fsbank_vc.lib
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/operations.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/path.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/codecvt_error_category.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/exception.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/unique_path.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/utf8_codecvt_facet.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/windows_file_codecvt.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/filesystem/src/windows_tools.hpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/system/extra/boost_system.natvis
        ${CMAKE_SOURCE_DIR}/src/boost/libs/thread/src/future.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/thread/src/tss_null.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/chrono/src/chrono.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/chrono/src/process_cpu_clocks.cpp
        ${CMAKE_SOURCE_DIR}/src/boost/libs/chrono/src/thread_clock.cpp
    )
    # Abseil (skip for Switch, handled by Boost mapping)
    if(NOT NINTENDO_SWITCH)
        list(APPEND LINK_LIBS
            absl::strings
            absl::str_format
            absl::base
            absl::synchronization
            absl::time
            absl::flat_hash_map
            absl::flat_hash_set
        )
    endif()
    # SQLite
    list(APPEND LINK_LIBS
        ${CMAKE_SOURCE_DIR}/src/sqlite/sqlite3.c
    )
    # Optional plugins
    if(EXISTS "${CMAKE_SOURCE_DIR}/src/fmod/plugins/fmod_haptics/lib/x64/fmod_haptics.dll")
        list(APPEND LINK_LIBS
            ${CMAKE_SOURCE_DIR}/src/fmod/plugins/fmod_haptics/lib/x64/fmod_haptics.dll
        )
    endif()
    if(EXISTS "${CMAKE_SOURCE_DIR}/src/fmod/plugins/resonance_audio/lib/x64/resonanceaudio.dll")
        list(APPEND LINK_LIBS
            ${CMAKE_SOURCE_DIR}/src/fmod/plugins/resonance_audio/lib/x64/resonanceaudio.dll
        )
    endif()
endif()

# Abseil libraries

# Always link Abseil if available (including for Switch)

# For Switch, only link header-only Abseil modules and use Boost for time/debugging
if(EXISTS ${ABSEIL_ROOT})
    if(NOT NINTENDO_SWITCH)
        list(APPEND LINK_LIBS
            absl::strings
            absl::str_format
            absl::base
            absl::synchronization
            absl::time
            absl::flat_hash_map
            absl::flat_hash_set
        )
    endif()
endif()

# Always link Boost for Switch
if(NINTENDO_SWITCH AND EXISTS ${BOOST_ROOT})
    # For Switch, use header-only Boost modules and link compatible sources if available
    # Header-only modules (no linking required)
    # If you have built .a or .so files for Switch, add them here
    # Example: ${BOOST_ROOT}/libs/filesystem/src/operations.cpp
    # Example: ${BOOST_ROOT}/libs/system/extra/boost_system.natvis
    # Example: ${BOOST_ROOT}/libs/thread/src/future.cpp
    # Example: ${BOOST_ROOT}/libs/chrono/src/chrono.cpp
endif()

# Platform-specific libraries
if(NINTENDO_SWITCH)
    list(APPEND LINK_LIBS
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_NET_LIBRARIES}
    )
    # Ensure /switch/media directory exists at build time
    set(SWITCH_MEDIA_DIR "$<TARGET_FILE_DIR:ProjectZomboidSwitch>/switch/PZSwitch/media")
    add_custom_command(
        TARGET ProjectZomboidSwitch PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${SWITCH_MEDIA_DIR}"
        COMMENT "Creating /switch/PZSwitch/media directory for Nintendo Switch assets"
    )

    # Place the .nro in /switch/PZSwitch/media
    set(NRO_OUTPUT_PATH "${SWITCH_MEDIA_DIR}/ProjectZomboidSwitch.nro")
    add_custom_command(
        TARGET ProjectZomboidSwitch POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:ProjectZomboidSwitch>" "${NRO_OUTPUT_PATH}"
        COMMENT "Copying .nro to /switch/PZSwitch/media"
    )

    # Zip the /switch/PZSwitch/media directory after build
    add_custom_command(
        TARGET ProjectZomboidSwitch POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E tar cfv "${SWITCH_MEDIA_DIR}.zip" --format=zip -- "${SWITCH_MEDIA_DIR}"
        COMMENT "Zipping /switch/PZSwitch/media directory"
    )
    
    # Switch-specific: Create .nro file
    include(${DEVKITPRO}/cmake/SwitchTools.cmake OPTIONAL)
    if(COMMAND add_nro_target)
        # Create icon.jpg if missing
        set(ICON_FILE "${CMAKE_SOURCE_DIR}/icon.jpg")
        if(NOT EXISTS ${ICON_FILE})
            # Create a placeholder - user should replace with actual icon
            file(WRITE "${CMAKE_BINARY_DIR}/icon_placeholder.txt" 
                "Replace icon.jpg with a 256x256 JPEG image")
            set(ICON_FILE "")
        endif()
        
        add_nro_target(ProjectZomboidSwitch
            NAME "Project Zomboid"
            AUTHOR "PZ Team"
            VERSION "${PROJECT_VERSION}"
            ${ICON_FILE}
        )
        message(STATUS "Will create .nro file for Switch")
    endif()
elseif(SDL2_FOUND)
    list(APPEND LINK_LIBS ${SDL2_LIBRARIES})
endif()

# Link all libraries to target

# Link Qt libraries
target_link_libraries(ProjectZomboidSwitch PRIVATE Qt5::Core Qt5::Gui)

if(LINK_LIBS)
    target_link_libraries(ProjectZomboidSwitch PRIVATE ${LINK_LIBS})
endif()

# Installation rules
install(TARGETS ProjectZomboidSwitch
    RUNTIME DESTINATION bin
)

# Build information
message(STATUS "=== Project Zomboid Convert2Cpp Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Target: ${NINTENDO_SWITCH}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Source files: ${SOURCE_COUNT}")
message(STATUS "Boost: ${BOOST_ROOT}")
message(STATUS "Abseil: ${ABSEIL_ROOT}")
if(NINTENDO_SWITCH)
    message(STATUS "Output: ProjectZomboidSwitch.nro")
else()
    message(STATUS "Output: pz_convert2cpp.exe")
endif()
