#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace inventory {

int InventoryItem::getSaveType() {
 // TODO: Implement getSaveType
 return 0;
}

IsoWorldInventoryObject InventoryItem::getWorldItem() {
 // TODO: Implement getWorldItem
 return nullptr;
}

void InventoryItem::setEquipParent(IsoGameCharacter parent) {
 // TODO: Implement setEquipParent
}

IsoGameCharacter InventoryItem::getEquipParent() {
 // TODO: Implement getEquipParent
 return nullptr;
}

std::string InventoryItem::getBringToBearSound() {
 // TODO: Implement getBringToBearSound
 return "";
}

std::string InventoryItem::getEquipSound() {
 // TODO: Implement getEquipSound
 return "";
}

std::string InventoryItem::getUnequipSound() {
 // TODO: Implement getUnequipSound
 return "";
}

void InventoryItem::setWorldItem(IsoWorldInventoryObject w) {
 // TODO: Implement setWorldItem
}

void InventoryItem::setJobDelta(float delta) {
 // TODO: Implement setJobDelta
}

float InventoryItem::getJobDelta() {
 // TODO: Implement getJobDelta
 return 0;
}

void InventoryItem::setJobType(const std::string& _type) {
 // TODO: Implement setJobType
}

std::string InventoryItem::getJobType() {
 // TODO: Implement getJobType
 return "";
}

bool InventoryItem::hasModData() {
 // TODO: Implement hasModData
 return false;
}

KahluaTable InventoryItem::getModData() {
 // TODO: Implement getModData
 return nullptr;
}

void InventoryItem::storeInByteData(IsoObject o) {
 // TODO: Implement storeInByteData
}

ByteBuffer InventoryItem::getByteData() {
 // TODO: Implement getByteData
 return nullptr;
}

bool InventoryItem::isRequiresEquippedBothHands() {
 // TODO: Implement isRequiresEquippedBothHands
 return false;
}

float InventoryItem::getA() {
 // TODO: Implement getA
 return 0;
}

float InventoryItem::getR() {
 // TODO: Implement getR
 return 0;
}

float InventoryItem::getG() {
 // TODO: Implement getG
 return 0;
}

float InventoryItem::getB() {
 // TODO: Implement getB
 return 0;
}

public InventoryItem::InventoryItem(const std::string& _module, const std::string& _name, const std::string& _type, const std::string& tex) {
 // TODO: Implement InventoryItem
 return nullptr;
}

public InventoryItem::InventoryItem(const std::string& _module, const std::string& _name, const std::string& _type, Item item) {
 // TODO: Implement InventoryItem
 return nullptr;
}

std::string InventoryItem::getType() {
 // TODO: Implement getType
 return "";
}

Texture InventoryItem::getTex() {
 // TODO: Implement getTex
 return nullptr;
}

std::string InventoryItem::getCategory() {
 // TODO: Implement getCategory
 return "";
}

bool InventoryItem::IsRotten() {
 // TODO: Implement IsRotten
 return false;
}

float InventoryItem::HowRotten() {
 // TODO: Implement HowRotten
 return 0;
}

bool InventoryItem::CanStack(InventoryItem item) {
 // TODO: Implement CanStack
 return false;
}

bool InventoryItem::ModDataMatches(InventoryItem item) {
 // TODO: Implement ModDataMatches
 return false;
}

void InventoryItem::DoTooltip(ObjectTooltip tooltipUI) {
 // TODO: Implement DoTooltip
}

std::string InventoryItem::getCleanString(float weight) {
 // TODO: Implement getCleanString
 return "";
}

void InventoryItem::DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
 // TODO: Implement DoTooltip
}

void InventoryItem::SetContainerPosition(int x, int y) {
 // TODO: Implement SetContainerPosition
}

void InventoryItem::Use() {
 // TODO: Implement Use
}

void InventoryItem::UseItem() {
 // TODO: Implement UseItem
}

void InventoryItem::Use(bool bCrafting) {
 // TODO: Implement Use
}

void InventoryItem::Use(bool bCrafting, bool bInContainer) {
 // TODO: Implement Use
}

bool InventoryItem::shouldUpdateInWorld() {
 // TODO: Implement shouldUpdateInWorld
 return false;
}

void InventoryItem::update() {
 // TODO: Implement update
}

bool InventoryItem::finishupdate() {
 // TODO: Implement finishupdate
 return false;
}

void InventoryItem::updateSound(BaseSoundEmitter emitter) {
 // TODO: Implement updateSound
}

std::string InventoryItem::getFullType() {
 // TODO: Implement getFullType
 return "";
}

void InventoryItem::save(ByteBuffer output, bool net) {
 // TODO: Implement save
}

InventoryItem InventoryItem::loadItem(ByteBuffer input, int WorldVersion) {
 // TODO: Implement loadItem
 return nullptr;
}

return InventoryItem::loadItem() {
 // TODO: Implement loadItem
 return nullptr;
}

InventoryItem InventoryItem::loadItem(ByteBuffer input, int WorldVersion, bool doSaveTypeCheck) {
 // TODO: Implement loadItem
 return nullptr;
}

void InventoryItem::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

bool InventoryItem::IsFood() {
 // TODO: Implement IsFood
 return false;
}

