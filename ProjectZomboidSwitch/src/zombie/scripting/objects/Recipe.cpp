#include <string>
#include "zombie/scripting/objects/Recipe.h"

namespace zombie {
namespace scripting {
namespace objects {

bool Recipe::isCanBeDoneFromFloor() {
    // TODO: Implement isCanBeDoneFromFloor
    return false;
}

void Recipe::setCanBeDoneFromFloor(bool var1) {
    // TODO: Implement setCanBeDoneFromFloor
}

public Recipe::Recipe() {
    // TODO: Implement Recipe
    return nullptr;
}

int Recipe::FindIndexOf(InventoryItem var1) {
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

void Recipe::Load(const std::string& var1, std::string[] var2) {
    // TODO: Implement Load
}

void Recipe::DoSource(const std::string& var1) {
    // TODO: Implement DoSource
}

void Recipe::DoResult(const std::string& var1) {
    // TODO: Implement DoResult
}

Result Recipe::getResult() {
    // TODO: Implement getResult
    return nullptr;
}

std::string Recipe::getSound() {
    // TODO: Implement getSound
    return "";
}

void Recipe::setSound(const std::string& var1) {
    // TODO: Implement setSound
}

std::string Recipe::getOriginalname() {
    // TODO: Implement getOriginalname
    return "";
}

void Recipe::setOriginalname(const std::string& var1) {
    // TODO: Implement setOriginalname
}

bool Recipe::needToBeLearn() {
    // TODO: Implement needToBeLearn
    return false;
}

void Recipe::setNeedToBeLearn(bool var1) {
    // TODO: Implement setNeedToBeLearn
}

std::string Recipe::getCategory() {
    // TODO: Implement getCategory
    return "";
}

void Recipe::setCategory(const std::string& var1) {
    // TODO: Implement setCategory
}

int Recipe::getRequiredSkillCount() {
    // TODO: Implement getRequiredSkillCount
    return 0;
}

RequiredSkill Recipe::getRequiredSkill(int var1) {
    // TODO: Implement getRequiredSkill
    return nullptr;
}

void Recipe::clearRequiredSkills() {
    // TODO: Implement clearRequiredSkills
}

void Recipe::addRequiredSkill(Perk var1, int var2) {
    // TODO: Implement addRequiredSkill
}

Source Recipe::findSource(const std::string& var1) {
    // TODO: Implement findSource
    return nullptr;
}

bool Recipe::isDestroy(const std::string& var1) {
    // TODO: Implement isDestroy
    return false;
}

bool Recipe::isKeep(const std::string& var1) {
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

void Recipe::setAllowDestroyedItem(bool var1) {
    // TODO: Implement setAllowDestroyedItem
}

bool Recipe::isAllowFrozenItem() {
    // TODO: Implement isAllowFrozenItem
    return false;
}

void Recipe::setAllowFrozenItem(bool var1) {
    // TODO: Implement setAllowFrozenItem
}

bool Recipe::isAllowRottenItem() {
    // TODO: Implement isAllowRottenItem
    return false;
}

void Recipe::setAllowRottenItem(bool var1) {
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

void Recipe::setNearItem(const std::string& var1) {
    // TODO: Implement setNearItem
}

std::string Recipe::getCanPerform() {
    // TODO: Implement getCanPerform
    return "";
}

void Recipe::setCanPerform(const std::string& var1) {
    // TODO: Implement setCanPerform
}

std::string Recipe::getLuaTest() {
    // TODO: Implement getLuaTest
    return "";
}

void Recipe::setLuaTest(const std::string& var1) {
    // TODO: Implement setLuaTest
}

std::string Recipe::getLuaCreate() {
    // TODO: Implement getLuaCreate
    return "";
}

void Recipe::setLuaCreate(const std::string& var1) {
    // TODO: Implement setLuaCreate
}

std::string Recipe::getLuaGrab() {
    // TODO: Implement getLuaGrab
    return "";
}

void Recipe::setLuaGrab(const std::string& var1) {
    // TODO: Implement setLuaGrab
}

std::string Recipe::getLuaGiveXP() {
    // TODO: Implement getLuaGiveXP
    return "";
}

void Recipe::setLuaGiveXP(const std::string& var1) {
    // TODO: Implement setLuaGiveXP
}

bool Recipe::isRemoveResultItem() {
    // TODO: Implement isRemoveResultItem
    return false;
}

void Recipe::setRemoveResultItem(bool var1) {
    // TODO: Implement setRemoveResultItem
}

std::string Recipe::getAnimNode() {
    // TODO: Implement getAnimNode
    return "";
}

void Recipe::setAnimNode(const std::string& var1) {
    // TODO: Implement setAnimNode
}

std::string Recipe::getProp1() {
    // TODO: Implement getProp1
    return "";
}

void Recipe::setProp1(const std::string& var1) {
    // TODO: Implement setProp1
}

std::string Recipe::getProp2() {
    // TODO: Implement getProp2
    return "";
}

void Recipe::setProp2(const std::string& var1) {
    // TODO: Implement setProp2
}

std::string Recipe::getTooltip() {
    // TODO: Implement getTooltip
    return "";
}

void Recipe::setStopOnWalk(bool var1) {
    // TODO: Implement setStopOnWalk
}

bool Recipe::isStopOnWalk() {
    // TODO: Implement isStopOnWalk
    return false;
}

void Recipe::setStopOnRun(bool var1) {
    // TODO: Implement setStopOnRun
}

bool Recipe::isStopOnRun() {
    // TODO: Implement isStopOnRun
    return false;
}

void Recipe::setIsHidden(bool var1) {
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

} // namespace objects
} // namespace scripting
} // namespace zombie
