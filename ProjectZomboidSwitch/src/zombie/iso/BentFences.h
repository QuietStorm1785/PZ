#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <lua5.4/lua.h>
#include <lua5.4/lualib.h>
#include <lua5.4/lauxlib.h>
#include "zombie/MapCollisionData.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoCell.h"

namespace zombie {
namespace iso {

class BentFences {
public:
    struct Entry {
        std::vector<std::string> collapsed;
        int collapsedOffset = 0;
        int collapsedSizeX = 0;
        int collapsedSizeY = 0;
        std::vector<std::string> debris;
        IsoDirections dir = IsoDirections::Max;
        bool doSmash = false;
        int health = 0;
        int length = 0;
        std::unordered_map<int, std::vector<std::string>> stages;
        std::vector<std::string> unbent;
        std::vector<std::string> bent;
        bool isNorth() const;
    };

    static BentFences& getInstance();

    void addFenceTiles(int version, KahluaTableImpl* tiles);
    bool isBentObject(IsoObject* obj) const;
    bool isUnbentObject(IsoObject* obj) const;
    void swapTiles(IsoObject* obj, IsoDirections dir);
    void bendFence(IsoObject* obj, IsoDirections dir);
    void unbendFence(IsoObject* obj);
    void Reset();

    // Additional methods from YAML/Java
    // ... (stubs for all other methods as needed)

private:
    BentFences();
    Entry* getEntryForObject(IsoObject* obj, IsoDirections dir = IsoDirections::Invalid) const;
    bool isValidObject(IsoObject* obj, const Entry* entry, bool unbent) const;
    IsoObject* getObjectForEntry(IsoGridSquare* sq, const std::vector<std::string>& tiles, int idx) const;
    void tableToTiles(KahluaTableImpl* table, std::vector<std::string>& out);
    void tableToTiles(KahluaTable* table, std::vector<std::string>& out, const std::string& key);

    // Fields
    std::vector<Entry> m_entries;
    std::unordered_map<std::string, std::vector<Entry*>> m_bentMap;
    std::unordered_map<std::string, std::vector<Entry*>> m_unbentMap;
    std::unordered_set<std::string> m_collapsedTiles;
    std::unordered_set<std::string> m_debrisTiles;
    std::unordered_map<std::string, std::vector<Entry*>> m_fenceMap;
};

} // namespace iso
} // namespace zombie
