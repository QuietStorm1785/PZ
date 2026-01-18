cmake_minimum_required(VERSION 3.10)
project(ProjectZomboidCpp VERSION 0.3.0 LANGUAGES CXX)

# Lua build needs C; enable C language and set standard
enable_language(C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Build options - allow selective compilation
option(BUILD_CORE_ONLY "Build only core subsystems" OFF)
option(BUILD_NETWORKING "Include networking subsystems" ON)
option(BUILD_AUDIO "Include audio subsystems" ON)
option(BUILD_UI "Include UI subsystems" ON)
option(BUILD_VEHICLES "Include vehicle subsystems" ON)
option(BUILD_RADIO "Include radio subsystems" OFF)
option(BUILD_MODDING "Include modding subsystems" OFF)
option(BUILD_FMOD "Enable FMOD integration on desktop (FMOD SDK required)" OFF)
option(BUILD_LUA "Build bundled Lua (switch cross-compatible)" ON)

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
    # Disable warnings for stub implementations
    add_compile_options(/wd4100) # unreferenced formal parameter
    add_compile_options(/wd4101) # unreferenced local variable
else()
    add_compile_options(-Wall -Wextra -pedantic)
    # Disable warnings for stub implementations
    add_compile_options(-Wno-unused-parameter)
    add_compile_options(-Wno-unused-variable)
    add_compile_options(-Wno-unused-function)
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
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    pkg_check_modules(SDL2_NET REQUIRED SDL2_net)
    include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_NET_INCLUDE_DIRS})
else()
    find_package(SDL2 REQUIRED)
    find_package(PkgConfig)
    if(PkgConfig_FOUND)
        pkg_check_modules(SDL2_IMAGE SDL2_image)
        pkg_check_modules(SDL2_MIXER SDL2_mixer)
        pkg_check_modules(SDL2_NET SDL2_net)
    endif()
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

# Optional FMOD detection (desktop only). For Switch we keep using SDL2 audio.
set(FMOD_FOUND FALSE)
if(BUILD_FMOD AND NOT NINTENDO_SWITCH)
    # Default FMOD root: env FMOD_SDK, else the extracted SDK in ../third_party
    if(NOT DEFINED FMOD_ROOT OR FMOD_ROOT STREQUAL "")
        set(FMOD_ROOT $ENV{FMOD_SDK})
    endif()
    if(NOT DEFINED FMOD_ROOT OR FMOD_ROOT STREQUAL "")
        set(FMOD_ROOT ${CMAKE_SOURCE_DIR}/../third_party/fmodstudioapi20312linux)
    endif()

    # Include dirs: core + studio headers
    find_path(FMOD_CORE_INCLUDE_DIR fmod.hpp
        HINTS ${FMOD_ROOT}/api/core/inc
    )
    find_path(FMOD_STUDIO_INCLUDE_DIR fmod_studio.hpp
        HINTS ${FMOD_ROOT}/api/studio/inc
    )

    # Libraries: prefer x86_64 host
    set(FMOD_LIB_HINTS
        ${FMOD_ROOT}/api/core/lib/x86_64
        ${FMOD_ROOT}/api/studio/lib/x86_64
        ${FMOD_ROOT}/api/core/lib
        ${FMOD_ROOT}/api/studio/lib
    )
    find_library(FMOD_CORE_LIB NAMES fmod fmodL HINTS ${FMOD_LIB_HINTS})
    find_library(FMOD_STUDIO_LIB NAMES fmodstudio fmodstudioL HINTS ${FMOD_LIB_HINTS})

    if(FMOD_CORE_INCLUDE_DIR AND FMOD_STUDIO_INCLUDE_DIR AND FMOD_CORE_LIB AND FMOD_STUDIO_LIB)
        set(FMOD_FOUND TRUE)
        set(FMOD_INCLUDE_DIRS ${FMOD_CORE_INCLUDE_DIR} ${FMOD_STUDIO_INCLUDE_DIR})
        set(FMOD_LIBRARIES ${FMOD_CORE_LIB} ${FMOD_STUDIO_LIB})
        message(STATUS "FMOD SDK found: ${FMOD_ROOT}")
        message(STATUS "FMOD includes: ${FMOD_INCLUDE_DIRS}")
        message(STATUS "FMOD libs: ${FMOD_LIBRARIES}")
    else()
        message(WARNING "FMOD SDK not found or incomplete (set FMOD_SDK env). Disabling FMOD integration.")
        set(BUILD_FMOD OFF)
    endif()
