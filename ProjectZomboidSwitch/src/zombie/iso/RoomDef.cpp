#include <string>
#include "zombie\iso/RoomDef.h"

namespace zombie {
namespace iso {

public RoomDef::RoomDef(int var1, const std::string& var2) {
    // TODO: Implement RoomDef
    return nullptr;
}

int RoomDef::getID() {
    // TODO: Implement getID
    return 0;
}

bool RoomDef::isExplored() {
    // TODO: Implement isExplored
    return false;
}

bool RoomDef::isInside(int var1, int var2, int var3) {
    // TODO: Implement isInside
    return false;
}

bool RoomDef::intersects(int var1, int var2, int var3, int var4) {
    // TODO: Implement intersects
    return false;
}

float RoomDef::getAreaOverlapping(IsoChunk var1) {
    // TODO: Implement getAreaOverlapping
    return 0;
}

float RoomDef::getAreaOverlapping(int var1, int var2, int var3, int var4) {
    // TODO: Implement getAreaOverlapping
    return 0;
}

void RoomDef::forEachChunk(IsoChunk> var1) {
    // TODO: Implement forEachChunk
}

IsoRoom RoomDef::getIsoRoom() {
    // TODO: Implement getIsoRoom
    return nullptr;
}

void RoomDef::refreshSquares() {
    // TODO: Implement refreshSquares
}

BuildingDef RoomDef::getBuilding() {
    // TODO: Implement getBuilding
    return nullptr;
}

void RoomDef::setBuilding(BuildingDef var1) {
    // TODO: Implement setBuilding
}

std::string RoomDef::getName() {
    // TODO: Implement getName
    return "";
}

int RoomDef::getY() {
    // TODO: Implement getY
    return 0;
}

int RoomDef::getX() {
    // TODO: Implement getX
    return 0;
}

int RoomDef::getX2() {
    // TODO: Implement getX2
    return 0;
}

int RoomDef::getY2() {
    // TODO: Implement getY2
    return 0;
}

int RoomDef::getW() {
    // TODO: Implement getW
    return 0;
}

int RoomDef::getH() {
    // TODO: Implement getH
    return 0;
}

int RoomDef::getZ() {
    // TODO: Implement getZ
    return 0;
}

void RoomDef::CalculateBounds() {
    // TODO: Implement CalculateBounds
}

long RoomDef::calculateMetaID(int var1, int var2) {
    // TODO: Implement calculateMetaID
    return 0;
}

int RoomDef::getArea() {
    // TODO: Implement getArea
    return 0;
}

void RoomDef::setExplored(bool var1) {
    // TODO: Implement setExplored
}

IsoGridSquare RoomDef::getFreeSquare() {
    // TODO: Implement getFreeSquare
    return nullptr;
}

IsoGridSquare RoomDef::getRandomSquare(Predicate<IsoGridSquare> var1) {
    // TODO: Implement getRandomSquare
    return nullptr;
}

bool RoomDef::isEmptyOutside() {
    // TODO: Implement isEmptyOutside
    return false;
}

bool RoomDef::isRoofFixed() {
    // TODO: Implement isRoofFixed
    return false;
}

void RoomDef::setRoofFixed(bool var1) {
    // TODO: Implement setRoofFixed
}

float RoomDef::getClosestPoint(float var1, float var2, Vector2f var3) {
    // TODO: Implement getClosestPoint
    return 0;
}

void RoomDef::Dispose() {
    // TODO: Implement Dispose
}

} // namespace iso
} // namespace zombie
