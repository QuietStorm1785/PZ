#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <cstdint>
#include "lua5.4/lua.h"
#include "lua5.4/lualib.h"
#include "lua5.4/lauxlib.h"
#include "zombie/MapCollisionData.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace iso {

class BrokenFences {
public:
    struct Tile {
        std::vector<std::string> self;
        std::vector<std::string> left;
        std::vector<std::string> right;
        std::vector<std::string> debrisN;
        std::vector<std::string> debrisS;
        std::vector<std::string> debrisW;
        std::vector<std::string> debrisE;
        Tile() = default;
        std::string pickRandom(const std::vector<std::string>& v) const;
    };

    static BrokenFences& getInstance();

    void addBrokenTiles(lua_State* L, int tableIndex);
    void addDebrisTiles(lua_State* L, int tableIndex);
    void setDestroyed(IsoObject* obj);
    void setDamagedLeft(IsoObject* obj);
    void setDamagedRight(IsoObject* obj);
    void updateSprite(IsoObject* obj, bool left, bool right);
    bool isBreakableObject(IsoObject* obj) const;
    void destroyFence(IsoObject* obj, IsoDirections dir);
    void Reset();

private:
    BrokenFences();
    std::vector<std::string> tableToTiles(lua_State* L, int tableIndex) const;
    void damageAdjacent(IsoGridSquare* sq, IsoDirections dir, IsoDirections causeDir);
    bool isNW(IsoObject* obj) const;
    bool isUnbroken(IsoObject* obj) const;
    bool isBrokenLeft(IsoObject* obj) const;
    bool isBrokenRight(IsoObject* obj) const;
    IsoObject* getBreakableObject(IsoGridSquare* sq, bool north) const;
    void addItems(IsoObject* obj, IsoGridSquare* sq);
    void addDebrisObject(IsoObject* obj, IsoDirections dir);

    // Maps
    std::unordered_map<std::string, std::shared_ptr<Tile>> s_unbrokenMap;
    std::unordered_map<std::string, std::shared_ptr<Tile>> s_brokenLeftMap;
    std::unordered_map<std::string, std::shared_ptr<Tile>> s_brokenRightMap;
    std::unordered_map<std::string, std::shared_ptr<Tile>> s_allMap;
};

} // namespace iso
} // namespace zombie
