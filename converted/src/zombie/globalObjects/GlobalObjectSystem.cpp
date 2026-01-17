#include "zombie/globalObjects/GlobalObjectSystem.h"

namespace zombie {
namespace globalObjects {

std::string GlobalObjectSystem::getName() {
  // TODO: Implement getName
  return "";
}

KahluaTable GlobalObjectSystem::getModData() {
  // TODO: Implement getModData
  return nullptr;
}

GlobalObject GlobalObjectSystem::newObject(int x, int y, int z) {
  // TODO: Implement newObject
  return nullptr;
}

void GlobalObjectSystem::removeObject(GlobalObject object) {
  // TODO: Implement removeObject
}

GlobalObject GlobalObjectSystem::getObjectAt(int x, int y, int z) {
  // TODO: Implement getObjectAt
  return nullptr;
}

bool GlobalObjectSystem::hasObjectsInChunk(int wx, int wy) {
  // TODO: Implement hasObjectsInChunk
  return false;
}

int GlobalObjectSystem::getObjectCount() {
  // TODO: Implement getObjectCount
  return 0;
}

GlobalObject GlobalObjectSystem::getObjectByIndex(int index) {
  // TODO: Implement getObjectByIndex
  return nullptr;
}

void GlobalObjectSystem::finishedWithList(ArrayList<GlobalObject> list) {
  // TODO: Implement finishedWithList
}

void GlobalObjectSystem::Reset() {
  // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
