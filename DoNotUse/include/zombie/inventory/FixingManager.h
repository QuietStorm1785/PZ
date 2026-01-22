#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Fixing.h"
#include "zombie/scripting/objects/Fixing/Fixer.h"
#include "zombie/scripting/objects/Fixing/FixerSkill.h"

namespace zombie {
namespace inventory {


class FixingManager {
public:
    // Returns all possible fixes for the given item
    static std::vector<std::shared_ptr<Fixing>> getFixes(const std::shared_ptr<InventoryItem>& item) {
        std::vector<std::shared_ptr<Fixing>> fixes;
        auto allFixings = ScriptManager::instance->getAllFixing();

        for (const auto& fixing : allFixings) {
            if (fixing && fixing->getRequiredItem().contains(item->getType())) {
                fixes.push_back(fixing);
            }
        }

        return fixes;
    }

    // Attempts to fix the item using the specified fixing and fixer
    static std::shared_ptr<InventoryItem> fixItem(std::shared_ptr<InventoryItem> item, std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<Fixing> fixing, std::shared_ptr<Fixer> fixer) {
        if (Rand::Next(100) >= getChanceOfFail(item, character, fixing, fixer)) {
            double repairPercent = getCondRepaired(item, character, fixing, fixer);
            int damage = item->getConditionMax() - item->getCondition();
            double repairAmount = damage * (repairPercent / 100.0);
            int actualRepair = static_cast<int>(std::round(repairAmount));
            if (actualRepair == 0) {
                actualRepair = 1;
            }

            item->setCondition(item->getCondition() + actualRepair);
            item->setHaveBeenRepaired(item->getHaveBeenRepaired() + 1);
        } else if (item->getCondition() > 0 && Rand::Next(5) == 0) {
            item->setCondition(item->getCondition() - 1);
            character->getEmitter()->playSound("FixingItemFailed");
        }

        useFixer(character, fixer, item);
        if (fixing->getGlobalItem()) {
            useFixer(character, fixing->getGlobalItem(), item);
        }

        addXp(character, fixer);
        return item;
    }

    // Adds experience points for using the fixer
    static void addXp(std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<Fixer> fixer) {
        if (fixer->getFixerSkills()) {
            for (const auto& skill : *fixer->getFixerSkills()) {
                character->getXp()->AddXP(Perks::FromString(skill->getSkillName()), Rand::Next(3, 6));
            }
        }
    }

    // Consumes fixer items from the character's inventory
    static void useFixer(std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<Fixer> fixer, std::shared_ptr<InventoryItem> item) {
        int usesNeeded = fixer->getNumberOfUse();

        auto& inventoryItems = character->getInventory()->getItems();
        for (size_t i = 0; i < inventoryItems.size(); ++i) {
            auto invItem = inventoryItems[i];
            if (invItem != item && invItem && invItem->getType() == fixer->getFixerName()) {
                if (auto drainable = std::dynamic_pointer_cast<DrainableComboItem>(invItem)) {
                    if (invItem->getType() == "DuctTape" || invItem->getType() == "Scotchtape") {
                        character->getEmitter()->playSound("FixWithTape");
                    }

                    int availableUses = drainable->getDrainableUsesInt();
                    int usesToConsume = std::min(availableUses, usesNeeded);

                    for (int j = 0; j < usesToConsume; ++j) {
                        invItem->Use();
                        --usesNeeded;
                        if (std::find(inventoryItems.begin(), inventoryItems.end(), invItem) == inventoryItems.end()) {
                            --i;  // Adjust index if item was removed
                            break;
                        }
                    }
                } else {
                    if (auto weapon = std::dynamic_pointer_cast<HandWeapon>(invItem)) {
                        if (character->getSecondaryHandItem() == invItem) {
                            character->setSecondaryHandItem(nullptr);
                        }

                        if (character->getPrimaryHandItem() == invItem) {
                            character->setPrimaryHandItem(nullptr);
                        }

                        // Disassemble weapon parts
                        if (weapon->getScope()) {
                            character->getInventory()->AddItem(weapon->getScope());
                        }
                        if (weapon->getClip()) {
                            character->getInventory()->AddItem(weapon->getClip());
                        }
                        if (weapon->getSling()) {
                            character->getInventory()->AddItem(weapon->getSling());
                        }
                        if (weapon->getStock()) {
                            character->getInventory()->AddItem(weapon->getStock());
                        }
                        if (weapon->getCanon()) {
                            character->getInventory()->AddItem(weapon->getCanon());
                        }
                        if (weapon->getRecoilpad()) {
                            character->getInventory()->AddItem(weapon->getRecoilpad());
                        }

                        int ammoToSpawn = 0;
                        if (weapon->getMagazineType() && weapon->isContainsClip()) {
                            auto magazine = InventoryItemFactory::CreateItem(weapon->getMagazineType());
                            magazine->setCurrentAmmoCount(weapon->getCurrentAmmoCount());
                            character->getInventory()->AddItem(magazine);
                        } else if (weapon->getCurrentAmmoCount() > 0) {
                            ammoToSpawn += weapon->getCurrentAmmoCount();
                        }

                        if (weapon->haveChamber() && weapon->isRoundChambered()) {
                            ++ammoToSpawn;
                        }

                        if (ammoToSpawn > 0) {
                            for (int k = 0; k < ammoToSpawn; ++k) {
                                auto ammo = InventoryItemFactory::CreateItem(weapon->getAmmoType());
                                character->getInventory()->AddItem(ammo);
                            }
                        }
                    }

                    character->getInventory()->Remove(invItem);
                    --i;
                    --usesNeeded;
                }

                if (usesNeeded == 0) {
                    break;
                }
            }
        }
    }

