#include <string>
#include "zombie/globalObjects/CGlobalObjectSystem.h"

namespace zombie {
namespace globalObjects {

public CGlobalObjectSystem::CGlobalObjectSystem(const std::string& var1) {
    // TODO: Implement CGlobalObjectSystem
    return nullptr;
}

GlobalObject CGlobalObjectSystem::makeObject(int var1, int var2, int var3) {
    // TODO: Implement makeObject
    return nullptr;
}

void CGlobalObjectSystem::sendCommand(const std::string& var1, IsoPlayer var2, KahluaTable var3) {
    // TODO: Implement sendCommand
}

void CGlobalObjectSystem::receiveServerCommand(const std::string& var1, KahluaTable var2) {
    // TODO: Implement receiveServerCommand
}

void CGlobalObjectSystem::receiveNewLuaObjectAt(int var1, int var2, int var3, KahluaTable var4) {
    // TODO: Implement receiveNewLuaObjectAt
}

void CGlobalObjectSystem::receiveRemoveLuaObjectAt(int var1, int var2, int var3) {
    // TODO: Implement receiveRemoveLuaObjectAt
}

void CGlobalObjectSystem::receiveUpdateLuaObjectAt(int var1, int var2, int var3, KahluaTable var4) {
    // TODO: Implement receiveUpdateLuaObjectAt
}

void CGlobalObjectSystem::Reset() {
    // TODO: Implement Reset
}

} // namespace globalObjects
} // namespace zombie
