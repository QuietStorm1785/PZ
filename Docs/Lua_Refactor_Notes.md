# Lua Refactor Notes

## Overview
The Lua implementation in Project Zomboid was refactored from its original Java-based scripting system to a modern C++ module. This refactor improves performance, maintainability, and integration with the C++ game engine.

## Key Changes
- **Complete rewrite in C++:** All Lua-related code is now in C++ under `ProjectZomboidSwitch/src/zombie/LuaCpp/`.
- **Modular design:** Lua functionality is split into logical modules (LuaManager, LuaBinder, LuaEventManager, etc.) for clarity and extensibility.
- **Direct Lua/C API usage:** The new implementation uses the official Lua C API for script execution, binding, and event handling.
- **Improved object binding:** Game objects and events are exposed to Lua scripts using robust C++ bindings, allowing for more flexible scripting.
- **Signal/event system:** Added a C++ signal/event system for Lua callbacks and game events.
- **Type safety:** Enhanced type safety and error handling in Lua-C++ interactions.
- **Performance:** Reduced overhead by eliminating Java-to-C++ translation layers.

## File Structure
- `LuaManager.cpp/h`: Main entry point for Lua scripting.
- `LuaBinder.cpp/h`: Handles binding C++ objects/functions to Lua.
- `LuaEventManager.cpp/h`: Manages Lua events and callbacks.
- `LuaSignal.cpp/h`: Implements signal/event system for Lua.
- `LuaObjectMapper.cpp/h`: Maps C++ objects to Lua tables.
- `LuaUtils.cpp/h`: Utility functions for Lua integration.

## Migration Notes
- All previous Java-based Lua scripts must be ported to C++ or adapted to the new API. This has yet to be tested, but will be when the development is finished. I will update this when I complete testing. 
- See code comments in each module for usage examples.

## Benefits
- Faster script execution
- Easier debugging and extension
- Better integration with C++ game logic