    // Calculates the chance of failure when fixing an item
    static double getChanceOfFail(std::shared_ptr<InventoryItem> item, std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<Fixing> fixing, std::shared_ptr<Fixer> fixer) {
        double chance = 3.0;
        if (fixer->getFixerSkills()) {
            for (const auto& skill : *fixer->getFixerSkills()) {
                int charLevel = character->getPerkLevel(Perks::FromString(skill->getSkillName()));
                int reqLevel = skill->getSkillLevel();
                if (charLevel < reqLevel) {
                    chance += (reqLevel - charLevel) * 30;
                } else {
                    chance -= (charLevel - reqLevel) * 5;
                }
            }
        }

        chance += item->getHaveBeenRepaired() * 2;
        if (character->Traits->Lucky->isSet()) {
            chance -= 5.0;
        }

        if (character->Traits->Unlucky->isSet()) {
            chance += 5.0;
        }

        if (chance > 100.0) {
            chance = 100.0;
        }

        if (chance < 0.0) {
            chance = 0.0;
        }

        return chance;
    }

    // Calculates the condition repaired percentage
    static double getCondRepaired(std::shared_ptr<InventoryItem> item, std::shared_ptr<IsoGameCharacter> character, std::shared_ptr<Fixing> fixing, std::shared_ptr<Fixer> fixer) {
        double repairPercent = 0.0;

        auto fixerIndex = fixing->getFixers().indexOf(fixer);
        if (fixerIndex == 0) {
            repairPercent = 50.0 / item->getHaveBeenRepaired();
        } else if (fixerIndex == 1) {
            repairPercent = 20.0 / item->getHaveBeenRepaired();
        } else {
            repairPercent = 10.0 / item->getHaveBeenRepaired();
        }

        if (fixer->getFixerSkills()) {
            for (const auto& skill : *fixer->getFixerSkills()) {
                int charLevel = character->getPerkLevel(Perks::FromString(skill->getSkillName()));
                int reqLevel = skill->getSkillLevel();
                if (charLevel > reqLevel) {
                    repairPercent += std::min((charLevel - reqLevel) * 5, 25);
                } else {
                    repairPercent -= (reqLevel - charLevel) * 15;
                }
            }
        }

        repairPercent *= fixing->getConditionModifier();
        repairPercent = std::max(0.0, repairPercent);
        return std::min(100.0, repairPercent);
    }
}
} // namespace inventory
} // namespace zombie
