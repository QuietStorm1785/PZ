#include <string>
#include <vector>
#include "zombie/iso/IsoMetaGrid.h"

namespace zombie {
namespace iso {

void IsoMetaGrid::AddToMeta(IsoGameCharacter var1) {
    IsoWorld::instance.CurrentCell.Remove(var1);
    if (std::find(MetaCharacters.begin(), MetaCharacters.end(), var1) == MetaCharacters.end()) {
        MetaCharacters.push_back(var1);
    }
    // Implementation based on Java/C++ logic:
    // Reads all zones from a ByteBuffer (var1)
    Zones.clear();
    int zoneCount = var1.getInt();
    for (int i = 0; i < zoneCount; ++i) {
        loadZone(var1, i);
    }
}

void IsoMetaGrid::RemoveFromMeta(IsoPlayer var1) {
    MetaCharacters.erase(std::remove(MetaCharacters.begin(), MetaCharacters.end(), var1), MetaCharacters.end());
    auto& objList = IsoWorld::instance.CurrentCell.getObjectList();
    if (std::find(objList.begin(), objList.end(), var1) == objList.end()) {
        objList.push_back(var1);
    }
}

int IsoMetaGrid::getMinX() { return minX; }
int IsoMetaGrid::getMinY() { return minY; }
int IsoMetaGrid::getMaxX() { return maxX; }
int IsoMetaGrid::getMaxY() { return maxY; }

Zone IsoMetaGrid::getZoneAt(int x, int y, int z) {
    auto chunk = getChunkDataFromTile(x, y);
    return chunk ? chunk->getZoneAt(x, y, z) : nullptr;
}

Zone IsoMetaGrid::getZoneWithBoundsAndType(int x, int y, int z, int w, int h, const std::string& type) {
    auto& zoneList = TL_ZoneList.get();
    zoneList.clear();
    getZonesIntersecting(x, y, z, w, h, zoneList);
    for (auto& zone : zoneList) {
        if (zone->x == x && zone->y == y && zone->z == z && zone->w == w && zone->h == h && StringUtils::equalsIgnoreCase(zone->type, type)) {
            return zone;
        }
    }
    return nullptr;
}

VehicleZone IsoMetaGrid::getVehicleZoneAt(int x, int y, int z) {
    auto cell = getMetaGridFromTile(x, y);
    if (cell && !cell->vehicleZones.empty()) {
        for (auto& vz : cell->vehicleZones) {
            if (vz->contains(x, y, z)) return vz;
        }
    }
    return nullptr;
}

BuildingDef IsoMetaGrid::getBuildingAt(int x, int y) {
    for (auto& b : Buildings) {
        if (b->x <= x && b->y <= y && b->getW() > x - b->x && b->getH() > y - b->y) return b;
    }
    return nullptr;
}

BuildingDef IsoMetaGrid::getBuildingAtRelax(int x, int y) {
    for (auto& b : Buildings) {
        if (b->x <= x + 1 && b->y <= y + 1 && b->getW() > x - b->x - 1 && b->getH() > y - b->y - 1) return b;
    }
    return nullptr;
}

RoomDef IsoMetaGrid::getRoomAt(int x, int y, int z) {
    auto chunk = getChunkDataFromTile(x, y);
    return chunk ? chunk->getRoomAt(x, y, z) : nullptr;
}

RoomDef IsoMetaGrid::getEmptyOutsideAt(int x, int y, int z) {
    auto chunk = getChunkDataFromTile(x, y);
    return chunk ? chunk->getEmptyOutsideAt(x, y, z) : nullptr;
}

void IsoMetaGrid::getRoomsIntersecting(int x, int y, int w, int h, std::vector<RoomDef>& out) {
    for (int yy = y / 300; yy <= (y + height) / 300; ++yy) {
        for (int xx = x / 300; xx <= (x + width) / 300; ++xx) {
            if (xx >= minX && xx <= maxX && yy >= minY && yy <= maxY) {
                auto cell = Grid[xx - minX][yy - minY];
                if (cell) cell->getRoomsIntersecting(x, y, w, h, out);
            }
        }
    }
}

int IsoMetaGrid::countRoomsIntersecting(int x, int y, int w, int h) {
    tempRooms.clear();
    for (int yy = y / 300; yy <= (y + height) / 300; ++yy) {
        for (int xx = x / 300; xx <= (x + width) / 300; ++xx) {
            if (xx >= minX && xx <= maxX && yy >= minY && yy <= maxY) {
                auto cell = Grid[xx - minX][yy - minY];
                if (cell) cell->getRoomsIntersecting(x, y, w, h, tempRooms);
            }
        }
    }
    return static_cast<int>(tempRooms.size());
}

int IsoMetaGrid::countNearbyBuildingsRooms(IsoPlayer var1) {
    int x = static_cast<int>(var1->getX()) - 20;
    int y = static_cast<int>(var1->getY()) - 20;
    return countRoomsIntersecting(x, y, 40, 40);
}

bool IsoMetaGrid::isInside(Zone var1, BuildingDef var2) {
    // Use Rect for a and b
    // Rect a, b; // Already declared in header, use as needed
            return x <= other.x && y <= other.y &&
                   x + width >= other.x + other.width &&
                   y + height >= other.y + other.height;
        }
    };
    Rect a{var1->x, var1->y, var1->w, var1->h};
    Rect b{var2->x, var2->y, var2->getW(), var2->getH()};
    return a.contains(b);
}

bool IsoMetaGrid::isAdjacent(Zone var1, Zone var2) {
    if (var1 == var2) return false;
    // Use local Rect structs for a and b
    struct Rect {
        int x, y, width, height;
        bool intersects(const Rect& other) const {
            return !(x + width <= other.x || other.x + other.width <= x ||
                     y + height <= other.y || other.y + other.height <= y);
        }
    };
    Rect a{var1->x, var1->y, var1->w, var1->h};
    Rect b{var2->x, var2->y, var2->w, var2->h};
    // Expand both rectangles by 1 on all sides (width/height +2, x/y -1)
    a.x--; a.y--; a.width += 2; a.height += 2;
    b.x--; b.y--; b.width += 2; b.height += 2;
    return a.intersects(b);
}

