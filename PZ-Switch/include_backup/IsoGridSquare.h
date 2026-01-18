#pragma once
#include <vector>
#include <memory>
#include "IsoObject.h"
#include "Terrain.h"
#include <glm/glm.hpp>

class IsoCell;
class IsoObject;
namespace zombie { namespace characters { class IsoPlayer; } }
class IsoZombie;

// Use shorter alias and smart pointer types
using IsoPlayer = zombie::characters::IsoPlayer;
using IsoPlayerPtr = std::shared_ptr<IsoPlayer>;
using IsoPlayerWeakPtr = std::weak_ptr<IsoPlayer>;
using IsoZombiePtr = std::shared_ptr<IsoZombie>;
using IsoZombieWeakPtr = std::weak_ptr<IsoZombie>;

/**
 * IsoGridSquare - Represents a single tile in the world grid
 * Contains objects, collision data, and tile properties
 */
class IsoGridSquare {
public:
    IsoGridSquare();
    IsoGridSquare(IsoCell* cell, int x, int y, int z);
    ~IsoGridSquare();

    // Position
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }

    // Cell access
    IsoCell* getCell() const { return cell; }

    // Object management
    void addObject(IsoObject* obj);
    void removeObject(IsoObject* obj);
    const std::vector<IsoObject*>& getObjects() const { return objects; }

    // Character management (non-owning references)
    void addCharacter(IsoPlayerPtr player);
    void addZombie(IsoZombiePtr zombie);
    void removeCharacter(IsoPlayerPtr player);
    void removeZombie(IsoZombiePtr zombie);
    
    std::vector<IsoPlayerPtr> getCharacters() const;
    std::vector<IsoZombiePtr> getZombies() const;
    bool hasCharacters() const;
    bool hasZombies() const;

    // Collision and pathfinding
    bool isSolid() const { return solid; }
    void setSolid(bool s);
    bool isSolidFloor() const { return solidFloor; }
    void setSolidFloor(bool sf);
    bool isBlocked() const { return solid || !solidFloor; }
    bool isFree(bool checkCharacters = true) const;

    // Neighbor access
    IsoGridSquare* getN() const { return n; }
    IsoGridSquare* getS() const { return s; }
    IsoGridSquare* getE() const { return e; }
    IsoGridSquare* getW() const { return w; }
    IsoGridSquare* getNE() const { return ne; }
    IsoGridSquare* getNW() const { return nw; }
    IsoGridSquare* getSE() const { return se; }
    IsoGridSquare* getSW() const { return sw; }

    void setN(IsoGridSquare* sq) { n = sq; }
    void setS(IsoGridSquare* sq) { s = sq; }
    void setE(IsoGridSquare* sq) { e = sq; }
    void setW(IsoGridSquare* sq) { w = sq; }
    void setNE(IsoGridSquare* sq) { ne = sq; }
    void setNW(IsoGridSquare* sq) { nw = sq; }
    void setSE(IsoGridSquare* sq) { se = sq; }
    void setSW(IsoGridSquare* sq) { sw = sq; }

    // Distance calculation
    float distanceTo(IsoGridSquare* other) const;

    // Terrain properties
    TerrainType getTerrain() const { return terrain; }
    void setTerrain(TerrainType t) { terrain = t; }
    float getMovementCost() const { return getTerrainCost(terrain); }
    bool isTerrainPassable() const { return ::isTerrainPassable(terrain); }

    // Rendering layers - for chunk rendering
    bool isWall() const { return hasWall; }
    void setWall(bool w) { hasWall = w; }
    
    bool hasRoof() const { return hasRoofTile; }
    void setRoof(bool r) { hasRoofTile = r; }
    
    bool hasGround() const { return hasGroundTile; }
    void setGround(bool g) { hasGroundTile = g; }

    // Update
    void update();

private:
    IsoCell* cell;
    int x, y, z;

    // Objects on this tile
    std::vector<IsoObject*> objects;
    std::vector<IsoPlayerWeakPtr> characters;  // Non-owning
    std::vector<IsoZombieWeakPtr> zombies;     // Non-owning

    // Tile properties
    bool solid;
    bool solidFloor;
    bool seen;
    TerrainType terrain;

    // Rendering layers
    bool hasGroundTile = true;   // Ground/floor
    bool hasWall = false;        // Wall
    bool hasRoofTile = false;    // Roof/overhead

    // Neighboring squares (8-way)
    IsoGridSquare* n;
    IsoGridSquare* s;
    IsoGridSquare* e;
    IsoGridSquare* w;
    IsoGridSquare* ne;
    IsoGridSquare* nw;
    IsoGridSquare* se;
    IsoGridSquare* sw;
};
