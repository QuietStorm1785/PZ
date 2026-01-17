#include "zombie/Lua/MapObjects.h"

namespace zombie {
namespace Lua {

void MapObjects::OnNewWithSprite(const std::string &spriteName,
                                 LuaClosure __function__, int priority) {
  // TODO: Implement OnNewWithSprite
}

void MapObjects::OnNewWithSprite(KahluaTable spriteNames,
                                 LuaClosure __function__, int priority) {
  // TODO: Implement OnNewWithSprite
}

void MapObjects::newGridSquare(IsoGridSquare square) {
  // TODO: Implement newGridSquare
}

void MapObjects::OnLoadWithSprite(const std::string &spriteName,
                                  LuaClosure __function__, int priority) {
  // TODO: Implement OnLoadWithSprite
}

void MapObjects::OnLoadWithSprite(KahluaTable spriteNames,
                                  LuaClosure __function__, int priority) {
  // TODO: Implement OnLoadWithSprite
}

void MapObjects::loadGridSquare(IsoGridSquare square) {
  // TODO: Implement loadGridSquare
}

void MapObjects::debugNewSquare(int x, int y, int z) {
  // TODO: Implement debugNewSquare
}

void MapObjects::debugLoadSquare(int x, int y, int z) {
  // TODO: Implement debugLoadSquare
}

void MapObjects::debugLoadChunk(int wx, int wy) {
  // TODO: Implement debugLoadChunk
}

void MapObjects::reroute(Prototype prototype, LuaClosure luaClosure) {
  // TODO: Implement reroute
}

void MapObjects::Reset() {
  // TODO: Implement Reset
}

} // namespace Lua
} // namespace zombie