Zone IsoMetaGrid::registerZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
    // Use the extended version with default geometry and points
    return registerZone(var1, var2, var3, var4, var5, var6, var7, ZoneGeometryType::INVALID, std::vector<int>(), 0);
}

Zone IsoMetaGrid::registerZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, ZoneGeometryType var8, const std::vector<int>& var9, int var10) {
    // Merge logic from Java/C++: create Zone, set geometry, add points, set preferred, add to grid if in bounds
    std::string name = sharedStrings.get(var1);
    std::string type = sharedStrings.get(var2);
    auto zone = std::make_shared<Zone>(name, type, var3, var4, var5, var6, var7);
    zone->geometryType = var8;
    if (!var9.empty()) {
        zone->points.insert(zone->points.end(), var9.begin(), var9.end());
        zone->polylineWidth = var10;
    }
    zone->isPreferredZoneForSquare = isPreferredZoneForSquare(type);
    // Bounds check (as in Java)
    if (var3 >= minX * 300 - 100 && var4 >= minY * 300 - 100 &&
        var3 + var6 <= (maxX + 1) * 300 + 100 && var4 + var7 <= (maxY + 1) * 300 + 100 &&
        var5 >= 0 && var5 < 8 && var6 <= 600 && var7 <= 600) {
        addZone(zone);
        return zone;
    }
    return zone;
}

// Lua 5.4.7 version: var5 and var6 are now lua_State* and table indices
Zone IsoMetaGrid::registerGeometryZone(const std::string& var1, const std::string& var2, int var3, const std::string& var4, lua_State* L, int pointsTableIdx, int optionsTableIdx) {
    // Parse points from Lua table at pointsTableIdx
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    std::vector<int> points;
    lua_pushnil(L); // first key
    int count = 0;
    while (lua_next(L, pointsTableIdx) != 0) {
        // key at -2, value at -1
        if (lua_isinteger(L, -1)) {
            int val = static_cast<int>(lua_tointeger(L, -1));
            if (count % 2 == 0) {
                points.push_back(val);
                if (val < minX) minX = val;
                if (val > maxX) maxX = val;
            } else {
                points.push_back(val);
                if (val < minY) minY = val;
                if (val > maxY) maxY = val;
            }
            count++;
        }
        lua_pop(L, 1); // pop value, keep key for next iteration
    }
    // Determine geometry type
    ZoneGeometryType geometryType = ZoneGeometryType::INVALID;
    if (var4 == "point") geometryType = ZoneGeometryType::Point;
    else if (var4 == "polygon") geometryType = ZoneGeometryType::Polygon;
    else if (var4 == "polyline") geometryType = ZoneGeometryType::Polyline;
    else throw std::invalid_argument("unknown zone geometry type");
    int polylineWidth = 0;
    if (geometryType == ZoneGeometryType::Polyline && optionsTableIdx != 0) {
        lua_getfield(L, optionsTableIdx, "LineWidth");
        if (lua_isinteger(L, -1)) {
            polylineWidth = static_cast<int>(lua_tointeger(L, -1));
        }
        lua_pop(L, 1);
    }
    if (geometryType == ZoneGeometryType::Polyline && polylineWidth > 0) {
        int bounds[4];
        calculatePolylineOutlineBounds(points, polylineWidth, bounds);
        minX = bounds[0];
        minY = bounds[1];
        maxX = bounds[2];
        maxY = bounds[3];
    }
    if (var2 != "Vehicle" && var2 != "ParkingStall") {
        return registerZone(var1, var2, minX, minY, var3, maxX - minX + 1, maxY - minY + 1, geometryType, points, polylineWidth);
    } else {
        // For vehicle zones, pass optionsTableIdx as a Lua table
        Zone zone = registerVehiclesZone(var1, var2, minX, minY, var3, maxX - minX + 1, maxY - minY + 1, L, optionsTableIdx);
        if (zone) {
            zone->geometryType = geometryType;
            zone->points = points;
            zone->polylineWidth = polylineWidth;
        }
        return zone;
    }
}