bool InventoryItem::IsWeapon() {
 // TODO: Implement IsWeapon
 return false;
}

bool InventoryItem::IsDrainable() {
 // TODO: Implement IsDrainable
 return false;
}

bool InventoryItem::IsLiterature() {
 // TODO: Implement IsLiterature
 return false;
}

bool InventoryItem::IsClothing() {
 // TODO: Implement IsClothing
 return false;
}

bool InventoryItem::IsInventoryContainer() {
 // TODO: Implement IsInventoryContainer
 return false;
}

bool InventoryItem::IsMap() {
 // TODO: Implement IsMap
 return false;
}

InventoryItem InventoryItem::LoadFromFile(DataInputStream dataInputStream) {
 // TODO: Implement LoadFromFile
 return nullptr;
}

ItemContainer InventoryItem::getOutermostContainer() {
 // TODO: Implement getOutermostContainer
 return nullptr;
}

bool InventoryItem::isInLocalPlayerInventory() {
 // TODO: Implement isInLocalPlayerInventory
 return false;
}

bool InventoryItem::isInPlayerInventory() {
 // TODO: Implement isInPlayerInventory
 return false;
}

ItemReplacement InventoryItem::getItemReplacementPrimaryHand() {
 // TODO: Implement getItemReplacementPrimaryHand
 return nullptr;
}

ItemReplacement InventoryItem::getItemReplacementSecondHand() {
 // TODO: Implement getItemReplacementSecondHand
 return nullptr;
}

ClothingItem InventoryItem::getClothingItem() {
 // TODO: Implement getClothingItem
 return nullptr;
}

std::string InventoryItem::getAlternateModelName() {
 // TODO: Implement getAlternateModelName
 return "";
}

ItemVisual InventoryItem::getVisual() {
 // TODO: Implement getVisual
 return nullptr;
}

bool InventoryItem::allowRandomTint() {
 // TODO: Implement allowRandomTint
 return false;
}

void InventoryItem::synchWithVisual() {
 // TODO: Implement synchWithVisual
}

int InventoryItem::getContainerX() {
 // TODO: Implement getContainerX
 return 0;
}

void InventoryItem::setContainerX(int _containerX) {
 // TODO: Implement setContainerX
}

int InventoryItem::getContainerY() {
 // TODO: Implement getContainerY
 return 0;
}

void InventoryItem::setContainerY(int _containerY) {
 // TODO: Implement setContainerY
}

bool InventoryItem::isDisappearOnUse() {
 // TODO: Implement isDisappearOnUse
 return false;
}

std::string InventoryItem::getName() {
 // TODO: Implement getName
 return "";
}

void InventoryItem::setName(const std::string& _name) {
 // TODO: Implement setName
}

std::string InventoryItem::getReplaceOnUse() {
 // TODO: Implement getReplaceOnUse
 return "";
}

void InventoryItem::setReplaceOnUse(const std::string& _replaceOnUse) {
 // TODO: Implement setReplaceOnUse
}

std::string InventoryItem::getReplaceOnUseFullType() {
 // TODO: Implement getReplaceOnUseFullType
 return "";
}

int InventoryItem::getConditionMax() {
 // TODO: Implement getConditionMax
 return 0;
}

void InventoryItem::setConditionMax(int _ConditionMax) {
 // TODO: Implement setConditionMax
}

ItemContainer InventoryItem::getRightClickContainer() {
 // TODO: Implement getRightClickContainer
 return nullptr;
}

void InventoryItem::setRightClickContainer(ItemContainer _rightClickContainer) {
 // TODO: Implement setRightClickContainer
}

std::string InventoryItem::getSwingAnim() {
 // TODO: Implement getSwingAnim
 return "";
}

Texture InventoryItem::getTexture() {
 // TODO: Implement getTexture
 return nullptr;
}

void InventoryItem::setTexture(Texture _texture) {
 // TODO: Implement setTexture
}

Texture InventoryItem::getTexturerotten() {
 // TODO: Implement getTexturerotten
 return nullptr;
}

void InventoryItem::setTexturerotten(Texture _texturerotten) {
 // TODO: Implement setTexturerotten
}

Texture InventoryItem::getTextureCooked() {
 // TODO: Implement getTextureCooked
 return nullptr;
}

void InventoryItem::setTextureCooked(Texture _textureCooked) {
 // TODO: Implement setTextureCooked
}

Texture InventoryItem::getTextureBurnt() {
 // TODO: Implement getTextureBurnt
 return nullptr;
}

void InventoryItem::setTextureBurnt(Texture _textureBurnt) {
 // TODO: Implement setTextureBurnt
}

void InventoryItem::setType(const std::string& _type) {
 // TODO: Implement setType
}

int InventoryItem::getCurrentUses() {
 // TODO: Implement getCurrentUses
 return 0;
}

int InventoryItem::getUses() {
 // TODO: Implement getUses
 return 0;
}

void InventoryItem::setUses(int _uses) {
 // TODO: Implement setUses
}

float InventoryItem::getAge() {
 // TODO: Implement getAge
 return 0;
}

void InventoryItem::setAge(float _Age) {
 // TODO: Implement setAge
}

