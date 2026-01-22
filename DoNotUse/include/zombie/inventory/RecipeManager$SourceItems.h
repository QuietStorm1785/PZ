#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/RecipeManager/RMRecipeItemList/Type.h"
#include "zombie/scripting/objects/Recipe.h"

namespace zombie {
namespace inventory {

class RecipeManager {
public:
    std::shared_ptr<InventoryItem> selectedItem;
    std::vector<std::shared_ptr<InventoryItem>> allItems;
    std::vector<std::vector<std::shared_ptr<InventoryItem>>> itemsPerSource;
    std::vector<Type> typePerSource;

    RecipeManager(std::shared_ptr<Recipe> recipe, std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<InventoryItem> selectedItem, const std::vector<std::shared_ptr<InventoryItem>>& items) {
        this->itemsPerSource.resize(recipe->getSource().size());
        for (auto& vec : this->itemsPerSource) {
            vec = std::vector<std::shared_ptr<InventoryItem>>();
        }

        this->typePerSource.resize(recipe->getSource().size());
        this->selectedItem = selectedItem;
    }

    // Returns all items
    std::vector<std::shared_ptr<InventoryItem>> getItems() {
        return allItems;
    }
};

} // namespace inventory
} // namespace zombie
