#include "zombie/characters/CharacterTimedActions/LuaTimedActionNew.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {

public
LuaTimedActionNew::LuaTimedActionNew(KahluaTable _table, IsoGameCharacter chr) {
  // TODO: Implement LuaTimedActionNew
  return nullptr;
}

void LuaTimedActionNew::waitToStart() {
  // TODO: Implement waitToStart
}

void LuaTimedActionNew::update() {
  // TODO: Implement update
}

bool LuaTimedActionNew::valid() {
  // TODO: Implement valid
  return false;
}

void LuaTimedActionNew::start() {
  // TODO: Implement start
}

void LuaTimedActionNew::stop() {
  // TODO: Implement stop
}

void LuaTimedActionNew::perform() {
  // TODO: Implement perform
}

void LuaTimedActionNew::Failed(Mover mover) {
  // TODO: Implement Failed
}

void LuaTimedActionNew::Succeeded(Path path, Mover mover) {
  // TODO: Implement Succeeded
}

void LuaTimedActionNew::Pathfind(IsoGameCharacter chr, int x, int y, int z) {
  // TODO: Implement Pathfind
}

std::string LuaTimedActionNew::getName() {
  // TODO: Implement getName
  return "";
}

void LuaTimedActionNew::setCurrentTime(float time) {
  // TODO: Implement setCurrentTime
}

void LuaTimedActionNew::setTime(int maxTime) {
  // TODO: Implement setTime
}

void LuaTimedActionNew::OnAnimEvent(AnimEvent event) {
  // TODO: Implement OnAnimEvent
}

std::string LuaTimedActionNew::getMetaType() {
  // TODO: Implement getMetaType
  return "";
}

} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