float InventoryItem::getLastAged() {
 // TODO: Implement getLastAged
 return 0;
}

void InventoryItem::setLastAged(float time) {
 // TODO: Implement setLastAged
}

void InventoryItem::updateAge() {
 // TODO: Implement updateAge
}

void InventoryItem::setAutoAge() {
 // TODO: Implement setAutoAge
}

bool InventoryItem::isIsCookable() {
 // TODO: Implement isIsCookable
 return false;
}

bool InventoryItem::isCookable() {
 // TODO: Implement isCookable
 return false;
}

void InventoryItem::setIsCookable(bool _IsCookable) {
 // TODO: Implement setIsCookable
}

float InventoryItem::getCookingTime() {
 // TODO: Implement getCookingTime
 return 0;
}

void InventoryItem::setCookingTime(float _CookingTime) {
 // TODO: Implement setCookingTime
}

float InventoryItem::getMinutesToCook() {
 // TODO: Implement getMinutesToCook
 return 0;
}

void InventoryItem::setMinutesToCook(float _MinutesToCook) {
 // TODO: Implement setMinutesToCook
}

float InventoryItem::getMinutesToBurn() {
 // TODO: Implement getMinutesToBurn
 return 0;
}

void InventoryItem::setMinutesToBurn(float _MinutesToBurn) {
 // TODO: Implement setMinutesToBurn
}

bool InventoryItem::isCooked() {
 // TODO: Implement isCooked
 return false;
}

void InventoryItem::setCooked(bool _Cooked) {
 // TODO: Implement setCooked
}

bool InventoryItem::isBurnt() {
 // TODO: Implement isBurnt
 return false;
}

void InventoryItem::setBurnt(bool _Burnt) {
 // TODO: Implement setBurnt
}

int InventoryItem::getOffAge() {
 // TODO: Implement getOffAge
 return 0;
}

void InventoryItem::setOffAge(int _OffAge) {
 // TODO: Implement setOffAge
}

int InventoryItem::getOffAgeMax() {
 // TODO: Implement getOffAgeMax
 return 0;
}

void InventoryItem::setOffAgeMax(int _OffAgeMax) {
 // TODO: Implement setOffAgeMax
}

float InventoryItem::getWeight() {
 // TODO: Implement getWeight
 return 0;
}

void InventoryItem::setWeight(float _Weight) {
 // TODO: Implement setWeight
}

float InventoryItem::getActualWeight() {
 // TODO: Implement getActualWeight
 return 0;
}

void InventoryItem::setActualWeight(float _ActualWeight) {
 // TODO: Implement setActualWeight
}

std::string InventoryItem::getWorldTexture() {
 // TODO: Implement getWorldTexture
 return "";
}

void InventoryItem::setWorldTexture(const std::string& _WorldTexture) {
 // TODO: Implement setWorldTexture
}

std::string InventoryItem::getDescription() {
 // TODO: Implement getDescription
 return "";
}

void InventoryItem::setDescription(const std::string& _Description) {
 // TODO: Implement setDescription
}

int InventoryItem::getCondition() {
 // TODO: Implement getCondition
 return 0;
}

void InventoryItem::setCondition(int _Condition, bool doSound) {
 // TODO: Implement setCondition
}

void InventoryItem::setCondition(int _Condition) {
 // TODO: Implement setCondition
}

std::string InventoryItem::getOffString() {
 // TODO: Implement getOffString
 return "";
}

void InventoryItem::setOffString(const std::string& _OffString) {
 // TODO: Implement setOffString
}

std::string InventoryItem::getCookedString() {
 // TODO: Implement getCookedString
 return "";
}

void InventoryItem::setCookedString(const std::string& _CookedString) {
 // TODO: Implement setCookedString
}

std::string InventoryItem::getUnCookedString() {
 // TODO: Implement getUnCookedString
 return "";
}

void InventoryItem::setUnCookedString(const std::string& _UnCookedString) {
 // TODO: Implement setUnCookedString
}

std::string InventoryItem::getBurntString() {
 // TODO: Implement getBurntString
 return "";
}

void InventoryItem::setBurntString(const std::string& _BurntString) {
 // TODO: Implement setBurntString
}

std::string InventoryItem::getModule() {
 // TODO: Implement getModule
 return "";
}

void InventoryItem::setModule(const std::string& _module) {
 // TODO: Implement setModule
}

bool InventoryItem::isAlwaysWelcomeGift() {
 // TODO: Implement isAlwaysWelcomeGift
 return false;
}

bool InventoryItem::isCanBandage() {
 // TODO: Implement isCanBandage
 return false;
}

float InventoryItem::getBoredomChange() {
 // TODO: Implement getBoredomChange
 return 0;
}

void InventoryItem::setBoredomChange(float _boredomChange) {
 // TODO: Implement setBoredomChange
}

float InventoryItem::getUnhappyChange() {
 // TODO: Implement getUnhappyChange
 return 0;
}

void InventoryItem::setUnhappyChange(float _unhappyChange) {
 // TODO: Implement setUnhappyChange
}

float InventoryItem::getStressChange() {
 // TODO: Implement getStressChange
 return 0;
}

void InventoryItem::setStressChange(float _stressChange) {
 // TODO: Implement setStressChange
}

