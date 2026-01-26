
#pragma once
#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <cstdint>
#include <glm/vec2.hpp>
#include "lua5.4/lua.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace iso {

class BuildingDef {
public:
    BuildingDef();

    // Fields
    lua_State* L; // Lua state for this building, or nullptr if not used
    bool seen;
    bool hasBeenVisited;
    std::string stash;
    int lootRespawnHour;
    // Removed TShortArrayList overlappedChunks; now using std::vector<short> overlappedChunks below
    bool bAlarmed;
    int x, y, x2, y2;
    Zone zone;
    int food;
    int ID;
    int keySpawned;
    int keyId;
    int64_t metaID;

    std::vector<std::shared_ptr<RoomDef>> rooms;
    std::vector<std::shared_ptr<RoomDef>> emptyoutside;
    std::vector<InventoryItem*> items;
    std::unordered_set<std::string> itemTypes;
    std::vector<short> overlappedChunks;

    // Methods
    lua_State* getLuaState() const;
    const std::vector<std::shared_ptr<RoomDef>>& getRooms() const;
    std::shared_ptr<RoomDef> getRoom(const std::string& name) const;
    bool isAllExplored() const;
    void setAllExplored(bool explored);
    std::shared_ptr<RoomDef> getFirstRoom() const;
    int getChunkX() const;
    int getChunkY() const;
    int getX() const;
    int getY() const;
    int getX2() const;
    int getY2() const;
    int getW() const;
    int getH() const;
    int getID() const;
    void refreshSquares();
    void CalculateBounds(std::vector<std::shared_ptr<RoomDef>>& allRooms);
    int64_t calculateMetaID(int worldX, int worldY) const;
    void recalculate();
    bool overlapsChunk(int chunkX, int chunkY) const;
    IsoGridSquare* getFreeSquareInRoom();
    bool containsRoom(const std::string& name) const;
    bool isFullyStreamedIn() const;
    bool isAnyChunkNewlyLoaded() const;
    Zone getZone() const;
    int getKeyId() const;
    void setKeyId(int id);
    int getKeySpawned() const;
    void setKeySpawned(int spawned);
    bool isHasBeenVisited() const;
    void setHasBeenVisited(bool visited);
    bool isAlarmed() const;
    void setAlarmed(bool alarmed);
    std::shared_ptr<RoomDef> getRandomRoom(int minArea) const;
    float getClosestPoint(float x, float y, glm::vec2& out) const;
    void Dispose();

public:
    // Static field for squareChoices (shared across all BuildingDef, as in Java)
    static std::vector<IsoGridSquare*> squareChoices;
};

} // namespace iso
} // namespace zombie
