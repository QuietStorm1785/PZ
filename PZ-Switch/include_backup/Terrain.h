#pragma once
#include <cstdint>

// Terrain types for world tiles - affects movement cost and pathfinding
enum class TerrainType : uint8_t {
    GRASS = 0,         // Normal grass (cost 1.0)
    CONCRETE = 1,      // Hard surface (cost 1.0)
    WATER = 2,         // Water (cost 2.0, slows zombies)
    MUD = 3,           // Muddy ground (cost 1.5)
    ROAD = 4,          // Paved road (cost 0.8, faster)
    FOREST = 5,        // Dense forest (cost 2.0, harder to move through)
    SAND = 6,          // Sand (cost 1.3)
    RUBBLE = 7,        // Destroyed terrain (cost 3.0, very slow)
    DEFAULT = GRASS
};

// Get movement cost multiplier for terrain type
inline float getTerrainCost(TerrainType terrain) {
    switch (terrain) {
        case TerrainType::GRASS:    return 1.0f;
        case TerrainType::CONCRETE: return 1.0f;
        case TerrainType::WATER:    return 2.0f;
        case TerrainType::MUD:      return 1.5f;
        case TerrainType::ROAD:     return 0.8f;
        case TerrainType::FOREST:   return 2.0f;
        case TerrainType::SAND:     return 1.3f;
        case TerrainType::RUBBLE:   return 3.0f;
        default:                    return 1.0f;
    }
}

// Check if terrain is passable
inline bool isTerrainPassable(TerrainType terrain) {
    // Water blocks movement unless swimming is implemented
    return terrain != TerrainType::WATER;
}