bool InventoryItem::hasTag(const std::string& tag) {
 // TODO: Implement hasTag
 return false;
}

void InventoryItem::setTaken(ArrayList<IsoObject> _Taken) {
 // TODO: Implement setTaken
}

IsoDirections InventoryItem::getPlaceDir() {
 // TODO: Implement getPlaceDir
 return nullptr;
}

void InventoryItem::setPlaceDir(IsoDirections _placeDir) {
 // TODO: Implement setPlaceDir
}

IsoDirections InventoryItem::getNewPlaceDir() {
 // TODO: Implement getNewPlaceDir
 return nullptr;
}

void InventoryItem::setNewPlaceDir(IsoDirections _newPlaceDir) {
 // TODO: Implement setNewPlaceDir
}

void InventoryItem::setReplaceOnUseOn(const std::string& _ReplaceOnUseOn) {
 // TODO: Implement setReplaceOnUseOn
}

std::string InventoryItem::getReplaceOnUseOn() {
 // TODO: Implement getReplaceOnUseOn
 return "";
}

std::string InventoryItem::getReplaceOnUseOnString() {
 // TODO: Implement getReplaceOnUseOnString
 return "";
}

std::string InventoryItem::getReplaceTypes() {
 // TODO: Implement getReplaceTypes
 return "";
}

std::string InventoryItem::getReplaceType(const std::string& key) {
 // TODO: Implement getReplaceType
 return "";
}

bool InventoryItem::hasReplaceType(const std::string& key) {
 // TODO: Implement hasReplaceType
 return false;
}

void InventoryItem::setIsWaterSource(bool _IsWaterSource) {
 // TODO: Implement setIsWaterSource
}

bool InventoryItem::isWaterSource() {
 // TODO: Implement isWaterSource
 return false;
}

bool InventoryItem::CanStackNoTemp(InventoryItem var1) {
 // TODO: Implement CanStackNoTemp
 return false;
}

void InventoryItem::CopyModData(KahluaTable DefaultModData) {
 // TODO: Implement CopyModData
}

void InventoryItem::copyModData(KahluaTable modData) {
 // TODO: Implement copyModData
}

int InventoryItem::getCount() {
 // TODO: Implement getCount
 return 0;
}

void InventoryItem::setCount(int count) {
 // TODO: Implement setCount
}

bool InventoryItem::isActivated() {
 // TODO: Implement isActivated
 return false;
}

void InventoryItem::setActivated(bool _activated) {
 // TODO: Implement setActivated
}

void InventoryItem::setActivatedRemote(bool _activated) {
 // TODO: Implement setActivatedRemote
}

void InventoryItem::setCanBeActivated(bool activatedItem) {
 // TODO: Implement setCanBeActivated
}

bool InventoryItem::canBeActivated() {
 // TODO: Implement canBeActivated
 return false;
}

void InventoryItem::setLightStrength(float _lightStrength) {
 // TODO: Implement setLightStrength
}

float InventoryItem::getLightStrength() {
 // TODO: Implement getLightStrength
 return 0;
}

bool InventoryItem::isTorchCone() {
 // TODO: Implement isTorchCone
 return false;
}

void InventoryItem::setTorchCone(bool _isTorchCone) {
 // TODO: Implement setTorchCone
}

float InventoryItem::getTorchDot() {
 // TODO: Implement getTorchDot
 return 0;
}

int InventoryItem::getLightDistance() {
 // TODO: Implement getLightDistance
 return 0;
}

void InventoryItem::setLightDistance(int _lightDistance) {
 // TODO: Implement setLightDistance
}

bool InventoryItem::canEmitLight() {
 // TODO: Implement canEmitLight
 return false;
}

bool InventoryItem::isEmittingLight() {
 // TODO: Implement isEmittingLight
 return false;
}

bool InventoryItem::canStoreWater() {
 // TODO: Implement canStoreWater
 return false;
}

float InventoryItem::getFatigueChange() {
 // TODO: Implement getFatigueChange
 return 0;
}

void InventoryItem::setFatigueChange(float _fatigueChange) {
 // TODO: Implement setFatigueChange
}

float InventoryItem::getCurrentCondition() {
 // TODO: Implement getCurrentCondition
 return 0;
}

void InventoryItem::setColor(Color color) {
 // TODO: Implement setColor
}

Color InventoryItem::getColor() {
 // TODO: Implement getColor
 return nullptr;
}

ColorInfo InventoryItem::getColorInfo() {
 // TODO: Implement getColorInfo
 return nullptr;
}

bool InventoryItem::isTwoHandWeapon() {
 // TODO: Implement isTwoHandWeapon
 return false;
}

std::string InventoryItem::getCustomMenuOption() {
 // TODO: Implement getCustomMenuOption
 return "";
}

void InventoryItem::setCustomMenuOption(const std::string& _customMenuOption) {
 // TODO: Implement setCustomMenuOption
}

void InventoryItem::setTooltip(const std::string& _tooltip) {
 // TODO: Implement setTooltip
}

std::string InventoryItem::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

std::string InventoryItem::getDisplayCategory() {
 // TODO: Implement getDisplayCategory
 return "";
}

void InventoryItem::setDisplayCategory(const std::string& _displayCategory) {
 // TODO: Implement setDisplayCategory
}

