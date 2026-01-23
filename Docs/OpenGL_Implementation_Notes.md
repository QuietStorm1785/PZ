# OpenGL Implementation Notes

## Overview
The OpenGL implementation in Project Zomboid Switch was refactored and expanded to support modern graphics features and Nintendo Switch compatibility.

## Key Changes
- **GLUS integration:** The project now uses GLUS (OpenGL Utility Library) for cross-platform OpenGL support, located in `ProjectZomboidSwitch/src/GLUS/`.
- **GraphicsWrapper module:** All OpenGL headers and wrappers are organized under `ProjectZomboidSwitch/include/GraphicsWrapper/`.
- **Modern OpenGL:** Refactored rendering code to use modern OpenGL practices (shaders, buffer objects, etc.).
- **Platform abstraction:** Graphics code is abstracted to support both desktop and Switch builds.
- **Error handling:** Improved error checking and debugging for OpenGL calls.
- **Performance:** Optimized rendering paths for Switch hardware.

## File Structure
- `GLUS/`: Contains GLUS sources and OpenGL helpers.
- `GraphicsWrapper/`: Contains C++ headers for OpenGL wrappers and graphics utilities.
- `src/zombie/core/opengl/`: Main game rendering logic using OpenGL.

## Migration Notes
- Legacy OpenGL code was updated to use shaders and buffer objects.
- All platform-specific code is isolated for easier maintenance.

## Benefits
- Improved graphics quality and performance
- Easier cross-platform development
- Better debugging and error reporting
