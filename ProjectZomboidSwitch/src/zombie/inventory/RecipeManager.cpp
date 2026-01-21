#include <string>
#include <vector>
#include "zombie/inventory/RecipeManager.h"

namespace zombie {
namespace inventory {

void RecipeManager::Loaded() {
    // TODO: Implement Loaded
}

Item RecipeManager::resolveItemModuleDotType(Recipe var0, const std::string& var1, Set<std::string> var2, const std::string& var3) {
    // TODO: Implement resolveItemModuleDotType
    return nullptr;
}

void RecipeManager::LoadedAfterLua() {
    // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Recipe var0, std::vector<Item> var1) {
    // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Recipe var0, const std::string& var1, const std::string& var2) {
    // TODO: Implement LoadedAfterLua
}

void RecipeManager::LoadedAfterLua(Source var0, std::vector<Item> var1) {
    // TODO: Implement LoadedAfterLua
}

bool RecipeManager::DoesWipeUseDelta(const std::string& var0, const std::string& var1) {
    // TODO: Implement DoesWipeUseDelta
    return false;
}

int RecipeManager::getKnownRecipesNumber(IsoGameCharacter var0) {
    // TODO: Implement getKnownRecipesNumber
    return 0;
}

bool RecipeManager::DoesUseItemUp(const std::string& var0, Recipe var1) {
    // TODO: Implement DoesUseItemUp
    return false;
}

bool RecipeManager::IsItemDestroyed(const std::string& var0, Recipe var1) {
    // TODO: Implement IsItemDestroyed
    return false;
}

float RecipeManager::UseAmount(const std::string& var0, Recipe var1, IsoGameCharacter var2) {
    // TODO: Implement UseAmount
    return 0;
}

bool RecipeManager::IsRecipeValid(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
    // TODO: Implement IsRecipeValid
    return false;
}

bool RecipeManager::isNearItem(Recipe var0, IsoGameCharacter var1) {
    // TODO: Implement isNearItem
    return false;
}

bool RecipeManager::CanPerform(Recipe var0, IsoGameCharacter var1, InventoryItem var2) {
    // TODO: Implement CanPerform
    return false;
}

bool RecipeManager::HasRequiredSkill(Recipe var0, IsoGameCharacter var1) {
    // TODO: Implement HasRequiredSkill
    return false;
}

bool RecipeManager::RecipeContainsItem(Recipe var0, InventoryItem var1) {
    // TODO: Implement RecipeContainsItem
    return false;
}

bool RecipeManager::HasAllRequiredItems(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
    // TODO: Implement HasAllRequiredItems
    return false;
}

bool RecipeManager::isAllItemsUsableRotten(Recipe var0, IsoGameCharacter var1, InventoryItem var2, std::vector<ItemContainer> var3) {
    // TODO: Implement isAllItemsUsableRotten
    return false;
}

bool RecipeManager::hasHeat(Recipe var0, InventoryItem var1, std::vector<ItemContainer> var2, IsoGameCharacter var3) {
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

int RecipeManager::getNumberOfTimesRecipeCanBeDone(Recipe var0, IsoGameCharacter var1, std::vector<ItemContainer> var2, InventoryItem var3) {
    // TODO: Implement getNumberOfTimesRecipeCanBeDone
    return 0;
}

InventoryItem RecipeManager::GetMovableRecipeTool(bool var0, Recipe var1, InventoryItem var2, IsoGameCharacter var3, std::vector<ItemContainer> var4) {
    // TODO: Implement GetMovableRecipeTool
    return nullptr;
}

InventoryItem RecipeManager::PerformMakeItem(Recipe var0, InventoryItem var1, IsoGameCharacter var2, std::vector<ItemContainer> var3) {
    // TODO: Implement PerformMakeItem
    return nullptr;
}

bool RecipeManager::ReduceUses(InventoryItem var0, float var1, IsoGameCharacter var2) {
    // TODO: Implement ReduceUses
    return false;
}

int RecipeManager::AvailableUses(InventoryItem var0) {
    // TODO: Implement AvailableUses
    return 0;
}

void RecipeManager::GivePlayerExperience(Recipe var0, std::vector<InventoryItem> var1, InventoryItem var2, IsoGameCharacter var3) {
    // TODO: Implement GivePlayerExperience
}

void RecipeManager::DebugPrintAllRecipes() {
    // TODO: Implement DebugPrintAllRecipes
}

Recipe RecipeManager::getDismantleRecipeFor(const std::string& var0) {
    // TODO: Implement getDismantleRecipeFor
    return nullptr;
}

} // namespace inventory
} // namespace zombie
