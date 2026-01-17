#!/bin/bash
# Build script for Nintendo Switch (devkitPro)

set -e

echo "=== Project Zomboid - Nintendo Switch Build ==="

# Setup devkitPro environment
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export DEVKITA64=$DEVKITPRO/devkitA64

# Check for devkitPro
if [ ! -d "$DEVKITPRO" ]; then
    echo "Error: devkitPro not found at $DEVKITPRO"
    echo "Install from: https://devkitpro.org/wiki/Getting_Started"
    exit 1
fi

# Check for CMake toolchain
TOOLCHAIN_FILE="$DEVKITPRO/cmake/Switch.cmake"
if [ ! -f "$TOOLCHAIN_FILE" ]; then
    echo "Error: Switch CMake toolchain not found at $TOOLCHAIN_FILE"
    exit 1
fi

# Create build directory
BUILD_DIR="build-switch"
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

echo ""
echo "Configuring for Nintendo Switch..."
cmake .. \
    -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" \
    -DCMAKE_BUILD_TYPE=Release \
    -DNINTENDO_SWITCH=ON

echo ""
echo "Building..."
make -j$(nproc 2>/dev/null || echo 4)

echo ""
echo "=== Build Complete ==="

# Check for output files
if [ -f "ProjectZomboidCpp.nro" ]; then
    echo "✓ Switch executable created: $BUILD_DIR/ProjectZomboidCpp.nro"
    echo ""
    echo "To install on Switch:"
    echo "  1. Copy ProjectZomboidCpp.nro to your SD card: /switch/"
    echo "  2. Launch via Homebrew Launcher"
    ls -lh ProjectZomboidCpp.nro
elif [ -f "ProjectZomboidCpp" ]; then
    echo "✓ Executable built: $BUILD_DIR/ProjectZomboidCpp"
    echo "⚠ Note: .nro creation requires nacptool and elf2nro"
    echo ""
    echo "To create .nro manually:"
    echo "  nacptool --create \"ProjectZomboid\" \"Port\" \"0.2.0\" ProjectZomboidCpp.nacp"
    echo "  elf2nro ProjectZomboidCpp ProjectZomboidCpp.nro --nacp=ProjectZomboidCpp.nacp"
else
    echo "⚠ Build completed but output file not found"
    echo "Check build output above for errors"
fi

echo ""
echo "Files in build directory:"
ls -lh ProjectZomboidCpp* 2>/dev/null || echo "No executables found"