int InventoryItem::getHaveBeenRepaired() {
 // TODO: Implement getHaveBeenRepaired
 return 0;
}

void InventoryItem::setHaveBeenRepaired(int _haveBeenRepaired) {
 // TODO: Implement setHaveBeenRepaired
}

bool InventoryItem::isBroken() {
 // TODO: Implement isBroken
 return false;
}

void InventoryItem::setBroken(bool _broken) {
 // TODO: Implement setBroken
}

std::string InventoryItem::getDisplayName() {
 // TODO: Implement getDisplayName
 return "";
}

bool InventoryItem::isTrap() {
 // TODO: Implement isTrap
 return false;
}

void InventoryItem::addExtraItem(const std::string& _type) {
 // TODO: Implement addExtraItem
}

bool InventoryItem::haveExtraItems() {
 // TODO: Implement haveExtraItems
 return false;
}

float InventoryItem::getExtraItemsWeight() {
 // TODO: Implement getExtraItemsWeight
 return 0;
}

bool InventoryItem::isCustomName() {
 // TODO: Implement isCustomName
 return false;
}

void InventoryItem::setCustomName(bool _customName) {
 // TODO: Implement setCustomName
}

bool InventoryItem::isFishingLure() {
 // TODO: Implement isFishingLure
 return false;
}

void InventoryItem::copyConditionModData(InventoryItem other) {
 // TODO: Implement copyConditionModData
}

void InventoryItem::setConditionFromModData(InventoryItem other) {
 // TODO: Implement setConditionFromModData
}

std::string InventoryItem::getBreakSound() {
 // TODO: Implement getBreakSound
 return "";
}

void InventoryItem::setBreakSound(const std::string& _breakSound) {
 // TODO: Implement setBreakSound
}

std::string InventoryItem::getPlaceOneSound() {
 // TODO: Implement getPlaceOneSound
 return "";
}

std::string InventoryItem::getPlaceMultipleSound() {
 // TODO: Implement getPlaceMultipleSound
 return "";
}

std::string InventoryItem::getSoundByID(const std::string& ID) {
 // TODO: Implement getSoundByID
 return "";
}

void InventoryItem::setBeingFilled(bool v) {
 // TODO: Implement setBeingFilled
}

bool InventoryItem::isBeingFilled() {
 // TODO: Implement isBeingFilled
 return false;
}

std::string InventoryItem::getFillFromDispenserSound() {
 // TODO: Implement getFillFromDispenserSound
 return "";
}

std::string InventoryItem::getFillFromTapSound() {
 // TODO: Implement getFillFromTapSound
 return "";
}

bool InventoryItem::isAlcoholic() {
 // TODO: Implement isAlcoholic
 return false;
}

void InventoryItem::setAlcoholic(bool _alcoholic) {
 // TODO: Implement setAlcoholic
}

float InventoryItem::getAlcoholPower() {
 // TODO: Implement getAlcoholPower
 return 0;
}

void InventoryItem::setAlcoholPower(float _alcoholPower) {
 // TODO: Implement setAlcoholPower
}

float InventoryItem::getBandagePower() {
 // TODO: Implement getBandagePower
 return 0;
}

void InventoryItem::setBandagePower(float _bandagePower) {
 // TODO: Implement setBandagePower
}

float InventoryItem::getReduceInfectionPower() {
 // TODO: Implement getReduceInfectionPower
 return 0;
}

void InventoryItem::setReduceInfectionPower(float reduceInfectionPower) {
 // TODO: Implement setReduceInfectionPower
}

void InventoryItem::saveWithSize(ByteBuffer output, bool net) {
 // TODO: Implement saveWithSize
}

bool InventoryItem::isCustomWeight() {
 // TODO: Implement isCustomWeight
 return false;
}

void InventoryItem::setCustomWeight(bool custom) {
 // TODO: Implement setCustomWeight
}

float InventoryItem::getContentsWeight() {
 // TODO: Implement getContentsWeight
 return 0;
}

float InventoryItem::getHotbarEquippedWeight() {
 // TODO: Implement getHotbarEquippedWeight
 return 0;
}

float InventoryItem::getEquippedWeight() {
 // TODO: Implement getEquippedWeight
 return 0;
}

float InventoryItem::getUnequippedWeight() {
 // TODO: Implement getUnequippedWeight
 return 0;
}

bool InventoryItem::isEquipped() {
 // TODO: Implement isEquipped
 return false;
}

int InventoryItem::getKeyId() {
 // TODO: Implement getKeyId
 return 0;
}

void InventoryItem::setKeyId(int _keyId) {
 // TODO: Implement setKeyId
}

bool InventoryItem::isTaintedWater() {
 // TODO: Implement isTaintedWater
 return false;
}

void InventoryItem::setTaintedWater(bool _taintedWater) {
 // TODO: Implement setTaintedWater
}

bool InventoryItem::isRemoteController() {
 // TODO: Implement isRemoteController
 return false;
}

void InventoryItem::setRemoteController(bool _remoteController) {
 // TODO: Implement setRemoteController
}

bool InventoryItem::canBeRemote() {
 // TODO: Implement canBeRemote
 return false;
}

