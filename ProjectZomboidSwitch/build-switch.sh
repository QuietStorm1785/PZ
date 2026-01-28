

#!/bin/bash
# Cross-platform build script for ProjectZomboidSwitch
set -e

TARGET=${1:-switch}
BUILDTYPE=${2:-Release}

# Detect MSYS2 vs Linux
if [[ -n "$MSYSTEM" ]]; then
    ENVIRONMENT="MSYS2"
else
    ENVIRONMENT="Linux"
fi

echo "Detected environment: $ENVIRONMENT"

if [[ "$TARGET" == "switch" ]]; then
    echo "=== Project Zomboid - Nintendo Switch Build ==="
    if [[ "$ENVIRONMENT" == "MSYS2" ]]; then
        export DEVKITPRO="/c/devkitPro"
    else
        export DEVKITPRO="/opt/devkitpro"
    fi
    export DEVKITARM=$DEVKITPRO/devkitARM
    export DEVKITA64=$DEVKITPRO/devkitA64

    # Check for devkitPro
    if [ ! -d "$DEVKITPRO" ]; then
        echo "Error: devkitPro not found at $DEVKITPRO"
        echo "Install from: https://devkitpro.org/wiki/Getting_Started"
        exit 1
    fi

    TOOLCHAIN_FILE="$DEVKITPRO/cmake/Switch.cmake"
    if [ ! -f "$TOOLCHAIN_FILE" ]; then
        echo "Error: Switch CMake toolchain not found at $TOOLCHAIN_FILE"
        exit 1
    fi

    BUILD_DIR="build-switch"
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    echo "Configuring for Nintendo Switch..."
    cmake .. \
        -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" \
        -DCMAKE_BUILD_TYPE=$BUILDTYPE \
        -DNINTENDO_SWITCH=ON \
        -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt5

    echo "Building..."
    make -j$(nproc 2>/dev/null || echo 4)

    echo "=== Build Complete ==="
    if [ -f "ProjectZomboidSwitch.nro" ]; then
        echo "✓ Switch executable created: $BUILD_DIR/ProjectZomboidSwitch.nro"
        echo "To install on Switch:"
        echo "  1. Copy ProjectZomboidSwitch.nro to your SD card: /switch/"
        echo "  2. Launch via Homebrew Launcher"
        ls -lh ProjectZomboidSwitch.nro
    elif [ -f "ProjectZomboidSwitch" ]; then
        echo "✓ Executable built: $BUILD_DIR/ProjectZomboidSwitch"
        echo "⚠ Note: .nro creation requires nacptool and elf2nro"
        echo "To create .nro manually:"
        echo "  nacptool --create \"ProjectZomboidSwitch\" \"Port\" \"0.2.0\" ProjectZomboidSwitch.nacp"
        echo "  elf2nro ProjectZomboidSwitch ProjectZomboidSwitch.nro --nacp=ProjectZomboidSwitch.nacp"
    else
        echo "⚠ Build completed but output file not found"
        echo "Check build output above for errors"
    fi
    echo "Files in build directory:"
    ls -lh ProjectZomboidSwitch* 2>/dev/null || echo "No executables found"

elif [[ "$TARGET" == "windows" ]]; then
    echo "=== Project Zomboid - Windows Build ==="
    BUILD_DIR="build-windows"
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    echo "Configuring for Windows..."
        cmake ../ProjectZomboidSwitch -DCMAKE_BUILD_TYPE=$BUILDTYPE
    echo "Building..."
    cmake --build . --config $BUILDTYPE
    echo "=== Build Complete ==="
    echo "Files in build directory:"
    ls -lh * || echo "No executables found"

elif [[ "$TARGET" == "linux" ]]; then
    echo "=== Project Zomboid - Linux Build ==="
    BUILD_DIR="build-linux"
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"
    echo "Configuring for Linux..."
    # Set CMAKE_PREFIX_PATH for Qt5 so CMake can find Qt5Config.cmake
        cmake ../ProjectZomboidSwitch -DCMAKE_BUILD_TYPE=$BUILDTYPE -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt5
    echo "Building..."
    cmake --build . --config $BUILDTYPE
    echo "=== Build Complete ==="
    echo "Files in build directory:"
    ls -lh * || echo "No executables found"

else
    echo "Unknown target: $TARGET"
    echo "Usage: $0 [switch|windows|linux] [Release|Debug]"
    exit 1
fi
