#include "zombie/globalObjects/CGlobalObjectSystem.h"

namespace zombie {
namespace globalObjects {

public
CGlobalObjectSystem::CGlobalObjectSystem(const std::string &name) {
  // TODO: Implement CGlobalObjectSystem
  return nullptr;
}

GlobalObject CGlobalObjectSystem::makeObject(int int0, int int1, int int2) {
  // TODO: Implement makeObject
  return nullptr;
}

void CGlobalObjectSystem::sendCommand(const std::string &command,
                                      IsoPlayer player, KahluaTable args) {
  // TODO: Implement sendCommand
}

void CGlobalObjectSystem::receiveServerCommand(const std::string &command,
                                               KahluaTable args) {
  // TODO: Implement receiveServerCommand
}

void CGlobalObjectSystem::receiveNewLuaObjectAt(int x, int y, int z,
                                                KahluaTable args) {
  // TODO: Implement receiveNewLuaObjectAt
}

void CGlobalObjectSystem::receiveRemoveLuaObjectAt(int x, int y, int z) {
  // TODO: Implement receiveRemoveLuaObjectAt
}

void CGlobalObjectSystem::receiveUpdateLuaObjectAt(int x, int y, int z,
                                                   KahluaTable args) {
  // TODO: Implement receiveUpdateLuaObjectAt
}

void CGlobalObjectSystem::Reset() {
  // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