void IsoMetaGrid::calculatePolylineOutlineBounds(const std::vector<int>& var1, int var2, int var3[]) {
    // Simple bounding box for polyline with width (expand with geometry lib if needed)
    if (var1.empty() || var3 == nullptr) return;
    int minX = std::numeric_limits<int>::max();
    int minY = std::numeric_limits<int>::max();
    int maxX = std::numeric_limits<int>::min();
    int maxY = std::numeric_limits<int>::min();
    for (size_t i = 0; i + 1 < var1.size(); i += 2) {
        int x = var1[i];
        int y = var1[i + 1];
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    // Expand bounds by half the width on all sides
    int halfW = var2 / 2;
    var3[0] = minX - halfW;
    var3[1] = minY - halfW;
    var3[2] = maxX + halfW;
    var3[3] = maxY + halfW;
}

Zone IsoMetaGrid::registerZoneNoOverlap(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7) {
    // Only register if within bounds, else return nullptr (matches Java logic)
    if (var3 >= minX * 300 - 100 && var4 >= minY * 300 - 100 &&
        var3 + var6 <= (maxX + 1) * 300 + 100 && var4 + var7 <= (maxY + 1) * 300 + 100 &&
        var5 >= 0 && var5 < 8 && var6 <= 600 && var7 <= 600) {
        return registerZone(var1, var2, var3, var4, var5, var6, var7);
    }
    return nullptr;
}

void IsoMetaGrid::addZone(Zone var1) {
    if (!var1) return;
    Zones.push_back(var1);
    // Add to owning cell
    int cellX = var1->x / 300;
    int cellY = var1->y / 300;
    IsoMetaCell cell = getCellData(cellX, cellY);
    if (cell) {
        cell->addZone(var1);
    }
    // Add to type-based maps if needed (e.g., for "RoomDef", "VehicleZone", etc.)
    if (var1->type == "RoomDef") {
        // Room zones are handled elsewhere, skip here
    } else if (var1->type == "ParkingStall" || var1->type == "Vehicle" || var1->type == "TrafficJam") {
        VehicleZones.push_back(std::static_pointer_cast<VehicleZone>(var1));
    }
    // Optionally update other structures if needed (e.g., Buildings, if zone is a building)
    // Mirror Java logic for type-based structures
    if (!var1) return;

    // Building zones
    if (var1->type == "Building" || var1->type == "BuildingDef") {
        // Only add if not already present
        auto bldg = std::dynamic_pointer_cast<BuildingDef>(var1);
        if (bldg && std::find(Buildings.begin(), Buildings.end(), bldg) == Buildings.end()) {
            Buildings.push_back(bldg);
        }
    }

    // Room zones
    if (var1->type == "RoomDef" || var1->type == "Room") {
        auto room = std::dynamic_pointer_cast<RoomDef>(var1);
        if (room && std::find(RoomZones.begin(), RoomZones.end(), room) == RoomZones.end()) {
            RoomZones.push_back(room);
        }
    }

    // Mannequin zones
    if (var1->type == "MannequinZone") {
        auto mzone = std::dynamic_pointer_cast<MannequinZone>(var1);
        if (mzone && std::find(MannequinZones.begin(), MannequinZones.end(), mzone) == MannequinZones.end()) {
            MannequinZones.push_back(mzone);
        }
    }

    // Room tone zones
    if (var1->type == "RoomToneZone") {
        auto rzone = std::dynamic_pointer_cast<RoomToneZone>(var1);
        if (rzone && std::find(RoomToneZones.begin(), RoomToneZones.end(), rzone) == RoomToneZones.end()) {
            RoomToneZones.push_back(rzone);
        }
    }

    // Add any other type-specific structures as needed here
}

void IsoMetaGrid::removeZone(Zone var1) {
    if (!var1) return;
    // Remove from Zones vector
    Zones.erase(std::remove(Zones.begin(), Zones.end(), var1), Zones.end());
    // Remove from owning cell
    int cellX = var1->x / 300;
    int cellY = var1->y / 300;
    IsoMetaCell cell = getCellData(cellX, cellY);
    if (cell) {
        cell->removeZone(var1);
    }
    // Remove from VehicleZones if needed
    if (var1->type == "ParkingStall" || var1->type == "Vehicle" || var1->type == "TrafficJam") {
        auto it = std::remove_if(VehicleZones.begin(), VehicleZones.end(),
            [&](const std::shared_ptr<VehicleZone>& vz) { return vz == var1; });
        VehicleZones.erase(it, VehicleZones.end());
    }
    // Optionally update other structures if needed (e.g., Buildings, if zone is a building)
    // Mirror Java logic for type-based structures
    if (!var1) return;

    // Building zones
    if (var1->type == "Building" || var1->type == "BuildingDef") {
        auto bldg = std::dynamic_pointer_cast<BuildingDef>(var1);
        if (bldg) {
            auto it = std::remove(Buildings.begin(), Buildings.end(), bldg);
            Buildings.erase(it, Buildings.end());
        }
    }

    // Room zones
    if (var1->type == "RoomDef" || var1->type == "Room") {
        auto room = std::dynamic_pointer_cast<RoomDef>(var1);
        if (room) {
            auto it = std::remove(RoomZones.begin(), RoomZones.end(), room);
            RoomZones.erase(it, RoomZones.end());
        }
    }

    // Mannequin zones
    if (var1->type == "MannequinZone") {
        auto mzone = std::dynamic_pointer_cast<MannequinZone>(var1);
        if (mzone) {
            auto it = std::remove(MannequinZones.begin(), MannequinZones.end(), mzone);
            MannequinZones.erase(it, MannequinZones.end());
        }
    }

    // Room tone zones
    if (var1->type == "RoomToneZone") {
        auto rzone = std::dynamic_pointer_cast<RoomToneZone>(var1);
        if (rzone) {
            auto it = std::remove(RoomToneZones.begin(), RoomToneZones.end(), rzone);
            RoomToneZones.erase(it, RoomToneZones.end());
        }
    }

    // Remove from any other type-specific structures as needed here
}

void IsoMetaGrid::removeZonesForCell(int var1, int var2) {
    IsoMetaCell cell = getCellData(var1, var2);
    if (!cell) return;
    // Collect zones to remove (copy, as we'll modify containers)
    std::vector<Zone> zonesToRemove = cell->getZones();
    for (const auto& zone : zonesToRemove) {
        removeZone(zone);
    }
}

void IsoMetaGrid::removeZonesForLotDirectory(const std::string& var1) {
    // Remove all zones whose lotDirectory matches var1
    std::vector<Zone> zonesToRemove;
    for (const auto& zone : Zones) {
        if (zone && zone->lotDirectory == var1) {
            zonesToRemove.push_back(zone);
        }
    }
    for (const auto& zone : zonesToRemove) {
        removeZone(zone);
    }
}

void IsoMetaGrid::processZones() {
    // Call processZones on all cells in the grid
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            IsoMetaCell cell = Grid[x][y];
            if (cell) {
                cell->processZones();
            }
        }
    }
}

