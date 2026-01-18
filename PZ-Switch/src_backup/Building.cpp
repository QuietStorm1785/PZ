#include "Building.h"

namespace zombie {
namespace building {

IsoRoom::IsoRoom(int id, RoomType type)
    : id(id), roomType(type) {
}

void IsoRoom::addGridSquare(IVec3 pos) {
    gridSquares.push_back(pos);
}

void IsoRoom::removeGridSquare(IVec3 pos) {
    auto it = std::find(gridSquares.begin(), gridSquares.end(), pos);
    if (it != gridSquares.end()) {
        gridSquares.erase(it);
    }
}

IsoBuilding::IsoBuilding(int id)
    : id(id) {
}

std::shared_ptr<IsoRoom> IsoBuilding::createRoom(RoomType type) {
    auto room = std::make_shared<IsoRoom>(rooms.size(), type);
    rooms.push_back(room);
    return room;
}

std::shared_ptr<IsoRoom> IsoBuilding::getRoom(int roomId) {
    if (roomId >= 0 && roomId < (int)rooms.size()) {
        return rooms[roomId];
    }
    return nullptr;
}

void IsoBuilding::addWall(Vec3 pos) {
    walls.push_back(pos);
}

void IsoBuilding::addDoor(Vec3 pos) {
    doors.push_back(pos);
}

void IsoBuilding::addBarricade(Vec3 pos) {
    barricades.push_back(pos);
}

std::shared_ptr<IsoBuilding> BuildingManager::createBuilding() {
    auto building = std::make_shared<IsoBuilding>(nextBuildingId++);
    buildings.push_back(building);
    return building;
}

std::shared_ptr<IsoBuilding> BuildingManager::getBuilding(int id) {
    for (auto& building : buildings) {
        if (building->getId() == id) {
            return building;
        }
    }
    return nullptr;
}

} // namespace building
} // namespace zombie
