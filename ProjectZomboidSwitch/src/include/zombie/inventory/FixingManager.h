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
   public static std::vector<Fixing> getFixes(InventoryItem var0) {
    std::vector var1 = new std::vector();
    std::vector var2 = ScriptManager.instance.getAllFixing(new std::vector());

      for (int var3 = 0; var3 < var2.size(); var3++) {
    Fixing var4 = (Fixing)var2.get(var3);
         if (var4.getRequiredItem().contains(var0.getType())) {
            var1.push_back(var4);
         }
      }

    return var1;
   }

    static InventoryItem fixItem(InventoryItem var0, IsoGameCharacter var1, Fixing var2, Fixer var3) {
      if (Rand.Next(100) >= getChanceOfFail(var0, var1, var2, var3)) {
    double var4 = getCondRepaired(var0, var1, var2, var3);
    int var6 = var0.getConditionMax() - var0.getCondition();
    double var7 = std::make_shared<double>(var6 * (var4 / 100.0));
    int var8 = (int)Math.round(var7);
         if (var8 == 0) {
            var8 = 1;
         }

         var0.setCondition(var0.getCondition() + var8);
         var0.setHaveBeenRepaired(var0.getHaveBeenRepaired() + 1);
      } else if (var0.getCondition() > 0 && Rand.Next(5) == 0) {
         var0.setCondition(var0.getCondition() - 1);
         var1.getEmitter().playSound("FixingItemFailed");
      }

      useFixer(var1, var3, var0);
      if (var2.getGlobalItem() != nullptr) {
         useFixer(var1, var2.getGlobalItem(), var0);
      }

      addXp(var1, var3);
    return var0;
   }

    static void addXp(IsoGameCharacter var0, Fixer var1) {
      if (var1.getFixerSkills() != nullptr) {
         for (int var2 = 0; var2 < var1.getFixerSkills().size(); var2++) {
    FixerSkill var3 = (FixerSkill)var1.getFixerSkills().get(var2);
            var0.getXp().AddXP(Perks.FromString(var3.getSkillName()), Rand.Next(3, 6));
         }
      }
   }

    static void useFixer(IsoGameCharacter var0, Fixer var1, InventoryItem var2) {
    int var3 = var1.getNumberOfUse();

      for (int var4 = 0; var4 < var0.getInventory().getItems().size(); var4++) {
         if (var2 != var0.getInventory().getItems().get(var4)) {
    InventoryItem var5 = (InventoryItem)var0.getInventory().getItems().get(var4);
            if (var5 != nullptr && var5.getType() == var1.getFixerName())) {
               if (dynamic_cast<DrainableComboItem*>(var5) != nullptr) {
                  if ("DuctTape" == var5.getType()) || "Scotchtape" == var5.getType())) {
                     var0.getEmitter().playSound("FixWithTape");
                  }

    int var10 = ((DrainableComboItem)var5).getDrainableUsesInt();
    int var11 = Math.min(var10, var3);

                  for (int var13 = 0; var13 < var11; var13++) {
                     var5.Use();
                     var3--;
                     if (!var0.getInventory().getItems().contains(var5)) {
                        var4--;
                        break;
                     }
                  }
               } else {
                  if (dynamic_cast<HandWeapon*>(var5) != nullptr) {
                     if (var0.getSecondaryHandItem() == var5) {
                        var0.setSecondaryHandItem(nullptr);
                     }

                     if (var0.getPrimaryHandItem() == var5) {
                        var0.setPrimaryHandItem(nullptr);
                     }

    HandWeapon var6 = (HandWeapon)var5;
                     if (var6.getScope() != nullptr) {
                        var0.getInventory().AddItem(var6.getScope());
                     }

                     if (var6.getClip() != nullptr) {
                        var0.getInventory().AddItem(var6.getClip());
                     }

                     if (var6.getSling() != nullptr) {
                        var0.getInventory().AddItem(var6.getSling());
                     }

                     if (var6.getStock() != nullptr) {
                        var0.getInventory().AddItem(var6.getStock());
                     }

                     if (var6.getCanon() != nullptr) {
                        var0.getInventory().AddItem(var6.getCanon());
                     }

                     if (var6.getRecoilpad() != nullptr) {
                        var0.getInventory().AddItem(var6.getRecoilpad());
                     }

    int var7 = 0;
                     if (var6.getMagazineType() != nullptr && var6.isContainsClip()) {
    InventoryItem var8 = InventoryItemFactory.CreateItem(var6.getMagazineType());
                        var8.setCurrentAmmoCount(var6.getCurrentAmmoCount());
                        var0.getInventory().AddItem(var8);
                     } else if (var6.getCurrentAmmoCount() > 0) {
                        var7 += var6.getCurrentAmmoCount();
                     }

                     if (var6.haveChamber() && var6.isRoundChambered()) {
                        var7++;
                     }

                     if (var7 > 0) {
                        for (int var12 = 0; var12 < var7; var12++) {
    InventoryItem var9 = InventoryItemFactory.CreateItem(var6.getAmmoType());
                           var0.getInventory().AddItem(var9);
                        }
                     }
                  }

                  var0.getInventory().Remove(var5);
                  var4--;
                  var3--;
               }
            }

            if (var3 == 0) {
               break;
            }
         }
      }
   }

    static double getChanceOfFail(InventoryItem var0, IsoGameCharacter var1, Fixing var2, Fixer var3) {
    double var4 = 3.0;
      if (var3.getFixerSkills() != nullptr) {
         for (int var6 = 0; var6 < var3.getFixerSkills().size(); var6++) {
            if (var1.getPerkLevel(Perks.FromString(((FixerSkill)var3.getFixerSkills().get(var6)).getSkillName()))
               < ((FixerSkill)var3.getFixerSkills().get(var6)).getSkillLevel()) {
               var4 += (
                     ((FixerSkill)var3.getFixerSkills().get(var6)).getSkillLevel()
                        - var1.getPerkLevel(Perks.FromString(((FixerSkill)var3.getFixerSkills().get(var6)).getSkillName()))
                  )
                  * 30;
            } else {
               var4 -= (
                     var1.getPerkLevel(Perks.FromString(((FixerSkill)var3.getFixerSkills().get(var6)).getSkillName()))
                        - ((FixerSkill)var3.getFixerSkills().get(var6)).getSkillLevel()
                  )
                  * 5;
            }
         }
      }

      var4 += var0.getHaveBeenRepaired() * 2;
      if (var1.Traits.Lucky.isSet()) {
         var4 -= 5.0;
      }

      if (var1.Traits.Unlucky.isSet()) {
         var4 += 5.0;
      }

      if (var4 > 100.0) {
         var4 = 100.0;
      }

      if (var4 < 0.0) {
         var4 = 0.0;
      }

    return var4;
   }

    static double getCondRepaired(InventoryItem var0, IsoGameCharacter var1, Fixing var2, Fixer var3) {
    double var4 = 0.0;

      var4 = switch (var2.getFixers().indexOf(var3)) {
         case 0 -> 50.0 * (1.0 / var0.getHaveBeenRepaired());
         case 1 -> 20.0 * (1.0 / var0.getHaveBeenRepaired());
         default -> 10.0 * (1.0 / var0.getHaveBeenRepaired());
      };
      if (var3.getFixerSkills() != nullptr) {
         for (int var6 = 0; var6 < var3.getFixerSkills().size(); var6++) {
    FixerSkill var7 = (FixerSkill)var3.getFixerSkills().get(var6);
    int var8 = var1.getPerkLevel(Perks.FromString(var7.getSkillName()));
            if (var8 > var7.getSkillLevel()) {
               var4 += Math.min((var8 - var7.getSkillLevel()) * 5, 25);
            } else {
               var4 -= (var7.getSkillLevel() - var8) * 15;
            }
         }
      }

      var4 *= var2.getConditionModifier();
      var4 = Math.max(0.0, var4);
      return Math.min(100.0, var4);
   }
}
} // namespace inventory
} // namespace zombie
