#include "zombie/ai/GameCharacterAIBrain.h"

namespace zombie {
namespace ai {

IsoGameCharacter GameCharacterAIBrain::getCharacter() {
 // TODO: Implement getCharacter
 return nullptr;
}

public GameCharacterAIBrain::GameCharacterAIBrain(IsoGameCharacter _character) {
 // TODO: Implement GameCharacterAIBrain
 return nullptr;
}

void GameCharacterAIBrain::update() {
 // TODO: Implement update
}

void GameCharacterAIBrain::postUpdateHuman(IsoPlayer isoPlayer) {
 // TODO: Implement postUpdateHuman
}

std::string GameCharacterAIBrain::getOrder() {
 // TODO: Implement getOrder
 return "";
}

void GameCharacterAIBrain::setOrder(const std::string& _order) {
 // TODO: Implement setOrder
}

SurvivorGroup GameCharacterAIBrain::getGroup() {
 // TODO: Implement getGroup
 return nullptr;
}

int GameCharacterAIBrain::getCloseZombieCount() {
 // TODO: Implement getCloseZombieCount
 return 0;
}

IsoZombie GameCharacterAIBrain::getClosestChasingZombie(bool recurse) {
 // TODO: Implement getClosestChasingZombie
 return nullptr;
}

IsoZombie GameCharacterAIBrain::getClosestChasingZombie() {
 // TODO: Implement getClosestChasingZombie
 return nullptr;
}

void GameCharacterAIBrain::AddBlockedMemory(int ttx, int tty, int ttz) {
 // TODO: Implement AddBlockedMemory
}

bool GameCharacterAIBrain::HasBlockedMemory(int lx, int ly, int lz, int x, int y, int z) {
 // TODO: Implement HasBlockedMemory
 return false;
}

void GameCharacterAIBrain::renderlast() {
 // TODO: Implement renderlast
}

} // namespace ai
} // namespace zombie
