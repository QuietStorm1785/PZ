
# Project Zomboid For the Nintendo Switch

## Third-Party Libraries (Upstream Sources)

This project uses official upstream sources for several core libraries. These are not included in the repository. You must download them manually into the `bin_res/` directory before building:

| Library         | Version   | Download URL                                                      | Extracted Folder                |
|-----------------|-----------|-------------------------------------------------------------------|---------------------------------|
| zlib            | develop   | https://github.com/madler/zlib/archive/refs/heads/develop.zip     | bin_res/zlib-develop/           |
| nlohmann/json   | develop   | https://github.com/nlohmann/json/archive/refs/heads/develop.zip   | bin_res/json-develop/           |
| sqlite          | master    | https://github.com/sqlite/sqlite/archive/refs/heads/master.zip    | bin_res/sqlite-master/          |
| lua             | 5.4.7     | https://www.lua.org/ftp/lua-5.4.7.tar.gz                          | bin_res/lua-5.4.7/              |

### Download and Extract Example (Linux/macOS)

```
cd bin_res
# zlib
wget https://github.com/madler/zlib/archive/refs/heads/develop.zip -O zlib.zip && unzip zlib.zip && rm zlib.zip
# nlohmann/json
wget https://github.com/nlohmann/json/archive/refs/heads/develop.zip -O nlohmann_json.zip && unzip nlohmann_json.zip && rm nlohmann_json.zip
# sqlite
wget https://github.com/sqlite/sqlite/archive/refs/heads/master.zip -O sqlite.zip && unzip sqlite.zip && rm sqlite.zip
# lua
wget https://www.lua.org/ftp/lua-5.4.7.tar.gz -O lua-5.4.7.tar.gz && tar -xzf lua-5.4.7.tar.gz && rm lua-5.4.7.tar.gz
```

After extraction, the build system will automatically use these folders. You do not need to modify CMakeLists.txt unless you change the folder names or locations.


**Remove any old copies of these libraries from ProjectZomboidSwitch/src/ to avoid conflicts.**

## Audio Backend Migration

**FMOD has been fully removed. Project Zomboid now uses OpenAL for all audio.**

All code, build scripts, and dependencies have been updated to require OpenAL. You must have OpenAL development libraries installed to build and run the project.

Converted Java-to-C++ codebase for Project Zomboid.

## Recent Changes

- Refactored entire Lua library into modern C++ (see ProjectZomboidSwitch/src/zombie/LuaCpp/)
- Integrated OpenGL support and reorganized graphics code (see ProjectZomboidSwitch/src/GLUS/)
- Cleaned up build artifacts and updated .gitignore to exclude build and DoNotUse folders
- Updated directory structure for clarity and maintainability

## Updated Directory Structure

```
ProjectZomboidSwitch/
├── abseil/                # Abseil C++ library
├── build/                 # Build output (now gitignored)
├── build-switch/          # Switch build output (now gitignored)
├── cmake/                 # CMake helper scripts
├── include/               # C++ header files
│   ├── GraphicsWrapper/   # OpenGL/graphics headers
│   ├── zombie/            # Main game headers
│   └── ...                # Other modules
├── src/                   # C++ source files
│   ├── GLUS/              # OpenGL/GLUS sources
│   ├── LuaCpp/            # Refactored Lua library in C++
│   └── ...                # Other modules
├── DoNotUse/              # Deprecated/legacy code (now gitignored)
├── CMakeLists.txt         # Main build config
└── ...
```

## Building


### Requirements

- CMake 3.10 or later
- C++20 compatible compiler
- Qt 5 (Core, Gui) development libraries (for QImage support)
- OpenAL development libraries (for audio)
- For Switch: devkitPro with devkitA64 toolchain



#### Installing Qt and OpenAL (Linux/Ubuntu example)

```
sudo apt update
sudo apt install qtbase5-dev qt5-qmake qtbase5-dev-tools libopenal-dev
```

#### Installing OpenAL (MSYS2/Windows example)

```
pacman -S mingw-w64-x86_64-openal
```

#### Installing OpenAL (macOS example)

```
brew install openal-soft
```

#### CMake Build Example (Desktop)

```
cd ProjectZomboidSwitch
mkdir build && cd build
cmake ..
make -j$(nproc)
```

#### Notes
- Ensure Qt5 is installed and CMake can find it (see error messages for missing Qt5::Core or Qt5::Gui).
- For other platforms, install Qt5 using your system's package manager or from https://www.qt.io/download.
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
- **Switch:** `build-switch/ProjectZomboidSwitch.nro`

## Instruction Manual: Running on Nintendo Switch

### Prerequisites
- You must own a legal copy of Project Zomboid on Steam.
- You will need the `/media` directory from your Steam install of Project Zomboid.

### How to Retrieve Your `/media` Files
1. On your PC, open Steam and locate Project Zomboid in your library.
2. Right-click Project Zomboid > Manage > Browse local files.
3. Find the `media` folder (usually at `.../steamapps/common/Project Zomboid/media`).
4. Copy the entire `media` folder to a safe location on your PC.

### Building and Preparing the Project
1. Build the project for Nintendo Switch using the provided scripts:
	```bash
	cd ProjectZomboidSwitch
	./build-switch.sh
	# or use build-switch.ps1 on Windows
	```
2. The output will be `ProjectZomboidSwitch.nro` in the `build-switch` directory.

### Copying to Your Nintendo Switch
1. Insert your Switch SD card into your PC.
2. Create a folder on the SD card: `/switch/ProjectZomboidSwitch/`
3. Copy the following to `/switch/ProjectZomboidSwitch/`:
	- `ProjectZomboidSwitch.nro` (the built executable)
	- The entire `media` folder from your Steam install
4. Your SD card should now have:
	```
	/switch/ProjectZomboidSwitch/
	  ├── ProjectZomboidSwitch.nro
	  └── media/
			└── [all game assets]
	```

### Legal Notice
- You must own your own copy of Project Zomboid to play this port.
- Do not distribute the `media` folder or any proprietary assets.
- This project is for personal use and experimentation only.

### Launching the Game
1. Insert the SD card back into your Nintendo Switch.
2. Launch the Homebrew Menu.
3. Select `ProjectZomboidSwitch` to start the game.

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
# SD:/switch/ProjectZomboidSwitch/ProjectZomboidSwitch.nro
```



## Notes
- This is a converted Java codebase - some patterns may not be idiomatic C++
- **Audio system now uses OpenAL (cross-platform, FMOD fully removed)**
- Switch builds use SDL2 audio subsystem
- OpenGL support is provided via GLUS and custom wrappers
- Lua scripting is now fully integrated in C++ via the LuaCpp module
