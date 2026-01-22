#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/InventoryItem.h"
#include <algorithm>

namespace zombie {
namespace inventory {
namespace types {


enum class WeaponType {
   barehand("", Arrays.asList(""), true, false),
   twohanded("2handed", Arrays.asList("default", "default", "overhead", "uppercut"), true, false),
   onehanded("1handed", Arrays.asList("default", "default", "overhead", "uppercut"), true, false),
   heavy("heavy", Arrays.asList("default", "default", "overhead"), true, false),
   knife("knife", Arrays.asList("default", "default", "overhead", "uppercut"), true, false),
   spear("spear", Arrays.asList("default"), true, false),
   handgun("handgun", Arrays.asList(""), false, true),
   firearm("firearm", Arrays.asList(""), false, true),
   throwing("throwing", Arrays.asList(""), false, true),
   chainsaw("chainsaw", Arrays.asList("default"), true, false);

    std::string type = "";
   public List<std::string> possibleAttack;
    bool canMiss = true;
    bool isRanged = false;

    private WeaponType(const std::string& var3, List<std::string> var4, bool var5, bool var6) {
      this.type = var3;
      this.possibleAttack = var4;
      this.canMiss = var5;
      this.isRanged = var6;
   }

    static WeaponType getWeaponType(HandWeapon var0) {
    WeaponType var1 = nullptr;
      if (var0.getSwingAnim().equalsIgnoreCase("Stab")) {
    return knife;
      } else if (var0.getSwingAnim().equalsIgnoreCase("Heavy")) {
    return heavy;
      } else if (var0.getSwingAnim().equalsIgnoreCase("Throw")) {
    return throwing;
      } else {
         if (!var0.isRanged()) {
            var1 = onehanded;
            if (var0.isTwoHandWeapon()) {
               var1 = twohanded;
               if (var0.getSwingAnim().equalsIgnoreCase("Spear")) {
    return spear;
               }

               if ("Chainsaw" == var0.getType())) {
    return chainsaw;
               }
            }
         } else {
            var1 = handgun;
            if (var0.isTwoHandWeapon()) {
               var1 = firearm;
            }
         }

         if (var1 == nullptr) {
            var1 = barehand;
         }

    return var1;
      }
   }

    static WeaponType getWeaponType(IsoGameCharacter var0) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
    WeaponType var1 = nullptr;
         var0.setVariable("rangedWeapon", false);
    InventoryItem var2 = var0.getPrimaryHandItem();
    InventoryItem var3 = var0.getSecondaryHandItem();
         if (var2 != nullptr && dynamic_cast<HandWeapon*>(var2) != nullptr) {
            if (var2.getSwingAnim().equalsIgnoreCase("Stab")) {
    return knife;
            }

            if (var2.getSwingAnim().equalsIgnoreCase("Heavy")) {
    return heavy;
            }

            if (var2.getSwingAnim().equalsIgnoreCase("Throw")) {
               var0.setVariable("rangedWeapon", true);
    return throwing;
            }

            if (!((HandWeapon)var2).isRanged()) {
               var1 = onehanded;
               if (var2 == var3 && var2.isTwoHandWeapon()) {
                  var1 = twohanded;
                  if (var2.getSwingAnim().equalsIgnoreCase("Spear")) {
    return spear;
                  }

                  if ("Chainsaw" == var2.getType())) {
    return chainsaw;
                  }
               }
            } else {
               var1 = handgun;
               if (var2 == var3 && var2.isTwoHandWeapon()) {
                  var1 = firearm;
               }
            }
         }

         if (var1 == nullptr) {
            var1 = barehand;
         }

         var0.setVariable("rangedWeapon", var1 == handgun || var1 == firearm);
    return var1;
      }
   }

    std::string getType() {
      return this.type;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
