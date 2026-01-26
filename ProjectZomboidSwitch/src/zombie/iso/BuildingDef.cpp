
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cstring>
#include "zombie/iso/BuildingDef.h"


namespace zombie {
namespace iso {

std::vector<IsoGridSquare*> BuildingDef::squareChoices;

BuildingDef::BuildingDef()
        : L(nullptr), seen(false), hasBeenVisited(false), stash(), lootRespawnHour(-1),
            bAlarmed(false), x(10000000), y(10000000), x2(-10000000), y2(-10000000),
            zone(), food(0), ID(0), keySpawned(0), keyId(-1), metaID(0) {
    // Lua state setup if needed
    L = LuaManager::getPlatform()->newTable();
}


lua_State* BuildingDef::getLuaState() const {
    return L;
}


std::shared_ptr<RoomDef> BuildingDef::getRoom(const std::string& name) const {
    for (const auto& room : rooms) {
        if (room && strcasecmp(room->getName().c_str(), name.c_str()) == 0) {
            return room;
        }
    }
    return nullptr;
}


bool BuildingDef::isAllExplored() const {
    for (const auto& room : rooms) {
        if (room && !room->bExplored) return false;
    }
    return true;
}


void BuildingDef::setAllExplored(bool explored) {
    for (const auto& room : rooms) {
        if (room) room->setExplored(explored);
    }
}


std::shared_ptr<RoomDef> BuildingDef::getFirstRoom() const {
    return !rooms.empty() ? rooms[0] : nullptr;
}


int BuildingDef::getChunkX() const {
    return x / 10;
}


int BuildingDef::getChunkY() const {
    return y / 10;
}


int BuildingDef::getX() const { return x; }


int BuildingDef::getY() const { return y; }


int BuildingDef::getX2() const { return x2; }


int BuildingDef::getY2() const { return y2; }


int BuildingDef::getW() const { return x2 - x; }


int BuildingDef::getH() const { return y2 - y; }


int BuildingDef::getID() const { return ID; }


void BuildingDef::refreshSquares() {
    for (const auto& room : rooms) {
        if (room) room->refreshSquares();
    }
}


void BuildingDef::CalculateBounds(std::vector<std::shared_ptr<RoomDef>>& allRooms) {
    for (const auto& room : rooms) {
        if (!room) continue;
        for (const auto& rect : room->rects) {
            if (rect.x < x) x = rect.x;
            if (rect.y < y) y = rect.y;
            if (rect.x + rect.w > x2) x2 = rect.x + rect.w;
            if (rect.y + rect.h > y2) y2 = rect.y + rect.h;
        }
    }
    for (const auto& room : emptyoutside) {
        if (!room) continue;
        for (const auto& rect : room->rects) {
            if (rect.x < x) x = rect.x;
            if (rect.y < y) y = rect.y;
            if (rect.x + rect.w > x2) x2 = rect.x + rect.w;
            if (rect.y + rect.h > y2) y2 = rect.y + rect.h;
        }
    }
    int minChunkX = x / 10;
    int minChunkY = y / 10;
    int maxChunkX = x2 / 10;
    int maxChunkY = y2 / 10;
    overlappedChunks.clear();
    allRooms.clear();
    allRooms.insert(allRooms.end(), rooms.begin(), rooms.end());
    allRooms.insert(allRooms.end(), emptyoutside.begin(), emptyoutside.end());
    for (const auto& room : allRooms) {
        if (!room) continue;
        for (const auto& rect : room->rects) {
            int chunkX0 = rect.x / 10;
            int chunkY0 = rect.y / 10;
            int chunkX1 = (rect.x + rect.w) / 10;
            int chunkY1 = (rect.y + rect.h) / 10;
            for (int cy = chunkY0; cy <= chunkY1; ++cy) {
                for (int cx = chunkX0; cx <= chunkX1; ++cx) {
                    if (!overlapsChunk(cx, cy)) {
                        overlappedChunks.push_back(static_cast<short>(cx));
                        overlappedChunks.push_back(static_cast<short>(cy));
                    }
                }
            }
        }
    }
}


int64_t BuildingDef::calculateMetaID(int worldX, int worldY) const {
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int minLevel = std::numeric_limits<int>::max();
    const auto& useRooms = rooms.empty() ? emptyoutside : rooms;
    for (const auto& room : useRooms) {
        if (!room) continue;
        if (room->level <= minLevel) {
            if (room->level < minLevel) {
                minX = std::numeric_limits<int>::max();
                minY = std::numeric_limits<int>::max();
            }
            minLevel = room->level;
            for (const auto& rect : room->rects) {
                if (rect.x <= minX && rect.y < minY) {
                    minX = rect.x;
                    minY = rect.y;
                }
            }
        }
    }
    minX -= worldX * 300;
    minY -= worldY * 300;
    return (static_cast<int64_t>(minLevel) << 32) | (static_cast<int64_t>(minY) << 16) | minX;
}


void BuildingDef::recalculate() {
    food = 0;
    items.clear();
    itemTypes.clear();
    for (const auto& room : rooms) {
        if (!room) continue;
        IsoRoom* isoRoom = room->getIsoRoom();
        if (!isoRoom) continue;
        for (auto* container : isoRoom->Containers) {
            if (!container) continue;
            for (auto* item : container->Items) {
                if (!item) continue;
                items.push_back(item);
                itemTypes.insert(item->getFullType());
                if (dynamic_cast<Food*>(item)) ++food;
            }
        }
    }
}


bool BuildingDef::overlapsChunk(int chunkX, int chunkY) const {
    for (size_t i = 0; i + 1 < overlappedChunks.size(); i += 2) {
        if (overlappedChunks[i] == chunkX && overlappedChunks[i + 1] == chunkY) return true;
    }
    return false;
}


IsoGridSquare* BuildingDef::getFreeSquareInRoom() {
    squareChoices.clear();
    for (const auto& room : rooms) {
        if (!room) continue;
        for (const auto& rect : room->rects) {
            for (int x0 = rect.getX(); x0 < rect.getX2(); ++x0) {
                for (int y0 = rect.getY(); y0 < rect.getY2(); ++y0) {
                    IsoGridSquare* sq = IsoWorld::instance->CurrentCell->getGridSquare(x0, y0, room->getZ());
                    if (sq && sq->isFree(false)) {
                        squareChoices.push_back(sq);
                    }
                }
            }
        }
    }
    if (!squareChoices.empty()) {
        int idx = Rand::Next(static_cast<int>(squareChoices.size()));
        return squareChoices[idx];
    }
    return nullptr;
}


bool BuildingDef::containsRoom(const std::string& name) const {
    for (const auto& room : rooms) {
        if (room && room->name == name) return true;
    }
    return false;
}


bool BuildingDef::isFullyStreamedIn() const {
    for (size_t i = 0; i + 1 < overlappedChunks.size(); i += 2) {
        short cx = overlappedChunks[i];
        short cy = overlappedChunks[i + 1];
        IsoChunk* chunk = GameServer::bServer ? ServerMap::instance->getChunk(cx, cy) : IsoWorld::instance->CurrentCell->getChunk(cx, cy);
        if (!chunk) return false;
    }
    return true;
}


bool BuildingDef::isAnyChunkNewlyLoaded() const {
    for (size_t i = 0; i + 1 < overlappedChunks.size(); i += 2) {
        short cx = overlappedChunks[i];
        short cy = overlappedChunks[i + 1];
        IsoChunk* chunk = GameServer::bServer ? ServerMap::instance->getChunk(cx, cy) : IsoWorld::instance->CurrentCell->getChunk(cx, cy);
        if (!chunk) return false;
        if (chunk->isNewChunk()) return true;
    }
    return false;
}


Zone BuildingDef::getZone() const {
    return zone;
}


int BuildingDef::getKeyId() const { return keyId; }


void BuildingDef::setKeyId(int id) { keyId = id; }


int BuildingDef::getKeySpawned() const { return keySpawned; }


void BuildingDef::setKeySpawned(int spawned) { keySpawned = spawned; }


bool BuildingDef::isHasBeenVisited() const { return hasBeenVisited; }


void BuildingDef::setHasBeenVisited(bool visited) {
    if (visited && !hasBeenVisited) {
        StashSystem::visitedBuilding(this);
    }
    hasBeenVisited = visited;
}


bool BuildingDef::isAlarmed() const { return bAlarmed; }


void BuildingDef::setAlarmed(bool alarmed) { bAlarmed = alarmed; }


std::shared_ptr<RoomDef> BuildingDef::getRandomRoom(int minArea) const {
    if (rooms.empty()) return nullptr;
    auto room = rooms[Rand::Next(static_cast<int>(rooms.size()))];
    if (minArea > 0 && room && room->area >= minArea) return room;
    int tries = 0;
    while (tries++ <= 20) {
        room = rooms[Rand::Next(static_cast<int>(rooms.size()))];
        if (room && room->area >= minArea) return room;
    }
    return room;
}


float BuildingDef::getClosestPoint(float x0, float y0, glm::vec2& out) const {
    float minDist = std::numeric_limits<float>::max();
    glm::vec2 temp;
    for (const auto& room : rooms) {
        if (!room) continue;
        float dist = room->getClosestPoint(x0, y0, temp);
        if (dist < minDist) {
            minDist = dist;
            out = temp;
        }
    }
    return minDist;
}


void BuildingDef::Dispose() {
    for (const auto& room : rooms) {
        if (room) room->Dispose();
    }
    emptyoutside.clear();
    rooms.clear();
}

} // namespace iso
} // namespace zombie


