#include "zombie/scripting/objects/EvolvedRecipe.h"

namespace zombie {
namespace scripting {
namespace objects {

public EvolvedRecipe::EvolvedRecipe(const std::string& _name) {
 // TODO: Implement EvolvedRecipe
 return nullptr;
}

void EvolvedRecipe::Load(const std::string& string0, String[] strings0) {
 // TODO: Implement Load
}

bool EvolvedRecipe::needToBeCooked(InventoryItem itemTest) {
 // TODO: Implement needToBeCooked
 return false;
}

void EvolvedRecipe::checkItemCanBeUse(ItemContainer container, const std::string& string, InventoryItem item1, int int1, ArrayList<InventoryItem> arrayList1) {
 // TODO: Implement checkItemCanBeUse
}

InventoryItem EvolvedRecipe::addItem(InventoryItem _baseItem, InventoryItem usedItem, IsoGameCharacter chr) {
 // TODO: Implement addItem
 return nullptr;
}

void EvolvedRecipe::checkUniqueRecipe(InventoryItem item) {
 // TODO: Implement checkUniqueRecipe
}

void EvolvedRecipe::addPoison(InventoryItem item0, InventoryItem item1, IsoGameCharacter character) {
 // TODO: Implement addPoison
}

void EvolvedRecipe::useSpice(Food food1, Food food0, float float1, int int0) {
 // TODO: Implement useSpice
}

ItemRecipe EvolvedRecipe::getItemRecipe(InventoryItem usedItem) {
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

bool EvolvedRecipe::isResultItem(InventoryItem item) {
 // TODO: Implement isResultItem
 return false;
}

bool EvolvedRecipe::isSpiceAdded(InventoryItem _baseItem, InventoryItem spiceItem) {
 // TODO: Implement isSpiceAdded
 return false;
}

std::string EvolvedRecipe::getAddIngredientSound() {
 // TODO: Implement getAddIngredientSound
 return "";
}

void EvolvedRecipe::setIsHidden(bool hide) {
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

void EvolvedRecipe::setAllowFrozenItem(bool allow) {
 // TODO: Implement setAllowFrozenItem
}

} // namespace objects
} // namespace scripting
} // namespace zombie
