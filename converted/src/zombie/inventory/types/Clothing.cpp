#include "zombie/inventory/types/Clothing.h"

namespace zombie {
namespace inventory {
namespace types {

std::string Clothing::getCategory() {
 // TODO: Implement getCategory
 return "";
}

public Clothing::Clothing(const std::string& module, const std::string& name, const std::string& itemType, const std::string& texName, const std::string& _palette, const std::string& _SpriteName) {
 // TODO: Implement Clothing
 return nullptr;
}

public Clothing::Clothing(const std::string& module, const std::string& name, const std::string& itemType, Item item, const std::string& _palette, const std::string& _SpriteName) {
 // TODO: Implement Clothing
 return nullptr;
}

bool Clothing::IsClothing() {
 // TODO: Implement IsClothing
 return false;
}

int Clothing::getSaveType() {
 // TODO: Implement getSaveType
 return 0;
}

void Clothing::Unwear() {
 // TODO: Implement Unwear
}

void Clothing::DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
 // TODO: Implement DoTooltip
}

bool Clothing::isDirty() {
 // TODO: Implement isDirty
 return false;
}

bool Clothing::isBloody() {
 // TODO: Implement isBloody
 return false;
}

std::string Clothing::getName() {
 // TODO: Implement getName
 return "";
}

void Clothing::update() {
 // TODO: Implement update
}

void Clothing::updateWetness() {
 // TODO: Implement updateWetness
}

void Clothing::updateWetness(bool bIgnoreEquipped) {
 // TODO: Implement updateWetness
}

float Clothing::getBulletDefense() {
 // TODO: Implement getBulletDefense
 return 0;
}

void Clothing::setBulletDefense(float _bulletDefense) {
 // TODO: Implement setBulletDefense
}

void Clothing::flushWetness() {
 // TODO: Implement flushWetness
}

bool Clothing::finishupdate() {
 // TODO: Implement finishupdate
 return false;
}

void Clothing::Use(bool bCrafting, bool bInContainer) {
 // TODO: Implement Use
}

bool Clothing::CanStack(InventoryItem item) {
 // TODO: Implement CanStack
 return false;
}

Clothing Clothing::CreateFromSprite(const std::string& Sprite) {
 // TODO: Implement CreateFromSprite
 return nullptr;
}

void Clothing::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

void Clothing::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

std::string Clothing::getSpriteName() {
 // TODO: Implement getSpriteName
 return "";
}

void Clothing::setSpriteName(const std::string& _SpriteName) {
 // TODO: Implement setSpriteName
}

std::string Clothing::getPalette() {
 // TODO: Implement getPalette
 return "";
}

void Clothing::setPalette(const std::string& _palette) {
 // TODO: Implement setPalette
}

float Clothing::getTemperature() {
 // TODO: Implement getTemperature
 return 0;
}

void Clothing::setTemperature(float _temperature) {
 // TODO: Implement setTemperature
}

void Clothing::setDirtyness(float delta) {
 // TODO: Implement setDirtyness
}

void Clothing::setBloodLevel(float delta) {
 // TODO: Implement setBloodLevel
}

float Clothing::getDirtyness() {
 // TODO: Implement getDirtyness
 return 0;
}

float Clothing::getBloodlevel() {
 // TODO: Implement getBloodlevel
 return 0;
}

float Clothing::getBloodlevelForPart(BloodBodyPartType part) {
 // TODO: Implement getBloodlevelForPart
 return 0;
}

float Clothing::getBloodLevel() {
 // TODO: Implement getBloodLevel
 return 0;
}

float Clothing::getBloodLevelForPart(BloodBodyPartType part) {
 // TODO: Implement getBloodLevelForPart
 return 0;
}

float Clothing::getWeight() {
 // TODO: Implement getWeight
 return 0;
}

void Clothing::setWetness(float percent) {
 // TODO: Implement setWetness
}

float Clothing::getWetness() {
 // TODO: Implement getWetness
 return 0;
}

float Clothing::getWeightWet() {
 // TODO: Implement getWeightWet
 return 0;
}

void Clothing::setWeightWet(float weight) {
 // TODO: Implement setWeightWet
}

int Clothing::getConditionLowerChance() {
 // TODO: Implement getConditionLowerChance
 return 0;
}

void Clothing::setConditionLowerChance(int conditionLowerChance) {
 // TODO: Implement setConditionLowerChance
}

void Clothing::setCondition(int Condition) {
 // TODO: Implement setCondition
}

float Clothing::getClothingDirtynessIncreaseLevel() {
 // TODO: Implement getClothingDirtynessIncreaseLevel
 return 0;
}

float Clothing::getInsulation() {
 // TODO: Implement getInsulation
 return 0;
}

void Clothing::setInsulation(float _insulation) {
 // TODO: Implement setInsulation
}

float Clothing::getStompPower() {
 // TODO: Implement getStompPower
 return 0;
}

void Clothing::setStompPower(float _stompPower) {
 // TODO: Implement setStompPower
}

float Clothing::getRunSpeedModifier() {
 // TODO: Implement getRunSpeedModifier
 return 0;
}

void Clothing::setRunSpeedModifier(float _runSpeedModifier) {
 // TODO: Implement setRunSpeedModifier
}

float Clothing::getCombatSpeedModifier() {
 // TODO: Implement getCombatSpeedModifier
 return 0;
}

void Clothing::setCombatSpeedModifier(float _combatSpeedModifier) {
 // TODO: Implement setCombatSpeedModifier
}

bool Clothing::isRemoveOnBroken() {
 // TODO: Implement isRemoveOnBroken
 return false;
}

void Clothing::setRemoveOnBroken(bool _removeOnBroken) {
 // TODO: Implement setRemoveOnBroken
}

bool Clothing::getCanHaveHoles() {
 // TODO: Implement getCanHaveHoles
 return false;
}

void Clothing::setCanHaveHoles(bool _canHaveHoles) {
 // TODO: Implement setCanHaveHoles
}

bool Clothing::isCosmetic() {
 // TODO: Implement isCosmetic
 return false;
}

std::string Clothing::toString() {
 // TODO: Implement toString
 return "";
}

float Clothing::getBiteDefense() {
 // TODO: Implement getBiteDefense
 return 0;
}

void Clothing::setBiteDefense(float _biteDefense) {
 // TODO: Implement setBiteDefense
}

float Clothing::getScratchDefense() {
 // TODO: Implement getScratchDefense
 return 0;
}

void Clothing::setScratchDefense(float _scratchDefense) {
 // TODO: Implement setScratchDefense
}

float Clothing::getNeckProtectionModifier() {
 // TODO: Implement getNeckProtectionModifier
 return 0;
}

void Clothing::setNeckProtectionModifier(float _neckProtectionModifier) {
 // TODO: Implement setNeckProtectionModifier
}

int Clothing::getChanceToFall() {
 // TODO: Implement getChanceToFall
 return 0;
}

void Clothing::setChanceToFall(int _chanceToFall) {
 // TODO: Implement setChanceToFall
}

float Clothing::getWindresistance() {
 // TODO: Implement getWindresistance
 return 0;
}

void Clothing::setWindresistance(float _windresistance) {
 // TODO: Implement setWindresistance
}

float Clothing::getWaterResistance() {
 // TODO: Implement getWaterResistance
 return 0;
}

void Clothing::setWaterResistance(float _waterResistance) {
 // TODO: Implement setWaterResistance
}

int Clothing::getHolesNumber() {
 // TODO: Implement getHolesNumber
 return 0;
}

int Clothing::getPatchesNumber() {
 // TODO: Implement getPatchesNumber
 return 0;
}

float Clothing::getDefForPart(BloodBodyPartType part, bool bite, bool bullet) {
 // TODO: Implement getDefForPart
 return 0;
}

int Clothing::getBiteDefenseFromItem(IsoGameCharacter chr, InventoryItem fabric) {
 // TODO: Implement getBiteDefenseFromItem
 return 0;
}

int Clothing::getScratchDefenseFromItem(IsoGameCharacter chr, InventoryItem fabric) {
 // TODO: Implement getScratchDefenseFromItem
 return 0;
}

void Clothing::removePatch(BloodBodyPartType part) {
 // TODO: Implement removePatch
}

bool Clothing::canFullyRestore(IsoGameCharacter chr, BloodBodyPartType part, InventoryItem fabric) {
 // TODO: Implement canFullyRestore
 return false;
}

void Clothing::addPatch(IsoGameCharacter chr, BloodBodyPartType part, InventoryItem fabric) {
 // TODO: Implement addPatch
}

int Clothing::getNbrOfCoveredParts() {
 // TODO: Implement getNbrOfCoveredParts
 return 0;
}

int Clothing::getCondLossPerHole() {
 // TODO: Implement getCondLossPerHole
 return 0;
}

void Clothing::copyPatchesTo(Clothing newClothing) {
 // TODO: Implement copyPatchesTo
}

std::string Clothing::getClothingExtraSubmenu() {
 // TODO: Implement getClothingExtraSubmenu
 return "";
}

bool Clothing::canBe3DRender() {
 // TODO: Implement canBe3DRender
 return false;
}

bool Clothing::isWorn() {
 // TODO: Implement isWorn
 return false;
}

std::string Clothing::getFabricTypeName() {
 // TODO: Implement getFabricTypeName
 return "";
}

int Clothing::getScratchDefense() {
 // TODO: Implement getScratchDefense
 return 0;
}

int Clothing::getBiteDefense() {
 // TODO: Implement getBiteDefense
 return 0;
}

int Clothing::getFabricType() {
 // TODO: Implement getFabricType
 return 0;
}

public Clothing::ClothingPatch() {
 // TODO: Implement ClothingPatch
 return nullptr;
}

public Clothing::ClothingPatch(int int0, int int1, bool boolean0) {
 // TODO: Implement ClothingPatch
 return nullptr;
}

void Clothing::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

void Clothing::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

void Clothing::save_old(ByteBuffer output, bool net) {
 // TODO: Implement save_old
}

void Clothing::load_old(ByteBuffer input, int WorldVersion, bool net) {
 // TODO: Implement load_old
}

private Clothing::ClothingPatchFabricType(int int1, const std::string& string1, int int2, int int3) {
 // TODO: Implement ClothingPatchFabricType
 return nullptr;
}

std::string Clothing::getType() {
 // TODO: Implement getType
 return "";
}

} // namespace types
} // namespace inventory
} // namespace zombie
