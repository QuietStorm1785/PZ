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
    # For Switch, SDL2_image, SDL2_mixer, and SDL2_net are usually found via pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_check_modules(SDL2_NET REQUIRED SDL2_net)
    if(SDL2_FOUND)
        include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS})
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
    # SDL2_net for networking
    find_package(SDL2_net QUIET)
    if(NOT SDL2_net_FOUND)
        # Try pkg-config if CMake module not found
        find_package(PkgConfig)
        if(PkgConfig_FOUND)
            pkg_check_modules(SDL2_NET REQUIRED SDL2_net)
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
    src/IsoPlayer.cpp
    src/IsoObject.cpp
    src/IsoGridSquare.cpp
    src/IsoChunk.cpp
    src/IsoCell.cpp
    src/IsoZombie.cpp
    src/NetworkManager.cpp
    src/Pathfinding.cpp
    src/Inventory.cpp
    src/Building.cpp
    src/AIBehaviors.cpp
    src/SaveLoad.cpp
    src/Animation.cpp
    src/AnimationController.cpp
    src/TextureAtlas.cpp
    src/Audio.cpp
    src/UI.cpp
    src/Tasks.cpp
    src/NetworkingEnhanced.cpp
    src/WorldContent.cpp
    src/WorldLoader.cpp
    src/SpatialGrid.cpp
    src/AudioInteractionSystem.cpp
    src/VisibilitySystem.cpp
    src/InventoryManager.cpp
    src/PathfindingThreadPool.cpp
    src/ObjectPool.cpp
    src/AssetStreaming.cpp
    src/ChunkManager.cpp
    src/ChunkRenderer.cpp
    src/PlayerChunkSync.cpp
    src/IsometricRenderer.cpp
    src/WorldCollisionSystem.cpp
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
    include/IsoPlayer.h
    include/IsoObject.h
    include/IsoGridSquare.h
    include/IsoChunk.h
    include/IsoCell.h
    include/IsoZombie.h
    include/NetworkManager.h
    include/Pathfinding.h
    include/Inventory.h
    include/Building.h
    include/AIBehaviors.h
    include/SaveLoad.h
    include/Animation.h
    include/Audio.h
    include/UI.h
    include/Tasks.h
    include/NetworkingEnhanced.h
    include/WorldContent.h
    include/WorldLoader.h
    include/Terrain.h
    include/SpatialGrid.h
    include/AudioInteractionSystem.h
    include/VisibilitySystem.h
    include/InventoryManager.h
    include/PathfindingThreadPool.h
    include/ObjectPool.h
    include/AssetStreaming.h
    include/ChunkManager.h
    include/ChunkRenderer.h
    include/PlayerChunkSync.h
    include/IsometricRenderer.h
    include/WorldCollisionSystem.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries
if(NINTENDO_SWITCH)
    target_link_libraries(${PROJECT_NAME} 
        SDL2::SDL2
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_NET_LIBRARIES}
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
    
    if(SDL2_net_FOUND)
        list(APPEND LINK_LIBS SDL2_net::SDL2_net)
    elseif(SDL2_NET_FOUND)
        list(APPEND LINK_LIBS ${SDL2_NET_LIBRARIES})
        include_directories(${SDL2_NET_INCLUDE_DIRS})
    else()
        message(WARNING "SDL2_net not found - networking will not work")
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

# Test executables (not for Switch)
if(NOT NINTENDO_SWITCH)
    # Create list of library sources (exclude main.cpp)
    set(LIB_SOURCES ${SOURCES})
    list(REMOVE_ITEM LIB_SOURCES src/main.cpp)
    
    # Use pkg-config to find SDL libraries for tests
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(TEST_SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(TEST_SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_check_modules(TEST_SDL2_NET REQUIRED SDL2_net)
    
    # Entity Pooling Test
    add_executable(test_pooling test_pooling.cpp ${LIB_SOURCES})
    target_include_directories(test_pooling PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        ${TEST_SDL2_IMAGE_INCLUDE_DIRS}
        ${TEST_SDL2_MIXER_INCLUDE_DIRS}
        ${TEST_SDL2_NET_INCLUDE_DIRS}
    )
    target_link_libraries(test_pooling PRIVATE 
        ${SDL2_LIBRARIES}
        ${TEST_SDL2_IMAGE_LIBRARIES}
        ${TEST_SDL2_MIXER_LIBRARIES}
        ${TEST_SDL2_NET_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
    )

    # Asset Streaming Test
    add_executable(test_streaming test_streaming.cpp ${LIB_SOURCES})
    target_include_directories(test_streaming PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
        ${TEST_SDL2_IMAGE_INCLUDE_DIRS}
        ${TEST_SDL2_MIXER_INCLUDE_DIRS}
        ${TEST_SDL2_NET_INCLUDE_DIRS}
    )
    target_link_libraries(test_streaming PRIVATE 
        ${SDL2_LIBRARIES}
        ${TEST_SDL2_IMAGE_LIBRARIES}
        ${TEST_SDL2_MIXER_LIBRARIES}
        ${TEST_SDL2_NET_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT}
    )
endif()
