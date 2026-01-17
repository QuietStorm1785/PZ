#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace iso {

public
RoomDef::RoomDef(int _ID, const std::string &_name) {
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

bool RoomDef::isInside(int _x, int _y, int z) {
  // TODO: Implement isInside
  return false;
}

bool RoomDef::intersects(int _x, int _y, int w, int h) {
  // TODO: Implement intersects
  return false;
}

float RoomDef::getAreaOverlapping(IsoChunk chunk) {
  // TODO: Implement getAreaOverlapping
  return 0;
}

float RoomDef::getAreaOverlapping(int _x, int _y, int w, int h) {
  // TODO: Implement getAreaOverlapping
  return 0;
}

void RoomDef::forEachChunk(IsoChunk > consumer) {
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

void RoomDef::setBuilding(BuildingDef def) {
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

long RoomDef::calculateMetaID(int cellX, int cellY) {
  // TODO: Implement calculateMetaID
  return 0;
}

int RoomDef::getArea() {
  // TODO: Implement getArea
  return 0;
}

void RoomDef::setExplored(bool explored) {
  // TODO: Implement setExplored
}

IsoGridSquare RoomDef::getFreeSquare() {
  // TODO: Implement getFreeSquare
  return nullptr;
}

IsoGridSquare RoomDef::getRandomSquare(Predicate<IsoGridSquare> predicate) {
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

void RoomDef::setRoofFixed(bool b) {
  // TODO: Implement setRoofFixed
}

float RoomDef::getClosestPoint(float _x, float _y, Vector2f closestXY) {
  // TODO: Implement getClosestPoint
  return 0;
}

void RoomDef::Dispose() {
  // TODO: Implement Dispose
}

public
RoomDef::RoomRect(int _x, int _y, int _w, int _h) {
  // TODO: Implement RoomRect
  return nullptr;
}

int RoomDef::getX() {
  // TODO: Implement getX
  return 0;
}

int RoomDef::getY() {
  // TODO: Implement getY
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

float RoomDef::getClosestPoint(float _x, float _y, Vector2f closestXY) {
  // TODO: Implement getClosestPoint
  return 0;
}

float RoomDef::getClosestPointOnEdge(float float3, float float1, float float2,
                                     float float0, float float5, float float4,
                                     float float6, Vector2f vector2f) {
  // TODO: Implement getClosestPointOnEdge
  return 0;
}

} // namespace iso
} // namespace zombie
