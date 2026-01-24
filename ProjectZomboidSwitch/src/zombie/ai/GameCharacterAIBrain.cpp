#include <string>
#include "zombie/ai/GameCharacterAIBrain.h"

namespace zombie {
namespace ai {

IsoGameCharacter GameCharacterAIBrain::getCharacter() {
    // Return the associated character
    DebugLog::AI.debug("GameCharacterAIBrain::getCharacter: called");
    return this->character;
}

public GameCharacterAIBrain::GameCharacterAIBrain(IsoGameCharacter var1) {
    // Constructor
    this->character = var1;
    DebugLog::AI.debug("GameCharacterAIBrain::GameCharacterAIBrain: constructed");
}

void GameCharacterAIBrain::update() {
    // No-op, but add debug
    DebugLog::AI.debug("GameCharacterAIBrain::update: called");
}

void GameCharacterAIBrain::postUpdateHuman(IsoPlayer var1) {
    // No-op, but add debug
    DebugLog::AI.debug("GameCharacterAIBrain::postUpdateHuman: called");
}

std::string GameCharacterAIBrain::getOrder() {
    // Return current order
    DebugLog::AI.debug("GameCharacterAIBrain::getOrder: called");
    return this->order;
}

void GameCharacterAIBrain::setOrder(const std::string& var1) {
    // Set current order
    this->order = var1;
    DebugLog::AI.debug("GameCharacterAIBrain::setOrder: set to %s", var1.c_str());
}

SurvivorGroup GameCharacterAIBrain::getGroup() {
    // Return group from character descriptor
    DebugLog::AI.debug("GameCharacterAIBrain::getGroup: called");
    return this->character->getDescriptor()->getGroup();
}

int GameCharacterAIBrain::getCloseZombieCount() {
    // Return number of close zombies
    DebugLog::AI.debug("GameCharacterAIBrain::getCloseZombieCount: called");
    this->character->getStats();
    return Stats::NumCloseZombies;
}

IsoZombie GameCharacterAIBrain::getClosestChasingZombie(bool var1) {
    // Find closest chasing zombie
    IsoZombie* closest = nullptr;
    float minDist = 1.0E7f;
    for (auto* zombie : this->chasingZombies) {
        float dist = zombie->DistTo(this->character);
        if (zombie->isOnFloor()) dist += 2.0f;
        if (dist < minDist) {
            minDist = dist;
            closest = zombie;
        }
    }
    DebugLog::AI.debug("GameCharacterAIBrain::getClosestChasingZombie: called");
    return closest;
}

IsoZombie GameCharacterAIBrain::getClosestChasingZombie() {
    // Overload: Find closest chasing zombie (default)
    return getClosestChasingZombie(false);
}

void GameCharacterAIBrain::AddBlockedMemory(int var1, int var2, int var3) {
    // Add blocked memory
    Vector3 key(var1, var2, var3);
    this->BlockedMemories[key] = std::vector<Vector3>();
    DebugLog::AI.debug("GameCharacterAIBrain::AddBlockedMemory: memory added");
}

bool GameCharacterAIBrain::HasBlockedMemory(int var1, int var2, int var3, int var4, int var5, int var6) {
    // Check for blocked memory
    Vector3 key(var1, var2, var3);
    bool hasMemory = this->BlockedMemories.find(key) != this->BlockedMemories.end();
    DebugLog::AI.debug("GameCharacterAIBrain::HasBlockedMemory: %s", hasMemory ? "true" : "false");
    return hasMemory;
}

void GameCharacterAIBrain::renderlast() {
    // No-op, but add debug
    DebugLog::AI.debug("GameCharacterAIBrain::renderlast: called");
}

} // namespace ai
} // namespace zombie
