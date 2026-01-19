#pragma once
#include <vector>
#include <memory>
#include <algorithm>

namespace zombie {
namespace building {

struct IVec3 {
 int x, y, z;
 IVec3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
 bool operator==(const IVec3& other) const { return x == other.x && y == other.y && z == other.z; }
};

struct Vec3 {
 float x, y, z;
 Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

enum class RoomType {
 BEDROOM,
 KITCHEN,
 BATHROOM,
 LIVING_ROOM,
 BASEMENT,
 ATTIC,
 HALLWAY,
 UNKNOWN
};

class IsoRoom {
public:
 IsoRoom(int id, RoomType type);
 ~IsoRoom() = default;
 
 int getId() const { return id; }
 RoomType getType() const { return roomType; }
 void setType(RoomType t) { roomType = t; }
 
 void addGridSquare(IVec3 pos);
 void removeGridSquare(IVec3 pos);
 
 const std::vector<IVec3>& getGridSquares() const { return gridSquares; }
 int getGridSquareCount() const noexcept { return gridSquares.size(); }
 
 bool isIndoor() const { return !gridSquares.empty(); }
 
private:
 int id;
 RoomType roomType;
 std::vector<IVec3> gridSquares;
};

class IsoBuilding {
public:
 IsoBuilding(int id);
 ~IsoBuilding() = default;
 
 int getId() const { return id; }
 
 std::shared_ptr<IsoRoom> createRoom(RoomType type);
 std::shared_ptr<IsoRoom> getRoom(int roomId);
 const std::vector<std::shared_ptr<IsoRoom>>& getRooms() const { return rooms; }
 
 void addWall(Vec3 pos);
 void addDoor(Vec3 pos);
 void addBarricade(Vec3 pos);
 
 int getWallCount() const noexcept { return walls.size(); }
 int getDoorCount() const noexcept { return doors.size(); }
 int getBarricadeCount() const noexcept { return barricades.size(); }
 
private:
 int id;
 std::vector<std::shared_ptr<IsoRoom>> rooms;
 std::vector<Vec3> walls;
 std::vector<Vec3> doors;
 std::vector<Vec3> barricades;
};

class BuildingManager {
public:
 static BuildingManager& getInstance() {
 static BuildingManager instance;
 return instance;
 }
 
 std::shared_ptr<IsoBuilding> createBuilding();
 std::shared_ptr<IsoBuilding> getBuilding(int id);
 const std::vector<std::shared_ptr<IsoBuilding>>& getBuildings() const { return buildings; }
 
private:
 BuildingManager() = default;
 ~BuildingManager() = default;
 
 std::vector<std::shared_ptr<IsoBuilding>> buildings;
 int nextBuildingId = 0;
};

} // namespace building
} // namespace zombie
