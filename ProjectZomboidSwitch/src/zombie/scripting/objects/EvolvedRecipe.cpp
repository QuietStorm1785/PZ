#include <string>
#include <vector>
#include "zombie\scripting\objects/EvolvedRecipe.h"

namespace zombie {
namespace scripting {
namespace objects {

public EvolvedRecipe::EvolvedRecipe(const std::string& var1) {
    // TODO: Implement EvolvedRecipe
    return nullptr;
}

void EvolvedRecipe::Load(const std::string& var1, std::string[] var2) {
    // TODO: Implement Load
}

bool EvolvedRecipe::needToBeCooked(InventoryItem var1) {
    // TODO: Implement needToBeCooked
    return false;
}

void EvolvedRecipe::checkItemCanBeUse(ItemContainer var1, const std::string& var2, InventoryItem var3, int var4, std::vector<InventoryItem> var5) {
    // TODO: Implement checkItemCanBeUse
}

InventoryItem EvolvedRecipe::addItem(InventoryItem var1, InventoryItem var2, IsoGameCharacter var3) {
    // TODO: Implement addItem
    return nullptr;
}

void EvolvedRecipe::checkUniqueRecipe(InventoryItem var1) {
    // TODO: Implement checkUniqueRecipe
}

void EvolvedRecipe::addPoison(InventoryItem var1, InventoryItem var2, IsoGameCharacter var3) {
    // TODO: Implement addPoison
}

void EvolvedRecipe::useSpice(Food var1, Food var2, float var3, int var4) {
    // TODO: Implement useSpice
}

ItemRecipe EvolvedRecipe::getItemRecipe(InventoryItem var1) {
    // TODO: Implement getItemRecipe
    return nullptr;
}

std::string EvolvedRecipe::getName() {
    // TODO: Implement getName
    return "";
}

std::string EvolvedRecipe::getOriginalname() {
    // TODO: Implement getOriginalname
    return "";
}

std::string EvolvedRecipe::getUntranslatedName() {
    // TODO: Implement getUntranslatedName
    return "";
}

std::string EvolvedRecipe::getBaseItem() {
    // TODO: Implement getBaseItem
    return "";
}

std::string EvolvedRecipe::getResultItem() {
    // TODO: Implement getResultItem
    return "";
}

std::string EvolvedRecipe::getFullResultItem() {
    // TODO: Implement getFullResultItem
    return "";
}

bool EvolvedRecipe::isCookable() {
    // TODO: Implement isCookable
    return false;
}

int EvolvedRecipe::getMaxItems() {
    // TODO: Implement getMaxItems
    return 0;
}

bool EvolvedRecipe::isResultItem(InventoryItem var1) {
    // TODO: Implement isResultItem
    return false;
}

bool EvolvedRecipe::isSpiceAdded(InventoryItem var1, InventoryItem var2) {
    // TODO: Implement isSpiceAdded
    return false;
}

std::string EvolvedRecipe::getAddIngredientSound() {
    // TODO: Implement getAddIngredientSound
    return "";
}

void EvolvedRecipe::setIsHidden(bool var1) {
    // TODO: Implement setIsHidden
}

bool EvolvedRecipe::isHidden() {
    // TODO: Implement isHidden
    return false;
}

bool EvolvedRecipe::isAllowFrozenItem() {
    // TODO: Implement isAllowFrozenItem
    return false;
}

void EvolvedRecipe::setAllowFrozenItem(bool var1) {
    // TODO: Implement setAllowFrozenItem
}

} // namespace objects
} // namespace scripting
} // namespace zombie
