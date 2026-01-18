#include "zombie/scripting/objects/Recipe.h"

namespace zombie {
namespace scripting {
namespace objects {

bool Recipe::isCanBeDoneFromFloor() {
 // TODO: Implement isCanBeDoneFromFloor
 return false;
}

void Recipe::setCanBeDoneFromFloor(bool _canBeDoneFromFloor) {
 // TODO: Implement setCanBeDoneFromFloor
}

public Recipe::Recipe() {
 // TODO: Implement Recipe
 return nullptr;
}

int Recipe::FindIndexOf(InventoryItem a) {
 // TODO: Implement FindIndexOf
 return 0;
}

int Recipe::getNumberOfNeededItem() {
 // TODO: Implement getNumberOfNeededItem
 return 0;
}

float Recipe::getTimeToMake() {
 // TODO: Implement getTimeToMake
 return 0;
}

std::string Recipe::getName() {
 // TODO: Implement getName
 return "";
}

std::string Recipe::getFullType() {
 // TODO: Implement getFullType
 return "";
}

void Recipe::Load(const std::string& string0, String[] strings0) {
 // TODO: Implement Load
}

void Recipe::DoSource(const std::string& type) {
 // TODO: Implement DoSource
}

void Recipe::DoResult(const std::string& type) {
 // TODO: Implement DoResult
}

std::string Recipe::getSound() {
 // TODO: Implement getSound
 return "";
}

void Recipe::setSound(const std::string& sound) {
 // TODO: Implement setSound
}

std::string Recipe::getOriginalname() {
 // TODO: Implement getOriginalname
 return "";
}

void Recipe::setOriginalname(const std::string& _originalname) {
 // TODO: Implement setOriginalname
}

bool Recipe::needToBeLearn() {
 // TODO: Implement needToBeLearn
 return false;
}

void Recipe::setNeedToBeLearn(bool _needToBeLearn) {
 // TODO: Implement setNeedToBeLearn
}

std::string Recipe::getCategory() {
 // TODO: Implement getCategory
 return "";
}

void Recipe::setCategory(const std::string& _category) {
 // TODO: Implement setCategory
}

int Recipe::getRequiredSkillCount() {
 // TODO: Implement getRequiredSkillCount
 return 0;
}

void Recipe::clearRequiredSkills() {
 // TODO: Implement clearRequiredSkills
}

void Recipe::addRequiredSkill(PerkFactory.Perk perk, int level) {
 // TODO: Implement addRequiredSkill
}

bool Recipe::isDestroy(const std::string& sourceFullType) {
 // TODO: Implement isDestroy
 return false;
}

bool Recipe::isKeep(const std::string& sourceFullType) {
 // TODO: Implement isKeep
 return false;
}

float Recipe::getHeat() {
 // TODO: Implement getHeat
 return 0;
}

bool Recipe::noBrokenItems() {
 // TODO: Implement noBrokenItems
 return false;
}

bool Recipe::isAllowDestroyedItem() {
 // TODO: Implement isAllowDestroyedItem
 return false;
}

void Recipe::setAllowDestroyedItem(bool allow) {
 // TODO: Implement setAllowDestroyedItem
}

bool Recipe::isAllowFrozenItem() {
 // TODO: Implement isAllowFrozenItem
 return false;
}

void Recipe::setAllowFrozenItem(bool allow) {
 // TODO: Implement setAllowFrozenItem
}

bool Recipe::isAllowRottenItem() {
 // TODO: Implement isAllowRottenItem
 return false;
}

void Recipe::setAllowRottenItem(bool boolean0) {
 // TODO: Implement setAllowRottenItem
}

int Recipe::getWaterAmountNeeded() {
 // TODO: Implement getWaterAmountNeeded
 return 0;
}

std::string Recipe::getNearItem() {
 // TODO: Implement getNearItem
 return "";
}

void Recipe::setNearItem(const std::string& _nearItem) {
 // TODO: Implement setNearItem
}

std::string Recipe::getCanPerform() {
 // TODO: Implement getCanPerform
 return "";
}

void Recipe::setCanPerform(const std::string& functionName) {
 // TODO: Implement setCanPerform
}

std::string Recipe::getLuaTest() {
 // TODO: Implement getLuaTest
 return "";
}

void Recipe::setLuaTest(const std::string& functionName) {
 // TODO: Implement setLuaTest
}

std::string Recipe::getLuaCreate() {
 // TODO: Implement getLuaCreate
 return "";
}

void Recipe::setLuaCreate(const std::string& functionName) {
 // TODO: Implement setLuaCreate
}

std::string Recipe::getLuaGrab() {
 // TODO: Implement getLuaGrab
 return "";
}

void Recipe::setLuaGrab(const std::string& functionName) {
 // TODO: Implement setLuaGrab
}

std::string Recipe::getLuaGiveXP() {
 // TODO: Implement getLuaGiveXP
 return "";
}

void Recipe::setLuaGiveXP(const std::string& functionName) {
 // TODO: Implement setLuaGiveXP
}

bool Recipe::isRemoveResultItem() {
 // TODO: Implement isRemoveResultItem
 return false;
}

void Recipe::setRemoveResultItem(bool _removeResultItem) {
 // TODO: Implement setRemoveResultItem
}

std::string Recipe::getAnimNode() {
 // TODO: Implement getAnimNode
 return "";
}

void Recipe::setAnimNode(const std::string& animNode) {
 // TODO: Implement setAnimNode
}

std::string Recipe::getProp1() {
 // TODO: Implement getProp1
 return "";
}

void Recipe::setProp1(const std::string& prop1) {
 // TODO: Implement setProp1
}

std::string Recipe::getProp2() {
 // TODO: Implement getProp2
 return "";
}

void Recipe::setProp2(const std::string& prop2) {
 // TODO: Implement setProp2
}

std::string Recipe::getTooltip() {
 // TODO: Implement getTooltip
 return "";
}

void Recipe::setStopOnWalk(bool stop) {
 // TODO: Implement setStopOnWalk
}

bool Recipe::isStopOnWalk() {
 // TODO: Implement isStopOnWalk
 return false;
}

void Recipe::setStopOnRun(bool stop) {
 // TODO: Implement setStopOnRun
}

bool Recipe::isStopOnRun() {
 // TODO: Implement isStopOnRun
 return false;
}

void Recipe::setIsHidden(bool hide) {
 // TODO: Implement setIsHidden
}

bool Recipe::isHidden() {
 // TODO: Implement isHidden
 return false;
}

bool Recipe::isInSameInventory() {
 // TODO: Implement isInSameInventory
 return false;
}

public Recipe::RequiredSkill(PerkFactory.Perk _perk, int _level) {
 // TODO: Implement RequiredSkill
 return nullptr;
}

int Recipe::getLevel() {
 // TODO: Implement getLevel
 return 0;
}

std::string Recipe::getType() {
 // TODO: Implement getType
 return "";
}

void Recipe::setType(const std::string& _type) {
 // TODO: Implement setType
}

int Recipe::getCount() {
 // TODO: Implement getCount
 return 0;
}

void Recipe::setCount(int _count) {
 // TODO: Implement setCount
}

std::string Recipe::getModule() {
 // TODO: Implement getModule
 return "";
}

void Recipe::setModule(const std::string& _module) {
 // TODO: Implement setModule
}

std::string Recipe::getFullType() {
 // TODO: Implement getFullType
 return "";
}

int Recipe::getDrainableCount() {
 // TODO: Implement getDrainableCount
 return 0;
}

void Recipe::setDrainableCount(int _count) {
 // TODO: Implement setDrainableCount
}

bool Recipe::isDestroy() {
 // TODO: Implement isDestroy
 return false;
}

void Recipe::setDestroy(bool _destroy) {
 // TODO: Implement setDestroy
}

bool Recipe::isKeep() {
 // TODO: Implement isKeep
 return false;
}

void Recipe::setKeep(bool _keep) {
 // TODO: Implement setKeep
}

float Recipe::getCount() {
 // TODO: Implement getCount
 return 0;
}

void Recipe::setCount(float _count) {
 // TODO: Implement setCount
}

float Recipe::getUse() {
 // TODO: Implement getUse
 return 0;
}

void Recipe::setUse(float _use) {
 // TODO: Implement setUse
}

std::string Recipe::getOnlyItem() {
 // TODO: Implement getOnlyItem
 return "";
}

} // namespace objects
} // namespace scripting
} // namespace zombie
