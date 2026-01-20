#include <string>
#include "zombie\scripting\objects/Fixing.h"

namespace zombie {
namespace scripting {
namespace objects {

void Fixing::Load(const std::string& var1, std::string[] var2) {
    // TODO: Implement Load
}

std::string Fixing::getName() {
    // TODO: Implement getName
    return "";
}

void Fixing::setName(const std::string& var1) {
    // TODO: Implement setName
}

void Fixing::addRequiredItem(const std::string& var1) {
    // TODO: Implement addRequiredItem
}

Fixer Fixing::usedInFixer(InventoryItem var1, IsoGameCharacter var2) {
    // TODO: Implement usedInFixer
    return nullptr;
}

InventoryItem Fixing::haveGlobalItem(IsoGameCharacter var1) {
    // TODO: Implement haveGlobalItem
    return nullptr;
}

InventoryItem Fixing::haveThisFixer(IsoGameCharacter var1, Fixer var2, InventoryItem var3) {
    // TODO: Implement haveThisFixer
    return nullptr;
}

int Fixing::countUses(IsoGameCharacter var1, Fixer var2, InventoryItem var3) {
    // TODO: Implement countUses
    return 0;
}

int Fixing::countUses(InventoryItem var0) {
    // TODO: Implement countUses
    return 0;
}

Fixer Fixing::getGlobalItem() {
    // TODO: Implement getGlobalItem
    return nullptr;
}

void Fixing::setGlobalItem(Fixer var1) {
    // TODO: Implement setGlobalItem
}

float Fixing::getConditionModifier() {
    // TODO: Implement getConditionModifier
    return 0;
}

void Fixing::setConditionModifier(float var1) {
    // TODO: Implement setConditionModifier
}

} // namespace objects
} // namespace scripting
} // namespace zombie
