#include "zombie/inventory/types/DrainableComboItem.h"

namespace zombie {
namespace inventory {
namespace types {

public
DrainableComboItem::DrainableComboItem(const std::string &module,
 const std::string &name,
 const std::string &itemType,
 const std::string &texName) {
 // TODO: Implement DrainableComboItem
 return nullptr;
}

public
DrainableComboItem::DrainableComboItem(const std::string &module,
 const std::string &name,
 const std::string &itemType, Item item) {
 // TODO: Implement DrainableComboItem
 return nullptr;
}

bool DrainableComboItem::IsDrainable() {
 // TODO: Implement IsDrainable
 return false;
}

int DrainableComboItem::getSaveType() {
 // TODO: Implement getSaveType
 return 0;
}

bool DrainableComboItem::CanStack(InventoryItem item) {
 // TODO: Implement CanStack
 return false;
}

float DrainableComboItem::getUsedDelta() {
 // TODO: Implement getUsedDelta
 return 0;
}

int DrainableComboItem::getDrainableUsesInt() {
 // TODO: Implement getDrainableUsesInt
 return 0;
}

float DrainableComboItem::getDrainableUsesFloat() {
 // TODO: Implement getDrainableUsesFloat
 return 0;
}

void DrainableComboItem::render() {
 // TODO: Implement render
}

void DrainableComboItem::renderlast() {
 // TODO: Implement renderlast
}

void DrainableComboItem::setUsedDelta(float usedDelta) {
 // TODO: Implement setUsedDelta
}

bool DrainableComboItem::shouldUpdateInWorld() {
 // TODO: Implement shouldUpdateInWorld
 return false;
}

void DrainableComboItem::update() {
 // TODO: Implement update
}

void DrainableComboItem::Use() {
 // TODO: Implement Use
}

void DrainableComboItem::updateWeight() {
 // TODO: Implement updateWeight
}

float DrainableComboItem::getWeightEmpty() {
 // TODO: Implement getWeightEmpty
 return 0;
}

void DrainableComboItem::setWeightEmpty(float weight) {
 // TODO: Implement setWeightEmpty
}

bool DrainableComboItem::isUseWhileEquiped() {
 // TODO: Implement isUseWhileEquiped
 return false;
}

void DrainableComboItem::setUseWhileEquiped(bool _bUseWhileEquiped) {
 // TODO: Implement setUseWhileEquiped
}

bool DrainableComboItem::isUseWhileUnequiped() {
 // TODO: Implement isUseWhileUnequiped
 return false;
}

void DrainableComboItem::setUseWhileUnequiped(bool _bUseWhileUnequiped) {
 // TODO: Implement setUseWhileUnequiped
}

int DrainableComboItem::getTicksPerEquipUse() {
 // TODO: Implement getTicksPerEquipUse
 return 0;
}

void DrainableComboItem::setTicksPerEquipUse(int _ticksPerEquipUse) {
 // TODO: Implement setTicksPerEquipUse
}

float DrainableComboItem::getUseDelta() {
 // TODO: Implement getUseDelta
 return 0;
}

void DrainableComboItem::setUseDelta(float _useDelta) {
 // TODO: Implement setUseDelta
}

float DrainableComboItem::getDelta() {
 // TODO: Implement getDelta
 return 0;
}

void DrainableComboItem::setDelta(float _delta) {
 // TODO: Implement setDelta
}

float DrainableComboItem::getTicks() {
 // TODO: Implement getTicks
 return 0;
}

void DrainableComboItem::setTicks(float _ticks) {
 // TODO: Implement setTicks
}

void DrainableComboItem::setReplaceOnDeplete(
 const std::string &_ReplaceOnDeplete) {
 // TODO: Implement setReplaceOnDeplete
}

std::string DrainableComboItem::getReplaceOnDeplete() {
 // TODO: Implement getReplaceOnDeplete
 return "";
}

std::string DrainableComboItem::getReplaceOnDepleteFullType() {
 // TODO: Implement getReplaceOnDepleteFullType
 return "";
}

void DrainableComboItem::setHeat(float heat) {
 // TODO: Implement setHeat
}

float DrainableComboItem::getHeat() {
 // TODO: Implement getHeat
 return 0;
}

float DrainableComboItem::getInvHeat() {
 // TODO: Implement getInvHeat
 return 0;
}

bool DrainableComboItem::finishupdate() {
 // TODO: Implement finishupdate
 return false;
}

int DrainableComboItem::getRemainingUses() {
 // TODO: Implement getRemainingUses
 return 0;
}

float DrainableComboItem::getRainFactor() {
 // TODO: Implement getRainFactor
 return 0;
}

void DrainableComboItem::setRainFactor(float _rainFactor) {
 // TODO: Implement setRainFactor
}

bool DrainableComboItem::canConsolidate() {
 // TODO: Implement canConsolidate
 return false;
}

void DrainableComboItem::setCanConsolidate(bool _canConsolidate) {
 // TODO: Implement setCanConsolidate
}

void DrainableComboItem::setReplaceOnCooked(List<String> replaceOnCooked) {
 // TODO: Implement setReplaceOnCooked
}

std::string DrainableComboItem::getOnCooked() {
 // TODO: Implement getOnCooked
 return "";
}

void DrainableComboItem::setOnCooked(const std::string &onCooked) {
 // TODO: Implement setOnCooked
}

} // namespace types
} // namespace inventory
} // namespace zombie
