#include <string>
#include <vector>
#include "zombie/iso/IsoMetaCell.h"


namespace zombie {
namespace iso {

void IsoMetaCell::addTrigger(std::shared_ptr<BuildingDef> def, int range, int type, const std::string& data) {
    triggers.push_back(std::make_shared<Trigger>(def, range, type, data));
}

void IsoMetaCell::checkTriggers() {
    if (IsoCamera::CamCharacter) {
        int x = static_cast<int>(IsoCamera::CamCharacter->getX());
        int y = static_cast<int>(IsoCamera::CamCharacter->getY());
        for (auto& trig : triggers) {
            if (x >= trig->def->x - trig->triggerRange &&
                x <= trig->def->x2 + trig->triggerRange &&
                y >= trig->def->y - trig->triggerRange &&
                y <= trig->def->y2 + trig->triggerRange) {
                if (!trig->triggered) {
                    LuaEventManager::triggerEvent("OnTriggerNPCEvent", trig->type, trig->data, trig->def);
                }
                LuaEventManager::triggerEvent("OnMultiTriggerNPCEvent", trig->type, trig->data, trig->def);
                trig->triggered = true;
            }
        }
    }
}

std::shared_ptr<IsoMetaChunk> IsoMetaCell::getChunk(int x, int y) {
    if (x >= 0 && x < 30 && y >= 0 && y < 30) {
        return ChunkMap[y * 30 + x];
    }
    return nullptr;
}

void IsoMetaCell::addZone(std::shared_ptr<Zone> zone, int baseX, int baseY) {
    int x0 = zone->x / 10;
    int y0 = zone->y / 10;
    int x1 = (zone->x + zone->w) / 10;
    if ((zone->x + zone->w) % 10 == 0) x1--;
    int y1 = (zone->y + zone->h) / 10;
    if ((zone->y + zone->h) % 10 == 0) y1--;
    x0 = PZMath::clamp(x0, baseX / 10, (baseX + 300) / 10);
    y0 = PZMath::clamp(y0, baseY / 10, (baseY + 300) / 10);
    x1 = PZMath::clamp(x1, baseX / 10, (baseX + 300) / 10 - 1);
    y1 = PZMath::clamp(y1, baseY / 10, (baseY + 300) / 10 - 1);
    for (int y = y0; y <= y1; ++y) {
        for (int x = x0; x <= x1; ++x) {
            if (zone->intersects(x * 10, y * 10, zone->z, 10, 10)) {
                int idx = x - baseX / 10 + (y - baseY / 10) * 30;
                if (ChunkMap[idx]) ChunkMap[idx]->addZone(zone);
            }
        }
    }
}

void IsoMetaCell::removeZone(std::shared_ptr<Zone> zone) {
    int x1 = (zone->x + zone->w) / 10;
    if ((zone->x + zone->w) % 10 == 0) x1--;
    int y1 = (zone->y + zone->h) / 10;
    if ((zone->y + zone->h) % 10 == 0) y1--;
    int baseX = wx * 300;
    int baseY = wy * 300;
    for (int y = zone->y / 10; y <= y1; ++y) {
        for (int x = zone->x / 10; x <= x1; ++x) {
            if (x >= baseX / 10 && x < (baseX + 300) / 10 && y >= baseY / 10 && y < (baseY + 300) / 10) {
                int idx = x - baseX / 10 + (y - baseY / 10) * 30;
                if (ChunkMap[idx]) ChunkMap[idx]->removeZone(zone);
            }
        }
    }
}

void IsoMetaCell::addRoom(std::shared_ptr<RoomDef> room, int baseX, int baseY) {
    int x1 = room->x2 / 10;
    if (room->x2 % 10 == 0) x1--;
    int y1 = room->y2 / 10;
    if (room->y2 % 10 == 0) y1--;
    for (int y = room->y / 10; y <= y1; ++y) {
        for (int x = room->x / 10; x <= x1; ++x) {
            if (x >= baseX / 10 && x < (baseX + 300) / 10 && y >= baseY / 10 && y < (baseY + 300) / 10) {
                int idx = x - baseX / 10 + (y - baseY / 10) * 30;
                if (ChunkMap[idx]) ChunkMap[idx]->addRoom(room);
            }
        }
    }
}

void IsoMetaCell::getZonesUnique(std::unordered_set<std::shared_ptr<Zone>>& out) {
    for (auto& chunk : ChunkMap) {
        if (chunk) chunk->getZonesUnique(out);
    }
}

void IsoMetaCell::getZonesIntersecting(int x, int y, int z, int w, int h, std::vector<std::shared_ptr<Zone>>& out) {
    int x1 = (x + w) / 10;
    if ((x + w) % 10 == 0) x1--;
    int y1 = (y + h) / 10;
    if ((y + h) % 10 == 0) y1--;
    int baseX = wx * 300;
    int baseY = wy * 300;
    for (int yy = y / 10; yy <= y1; ++yy) {
        for (int xx = x / 10; xx <= x1; ++xx) {
            if (xx >= baseX / 10 && xx < (baseX + 300) / 10 && yy >= baseY / 10 && yy < (baseY + 300) / 10) {
                int idx = xx - baseX / 10 + (yy - baseY / 10) * 30;
                if (ChunkMap[idx]) ChunkMap[idx]->getZonesIntersecting(x, y, z, w, h, out);
            }
        }
    }
}

void IsoMetaCell::getRoomsIntersecting(int x, int y, int z, int w, std::vector<std::shared_ptr<RoomDef>>& out) {
    int x1 = (x + z) / 10;
    if ((x + z) % 10 == 0) x1--;
    int y1 = (y + w) / 10;
    if ((y + w) % 10 == 0) y1--;
    int baseX = wx * 300;
    int baseY = wy * 300;
    for (int yy = y / 10; yy <= y1; ++yy) {
        for (int xx = x / 10; xx <= x1; ++xx) {
            if (xx >= baseX / 10 && xx < (baseX + 300) / 10 && yy >= baseY / 10 && yy < (baseY + 300) / 10) {
                int idx = xx - baseX / 10 + (yy - baseY / 10) * 30;
                if (ChunkMap[idx]) ChunkMap[idx]->getRoomsIntersecting(x, y, z, w, out);
            }
        }
    }
}

void IsoMetaCell::Dispose() {
    for (auto& chunk : ChunkMap) {
        if (chunk) {
            chunk->Dispose();
            chunk = nullptr;
        }
    }
    info = nullptr;
    mannequinZones.clear();
    roomTones.clear();
}

} // namespace iso
} // namespace zombie