endif()

# Lua (bundled source) - built as static lib, usable for Switch cross
set(LUA_FOUND FALSE)
if(BUILD_LUA)
    set(LUA_ROOT ${CMAKE_SOURCE_DIR}/../third_party/lua/lua-5.4.7)
    if(EXISTS ${LUA_ROOT}/src/lapi.c)
        set(LUA_FOUND TRUE)
        set(LUA_SOURCES
            ${LUA_ROOT}/src/lapi.c
            ${LUA_ROOT}/src/lauxlib.c
            ${LUA_ROOT}/src/lbaselib.c
            ${LUA_ROOT}/src/lcode.c
            ${LUA_ROOT}/src/lcorolib.c
            ${LUA_ROOT}/src/lctype.c
            ${LUA_ROOT}/src/ldebug.c
            ${LUA_ROOT}/src/ldo.c
            ${LUA_ROOT}/src/ldump.c
            ${LUA_ROOT}/src/lfunc.c
            ${LUA_ROOT}/src/lgc.c
            ${LUA_ROOT}/src/linit.c
            ${LUA_ROOT}/src/liolib.c
            ${LUA_ROOT}/src/llex.c
            ${LUA_ROOT}/src/lmathlib.c
            ${LUA_ROOT}/src/lmem.c
            ${LUA_ROOT}/src/loadlib.c
            ${LUA_ROOT}/src/lobject.c
            ${LUA_ROOT}/src/lopcodes.c
            ${LUA_ROOT}/src/loslib.c
            ${LUA_ROOT}/src/lparser.c
            ${LUA_ROOT}/src/lstate.c
            ${LUA_ROOT}/src/lstring.c
            ${LUA_ROOT}/src/lstrlib.c
            ${LUA_ROOT}/src/ltable.c
            ${LUA_ROOT}/src/ltablib.c
            ${LUA_ROOT}/src/ltm.c
            ${LUA_ROOT}/src/lundump.c
            ${LUA_ROOT}/src/lutf8lib.c
            ${LUA_ROOT}/src/lvm.c
            ${LUA_ROOT}/src/lzio.c
        )
        add_library(lua STATIC ${LUA_SOURCES})
        target_include_directories(lua PUBLIC ${LUA_ROOT}/src)
        # Lua on Switch: use ISO C (not POSIX _setjmp/_longjmp)
        if(NINTENDO_SWITCH)
            # Switch newlib doesn't have _setjmp/_longjmp; use ISO C setjmp/longjmp
            # No LUA_USE_POSIX definition needed
        else()
            # Desktop/other platforms: use POSIX subset
            target_compile_definitions(lua PUBLIC LUA_USE_POSIX)
        endif()
    else()
        message(WARNING "Lua sources not found at ${LUA_ROOT}. Disable BUILD_LUA or set LUA_ROOT.")
        set(BUILD_LUA OFF)
    endif()
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# ============================================================================
# SOURCE FILE COLLECTION
# ============================================================================

# Custom PZ-Switch implementations (always included)
set(CUSTOM_SOURCES
    src/main.cpp
    src/Core.cpp
    src/GameWindow.cpp
    src/Config.cpp
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
    src/Inventory.cpp
    src/Building.cpp
    src/AIBehaviors.cpp
    src/SaveLoad.cpp
    src/Animation.cpp
    src/AnimationController.cpp
    src/TextureAtlas.cpp
    src/SpriteLoader.cpp
    src/Audio.cpp
    src/UI.cpp
    src/Tasks.cpp
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
    src/MainMenuScreen.cpp
    src/OptionsScreen.cpp
    src/ControllerRebindUI.cpp
    src/RadialMenu.cpp
)