void InventoryItem::setCanBeRemote(bool _canBeRemote) {
 // TODO: Implement setCanBeRemote
}

int InventoryItem::getRemoteControlID() {
 // TODO: Implement getRemoteControlID
 return 0;
}

void InventoryItem::setRemoteControlID(int _remoteControlID) {
 // TODO: Implement setRemoteControlID
}

int InventoryItem::getRemoteRange() {
 // TODO: Implement getRemoteRange
 return 0;
}

void InventoryItem::setRemoteRange(int _remoteRange) {
 // TODO: Implement setRemoteRange
}

std::string InventoryItem::getExplosionSound() {
 // TODO: Implement getExplosionSound
 return "";
}

void InventoryItem::setExplosionSound(const std::string& _explosionSound) {
 // TODO: Implement setExplosionSound
}

std::string InventoryItem::getCountDownSound() {
 // TODO: Implement getCountDownSound
 return "";
}

void InventoryItem::setCountDownSound(const std::string& sound) {
 // TODO: Implement setCountDownSound
}

float InventoryItem::getColorRed() {
 // TODO: Implement getColorRed
 return 0;
}

void InventoryItem::setColorRed(float _colorRed) {
 // TODO: Implement setColorRed
}

float InventoryItem::getColorGreen() {
 // TODO: Implement getColorGreen
 return 0;
}

void InventoryItem::setColorGreen(float _colorGreen) {
 // TODO: Implement setColorGreen
}

float InventoryItem::getColorBlue() {
 // TODO: Implement getColorBlue
 return 0;
}

void InventoryItem::setColorBlue(float _colorBlue) {
 // TODO: Implement setColorBlue
}

std::string InventoryItem::getEvolvedRecipeName() {
 // TODO: Implement getEvolvedRecipeName
 return "";
}

void InventoryItem::setEvolvedRecipeName(const std::string& _evolvedRecipeName) {
 // TODO: Implement setEvolvedRecipeName
}

float InventoryItem::getMetalValue() {
 // TODO: Implement getMetalValue
 return 0;
}

void InventoryItem::setMetalValue(float _metalValue) {
 // TODO: Implement setMetalValue
}

float InventoryItem::getItemHeat() {
 // TODO: Implement getItemHeat
 return 0;
}

void InventoryItem::setItemHeat(float _itemHeat) {
 // TODO: Implement setItemHeat
}

float InventoryItem::getInvHeat() {
 // TODO: Implement getInvHeat
 return 0;
}

float InventoryItem::getMeltingTime() {
 // TODO: Implement getMeltingTime
 return 0;
}

void InventoryItem::setMeltingTime(float _meltingTime) {
 // TODO: Implement setMeltingTime
}

std::string InventoryItem::getWorker() {
 // TODO: Implement getWorker
 return "";
}

void InventoryItem::setWorker(const std::string& _worker) {
 // TODO: Implement setWorker
}

int InventoryItem::getID() {
 // TODO: Implement getID
 return 0;
}

void InventoryItem::setID(int itemId) {
 // TODO: Implement setID
}

bool InventoryItem::isWet() {
 // TODO: Implement isWet
 return false;
}

void InventoryItem::setWet(bool _isWet) {
 // TODO: Implement setWet
}

float InventoryItem::getWetCooldown() {
 // TODO: Implement getWetCooldown
 return 0;
}

void InventoryItem::setWetCooldown(float _wetCooldown) {
 // TODO: Implement setWetCooldown
}

std::string InventoryItem::getItemWhenDry() {
 // TODO: Implement getItemWhenDry
 return "";
}

void InventoryItem::setItemWhenDry(const std::string& _itemWhenDry) {
 // TODO: Implement setItemWhenDry
}

bool InventoryItem::isFavorite() {
 // TODO: Implement isFavorite
 return false;
}

void InventoryItem::setFavorite(bool _favorite) {
 // TODO: Implement setFavorite
}

void InventoryItem::setRequireInHandOrInventory(ArrayList<String> _requireInHandOrInventory) {
 // TODO: Implement setRequireInHandOrInventory
}

bool InventoryItem::isCustomColor() {
 // TODO: Implement isCustomColor
 return false;
}

void InventoryItem::setCustomColor(bool _customColor) {
 // TODO: Implement setCustomColor
}

void InventoryItem::doBuildingStash() {
 // TODO: Implement doBuildingStash
}

void InventoryItem::setStashMap(const std::string& _stashMap) {
 // TODO: Implement setStashMap
}

int InventoryItem::getMechanicType() {
 // TODO: Implement getMechanicType
 return 0;
}

float InventoryItem::getItemCapacity() {
 // TODO: Implement getItemCapacity
 return 0;
}

void InventoryItem::setItemCapacity(float capacity) {
 // TODO: Implement setItemCapacity
}

int InventoryItem::getMaxCapacity() {
 // TODO: Implement getMaxCapacity
 return 0;
}

void InventoryItem::setMaxCapacity(int _maxCapacity) {
 // TODO: Implement setMaxCapacity
}

bool InventoryItem::isConditionAffectsCapacity() {
 // TODO: Implement isConditionAffectsCapacity
 return false;
}

float InventoryItem::getBrakeForce() {
 // TODO: Implement getBrakeForce
 return 0;
}

