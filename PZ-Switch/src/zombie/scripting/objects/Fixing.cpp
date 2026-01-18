#include "zombie/scripting/objects/Fixing.h"

namespace zombie {
namespace scripting {
namespace objects {

void Fixing::Load(const std::string &string0, String[] strings0) {
 // TODO: Implement Load
}

std::string Fixing::getName() {
 // TODO: Implement getName
 return "";
}

void Fixing::setName(const std::string &_name) {
 // TODO: Implement setName
}

void Fixing::addRequiredItem(const std::string &_require) {
 // TODO: Implement addRequiredItem
}

InventoryItem Fixing::haveGlobalItem(IsoGameCharacter chr) {
 // TODO: Implement haveGlobalItem
 return nullptr;
}

InventoryItem Fixing::haveThisFixer(IsoGameCharacter chr, Fixing.Fixer fixer,
 InventoryItem brokenObject) {
 // TODO: Implement haveThisFixer
 return nullptr;
}

int Fixing::countUses(IsoGameCharacter chr, Fixing.Fixer fixer,
 InventoryItem brokenObject) {
 // TODO: Implement countUses
 return 0;
}

int Fixing::countUses(InventoryItem item) {
 // TODO: Implement countUses
 return 0;
}

void Fixing::setGlobalItem(Fixing.Fixer _globalItem) {
 // TODO: Implement setGlobalItem
}

float Fixing::getConditionModifier() {
 // TODO: Implement getConditionModifier
 return 0;
}

void Fixing::setConditionModifier(float _conditionModifier) {
 // TODO: Implement setConditionModifier
}

public
Fixing::Fixer(const std::string &name, LinkedList<Fixing.FixerSkill> _skills,
 int _numberOfUse) {
 // TODO: Implement Fixer
 return nullptr;
}

std::string Fixing::getFixerName() {
 // TODO: Implement getFixerName
 return "";
}

int Fixing::getNumberOfUse() {
 // TODO: Implement getNumberOfUse
 return 0;
}

public
Fixing::FixerSkill(const std::string &_skillName, int _skillLvl) {
 // TODO: Implement FixerSkill
 return nullptr;
}

std::string Fixing::getSkillName() {
 // TODO: Implement getSkillName
 return "";
}

int Fixing::getSkillLevel() {
 // TODO: Implement getSkillLevel
 return 0;
}

bool Fixing::test(InventoryItem arg0) {
 // TODO: Implement test
 return false;
}

} // namespace objects
} // namespace scripting
} // namespace zombie