# Core zombie subsystems (conditional)
if(NOT BUILD_CORE_ONLY)
    file(GLOB_RECURSE ZOMBIE_CORE_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/core/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/zombie/characters/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/zombie/iso/*.cpp"
    )
    list(LENGTH ZOMBIE_CORE_SOURCES CORE_COUNT)
    message(STATUS "Found ${CORE_COUNT} core zombie source files")
else()
    set(ZOMBIE_CORE_SOURCES "")
endif()

# Networking subsystems
if(BUILD_NETWORKING)
    file(GLOB_RECURSE ZOMBIE_NETWORK_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/network/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/zombie/spnetwork/*.cpp"
    )
    set(CUSTOM_SOURCES ${CUSTOM_SOURCES} src/NetworkManager.cpp src/NetworkingEnhanced.cpp src/Pathfinding.cpp)
else()
    set(ZOMBIE_NETWORK_SOURCES "")
endif()

# Audio subsystems
if(BUILD_AUDIO)
    file(GLOB_RECURSE ZOMBIE_AUDIO_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/audio/*.cpp"
    )
else()
    set(ZOMBIE_AUDIO_SOURCES "")
endif()

# UI subsystems
if(BUILD_UI)
    file(GLOB_RECURSE ZOMBIE_UI_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/ui/*.cpp"
    )
else()
    set(ZOMBIE_UI_SOURCES "")
endif()

# Vehicle subsystems
if(BUILD_VEHICLES)
    file(GLOB_RECURSE ZOMBIE_VEHICLE_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/vehicles/*.cpp"
    )
else()
    set(ZOMBIE_VEHICLE_SOURCES "")
endif()

# Radio subsystems (optional - large)
if(BUILD_RADIO)
    file(GLOB_RECURSE ZOMBIE_RADIO_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/radio/*.cpp"
    )
else()
    set(ZOMBIE_RADIO_SOURCES "")
endif()

# Modding subsystems (optional)
if(BUILD_MODDING)
    file(GLOB_RECURSE ZOMBIE_MODDING_SOURCES
        "${CMAKE_SOURCE_DIR}/src/zombie/modding/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/zombie/scripting/*.cpp"
    )
else()
    set(ZOMBIE_MODDING_SOURCES "")
endif()

# Additional zombie subsystems (selective)
file(GLOB_RECURSE ZOMBIE_ADDITIONAL_SOURCES
    "${CMAKE_SOURCE_DIR}/src/zombie/inventory/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/ai/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/input/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/util/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/world/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/worldMap/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/debug/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/config/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/gameStates/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/globalObjects/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/popman/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/chat/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/commands/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/zombie/sandbox/*.cpp"
)

# Third-party subsystems (converted from Java libs)
file(GLOB_RECURSE THIRDPARTY_SOURCES
    "${CMAKE_SOURCE_DIR}/src/org/lwjgl/opengl/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/astar/*.cpp"
)

# FMOD sources (optional; only if BUILD_FMOD=ON and SDK present)
set(FMOD_SHIM_SOURCES ${CMAKE_SOURCE_DIR}/src/fmod/javafmod.cpp)
if(BUILD_FMOD AND FMOD_FOUND)
    file(GLOB_RECURSE FMOD_SOURCES "${CMAKE_SOURCE_DIR}/src/fmod/*.cpp")
endif()

# Combine all sources
set(ALL_SOURCES
    ${CUSTOM_SOURCES}
)

if(NOT BUILD_CORE_ONLY)
    list(APPEND ALL_SOURCES ${ZOMBIE_CORE_SOURCES})
endif()

if(BUILD_NETWORKING)
    list(APPEND ALL_SOURCES ${ZOMBIE_NETWORK_SOURCES})
endif()

if(BUILD_AUDIO)
    list(APPEND ALL_SOURCES ${ZOMBIE_AUDIO_SOURCES})
endif()

if(BUILD_UI)
    list(APPEND ALL_SOURCES ${ZOMBIE_UI_SOURCES})
endif()

if(BUILD_VEHICLES)
    list(APPEND ALL_SOURCES ${ZOMBIE_VEHICLE_SOURCES})
endif()

if(BUILD_RADIO)
    list(APPEND ALL_SOURCES ${ZOMBIE_RADIO_SOURCES})
endif()

if(BUILD_MODDING)
    list(APPEND ALL_SOURCES ${ZOMBIE_MODDING_SOURCES})
endif()

list(APPEND ALL_SOURCES ${ZOMBIE_ADDITIONAL_SOURCES})
list(APPEND ALL_SOURCES ${THIRDPARTY_SOURCES})
list(APPEND ALL_SOURCES ${FMOD_SHIM_SOURCES})
if(BUILD_FMOD AND FMOD_FOUND)
    list(APPEND ALL_SOURCES ${FMOD_SOURCES})
endif()

if(BUILD_LUA AND LUA_FOUND)
    # Lua built as separate static lib; no direct sources added here
endif()

# Remove duplicates and non-existent files
list(REMOVE_DUPLICATES ALL_SOURCES)

# Filter out files that don't exist or cause issues
set(FILTERED_SOURCES "")
foreach(SOURCE_FILE ${ALL_SOURCES})
    # Check if path is absolute or relative
    if(IS_ABSOLUTE ${SOURCE_FILE})
        if(EXISTS "${SOURCE_FILE}")
            list(APPEND FILTERED_SOURCES ${SOURCE_FILE})
        endif()
    else()
        if(EXISTS "${CMAKE_SOURCE_DIR}/${SOURCE_FILE}")
            list(APPEND FILTERED_SOURCES ${SOURCE_FILE})
        endif()
    endif()
endforeach()

# Print build configuration
list(LENGTH FILTERED_SOURCES SOURCE_COUNT)
message(STATUS "=== Project Zomboid C++ Build Configuration ===")
message(STATUS "Total source files: ${SOURCE_COUNT}")
message(STATUS "Build core only: ${BUILD_CORE_ONLY}")
message(STATUS "Build networking: ${BUILD_NETWORKING}")
message(STATUS "Build audio: ${BUILD_AUDIO}")
message(STATUS "Build UI: ${BUILD_UI}")
message(STATUS "Build vehicles: ${BUILD_VEHICLES}")
message(STATUS "Build radio: ${BUILD_RADIO}")
message(STATUS "Build modding: ${BUILD_MODDING}")
message(STATUS "Build FMOD (desktop only): ${BUILD_FMOD} (found: ${FMOD_FOUND})")
message(STATUS "Build Lua: ${BUILD_LUA} (found: ${LUA_FOUND})")

# Create executable
add_executable(${PROJECT_NAME} ${FILTERED_SOURCES})

if(BUILD_FMOD AND FMOD_FOUND)
    target_compile_definitions(${PROJECT_NAME} PUBLIC BUILD_FMOD_ENABLED)
endif()

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
    endif()
    
    if(SDL2_mixer_FOUND)
        list(APPEND LINK_LIBS SDL2_mixer::SDL2_mixer)
    elseif(SDL2_MIXER_FOUND)
        list(APPEND LINK_LIBS ${SDL2_MIXER_LIBRARIES})
        include_directories(${SDL2_MIXER_INCLUDE_DIRS})
    endif()
    
    if(SDL2_net_FOUND)
        list(APPEND LINK_LIBS SDL2_net::SDL2_net)
    elseif(SDL2_NET_FOUND)
        list(APPEND LINK_LIBS ${SDL2_NET_LIBRARIES})
        include_directories(${SDL2_NET_INCLUDE_DIRS})
    endif()
    if(BUILD_FMOD AND FMOD_FOUND)
        list(APPEND LINK_LIBS ${FMOD_LIBRARIES})
        include_directories(${FMOD_INCLUDE_DIRS})
    endif()
    
    target_link_libraries(${PROJECT_NAME} ${LINK_LIBS})
endif()

# Link Lua if available
if(BUILD_LUA AND LUA_FOUND)
    target_link_libraries(${PROJECT_NAME} lua)
endif()

# For Nintendo Switch (with devkitPro)
if(NINTENDO_SWITCH)
    message(STATUS "Building for Nintendo Switch")
    message(STATUS "DEVKITPRO: $ENV{DEVKITPRO}")
    
    # Switch executables use .elf extension
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".elf")
    
    # Create NRO (Nintendo Switch executable)
    if(EXISTS "$ENV{DEVKITPRO}/tools/bin/nacptool")
        # Define Switch homebrew directory structure
        set(SWITCH_APP_DIR "${CMAKE_CURRENT_BINARY_DIR}/switch/PZSwitch")
        
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            # Create .nacp metadata file
            COMMAND $ENV{DEVKITPRO}/tools/bin/nacptool 
                --create "Project Zomboid" "C++ Port" "${PROJECT_VERSION}" 
                ${PROJECT_NAME}.nacp
            # Convert ELF to NRO
            COMMAND $ENV{DEVKITPRO}/tools/bin/elf2nro 
                ${PROJECT_NAME}.elf ${PROJECT_NAME}.nro 
                --nacp=${PROJECT_NAME}.nacp
            # Create Switch homebrew directory structure
            COMMAND ${CMAKE_COMMAND} -E make_directory ${SWITCH_APP_DIR}
            # Copy .nro to Switch directory
            COMMAND ${CMAKE_COMMAND} -E copy 
                ${PROJECT_NAME}.nro 
                ${SWITCH_APP_DIR}/${PROJECT_NAME}.nro
            # Copy metadata file
            COMMAND ${CMAKE_COMMAND} -E copy 
                ${PROJECT_NAME}.nacp 
                ${SWITCH_APP_DIR}/${PROJECT_NAME}.nacp
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Creating .nro file and Switch directory structure at ${SWITCH_APP_DIR}..."
            VERBATIM
        )
        
        # Optional: Copy icon if it exists
        if(EXISTS "${CMAKE_SOURCE_DIR}/icon.jpg")
            add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy 
                    ${CMAKE_SOURCE_DIR}/icon.jpg 
                    ${SWITCH_APP_DIR}/icon.jpg
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Copying icon to Switch directory..."
                VERBATIM
            )
        endif()
        
        message(STATUS "Will create .nro file and Switch directory structure after build")
        message(STATUS "Switch app location: ${SWITCH_APP_DIR}")
    else()
        message(WARNING "nacptool/elf2nro not found - .nro creation will be skipped")
    endif()
endif()

# Copy media assets to build directory
if(NOT NINTENDO_SWITCH)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
            ${CMAKE_SOURCE_DIR}/../media
            ${CMAKE_CURRENT_BINARY_DIR}/media
        COMMENT "Creating symlink to media directory..."
    )
else()
    message(STATUS "Switch build - assets must be bundled separately")
endif()

# Installation
if(NINTENDO_SWITCH)
    # Install to Switch SD card structure
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.nro 
            DESTINATION switch/PZSwitch)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.nacp 
            DESTINATION switch/PZSwitch)
    if(EXISTS "${CMAKE_SOURCE_DIR}/icon.jpg")
        install(FILES ${CMAKE_SOURCE_DIR}/icon.jpg 
                DESTINATION switch/PZSwitch)
    endif()
    # Optional: Create README for Switch
    file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/README.txt 
        "Project Zomboid - Nintendo Switch Port\n\n"
        "Version: ${PROJECT_VERSION}\n"
        "Build Date: ${CMAKE_BUILD_TYPE}\n\n"
        "To run: Launch from Homebrew Menu\n\n"
        "Notes:\n"
        "- This is a work-in-progress port\n"
        "- Most game logic is stubbed\n"
        "- Assets not included in this build\n"
    )
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/README.txt 
            DESTINATION switch/PZSwitch)
else()
    install(TARGETS ${PROJECT_NAME} DESTINATION bin)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/../media DESTINATION share/${PROJECT_NAME})
endif()
