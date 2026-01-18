#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

class IsoGridSquare;
class IsoObject;
namespace zombie { namespace characters { class IsoPlayer; } }
using IsoPlayer = zombie::characters::IsoPlayer;

/**
 * SpatialGrid - Fast spatial queries for objects and entities
 * Uses a simple grid-based partitioning for O(1) cell lookup
 */
class SpatialGrid {
public:
 SpatialGrid(int cellSize = 32);
 ~SpatialGrid();

 // Register object at position
 void insertObject(float x, float y, IsoObject* obj);
 void removeObject(float x, float y, IsoObject* obj);
 void updateObject(float oldX, float oldY, float newX, float newY, IsoObject* obj);

 // Query objects near a point (circle)
 std::vector<IsoObject*> queryObjects(float x, float y, float radius);

 // Query objects in a box
 std::vector<IsoObject*> queryObjectsBox(float x, float y, float width, float height);

 // Clear all entries
 void clear();

private:
 int cellSize;
 std::unordered_map<int, std::vector<IsoObject*>> grid;

 int getCellKey(float x, float y) const;
 void getCellCoords(float x, float y, int& cellX, int& cellY) const;
};

/**
 * EntitySpatialGrid - Fast queries for player and entity positions
 */
class EntitySpatialGrid {
public:
 EntitySpatialGrid(int cellSize = 32);
 ~EntitySpatialGrid();

 // Update entity position
 void insertEntity(float x, float y, IsoPlayer* entity);
 void updateEntity(float oldX, float oldY, float newX, float newY, IsoPlayer* entity);
 void removeEntity(float x, float y, IsoPlayer* entity);

 // Query entities near a point
 std::vector<IsoPlayer*> queryEntities(float x, float y, float radius);

 void clear();

private:
 int cellSize;
 std::unordered_map<int, std::vector<IsoPlayer*>> grid;

 int getCellKey(float x, float y) const;
 void getCellCoords(float x, float y, int& cellX, int& cellY) const;
};
