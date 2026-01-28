#!/bin/bash
# Quick build script for Linux/macOS

set -e

echo "=== Project Zomboid C++ Build Script ==="


# Check for SDL2
if ! pkg-config --exists sdl2; then
    echo "Error: SDL2 not found. Please install SDL2 development libraries."
    echo "  Ubuntu/Debian: sudo apt-get install libsdl2-dev"
    echo "  macOS: brew install sdl2"
    exit 1
fi

# Check for OpenAL
if ! pkg-config --exists openal; then
    echo "Error: OpenAL not found. Please install OpenAL development libraries."
    echo "  Ubuntu/Debian: sudo apt-get install libopenal-dev"
    echo "  macOS: brew install openal-soft"
    exit 1
fi

# Create build directory
mkdir -p build
cd build

# Configure
echo "Configuring with CMake..."
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build
echo "Building..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "=== Build Complete ==="
echo "Executable: build/ProjectZomboidCpp"
echo ""
echo "Run with: ./build/ProjectZomboidCpp"
echo "  Options:"
echo "    -width 1920 -height 1080"
echo "    -fullscreen"
echo "    -debug"
