#include "zombie/iso/BuildingDef.h"

namespace zombie {
namespace iso {

public
BuildingDef::BuildingDef() {
  // TODO: Implement BuildingDef
  return nullptr;
}

KahluaTable BuildingDef::getTable() {
  // TODO: Implement getTable
  return nullptr;
}

RoomDef BuildingDef::getRoom(const std::string &roomName) {
  // TODO: Implement getRoom
  return nullptr;
}

bool BuildingDef::isAllExplored() {
  // TODO: Implement isAllExplored
  return false;
}

void BuildingDef::setAllExplored(bool b) {
  // TODO: Implement setAllExplored
}

RoomDef BuildingDef::getFirstRoom() {
  // TODO: Implement getFirstRoom
  return nullptr;
}

int BuildingDef::getChunkX() {
  // TODO: Implement getChunkX
  return 0;
}

int BuildingDef::getChunkY() {
  // TODO: Implement getChunkY
  return 0;
}

int BuildingDef::getX() {
  // TODO: Implement getX
  return 0;
}

int BuildingDef::getY() {
  // TODO: Implement getY
  return 0;
}

int BuildingDef::getX2() {
  // TODO: Implement getX2
  return 0;
}

int BuildingDef::getY2() {
  // TODO: Implement getY2
  return 0;
}

int BuildingDef::getW() {
  // TODO: Implement getW
  return 0;
}

int BuildingDef::getH() {
  // TODO: Implement getH
  return 0;
}

int BuildingDef::getID() {
  // TODO: Implement getID
  return 0;
}

void BuildingDef::refreshSquares() {
  // TODO: Implement refreshSquares
}

void BuildingDef::CalculateBounds(ArrayList<RoomDef> tempRooms) {
  // TODO: Implement CalculateBounds
}

long BuildingDef::calculateMetaID(int cellX, int cellY) {
  // TODO: Implement calculateMetaID
  return 0;
}

void BuildingDef::recalculate() {
  // TODO: Implement recalculate
}

bool BuildingDef::overlapsChunk(int wx, int wy) {
  // TODO: Implement overlapsChunk
  return false;
}

IsoGridSquare BuildingDef::getFreeSquareInRoom() {
  // TODO: Implement getFreeSquareInRoom
  return nullptr;
}

bool BuildingDef::containsRoom(const std::string &name) {
  // TODO: Implement containsRoom
  return false;
}

bool BuildingDef::isFullyStreamedIn() {
  // TODO: Implement isFullyStreamedIn
  return false;
}

bool BuildingDef::isAnyChunkNewlyLoaded() {
  // TODO: Implement isAnyChunkNewlyLoaded
  return false;
}

int BuildingDef::getKeyId() {
  // TODO: Implement getKeyId
  return 0;
}

void BuildingDef::setKeyId(int _keyId) {
  // TODO: Implement setKeyId
}

int BuildingDef::getKeySpawned() {
  // TODO: Implement getKeySpawned
  return 0;
}

void BuildingDef::setKeySpawned(int _keySpawned) {
  // TODO: Implement setKeySpawned
}

bool BuildingDef::isHasBeenVisited() {
  // TODO: Implement isHasBeenVisited
  return false;
}

void BuildingDef::setHasBeenVisited(bool _hasBeenVisited) {
  // TODO: Implement setHasBeenVisited
}

bool BuildingDef::isAlarmed() {
  // TODO: Implement isAlarmed
  return false;
}

void BuildingDef::setAlarmed(bool alarm) {
  // TODO: Implement setAlarmed
}

RoomDef BuildingDef::getRandomRoom(int minArea) {
  // TODO: Implement getRandomRoom
  return nullptr;
}

float BuildingDef::getClosestPoint(float _x, float _y, Vector2f closestXY) {
  // TODO: Implement getClosestPoint
  return 0;
}

void BuildingDef::Dispose() {
  // TODO: Implement Dispose
}

} // namespace iso
} // namespace zombie
