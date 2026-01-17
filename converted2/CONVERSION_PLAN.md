# Java to C++ Conversion Plan

## Scope
- **Total Files:** 563 Java files
- **Total Lines:** ~105,000 lines of code
- **Size:** 4.8MB

## Priority Order

### Phase 1: Core Infrastructure (COMPLETED in /Converted)
- ✅ GameWindow.java → GameWindow.cpp
- ✅ GameTime.java → GameTime.cpp
- ✅ Core.java → Core.cpp
- ✅ GameStateMachine.java → GameStateMachine.cpp

### Phase 2: Essential Systems (IN PROGRESS)
- [ ] ZomboidGlobals.java
- [ ] SaveManager.java
- [ ] WorldSoundManager.java
- [ ] MusicManager.java
- [ ] SoundManager.java

### Phase 3: Game Objects
- [ ] characters/* (Player, Zombie, NPC classes)
- [ ] inventory/* (Item system)
- [ ] iso/* (Isometric world)

### Phase 4: Game Logic
- [ ] ai/* (AI pathfinding and behavior)
- [ ] behaviors/* (Character behaviors)
- [ ] scripting/* (Game scripts)

### Phase 5: UI & Networking
- [ ] ui/* (User interface)
- [ ] network/* (Multiplayer)
- [ ] gameStates/* (Game state management)

### Phase 6: Advanced Features
- [ ] modding/* (Mod support)
- [ ] Quests/* (Quest system)
- [ ] console/* (Debug console)

## Conversion Strategy

### Automated Conversion (Java → C++)
1. Package declarations → namespace
2. Import statements → #include directives
3. Class declarations → class/struct definitions
4. Java collections → STL containers
5. synchronized → std::mutex
6. Exception handling → C++ exceptions
7. Garbage collection → Smart pointers

### Manual Review Required
- Complex Java-specific features
- Multi-threading logic
- Network serialization
- UI rendering (Java2D → SDL2)

## Current Status
**Phase 1:** Complete (5 files, ~2,000 lines)
**Phase 2:** Starting
**Total Progress:** ~2%
