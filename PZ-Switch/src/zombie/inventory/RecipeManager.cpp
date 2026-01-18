#include "zombie/inventory/RecipeManager.h"

namespace zombie {
namespace inventory {

void RecipeManager::Loaded() {
 // TODO: Implement Loaded
}

Item RecipeManager::resolveItemModuleDotType(Recipe recipe,
 const std::string &string0,
 Set<String> set,
 const std::string &string2) {
 // TODO: Implement resolveItemModuleDotType
 return nullptr;
}

void RecipeManager::LoadedAfterLua() {
 // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Recipe recipe, ArrayList<Item> arrayList) {
 // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Recipe recipe, const std::string &string0,
 const std::string &string1) {
 // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Recipe.Source source,
 ArrayList<Item> arrayList) {
 // TODO: Implement LoadedAfterLua
}

bool RecipeManager::DoesWipeUseDelta(const std::string &itemToUse,
 const std::string &itemToMake) {
 // TODO: Implement DoesWipeUseDelta
 return false;
}

int RecipeManager::getKnownRecipesNumber(IsoGameCharacter chr) {
 // TODO: Implement getKnownRecipesNumber
 return 0;
}

bool RecipeManager::DoesUseItemUp(const std::string &itemToUse, Recipe recipe) {
 // TODO: Implement DoesUseItemUp
 return false;
}

bool RecipeManager::IsItemDestroyed(const std::string &itemToUse,
 Recipe recipe) {
 // TODO: Implement IsItemDestroyed
 return false;
}

float RecipeManager::UseAmount(const std::string &sourceFullType, Recipe recipe,
 IsoGameCharacter chr) {
 // TODO: Implement UseAmount
 return 0;
}

bool RecipeManager::IsRecipeValid(Recipe recipe, IsoGameCharacter chr,
 InventoryItem item,
 ArrayList<ItemContainer> containers) {
 // TODO: Implement IsRecipeValid
 return false;
}

bool RecipeManager::isNearItem(Recipe recipe, IsoGameCharacter character) {
 // TODO: Implement isNearItem
 return false;
}

bool RecipeManager::CanPerform(Recipe recipe, IsoGameCharacter character,
 InventoryItem item) {
 // TODO: Implement CanPerform
 return false;
}

bool RecipeManager::HasRequiredSkill(Recipe recipe,
 IsoGameCharacter character) {
 // TODO: Implement HasRequiredSkill
 return false;
}

bool RecipeManager::RecipeContainsItem(Recipe recipe, InventoryItem item) {
 // TODO: Implement RecipeContainsItem
 return false;
}

bool RecipeManager::HasAllRequiredItems(Recipe recipe, IsoGameCharacter chr,
 InventoryItem selectedItem,
 ArrayList<ItemContainer> containers) {
 // TODO: Implement HasAllRequiredItems
 return false;
}

bool RecipeManager::isAllItemsUsableRotten(Recipe recipe,
 IsoGameCharacter character,
 InventoryItem item1,
 ArrayList<ItemContainer> arrayList) {
 // TODO: Implement isAllItemsUsableRotten
 return false;
}

bool RecipeManager::hasHeat(Recipe recipe, InventoryItem item,
 ArrayList<ItemContainer> containers,
 IsoGameCharacter chr) {
 // TODO: Implement hasHeat
 return false;
}

return RecipeManager::getAvailableItems() {
 // TODO: Implement getAvailableItems
 return nullptr;
}

return RecipeManager::getAvailableItems() {
 // TODO: Implement getAvailableItems
 return nullptr;
}

int RecipeManager::getNumberOfTimesRecipeCanBeDone(
 Recipe recipe, IsoGameCharacter chr, ArrayList<ItemContainer> containers,
 InventoryItem selectedItem) {
 // TODO: Implement getNumberOfTimesRecipeCanBeDone
 return 0;
}

InventoryItem
RecipeManager::PerformMakeItem(Recipe recipe, InventoryItem selectedItem,
 IsoGameCharacter chr,
 ArrayList<ItemContainer> containers) {
 // TODO: Implement PerformMakeItem
 return nullptr;
}

bool RecipeManager::ReduceUses(InventoryItem item, float float1,
 IsoGameCharacter var2) {
 // TODO: Implement ReduceUses
 return false;
}

int RecipeManager::AvailableUses(InventoryItem item) {
 // TODO: Implement AvailableUses
 return 0;
}

void RecipeManager::GivePlayerExperience(Recipe recipe,
 ArrayList<InventoryItem> arrayList,
 InventoryItem item,
 IsoGameCharacter character) {
 // TODO: Implement GivePlayerExperience
}

void RecipeManager::DebugPrintAllRecipes() {
 // TODO: Implement DebugPrintAllRecipes
}

Recipe RecipeManager::getDismantleRecipeFor(const std::string &item) {
 // TODO: Implement getDismantleRecipeFor
 return nullptr;
}

void RecipeManager::getItemsFromContainers(IsoGameCharacter character,
 ArrayList<ItemContainer> arrayList,
 InventoryItem item) {
 // TODO: Implement getItemsFromContainers
}

void RecipeManager::getItemsFromContainer(IsoGameCharacter character,
 ItemContainer container,
 InventoryItem item1) {
 // TODO: Implement getItemsFromContainer
}

bool RecipeManager::Test(InventoryItem item) {
 // TODO: Implement Test
 return false;
}

bool RecipeManager::hasItems() {
 // TODO: Implement hasItems
 return false;
}

bool RecipeManager::isKeep(const std::string &string) {
 // TODO: Implement isKeep
 return false;
}

void RecipeManager::getAvailableItems(RecipeManager.SourceItems sourceItems,
 bool boolean0) {
 // TODO: Implement getAvailableItems
}

void RecipeManager::Use(ArrayList<InventoryItem> arrayList) {
 // TODO: Implement Use
}

void RecipeManager::release(RecipeManager.RMRecipe rMRecipe) {
 // TODO: Implement release
}

int RecipeManager::Use(int int1) {
 // TODO: Implement Use
 return 0;
}

int RecipeManager::UseWater(int int1) {
 // TODO: Implement UseWater
 return 0;
}

void RecipeManager::release(RecipeManager.RMRecipeItem rMRecipeItem) {
 // TODO: Implement release
}

void RecipeManager::getItemsFrom(
 ArrayList<RecipeManager.RMRecipeItem> arrayList,
 RecipeManager.RMRecipe rMRecipe) {
 // TODO: Implement getItemsFrom
}

bool RecipeManager::hasItems() {
 // TODO: Implement hasItems
 return false;
}

int RecipeManager::indexOf(InventoryItem item) {
 // TODO: Implement indexOf
 return 0;
}

void RecipeManager::getAvailableItems(RecipeManager.SourceItems sourceItems,
 bool boolean0) {
 // TODO: Implement getAvailableItems
}

void RecipeManager::Use(ArrayList<InventoryItem> arrayList) {
 // TODO: Implement Use
}

void RecipeManager::release(RecipeManager.RMRecipeItemList rMRecipeItemList) {
 // TODO: Implement release
}

void RecipeManager::getItemsFrom(
 ArrayList<RecipeManager.RMRecipeItem> arrayList,
 RecipeManager.RMRecipe rMRecipe) {
 // TODO: Implement getItemsFrom
}

bool RecipeManager::hasItems() {
 // TODO: Implement hasItems
 return false;
}

bool RecipeManager::isKeep(const std::string &string) {
 // TODO: Implement isKeep
 return false;
}

void RecipeManager::getAvailableItems(RecipeManager.SourceItems sourceItems,
 bool boolean0) {
 // TODO: Implement getAvailableItems
}

void RecipeManager::Use(ArrayList<InventoryItem> arrayList) {
 // TODO: Implement Use
}

void RecipeManager::release(RecipeManager.RMRecipeSource rMRecipeSource) {
 // TODO: Implement release
}

} // namespace inventory
} // namespace zombie
