#include <string>
#include "zombie\Lua/MapObjects.h"

namespace zombie {
namespace Lua {

Callback MapObjects::getOnNew(const std::string& var0) {
    // TODO: Implement getOnNew
    return nullptr;
}

void MapObjects::OnNewWithSprite(const std::string& var0, LuaClosure var1, int var2) {
    // TODO: Implement OnNewWithSprite
}

void MapObjects::OnNewWithSprite(KahluaTable var0, LuaClosure var1, int var2) {
    // TODO: Implement OnNewWithSprite
}

void MapObjects::newGridSquare(IsoGridSquare var0) {
    // TODO: Implement newGridSquare
}

Callback MapObjects::getOnLoad(const std::string& var0) {
    // TODO: Implement getOnLoad
    return nullptr;
}

void MapObjects::OnLoadWithSprite(const std::string& var0, LuaClosure var1, int var2) {
    // TODO: Implement OnLoadWithSprite
}

void MapObjects::OnLoadWithSprite(KahluaTable var0, LuaClosure var1, int var2) {
    // TODO: Implement OnLoadWithSprite
}

void MapObjects::loadGridSquare(IsoGridSquare var0) {
    // TODO: Implement loadGridSquare
}

void MapObjects::debugNewSquare(int var0, int var1, int var2) {
    // TODO: Implement debugNewSquare
}

void MapObjects::debugLoadSquare(int var0, int var1, int var2) {
    // TODO: Implement debugLoadSquare
}

void MapObjects::debugLoadChunk(int var0, int var1) {
    // TODO: Implement debugLoadChunk
}

void MapObjects::reroute(Prototype var0, LuaClosure var1) {
    // TODO: Implement reroute
}

void MapObjects::Reset() {
    // TODO: Implement Reset
}

} // namespace Lua
} // namespace zombie
