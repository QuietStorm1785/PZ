# FMOD Implementation Notes

## Overview
FMOD audio integration in Project Zomboid Switch was refactored to support C++ and Nintendo Switch compatibility, replacing the original Java-based audio system.

## Key Changes
- **C++ FMOD integration:** All FMOD usage is now handled in C++ under `ProjectZomboidSwitch/src/fmod/`.
- **Modular audio system:** FMOD components (Core, Studio, FSBANK, Haptics, Resonance Audio) are organized for easier management and extension.
- **Platform abstraction:** Audio code is abstracted to support both desktop and Switch builds, with platform-specific initialization and resource management.
- **Improved error handling:** Enhanced error checking and logging for FMOD API calls.
- **Performance:** Optimized audio streaming and mixing for Switch hardware.
- **Event-driven audio:** Game events and Lua scripts can trigger FMOD audio playback via the new C++ event system.

## File Structure
- `src/fmod/core/`: FMOD Core API integration
- `src/fmod/studio/`: FMOD Studio API integration
- `src/fmod/fsbank/`: FMOD FSBANK support
- `src/fmod/plugins/`: Haptics and Resonance Audio plugins
- `src/zombie/audio/`: Game audio logic and FMOD event handling

## Migration Notes
- All previous Java-based FMOD code was ported to C++ and updated for FMOD API changes.
- Platform-specific code is isolated for easier maintenance and debugging.
- See code comments for usage examples and initialization details.

## Benefits
- Higher audio quality and reliability
- Easier cross-platform development
- Better integration with game events and Lua scripting
- Improved performance and resource management