void InventoryItem::setBrakeForce(float _brakeForce) {
 // TODO: Implement setBrakeForce
}

int InventoryItem::getChanceToSpawnDamaged() {
 // TODO: Implement getChanceToSpawnDamaged
 return 0;
}

void InventoryItem::setChanceToSpawnDamaged(int _chanceToSpawnDamaged) {
 // TODO: Implement setChanceToSpawnDamaged
}

float InventoryItem::getConditionLowerNormal() {
 // TODO: Implement getConditionLowerNormal
 return 0;
}

void InventoryItem::setConditionLowerNormal(float _conditionLowerNormal) {
 // TODO: Implement setConditionLowerNormal
}

float InventoryItem::getConditionLowerOffroad() {
 // TODO: Implement getConditionLowerOffroad
 return 0;
}

void InventoryItem::setConditionLowerOffroad(float _conditionLowerOffroad) {
 // TODO: Implement setConditionLowerOffroad
}

float InventoryItem::getWheelFriction() {
 // TODO: Implement getWheelFriction
 return 0;
}

void InventoryItem::setWheelFriction(float _wheelFriction) {
 // TODO: Implement setWheelFriction
}

float InventoryItem::getSuspensionDamping() {
 // TODO: Implement getSuspensionDamping
 return 0;
}

void InventoryItem::setSuspensionDamping(float _suspensionDamping) {
 // TODO: Implement setSuspensionDamping
}

float InventoryItem::getSuspensionCompression() {
 // TODO: Implement getSuspensionCompression
 return 0;
}

void InventoryItem::setSuspensionCompression(float _suspensionCompression) {
 // TODO: Implement setSuspensionCompression
}

void InventoryItem::setInfected(bool infected) {
 // TODO: Implement setInfected
}

bool InventoryItem::isInfected() {
 // TODO: Implement isInfected
 return false;
}

float InventoryItem::getEngineLoudness() {
 // TODO: Implement getEngineLoudness
 return 0;
}

void InventoryItem::setEngineLoudness(float _engineLoudness) {
 // TODO: Implement setEngineLoudness
}

std::string InventoryItem::getStaticModel() {
 // TODO: Implement getStaticModel
 return "";
}

void InventoryItem::setIconsForTexture(ArrayList<String> _iconsForTexture) {
 // TODO: Implement setIconsForTexture
}

float InventoryItem::getScore(SurvivorDesc desc) {
 // TODO: Implement getScore
 return 0;
}

IsoGameCharacter InventoryItem::getPreviousOwner() {
 // TODO: Implement getPreviousOwner
 return nullptr;
}

void InventoryItem::setPreviousOwner(IsoGameCharacter _previousOwner) {
 // TODO: Implement setPreviousOwner
}

Item InventoryItem::getScriptItem() {
 // TODO: Implement getScriptItem
 return nullptr;
}

void InventoryItem::setScriptItem(Item _ScriptItem) {
 // TODO: Implement setScriptItem
}

ItemType InventoryItem::getCat() {
 // TODO: Implement getCat
 return nullptr;
}

void InventoryItem::setCat(ItemType _cat) {
 // TODO: Implement setCat
}

ItemContainer InventoryItem::getContainer() {
 // TODO: Implement getContainer
 return nullptr;
}

void InventoryItem::setContainer(ItemContainer _container) {
 // TODO: Implement setContainer
}

void InventoryItem::setBloodClothingType(ArrayList<BloodClothingType> _bloodClothingType) {
 // TODO: Implement setBloodClothingType
}

void InventoryItem::setBlood(BloodBodyPartType bodyPartType, float amount) {
 // TODO: Implement setBlood
}

float InventoryItem::getBlood(BloodBodyPartType bodyPartType) {
 // TODO: Implement getBlood
 return 0;
}

void InventoryItem::setDirt(BloodBodyPartType bodyPartType, float amount) {
 // TODO: Implement setDirt
}

float InventoryItem::getDirt(BloodBodyPartType bodyPartType) {
 // TODO: Implement getDirt
 return 0;
}

std::string InventoryItem::getClothingItemName() {
 // TODO: Implement getClothingItemName
 return "";
}

int InventoryItem::getStashChance() {
 // TODO: Implement getStashChance
 return 0;
}

void InventoryItem::setStashChance(int _stashChance) {
 // TODO: Implement setStashChance
}

std::string InventoryItem::getEatType() {
 // TODO: Implement getEatType
 return "";
}

bool InventoryItem::isUseWorldItem() {
 // TODO: Implement isUseWorldItem
 return false;
}

bool InventoryItem::isHairDye() {
 // TODO: Implement isHairDye
 return false;
}

std::string InventoryItem::getAmmoType() {
 // TODO: Implement getAmmoType
 return "";
}

void InventoryItem::setAmmoType(const std::string& _ammoType) {
 // TODO: Implement setAmmoType
}

int InventoryItem::getMaxAmmo() {
 // TODO: Implement getMaxAmmo
 return 0;
}

void InventoryItem::setMaxAmmo(int maxAmmoCount) {
 // TODO: Implement setMaxAmmo
}

int InventoryItem::getCurrentAmmoCount() {
 // TODO: Implement getCurrentAmmoCount
 return 0;
}

