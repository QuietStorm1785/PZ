# Project Zomboid Convert2Cpp

Converted Java-to-C++ codebase for Project Zomboid.

## Directory Structure

```
Convert2Cpp/
├── include/          # Header files (.h)
│   ├── astar/       # A* pathfinding
│   ├── com/         # Common utilities
│   ├── fmod/        # FMOD audio integration
│   ├── N3D/         # 3D graphics (if applicable)
│   └── zombie/      # Main game code
├── src/             # Implementation files (.cpp)
│   └── [mirrors include structure]
└── CMakeLists.txt   # Build configuration
```

## Building

### Requirements

- CMake 3.10 or later
- C++17 compatible compiler
- For Switch: devkitPro with devkitA64 toolchain
- **Boost** (located at `../boost`)
- **Abseil** (located at `../abseil`)
- Optional: SDL2 (for audio/graphics features)

### Windows Build

```powershell
# Release build (default)
.\build-windows.ps1

# Debug build
.\build-windows.ps1 -Config Debug

# Clean build
.\build-windows.ps1 -Clean
```

### Nintendo Switch Build

```powershell
# Using PowerShell
.\build-switch.ps1

# Clean build
.\build-switch.ps1 -Clean
```

Or from MSYS2:
```bash
./build-switch.sh
```

## Output

- **Windows:** `build-windows/pz_convert2cpp.exe`
- **Switch:** `build-switch/ProjectZomboid_Convert2Cpp.nro`

## Statistics

- **Source Files:** 435
- **Header Files:** 435
- **Total Lines:** ~100,000+ (estimated)

## Usage

Run the executable:
```powershell
# Windows
.\build-windows\pz_convert2cpp.exe

# Switch - copy to SD card
# SD:/switch/ProjectZomboid_Convert2Cpp/ProjectZomboid_Convert2Cpp.nro
```

## Notes

- This is a converted Java codebase - some patterns may not be idiomatic C++
- Audio systems require SDL2_mixer or FMOD depending on platform
- Switch builds use SDL2 audio subsystem
