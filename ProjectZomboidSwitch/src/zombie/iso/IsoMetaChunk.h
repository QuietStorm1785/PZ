#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include <algorithm>

namespace zombie {
namespace iso {

enum class ChunkState {
    Unloaded,
    Loading,
    Loaded,
    Error
};

class IsoMetaChunk {
public:
    static constexpr float zombiesMinPerChunk = 0.06F;
    static constexpr float zombiesFullPerChunk = 12.0F;
    int ZombieIntensity = 0;
    std::vector<std::shared_ptr<Zone>> zones;
    std::vector<std::shared_ptr<RoomDef>> rooms;
    ChunkState state = ChunkState::Unloaded;

    IsoMetaChunk() = default;

    float getZombieIntensity(bool adjusted = true) const {
        float var2 = static_cast<float>(ZombieIntensity);
        float var3 = var2 / 255.0F;
        if (SandboxOptions::instance.Distribution.getValue() == 2) {
            var2 = 128.0F;
            var3 = 0.5F;
        }
        var2 *= 0.5F;
        switch (SandboxOptions::instance.Zombies.getValue()) {
            case 1: var2 *= 4.0F; break;
            case 2: var2 *= 3.0F; break;
            case 3: var2 *= 2.0F; break;
            case 5: var2 *= 0.35F; break;
            case 6: var2 = 0.0F; break;
        }
        var3 = var2 / 255.0F;
        float var4 = 11.94F * var3;
        var2 = 0.06F + var4;
        if (!adjusted) return var2;
        float var5 = var3 * 10.0F;
        if (Rand::Next(3) == 0) return 0.0F;
        var5 *= 0.5F;
        int var6 = 1000;
        switch (SandboxOptions::instance.Zombies.getValue()) {
            case 1: var6 = static_cast<int>(var6 / 2.0F); break;
            case 2: var6 = static_cast<int>(var6 / 1.7F); break;
            case 3: var6 = static_cast<int>(var6 / 1.5F); break;
            case 5: var6 = static_cast<int>(var6 * 1.5F); break;
        }
        if (Rand::Next(var6) < var5 /* && IsoWorld::getZombiesEnabled() */) {
            var2 = 12.0F;
        }
        return var2;
    }

    float getZombieIntensity() const { return getZombieIntensity(true); }
    void setZombieIntensity(int val) { if (val >= 0) ZombieIntensity = val; }

    float getLootZombieIntensity() const {
        float var1 = static_cast<float>(ZombieIntensity);
        float var2 = var1 / 255.0F;
        float var3 = 11.94F * var2;
        var1 = 0.06F + var3;
        float var4 = var2 * 10.0F;
        var2 = var2 * var2 * var2;
        if (Rand::Next(300) <= var4) var1 = 120.0F;
        // if (IsoWorld::getZombiesDisabled()) return 400.0F;
        return var1;
    }
    int getUnadjustedZombieIntensity() const { return ZombieIntensity; }

    void addZone(const std::shared_ptr<Zone>& zone) { zones.push_back(zone); }
    void removeZone(const std::shared_ptr<Zone>& zone) {
        zones.erase(std::remove(zones.begin(), zones.end(), zone), zones.end());
    }
    std::shared_ptr<Zone> getZone(size_t idx) const {
        return idx < zones.size() ? zones[idx] : nullptr;
    }
    std::shared_ptr<Zone> getZoneAt(int x, int y, int z) const {
        for (auto it = zones.rbegin(); it != zones.rend(); ++it) {
            if ((*it)->contains(x, y, z)) {
                if ((*it)->isPreferredZoneForSquare) return *it;
            }
        }
        for (auto it = zones.rbegin(); it != zones.rend(); ++it) {
            if ((*it)->contains(x, y, z)) return *it;
        }
        return nullptr;
    }
    std::vector<std::shared_ptr<Zone>> getZonesAt(int x, int y, int z) const {
        std::vector<std::shared_ptr<Zone>> result;
        for (const auto& zone : zones) {
            if (zone->contains(x, y, z)) result.push_back(zone);
        }
        return result;
    }
    void getZonesUnique(std::unordered_set<std::shared_ptr<Zone>>& out) const {
        for (const auto& zone : zones) out.insert(zone);
    }
    void getZonesIntersecting(int x, int y, int z, int w, int h, std::vector<std::shared_ptr<Zone>>& out) const {
        for (const auto& zone : zones) {
            if (std::find(out.begin(), out.end(), zone) == out.end() && zone->intersects(x, y, z, w, h)) {
                out.push_back(zone);
            }
        }
    }
    void clearZones() { zones.clear(); }
    void clearRooms() { rooms.clear(); }
    size_t numZones() const { return zones.size(); }
    void addRoom(const std::shared_ptr<RoomDef>& room) { rooms.push_back(room); }
    std::shared_ptr<RoomDef> getRoomAt(int x, int y, int level) const {
        for (const auto& room : rooms) {
            if (!room->isEmptyOutside() && room->level == level) {
                for (const auto& rect : room->rects) {
                    if (rect->x <= x && rect->y <= y && x < rect->getX2() && y < rect->getY2()) return room;
                }
            }
        }
        return nullptr;
    }
    std::shared_ptr<RoomDef> getEmptyOutsideAt(int x, int y, int level) const {
        for (const auto& room : rooms) {
            if (room->isEmptyOutside() && room->level == level) {
                for (const auto& rect : room->rects) {
                    if (rect->x <= x && rect->y <= y && x < rect->getX2() && y < rect->getY2()) return room;
                }
            }
        }
        return nullptr;
    }
    size_t getNumRooms() const { return rooms.size(); }
    void getRoomsIntersecting(int x, int y, int w, int h, std::vector<std::shared_ptr<RoomDef>>& out) const {
        for (const auto& room : rooms) {
            if (!room->isEmptyOutside() && std::find(out.begin(), out.end(), room) == out.end() && room->intersects(x, y, w, h)) {
                out.push_back(room);
            }
        }
    }
    void Dispose() {
        rooms.clear();
        zones.clear();
        state = ChunkState::Unloaded;
    }
};
} // namespace iso
} // namespace zombie
