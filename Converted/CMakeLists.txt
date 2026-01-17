cmake_minimum_required(VERSION 3.10)
project(ProjectZomboidCpp VERSION 0.2.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    else()
        add_compile_options(-O3)
    endif()
endif()

# Find SDL2
if(NINTENDO_SWITCH)
    # Switch uses portlibs
    find_package(SDL2 REQUIRED)
    # For Switch, SDL2_image and SDL2_mixer are usually found via pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
    endif()
else()
    find_package(SDL2 REQUIRED)
    # SDL2_image for loading PNG/JPG assets
    find_package(SDL2_image QUIET)
    if(NOT SDL2_image_FOUND)
        # Try pkg-config if CMake module not found
        find_package(PkgConfig)
        if(PkgConfig_FOUND)
            pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
        endif()
    endif()
    # SDL2_mixer for audio playback
    find_package(SDL2_mixer QUIET)
    if(NOT SDL2_mixer_FOUND)
        # Try pkg-config if CMake module not found
        find_package(PkgConfig)
        if(PkgConfig_FOUND)
            pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
        endif()
    endif()
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/Core.cpp
    src/GameWindow.cpp
    src/GameStateMachine.cpp
    src/GameTime.cpp
    src/TextureManager.cpp
    src/Sprite.cpp
    src/SpriteBatch.cpp
    src/SpriteAnimation.cpp
    src/BitmapFont.cpp
    src/TileMap.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Collision.cpp
    src/InputManager.cpp
    src/SoundManager.cpp
)

# Headers
set(HEADERS
    include/Core.h
    include/GameWindow.h
    include/GameState.h
    include/GameStateMachine.h
    include/GameTime.h
    include/TextureManager.h
    include/Sprite.h
    include/SpriteBatch.h
    include/SpriteAnimation.h
    include/BitmapFont.h
    include/TileMap.h
    include/Entity.h
    include/Player.h
    include/Collision.h
    include/InputManager.h
    include/SoundManager.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
if(NINTENDO_SWITCH)
    target_link_libraries(${PROJECT_NAME} 
        SDL2::SDL2
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
    )
else()
    set(LINK_LIBS ${SDL2_LIBRARIES})
    
    if(SDL2_image_FOUND)
        list(APPEND LINK_LIBS SDL2_image::SDL2_image)
    elseif(SDL2_IMAGE_FOUND)
        list(APPEND LINK_LIBS ${SDL2_IMAGE_LIBRARIES})
        include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    else()
        message(WARNING "SDL2_image not found - texture loading may not work")
    endif()
    
    if(SDL2_mixer_FOUND)
        list(APPEND LINK_LIBS SDL2_mixer::SDL2_mixer)
    elseif(SDL2_MIXER_FOUND)
        list(APPEND LINK_LIBS ${SDL2_MIXER_LIBRARIES})
        include_directories(${SDL2_MIXER_INCLUDE_DIRS})
    else()
        message(WARNING "SDL2_mixer not found - audio playback will not work")
    endif()
    
    target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
endif()

# Copy media assets to build directory
# This creates a symlink on Unix or copies on Windows/Switch
if(NOT NINTENDO_SWITCH)
    # Create symlink to media directory for easy testing
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_SOURCE_DIR}/../media
            ${CMAKE_CURRENT_BINARY_DIR}/media
        COMMENT "Creating symlink to media directory..."
    )
else()
    # For Switch, we'll need to package assets differently
    # For now, just note this in the build output
    message(STATUS "Switch build - assets must be bundled separately")
    # TODO: Add romfs packaging for Switch
endif()

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/../media DESTINATION share/${PROJECT_NAME})

# Print configuration
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "SDL2 Include: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 Libraries: ${SDL2_LIBRARIES}")

# For Nintendo Switch (with devkitPro)
if(NINTENDO_SWITCH)
    message(STATUS "Building for Nintendo Switch")
    message(STATUS "DEVKITPRO: $ENV{DEVKITPRO}")
    
    # Switch executables use .elf extension
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
    
    # Create NRO (Nintendo Switch executable) 
    # Note: Requires nacptool and elf2nro in PATH
    if(EXISTS "$ENV{DEVKITPRO}/tools/bin/nacptool")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND $ENV{DEVKITPRO}/tools/bin/nacptool 
                --create "Project Zomboid" "C++ Port" "${PROJECT_VERSION}" 
                ${PROJECT_NAME}.nacp
            COMMAND $ENV{DEVKITPRO}/tools/bin/elf2nro 
                ${PROJECT_NAME}.elf ${PROJECT_NAME}.nro 
                --nacp=${PROJECT_NAME}.nacp
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Creating .nro file for Switch..."
            VERBATIM
        )
        message(STATUS "Will create .nro file after build")
    else()
        message(WARNING "nacptool/elf2nro not found - .nro creation will be skipped")
        message(WARNING "Install with: sudo dkp-pacman -S switch-tools")
    endif()
endif()