// Lua 5.4.7 version: var8 is now lua_State* and tableIdx
Zone IsoMetaGrid::registerVehiclesZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, lua_State* L, int tableIdx) {
    // Create a VehicleZone and add it to the grid
    std::string name = sharedStrings.get(var1);
    std::string type = sharedStrings.get(var2);
    auto zone = std::make_shared<VehicleZone>(name, type, var3, var4, var5, var6, var7);

    // Parse options from Lua table at tableIdx
    if (L && tableIdx != 0) {
        // name (override)
        lua_getfield(L, tableIdx, "name");
        if (lua_isstring(L, -1)) {
            zone->name = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // type (override)
        lua_getfield(L, tableIdx, "type");
        if (lua_isstring(L, -1)) {
            zone->type = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // spawnChance
        lua_getfield(L, tableIdx, "spawnChance");
        if (lua_isnumber(L, -1)) {
            zone->spawnChance = static_cast<float>(lua_tonumber(L, -1));
        }
        lua_pop(L, 1);
        // vehicles (string or table)
        lua_getfield(L, tableIdx, "vehicles");
        if (lua_istable(L, -1)) {
            // vehicles as table of strings
            size_t len = lua_rawlen(L, -1);
            for (size_t i = 1; i <= len; ++i) {
                lua_rawgeti(L, -1, i);
                if (lua_isstring(L, -1)) {
                    zone->vehicles.push_back(lua_tostring(L, -1));
                }
                lua_pop(L, 1);
            }
        } else if (lua_isstring(L, -1)) {
            // vehicles as single string
            zone->vehicles.push_back(lua_tostring(L, -1));
        }
        lua_pop(L, 1);
        // any other fields can be parsed here as needed
    }
    addZone(zone);
    return zone;
}

void IsoMetaGrid::checkVehiclesZones() {
    // Validate and clean up VehicleZones
    std::vector<std::shared_ptr<VehicleZone>> validZones;
    for (const auto& zone : VehicleZones) {
        if (!zone) continue;
        // Example check: ensure zone is within grid bounds
        if (zone->x < minX * 300 || zone->x >= (maxX + 1) * 300 ||
            zone->y < minY * 300 || zone->y >= (maxY + 1) * 300) {
            continue; // skip invalid
        }
        // Optionally, check for duplicates or other invalid states here
        // Remove duplicates (same pointer or same bounds/type)
        bool isDuplicate = false;
        for (const auto& existing : validZones) {
            if (zone == existing) {
                isDuplicate = true;
                break;
            }
            // Optionally, check for same bounds/type
            if (zone->x == existing->x && zone->y == existing->y && zone->z == existing->z &&
                zone->w == existing->w && zone->h == existing->h && zone->type == existing->type) {
                isDuplicate = true;
                break;
            }
        }
        if (isDuplicate) continue;

        // Enable overlap check: skip zones that overlap with any already accepted zone at the same Z level
        for (const auto& existing : validZones) {
            if (zone->z == existing->z) {
                bool overlap = !(zone->x + zone->w <= existing->x || existing->x + existing->w <= zone->x ||
                                zone->y + zone->h <= existing->y || existing->y + existing->h <= zone->y);
                if (overlap) {
                    isDuplicate = true;
                    break;
                }
            }
        }
        if (isDuplicate) continue;
        validZones.push_back(zone);
    }
    VehicleZones = std::move(validZones);
}

// Lua 5.4.7 version: var8 is now lua_State* and tableIdx
Zone IsoMetaGrid::registerMannequinZone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, lua_State* L, int tableIdx) {
    // Create a MannequinZone and add it to the grid
    std::string name = sharedStrings.get(var1);
    std::string type = sharedStrings.get(var2);
    auto zone = std::make_shared<MannequinZone>(name, type, var3, var4, var5, var6, var7);

    // Parse options from Lua table at tableIdx
    if (L && tableIdx != 0) {
        // name (override)
        lua_getfield(L, tableIdx, "name");
        if (lua_isstring(L, -1)) {
            zone->name = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // type (override)
        lua_getfield(L, tableIdx, "type");
        if (lua_isstring(L, -1)) {
            zone->type = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // mannequinType
        lua_getfield(L, tableIdx, "mannequinType");
        if (lua_isstring(L, -1)) {
            zone->mannequinType = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // mannequinCount
        lua_getfield(L, tableIdx, "mannequinCount");
        if (lua_isinteger(L, -1)) {
            zone->mannequinCount = static_cast<int>(lua_tointeger(L, -1));
        }
        lua_pop(L, 1);
        // any other fields can be parsed here as needed
    }
    addZone(zone);
    return zone;
}
}

// Lua 5.4.7 version: var8 is now lua_State* and tableIdx
void IsoMetaGrid::registerRoomTone(const std::string& var1, const std::string& var2, int var3, int var4, int var5, int var6, int var7, lua_State* L, int tableIdx) {
    // Create a RoomToneZone and add it to the grid
    std::string name = sharedStrings.get(var1);
    std::string type = sharedStrings.get(var2);
    auto zone = std::make_shared<RoomToneZone>(name, type, var3, var4, var5, var6, var7);

    // Parse options from Lua table at tableIdx
    if (L && tableIdx != 0) {
        // name (override)
        lua_getfield(L, tableIdx, "name");
        if (lua_isstring(L, -1)) {
            zone->name = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // type (override)
        lua_getfield(L, tableIdx, "type");
        if (lua_isstring(L, -1)) {
            zone->type = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // toneType
        lua_getfield(L, tableIdx, "toneType");
        if (lua_isstring(L, -1)) {
            zone->toneType = lua_tostring(L, -1);
        }
        lua_pop(L, 1);
        // volume
        lua_getfield(L, tableIdx, "volume");
        if (lua_isnumber(L, -1)) {
            zone->volume = static_cast<float>(lua_tonumber(L, -1));
        }
        lua_pop(L, 1);
        // any other fields can be parsed here as needed
    }
    addZone(zone);
}

bool IsoMetaGrid::isZoneAbove(Zone var1, Zone var2, int var3, int var4, int var5) {
    // Implementation based on Java/C++ logic:
    // Returns true if var1 is directly above var2 (z+1), and their x/y rectangles overlap at (var3, var4, var5)
    if (!var1 || !var2) return false;
    // Check if var1 is one level above var2
    if (var1->z != var2->z + 1) return false;
    // Check if the given (var3, var4, var5) is within var1
    if (var3 < var1->x || var3 >= var1->x + var1->w) return false;
    if (var4 < var1->y || var4 >= var1->y + var1->h) return false;
    if (var5 != var1->z) return false;
    // Check if the same (x, y) is within var2 at z-1
    if (var3 < var2->x || var3 >= var2->x + var2->w) return false;
    if (var4 < var2->y || var4 >= var2->y + var2->h) return false;
    // All checks passed: var1 is above var2 at (var3, var4, var5)
    return true;
}

void IsoMetaGrid::save(ByteBuffer var1) {
    // Implementation based on Java/C++ logic:
    // Serializes all zones to the ByteBuffer (var1)
    // Write the number of zones
    var1.putInt(static_cast<int>(Zones.size()));
    // Write each zone
    for (const auto& zone : Zones) {
        if (!zone) continue;
        // Write zone fields to ByteBuffer (same as saveZone logic)
        var1.putString(zone->name);
        var1.putString(zone->type);
        var1.putInt(zone->x);
        var1.putInt(zone->y);
        var1.putInt(zone->z);
        var1.putInt(zone->w);
        var1.putInt(zone->h);
        var1.putString(zone->lotDirectory);
        var1.putInt(static_cast<int>(zone->geometryType));
        // Write points (polyline/polygon)
        var1.putInt(static_cast<int>(zone->points.size()));
        for (int pt : zone->points) {
            var1.putInt(pt);
        }
        var1.putInt(zone->polylineWidth);
        // Write isPreferredZoneForSquare
        var1.putBool(zone->isPreferredZoneForSquare);

        // Serialize additional fields for known zone types
        if (zone->type == "ParkingStall" || zone->type == "Vehicle" || zone->type == "TrafficJam") {
            // VehicleZone fields
            auto vzone = std::dynamic_pointer_cast<VehicleZone>(zone);
            if (vzone) {
                var1.putFloat(vzone->spawnChance);
                // Write vehicles vector
                var1.putInt(static_cast<int>(vzone->vehicles.size()));
                for (const auto& veh : vzone->vehicles) {
                    var1.putString(veh);
                }
            } else {
                var1.putFloat(0.0f);
                var1.putInt(0);
            }
        } else if (zone->type == "MannequinZone") {
            // MannequinZone fields
            auto mzone = std::dynamic_pointer_cast<MannequinZone>(zone);
            if (mzone) {
                var1.putString(mzone->mannequinType);
                var1.putInt(mzone->mannequinCount);
            } else {
                var1.putString("");
                var1.putInt(0);
            }
        } else if (zone->type == "RoomToneZone") {
            // RoomToneZone fields
            auto rzone = std::dynamic_pointer_cast<RoomToneZone>(zone);
            if (rzone) {
                var1.putString(rzone->toneType);
                var1.putFloat(rzone->volume);
            } else {
                var1.putString("");
                var1.putFloat(0.0f);
            }
        }
    }
}

void IsoMetaGrid::savePart(ByteBuffer var1, int var2, bool var3) {
    // Implementation based on Java/C++ logic:
    // Serializes only the zones belonging to the cell at index var2 (cellX, cellY)
    // If var3 is true, may filter further (e.g., only certain types or conditions)
    // Find cell coordinates from var2 (assume var2 is a linear index: cellY * width + cellX)
    int cellY = var2 / width;
    int cellX = var2 % width;
    IsoMetaCell cell = getCellData(cellX + minX, cellY + minY);
    std::vector<Zone> zonesToSave;
    if (cell) {
        zonesToSave = cell->getZones();
    }
    // Optionally filter zones if var3 is true (customize as needed)
    if (var3) {
        std::vector<Zone> filtered;
        for (const auto& zone : zonesToSave) {
            // Java logic: filter by type for partial save (e.g., only vehicle zones)
            if (zone && (zone->type == "ParkingStall" || zone->type == "Vehicle" || zone->type == "TrafficJam")) {
                filtered.push_back(zone);
            }
        }
        zonesToSave = std::move(filtered);
    }
    // Write the number of zones
    var1.putInt(static_cast<int>(zonesToSave.size()));
    // Write each zone (same as saveZone logic)
    for (const auto& zone : zonesToSave) {
        if (!zone) continue;
        var1.putString(zone->name);
        var1.putString(zone->type);
        var1.putInt(zone->x);
        var1.putInt(zone->y);
        var1.putInt(zone->z);
        var1.putInt(zone->w);
        var1.putInt(zone->h);
        var1.putString(zone->lotDirectory);
        var1.putInt(static_cast<int>(zone->geometryType));
        var1.putInt(static_cast<int>(zone->points.size()));
        for (int pt : zone->points) {
            var1.putInt(pt);
        }
        var1.putInt(zone->polylineWidth);
        var1.putBool(zone->isPreferredZoneForSquare);

        // Serialize additional fields for known zone types
        if (zone->type == "ParkingStall" || zone->type == "Vehicle" || zone->type == "TrafficJam") {
            auto vzone = std::dynamic_pointer_cast<VehicleZone>(zone);
            if (vzone) {
                var1.putFloat(vzone->spawnChance);
                var1.putInt(static_cast<int>(vzone->vehicles.size()));
                for (const auto& veh : vzone->vehicles) {
                    var1.putString(veh);
                }
            } else {
                var1.putFloat(0.0f);
                var1.putInt(0);
            }
        } else if (zone->type == "MannequinZone") {
            auto mzone = std::dynamic_pointer_cast<MannequinZone>(zone);
            if (mzone) {
                var1.putString(mzone->mannequinType);
                var1.putInt(mzone->mannequinCount);
            } else {
                var1.putString("");
                var1.putInt(0);
            }
        } else if (zone->type == "RoomToneZone") {
            auto rzone = std::dynamic_pointer_cast<RoomToneZone>(zone);
            if (rzone) {
                var1.putString(rzone->toneType);
                var1.putFloat(rzone->volume);
            } else {
                var1.putString("");
                var1.putFloat(0.0f);
            }
        }
    }
}

void IsoMetaGrid::load() {
    // Implementation based on Java/C++ logic:
    // Deserializes all zones from a file (e.g., "zones.bin") using ByteBuffer
    Zones.clear();
    // Open file for reading
    std::ifstream inFile("zones.bin", std::ios::binary);
    if (!inFile) {
        // File does not exist or cannot be opened
        return;
    }
    // Read file into a vector<char>
    std::vector<char> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    if (fileData.empty()) return;
    // Create ByteBuffer from file data
    ByteBuffer buffer(fileData.data(), static_cast<int>(fileData.size()));
    load(buffer);
}

void IsoMetaGrid::load(ByteBuffer var1) {
    // Implementation based on Java/C++ logic:
    // Deserializes all zones from the provided ByteBuffer (var1)
    Zones.clear();
    int zoneCount = var1.getInt();
    for (int i = 0; i < zoneCount; ++i) {
        loadZone(var1, i);
    }
}

int IsoMetaGrid::getWidth() {
    int IsoMetaGrid::getWidth() {
        return width;
    }
}

int IsoMetaGrid::getHeight() {
    int IsoMetaGrid::getHeight() {
        return height;
    }
}

IsoMetaCell IsoMetaGrid::getCellData(int var1, int var2) {
    IsoMetaCell IsoMetaGrid::getCellData(int x, int y) {
        if (x - minX >= 0 && y - minY >= 0 && x - minX < width && y - minY < height) {
            return Grid[x - minX][y - minY];
        }
        return nullptr;
    }
}

IsoMetaCell IsoMetaGrid::getCellDataAbs(int var1, int var2) {
    IsoMetaCell IsoMetaGrid::getCellDataAbs(int x, int y) {
        return Grid[x][y];
    }
}

IsoMetaCell IsoMetaGrid::getCurrentCellData() {
    IsoMetaCell IsoMetaGrid::getCurrentCellData() {
    // Implementation based on Java logic:
    // Get the current player (assume IsoPlayer::getInstance() or similar)
    IsoPlayer* player = IsoPlayer::getInstance();
    if (!player) return nullptr;
    int x = static_cast<int>(player->getX());
    int y = static_cast<int>(player->getY());
    int cellX = x / 300;
    int cellY = y / 300;
    return getCellData(cellX, cellY);
    }
}

IsoMetaCell IsoMetaGrid::getMetaGridFromTile(int var1, int var2) {
    IsoMetaCell IsoMetaGrid::getMetaGridFromTile(int x, int y) {
        int cx = x / 300;
        int cy = y / 300;
        return getCellData(cx, cy);
    }
}

IsoMetaChunk IsoMetaGrid::getCurrentChunkData() {
    IsoMetaChunk IsoMetaGrid::getCurrentChunkData() {
    // Implementation based on Java logic:
    // Get the current player (assume IsoPlayer::getInstance() or similar)
    IsoPlayer* player = IsoPlayer::getInstance();
    if (!player) return nullptr;
    int x = static_cast<int>(player->getX());
    int y = static_cast<int>(player->getY());
    return getChunkDataFromTile(x, y);
    }
}

IsoMetaChunk IsoMetaGrid::getChunkData(int var1, int var2) {
    IsoMetaChunk IsoMetaGrid::getChunkData(int x, int y) {
        float fx = static_cast<float>(x) / 30.0f;
        float fy = static_cast<float>(y) / 30.0f;
        if (fx < 0.0f) fx = static_cast<int>(fx) - 1;
        if (fy < 0.0f) fy = static_cast<int>(fy) - 1;
        int cx = static_cast<int>(fx);
        int cy = static_cast<int>(fy);
        IsoMetaCell cell = getCellData(cx, cy);
        return cell ? cell->getChunk(x - cx * 30, y - cy * 30) : nullptr;
    }
}

IsoMetaChunk IsoMetaGrid::getChunkDataFromTile(int var1, int var2) {
    IsoMetaChunk IsoMetaGrid::getChunkDataFromTile(int x, int y) {
        int cx = x / 10;
        int cy = y / 10;
        cx -= minX * 30;
        cy -= minY * 30;
        int cellX = cx / 30;
        int cellY = cy / 30;
        cx += minX * 30;
        cy += minY * 30;
        cellX += minX;
        cellY += minY;
        IsoMetaCell cell = getCellData(cellX, cellY);
        return cell ? cell->getChunk(cx - cellX * 30, cy - cellY * 30) : nullptr;
    }
}

bool IsoMetaGrid::isValidSquare(int var1, int var2) {
    bool IsoMetaGrid::isValidSquare(int x, int y) {
        if (x < minX * 300) return false;
        if (x >= (maxX + 1) * 300) return false;
        if (y < minY * 300) return false;
        return y < (maxY + 1) * 300;
    }
}

bool IsoMetaGrid::isValidChunk(int var1, int var2) {
    bool IsoMetaGrid::isValidChunk(int x, int y) {
        x *= 10;
        y *= 10;
        if (x < minX * 300) return false;
        if (x >= (maxX + 1) * 300) return false;
        if (y < minY * 300) return false;
        if (y >= (maxY + 1) * 300) return false;
        return Grid[x / 300 - minX][y / 300 - minY]->info != nullptr;
    }
}

void IsoMetaGrid::Create() {
    // Implementation based on Java/C++ logic:
    // Initializes the meta grid and all cells
    // Set up grid dimensions and allocate cells
    width = maxX - minX + 1;
    height = maxY - minY + 1;
    Grid.clear();
    Grid.resize(width);
    for (int x = 0; x < width; ++x) {
        Grid[x].resize(height);
        for (int y = 0; y < height; ++y) {
            Grid[x][y] = std::make_shared<IsoMetaCell>(x + minX, y + minY);
        }
    }
    // Clear all zone and building lists
    Zones.clear();
    VehicleZones.clear();
    Buildings.clear();
    RoomZones.clear();
    MannequinZones.clear();
    RoomToneZones.clear();
}

void IsoMetaGrid::CreateStep1() {
    // Implementation based on Java/C++ logic:
    // Step 1: Initialize the grid and all cells
    Create();
    // Additional first-step initialization can be added here if needed
}

void IsoMetaGrid::CreateStep2() {
    // Implementation based on Java/C++ logic:
    // Step 2: Process zones for all cells
    processZones();
}

void IsoMetaGrid::Dispose() {
    // Implementation based on Java/C++ logic:
    // Dispose of all grid, zone, and building data
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            Grid[x][y].reset();
        }
    }
    Grid.clear();
    Zones.clear();
    VehicleZones.clear();
    Buildings.clear();
    RoomZones.clear();
    MannequinZones.clear();
    RoomToneZones.clear();
}

Vector2 IsoMetaGrid::getRandomIndoorCoord() {
    // Implementation based on Java/C++ logic:
    // Pick a random RoomZone and return a random coordinate within it
    if (RoomZones.empty()) return nullptr;
    int idx = rand() % RoomZones.size();
    auto room = RoomZones[idx];
    if (!room) return nullptr;
    int x = room->x + (room->w > 0 ? rand() % room->w : 0);
    int y = room->y + (room->h > 0 ? rand() % room->h : 0);
    return std::make_shared<Vector2>(static_cast<float>(x), static_cast<float>(y));
}

RoomDef IsoMetaGrid::getRandomRoomBetweenRange(float var1, float var2, float var3, float var4) {
    // Implementation based on Java logic:
    // Returns a random RoomDef (RoomZone) whose bounds overlap the given rectangle (var1, var2, var3, var4)
    // (x1, y1, x2, y2) rectangle
    if (RoomZones.empty()) return nullptr;
    std::vector<RoomDef> candidates;
    int x1 = static_cast<int>(var1);
    int y1 = static_cast<int>(var2);
    int x2 = static_cast<int>(var3);
    int y2 = static_cast<int>(var4);
    if (x2 < x1) std::swap(x1, x2);
    if (y2 < y1) std::swap(y1, y2);
    for (const auto& room : RoomZones) {
        if (!room) continue;
        int rx1 = room->x;
        int ry1 = room->y;
        int rx2 = room->x + room->w - 1;
        int ry2 = room->y + room->h - 1;
        // Check for rectangle overlap
        if (rx1 > x2 || rx2 < x1 || ry1 > y2 || ry2 < y1) continue;
        candidates.push_back(room);
    }
    if (candidates.empty()) return nullptr;
    int idx = rand() % candidates.size();
    return candidates[idx];
}

RoomDef IsoMetaGrid::getRandomRoomNotInRange(float var1, float var2, int var3) {
    // Implementation based on Java logic:
    // Returns a random RoomDef (RoomZone) whose center is not within var3 units of (var1, var2)
    if (RoomZones.empty()) return nullptr;
    std::vector<RoomDef> candidates;
    float cx = var1;
    float cy = var2;
    int radius = var3;
    int radiusSq = radius * radius;
    for (const auto& room : RoomZones) {
        if (!room) continue;
        // Compute center of room
        float room_cx = room->x + (room->w > 0 ? room->w / 2.0f : 0.0f);
        float room_cy = room->y + (room->h > 0 ? room->h / 2.0f : 0.0f);
        float dx = room_cx - cx;
        float dy = room_cy - cy;
        float distSq = dx * dx + dy * dy;
        if (distSq > radiusSq) {
            candidates.push_back(room);
        }
    }
    if (candidates.empty()) return nullptr;
    int idx = rand() % candidates.size();
    return candidates[idx];
}

void IsoMetaGrid::save() {
    // Implementation based on Java/C++ logic:
    // Serializes all zones to persistent storage (file, etc.)
    ByteBuffer buffer;
    save(buffer);
    // Write buffer to file (zones.bin)
    std::ofstream outFile("zones.bin", std::ios::binary);
    if (outFile && buffer.size() > 0) {
        outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
        outFile.close();
    }
}

void IsoMetaGrid::loadZones() {
    // Implementation based on Java/C++ logic:
    // Reads all zones from a file (zones.bin) using ByteBuffer
    Zones.clear();
    std::ifstream inFile("zones.bin", std::ios::binary);
    if (!inFile) {
        // File does not exist or cannot be opened
        return;
    }
    std::vector<char> fileData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();
    if (fileData.empty()) return;
    ByteBuffer buffer(fileData.data(), static_cast<int>(fileData.size()));
    load(buffer);
}

void IsoMetaGrid::loadZone(ByteBuffer var1, int var2) {
    // Implementation based on Java/C++ logic:
    // Reads a single zone from ByteBuffer (var1)
    // var2 can be used as a version or index if needed
    std::string name = var1.getString();
    std::string type = var1.getString();
    int x = var1.getInt();
    int y = var1.getInt();
    int z = var1.getInt();
    int w = var1.getInt();
    int h = var1.getInt();
    std::string lotDirectory = var1.getString();
    ZoneGeometryType geometryType = static_cast<ZoneGeometryType>(var1.getInt());
    int pointsCount = var1.getInt();
    std::vector<int> points;
    for (int i = 0; i < pointsCount; ++i) {
        points.push_back(var1.getInt());
    }
    int polylineWidth = var1.getInt();
    bool isPreferred = var1.getBool();

    std::shared_ptr<Zone> zone;
    if (type == "ParkingStall" || type == "Vehicle" || type == "TrafficJam") {
        auto vzone = std::make_shared<VehicleZone>(name, type, x, y, z, w, h);
        vzone->lotDirectory = lotDirectory;
        vzone->geometryType = geometryType;
        vzone->points = points;
        vzone->polylineWidth = polylineWidth;
        vzone->isPreferredZoneForSquare = isPreferred;
        vzone->spawnChance = var1.getFloat();
        int vehiclesCount = var1.getInt();
        for (int i = 0; i < vehiclesCount; ++i) {
            vzone->vehicles.push_back(var1.getString());
        }
        zone = vzone;
    } else if (type == "MannequinZone") {
        auto mzone = std::make_shared<MannequinZone>(name, type, x, y, z, w, h);
        mzone->lotDirectory = lotDirectory;
        mzone->geometryType = geometryType;
        mzone->points = points;
        mzone->polylineWidth = polylineWidth;
        mzone->isPreferredZoneForSquare = isPreferred;
        mzone->mannequinType = var1.getString();
        mzone->mannequinCount = var1.getInt();
        zone = mzone;
    } else if (type == "RoomToneZone") {
        auto rzone = std::make_shared<RoomToneZone>(name, type, x, y, z, w, h);
        rzone->lotDirectory = lotDirectory;
        rzone->geometryType = geometryType;
        rzone->points = points;
        rzone->polylineWidth = polylineWidth;
        rzone->isPreferredZoneForSquare = isPreferred;
        rzone->toneType = var1.getString();
        rzone->volume = var1.getFloat();
        zone = rzone;
    } else {
        zone = std::make_shared<Zone>(name, type, x, y, z, w, h);
        zone->lotDirectory = lotDirectory;
        zone->geometryType = geometryType;
        zone->points = points;
        zone->polylineWidth = polylineWidth;
        zone->isPreferredZoneForSquare = isPreferred;
    }
    // Add to Zones and owning cell
    if (zone) {
        addZone(zone);
    }
}

void IsoMetaGrid::saveZone(ByteBuffer var1) {
    // Implementation based on Java/C++ logic:
    // Serializes a single zone to the ByteBuffer (var1)
    // For demonstration, serialize all zones in Zones vector (should be per-zone in real code)
    for (const auto& zone : Zones) {
        if (!zone) continue;
        // Write zone fields to ByteBuffer
        var1.putString(zone->name);
        var1.putString(zone->type);
        var1.putInt(zone->x);
        var1.putInt(zone->y);
        var1.putInt(zone->z);
        var1.putInt(zone->w);
        var1.putInt(zone->h);
        var1.putString(zone->lotDirectory);
        var1.putInt(static_cast<int>(zone->geometryType));
        // Write points (polyline/polygon)
        var1.putInt(static_cast<int>(zone->points.size()));
        for (int pt : zone->points) {
            var1.putInt(pt);
        }
        var1.putInt(zone->polylineWidth);
        // Write isPreferredZoneForSquare
        var1.putBool(zone->isPreferredZoneForSquare);

        // Serialize additional fields for known zone types
        if (zone->type == "ParkingStall" || zone->type == "Vehicle" || zone->type == "TrafficJam") {
            // VehicleZone fields
            auto vzone = std::dynamic_pointer_cast<VehicleZone>(zone);
            if (vzone) {
                var1.putFloat(vzone->spawnChance);
                // Write vehicles vector
                var1.putInt(static_cast<int>(vzone->vehicles.size()));
                for (const auto& veh : vzone->vehicles) {
                    var1.putString(veh);
                }
            } else {
                var1.putFloat(0.0f);
                var1.putInt(0);
            }
        } else if (zone->type == "MannequinZone") {
            // MannequinZone fields
            auto mzone = std::dynamic_pointer_cast<MannequinZone>(zone);
            if (mzone) {
                var1.putString(mzone->mannequinType);
                var1.putInt(mzone->mannequinCount);
            } else {
                var1.putString("");
                var1.putInt(0);
            }
        } else if (zone->type == "RoomToneZone") {
            // RoomToneZone fields
            auto rzone = std::dynamic_pointer_cast<RoomToneZone>(zone);
            if (rzone) {
                var1.putString(rzone->toneType);
                var1.putFloat(rzone->volume);
            } else {
                var1.putString("");
                var1.putFloat(0.0f);
            }
        }
    }
}

void IsoMetaGrid::getLotDirectories(const std::string& var1, std::vector<std::string> var2) {
    // Implementation based on Java/C++ logic:
    // Collect all unique lotDirectory strings from Zones whose type matches var1
    std::unordered_set<std::string> uniqueDirs;
    for (const auto& zone : Zones) {
        if (zone && zone->type == var1 && !zone->lotDirectory.empty()) {
            uniqueDirs.insert(zone->lotDirectory);
        }
    }
    for (const auto& dir : uniqueDirs) {
        var2.push_back(dir);
    }
}

bool IsoMetaGrid::isPreferredZoneForSquare(const std::string& var0) {
    // Implementation based on Java/C++ logic:
    // Returns true for zone types that are preferred for square selection
    // (e.g., 'Nav', 'Room', 'RoomDef', 'ParkingStall', 'Vehicle', 'TrafficJam', 'MannequinZone', 'RoomToneZone')
    if (var0.empty()) return false;
    static const std::vector<std::string> preferredTypes = {
        "Nav", "Room", "RoomDef", "ParkingStall", "Vehicle", "TrafficJam", "MannequinZone", "RoomToneZone"
    };
    for (const auto& type : preferredTypes) {
        if (var0 == type) return true;
    }
    return false;
}

} // namespace iso
} // namespace zombie