void InventoryItem::setCurrentAmmoCount(int ammo) {
 // TODO: Implement setCurrentAmmoCount
}

std::string InventoryItem::getGunType() {
 // TODO: Implement getGunType
 return "";
}

void InventoryItem::setGunType(const std::string& _gunType) {
 // TODO: Implement setGunType
}

bool InventoryItem::hasBlood() {
 // TODO: Implement hasBlood
 return false;
}

bool InventoryItem::hasDirt() {
 // TODO: Implement hasDirt
 return false;
}

std::string InventoryItem::getAttachmentType() {
 // TODO: Implement getAttachmentType
 return "";
}

void InventoryItem::setAttachmentType(const std::string& _attachmentType) {
 // TODO: Implement setAttachmentType
}

int InventoryItem::getAttachedSlot() {
 // TODO: Implement getAttachedSlot
 return 0;
}

void InventoryItem::setAttachedSlot(int _attachedSlot) {
 // TODO: Implement setAttachedSlot
}

void InventoryItem::setAttachmentsProvided(ArrayList<String> _attachmentsProvided) {
 // TODO: Implement setAttachmentsProvided
}

std::string InventoryItem::getAttachedSlotType() {
 // TODO: Implement getAttachedSlotType
 return "";
}

void InventoryItem::setAttachedSlotType(const std::string& _attachedSlotType) {
 // TODO: Implement setAttachedSlotType
}

std::string InventoryItem::getAttachmentReplacement() {
 // TODO: Implement getAttachmentReplacement
 return "";
}

void InventoryItem::setAttachmentReplacement(const std::string& attachementReplacement) {
 // TODO: Implement setAttachmentReplacement
}

std::string InventoryItem::getAttachedToModel() {
 // TODO: Implement getAttachedToModel
 return "";
}

void InventoryItem::setAttachedToModel(const std::string& _attachedToModel) {
 // TODO: Implement setAttachedToModel
}

std::string InventoryItem::getFabricType() {
 // TODO: Implement getFabricType
 return "";
}

std::string InventoryItem::getStringItemType() {
 // TODO: Implement getStringItemType
 return "";
}

bool InventoryItem::isProtectFromRainWhileEquipped() {
 // TODO: Implement isProtectFromRainWhileEquipped
 return false;
}

bool InventoryItem::isEquippedNoSprint() {
 // TODO: Implement isEquippedNoSprint
 return false;
}

std::string InventoryItem::getBodyLocation() {
 // TODO: Implement getBodyLocation
 return "";
}

std::string InventoryItem::getMakeUpType() {
 // TODO: Implement getMakeUpType
 return "";
}

bool InventoryItem::isHidden() {
 // TODO: Implement isHidden
 return false;
}

std::string InventoryItem::getConsolidateOption() {
 // TODO: Implement getConsolidateOption
 return "";
}

std::string InventoryItem::getWorldStaticItem() {
 // TODO: Implement getWorldStaticItem
 return "";
}

void InventoryItem::setRegistry_id(Item itemscript) {
 // TODO: Implement setRegistry_id
}

short InventoryItem::getRegistry_id() {
 // TODO: Implement getRegistry_id
 return 0;
}

std::string InventoryItem::getModID() {
 // TODO: Implement getModID
 return "";
}

std::string InventoryItem::getModName() {
 // TODO: Implement getModName
 return "";
}

bool InventoryItem::isVanilla() {
 // TODO: Implement isVanilla
 return false;
}

short InventoryItem::getRecordedMediaIndex() {
 // TODO: Implement getRecordedMediaIndex
 return 0;
}

void InventoryItem::setRecordedMediaIndex(short _id) {
 // TODO: Implement setRecordedMediaIndex
}

void InventoryItem::setRecordedMediaIndexInteger(int _id) {
 // TODO: Implement setRecordedMediaIndexInteger
}

bool InventoryItem::isRecordedMedia() {
 // TODO: Implement isRecordedMedia
 return false;
}

MediaData InventoryItem::getMediaData() {
 // TODO: Implement getMediaData
 return nullptr;
}

uint8_t InventoryItem::getMediaType() {
 // TODO: Implement getMediaType
 return 0;
}

void InventoryItem::setMediaType(uint8_t b) {
 // TODO: Implement setMediaType
}

void InventoryItem::setRecordedMediaData(MediaData data) {
 // TODO: Implement setRecordedMediaData
}

void InventoryItem::setWorldZRotation(int rot) {
 // TODO: Implement setWorldZRotation
}

void InventoryItem::setWorldScale(float scale) {
 // TODO: Implement setWorldScale
}

std::string InventoryItem::getLuaCreate() {
 // TODO: Implement getLuaCreate
 return "";
}

bool InventoryItem::isInitialised() {
 // TODO: Implement isInitialised
 return false;
}

void InventoryItem::setInitialised(bool initialised) {
 // TODO: Implement setInitialised
}

void InventoryItem::initialiseItem() {
 // TODO: Implement initialiseItem
}

std::string InventoryItem::getSoundParameter(const std::string& parameterName) {
 // TODO: Implement getSoundParameter
 return "";
}

} // namespace inventory
} // namespace zombie
