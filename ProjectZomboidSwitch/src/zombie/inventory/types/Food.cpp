#include <stack>
#include <string>
#include <vector>
#include "zombie\inventory\types/Food.h"

namespace zombie {
namespace inventory {
namespace types {

std::string Food::getCategory() {
    // TODO: Implement getCategory
    return "";
}

public Food::Food(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement Food
    return nullptr;
}

public Food::Food(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
    // TODO: Implement Food
    return nullptr;
}

bool Food::IsFood() {
    // TODO: Implement IsFood
    return false;
}

int Food::getSaveType() {
    // TODO: Implement getSaveType
    return 0;
}

void Food::update() {
    // TODO: Implement update
}

void Food::updateSound(BaseSoundEmitter var1) {
    // TODO: Implement updateSound
}

bool Food::shouldPlayCookingSound() {
    // TODO: Implement shouldPlayCookingSound
    return false;
}

void Food::setCookingParameter(BaseSoundEmitter var1) {
    // TODO: Implement setCookingParameter
}

void Food::updateTemperature() {
    // TODO: Implement updateTemperature
}

void Food::updateRotting(ItemContainer var1) {
    // TODO: Implement updateRotting
}

void Food::updateAge() {
    // TODO: Implement updateAge
}

void Food::setAutoAge() {
    // TODO: Implement setAutoAge
}

void Food::updateFreezing(ItemContainer var1) {
    // TODO: Implement updateFreezing
}

float Food::getActualWeight() {
    // TODO: Implement getActualWeight
    return 0;
}

float Food::getWeight() {
    // TODO: Implement getWeight
    return 0;
}

bool Food::CanStack(InventoryItem var1) {
    // TODO: Implement CanStack
    return false;
}

void Food::save(ByteBuffer var1, bool var2) {
    // TODO: Implement save
}

void Food::load(ByteBuffer var1, int var2) {
    // TODO: Implement load
}

bool Food::finishupdate() {
    // TODO: Implement finishupdate
    return false;
}

bool Food::shouldUpdateInWorld() {
    // TODO: Implement shouldUpdateInWorld
    return false;
}

std::string Food::getName() {
    // TODO: Implement getName
    return "";
}

void Food::DoTooltip(ObjectTooltip var1, Layout var2) {
    // TODO: Implement DoTooltip
}

float Food::getEnduranceChange() {
    // TODO: Implement getEnduranceChange
    return 0;
}

void Food::setEnduranceChange(float var1) {
    // TODO: Implement setEnduranceChange
}

float Food::getUnhappyChange() {
    // TODO: Implement getUnhappyChange
    return 0;
}

float Food::getBoredomChange() {
    // TODO: Implement getBoredomChange
    return 0;
}

float Food::getHungerChange() {
    // TODO: Implement getHungerChange
    return 0;
}

float Food::getStressChange() {
    // TODO: Implement getStressChange
    return 0;
}

float Food::getBoredomChangeUnmodified() {
    // TODO: Implement getBoredomChangeUnmodified
    return 0;
}

float Food::getEnduranceChangeUnmodified() {
    // TODO: Implement getEnduranceChangeUnmodified
    return 0;
}

float Food::getStressChangeUnmodified() {
    // TODO: Implement getStressChangeUnmodified
    return 0;
}

float Food::getThirstChangeUnmodified() {
    // TODO: Implement getThirstChangeUnmodified
    return 0;
}

float Food::getUnhappyChangeUnmodified() {
    // TODO: Implement getUnhappyChangeUnmodified
    return 0;
}

float Food::getScore(SurvivorDesc var1) {
    // TODO: Implement getScore
    return 0;
}

bool Food::isBadCold() {
    // TODO: Implement isBadCold
    return false;
}

void Food::setBadCold(bool var1) {
    // TODO: Implement setBadCold
}

bool Food::isGoodHot() {
    // TODO: Implement isGoodHot
    return false;
}

void Food::setGoodHot(bool var1) {
    // TODO: Implement setGoodHot
}

bool Food::isCookedInMicrowave() {
    // TODO: Implement isCookedInMicrowave
    return false;
}

void Food::setCookedInMicrowave(bool var1) {
    // TODO: Implement setCookedInMicrowave
}

float Food::getHeat() {
    // TODO: Implement getHeat
    return 0;
}

float Food::getInvHeat() {
    // TODO: Implement getInvHeat
    return 0;
}

void Food::setHeat(float var1) {
    // TODO: Implement setHeat
}

float Food::getEndChange() {
    // TODO: Implement getEndChange
    return 0;
}

void Food::setEndChange(float var1) {
    // TODO: Implement setEndChange
}

float Food::getBaseHungChange() {
    // TODO: Implement getBaseHungChange
    return 0;
}

float Food::getHungChange() {
    // TODO: Implement getHungChange
    return 0;
}

void Food::setHungChange(float var1) {
    // TODO: Implement setHungChange
}

std::string Food::getUseOnConsume() {
    // TODO: Implement getUseOnConsume
    return "";
}

void Food::setUseOnConsume(const std::string& var1) {
    // TODO: Implement setUseOnConsume
}

bool Food::isRotten() {
    // TODO: Implement isRotten
    return false;
}

bool Food::isFresh() {
    // TODO: Implement isFresh
    return false;
}

void Food::setRotten(bool var1) {
    // TODO: Implement setRotten
}

bool Food::isbDangerousUncooked() {
    // TODO: Implement isbDangerousUncooked
    return false;
}

void Food::setbDangerousUncooked(bool var1) {
    // TODO: Implement setbDangerousUncooked
}

int Food::getLastCookMinute() {
    // TODO: Implement getLastCookMinute
    return 0;
}

void Food::setLastCookMinute(int var1) {
    // TODO: Implement setLastCookMinute
}

float Food::getThirstChange() {
    // TODO: Implement getThirstChange
    return 0;
}

void Food::setThirstChange(float var1) {
    // TODO: Implement setThirstChange
}

void Food::setReplaceOnCooked(List<std::string> var1) {
    // TODO: Implement setReplaceOnCooked
}

float Food::getBaseHunger() {
    // TODO: Implement getBaseHunger
    return 0;
}

void Food::setBaseHunger(float var1) {
    // TODO: Implement setBaseHunger
}

bool Food::isSpice() {
    // TODO: Implement isSpice
    return false;
}

void Food::setSpice(bool var1) {
    // TODO: Implement setSpice
}

bool Food::isPoison() {
    // TODO: Implement isPoison
    return false;
}

int Food::getPoisonDetectionLevel() {
    // TODO: Implement getPoisonDetectionLevel
    return 0;
}

void Food::setPoisonDetectionLevel(int var1) {
    // TODO: Implement setPoisonDetectionLevel
}

int Food::getPoisonLevelForRecipe() {
    // TODO: Implement getPoisonLevelForRecipe
    return 0;
}

void Food::setPoisonLevelForRecipe(int var1) {
    // TODO: Implement setPoisonLevelForRecipe
}

int Food::getUseForPoison() {
    // TODO: Implement getUseForPoison
    return 0;
}

void Food::setUseForPoison(int var1) {
    // TODO: Implement setUseForPoison
}

int Food::getPoisonPower() {
    // TODO: Implement getPoisonPower
    return 0;
}

void Food::setPoisonPower(int var1) {
    // TODO: Implement setPoisonPower
}

std::string Food::getFoodType() {
    // TODO: Implement getFoodType
    return "";
}

void Food::setFoodType(const std::string& var1) {
    // TODO: Implement setFoodType
}

bool Food::isRemoveNegativeEffectOnCooked() {
    // TODO: Implement isRemoveNegativeEffectOnCooked
    return false;
}

void Food::setRemoveNegativeEffectOnCooked(bool var1) {
    // TODO: Implement setRemoveNegativeEffectOnCooked
}

std::string Food::getCookingSound() {
    // TODO: Implement getCookingSound
    return "";
}

std::string Food::getCustomEatSound() {
    // TODO: Implement getCustomEatSound
    return "";
}

void Food::setCustomEatSound(const std::string& var1) {
    // TODO: Implement setCustomEatSound
}

std::string Food::getChef() {
    // TODO: Implement getChef
    return "";
}

void Food::setChef(const std::string& var1) {
    // TODO: Implement setChef
}

std::string Food::getOnCooked() {
    // TODO: Implement getOnCooked
    return "";
}

void Food::setOnCooked(const std::string& var1) {
    // TODO: Implement setOnCooked
}

std::string Food::getHerbalistType() {
    // TODO: Implement getHerbalistType
    return "";
}

void Food::setHerbalistType(const std::string& var1) {
    // TODO: Implement setHerbalistType
}

void Food::setSpices(std::vector<std::string> var1) {
    // TODO: Implement setSpices
}

Texture Food::getTex() {
    // TODO: Implement getTex
    return nullptr;
}

std::string Food::getWorldTexture() {
    // TODO: Implement getWorldTexture
    return "";
}

int Food::getReduceFoodSickness() {
    // TODO: Implement getReduceFoodSickness
    return 0;
}

void Food::setReduceFoodSickness(int var1) {
    // TODO: Implement setReduceFoodSickness
}

int Food::getFluReduction() {
    // TODO: Implement getFluReduction
    return 0;
}

void Food::setFluReduction(int var1) {
    // TODO: Implement setFluReduction
}

float Food::getPainReduction() {
    // TODO: Implement getPainReduction
    return 0;
}

void Food::setPainReduction(float var1) {
    // TODO: Implement setPainReduction
}

float Food::getCarbohydrates() {
    // TODO: Implement getCarbohydrates
    return 0;
}

void Food::setCarbohydrates(float var1) {
    // TODO: Implement setCarbohydrates
}

float Food::getLipids() {
    // TODO: Implement getLipids
    return 0;
}

void Food::setLipids(float var1) {
    // TODO: Implement setLipids
}

float Food::getProteins() {
    // TODO: Implement getProteins
    return 0;
}

void Food::setProteins(float var1) {
    // TODO: Implement setProteins
}

float Food::getCalories() {
    // TODO: Implement getCalories
    return 0;
}

void Food::setCalories(float var1) {
    // TODO: Implement setCalories
}

bool Food::isPackaged() {
    // TODO: Implement isPackaged
    return false;
}

void Food::setPackaged(bool var1) {
    // TODO: Implement setPackaged
}

float Food::getFreezingTime() {
    // TODO: Implement getFreezingTime
    return 0;
}

void Food::setFreezingTime(float var1) {
    // TODO: Implement setFreezingTime
}

void Food::freeze() {
    // TODO: Implement freeze
}

bool Food::isFrozen() {
    // TODO: Implement isFrozen
    return false;
}

void Food::setFrozen(bool var1) {
    // TODO: Implement setFrozen
}

bool Food::canBeFrozen() {
    // TODO: Implement canBeFrozen
    return false;
}

void Food::setCanBeFrozen(bool var1) {
    // TODO: Implement setCanBeFrozen
}

bool Food::isFreezing() {
    // TODO: Implement isFreezing
    return false;
}

bool Food::isThawing() {
    // TODO: Implement isThawing
    return false;
}

std::string Food::getReplaceOnRotten() {
    // TODO: Implement getReplaceOnRotten
    return "";
}

void Food::setReplaceOnRotten(const std::string& var1) {
    // TODO: Implement setReplaceOnRotten
}

void Food::multiplyFoodValues(float var1) {
    // TODO: Implement multiplyFoodValues
}

float Food::getRottenTime() {
    // TODO: Implement getRottenTime
    return 0;
}

void Food::setRottenTime(float var1) {
    // TODO: Implement setRottenTime
}

float Food::getCompostTime() {
    // TODO: Implement getCompostTime
    return 0;
}

void Food::setCompostTime(float var1) {
    // TODO: Implement setCompostTime
}

std::string Food::getOnEat() {
    // TODO: Implement getOnEat
    return "";
}

void Food::setOnEat(const std::string& var1) {
    // TODO: Implement setOnEat
}

bool Food::isBadInMicrowave() {
    // TODO: Implement isBadInMicrowave
    return false;
}

void Food::setBadInMicrowave(bool var1) {
    // TODO: Implement setBadInMicrowave
}

void Food::destroyThisItem() {
    // TODO: Implement destroyThisItem
}

} // namespace types
} // namespace inventory
} // namespace zombie
