#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/scripting/objects/Fixing/Fixer.h"
#include "zombie/scripting/objects/Fixing/FixerSkill.h"
#include "zombie/scripting/objects/Fixing/PredicateRequired.h"
#include "zombie/util/Type.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class Fixing : public BaseScriptObject {
public:
    std::string name = nullptr;
   private std::vector<std::string> require = nullptr;
   private const std::list<Fixer> fixers = std::make_unique<std::list<>>();
    Fixer globalItem = nullptr;
    float conditionModifier = 1.0F;
    static const PredicateRequired s_PredicateRequired = std::make_shared<PredicateRequired>();
   private static const std::vector<InventoryItem> s_InventoryItems = std::make_unique<std::vector<>>();

    void Load(const std::string& var1, std::string[] var2) {
      this.setName(var1);

      for (int var3 = 0; var3 < var2.length; var3++) {
         if (!var2[var3].trim().empty() && var2[var3].contains(":")) {
            std::string[] var4 = var2[var3].split(":");
    std::string var5 = var4[0].trim();
    std::string var6 = var4[1].trim();
            if (var5 == "Require")) {
    std::vector var11 = Arrays.asList(var6.split(";

               for (int var12 = 0; var12 < var11.size(); var12++) {
                  this.addRequiredItem(((std::string)var11.get(var12)).trim());
               }
            } else if (!var5 == "Fixer")) {
               if (var5 == "GlobalItem")) {
                  if (var6.contains("=")) {
                     this.setGlobalItem(std::make_shared<Fixer>(var6.split("=")[0], nullptr, int.parseInt(var6.split("=")[1])));
                  } else {
                     this.setGlobalItem(std::make_shared<Fixer>(var6, nullptr, 1));
                  }
               } else if (var5 == "ConditionModifier")) {
                  this.setConditionModifier(float.parseFloat(var6.trim()));
               }
            } else if (!var6.contains(";")) {
               if (var6.contains("=")) {
                  this.fixers.push_back(std::make_shared<Fixer>(var6.split("=")[0], nullptr, int.parseInt(var6.split("=")[1])));
               } else {
                  this.fixers.push_back(std::make_shared<Fixer>(var6, nullptr, 1));
               }
            } else {
    std::list var7 = new std::list();
    std::vector var8 = Arrays.asList(var6.split(";

               for (int var9 = 1; var9 < var8.size(); var9++) {
                  std::string[] var10 = ((std::string)var8.get(var9)).trim().split("=");
                  var7.push_back(std::make_shared<FixerSkill>(var10[0].trim(), int.parseInt(var10[1].trim())));
               }

               if (var6.split(";")[0].trim().contains("=")) {
                  std::string[] var13 = var6.split(";")[0].trim().split("=");
                  this.fixers.push_back(std::make_shared<Fixer>(var13[0], var7, int.parseInt(var13[1])));
               } else {
                  this.fixers.push_back(std::make_shared<Fixer>(var6.split(";")[0].trim(), var7, 1));
               }
            }
         }
      }
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

   public std::vector<std::string> getRequiredItem() {
      return this.require;
   }

    void addRequiredItem(const std::string& var1) {
      if (this.require == nullptr) {
         this.require = std::make_unique<std::vector<>>();
      }

      this.require.push_back(var1);
   }

   public std::list<Fixer> getFixers() {
      return this.fixers;
   }

    Fixer usedInFixer(InventoryItem var1, IsoGameCharacter var2) {
      for (int var3 = 0; var3 < this.getFixers().size(); var3++) {
    Fixer var4 = this.getFixers().get(var3);
         if (var4.getFixerName() == var1.getType())) {
            if (dynamic_cast<DrainableComboItem*>(var1) != nullptr var5) {
               if (!(var5.getUsedDelta() < 1.0F)) {
    return var4;
               }

               if (var5.getDrainableUsesInt() >= var4.getNumberOfUse()) {
    return var4;
               }
            } else if (var2.getInventory().getCountTypeRecurse(this.getModule().getName() + "." + var4.getFixerName()) >= var4.getNumberOfUse()) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    InventoryItem haveGlobalItem(IsoGameCharacter var1) {
      s_InventoryItems.clear();
    std::vector var2 = this.getRequiredFixerItems(var1, this.getGlobalItem(), nullptr, s_InventoryItems);
    return var2 = = nullptr ? nullptr : (InventoryItem)var2.get(0);
   }

    InventoryItem haveThisFixer(IsoGameCharacter var1, Fixer var2, InventoryItem var3) {
      s_InventoryItems.clear();
    std::vector var4 = this.getRequiredFixerItems(var1, var2, var3, s_InventoryItems);
    return var4 = = nullptr ? nullptr : (InventoryItem)var4.get(0);
   }

    int countUses(IsoGameCharacter var1, Fixer var2, InventoryItem var3) {
      s_InventoryItems.clear();
      s_PredicateRequired.uses = 0;
      this.getRequiredFixerItems(var1, var2, var3, s_InventoryItems);
      return s_PredicateRequired.uses;
   }

    static int countUses(InventoryItem var0) {
    DrainableComboItem var1 = (DrainableComboItem)Type.tryCastTo(var0, DrainableComboItem.class);
      return var1 != nullptr ? var1.getDrainableUsesInt() : 1;
   }

   public std::vector<InventoryItem> getRequiredFixerItems(IsoGameCharacter var1, Fixer var2, InventoryItem var3, std::vector<InventoryItem> var4) {
      if (var2 == nullptr) {
    return nullptr;
      } else {
         assert Thread.currentThread() == GameWindow.GameThread;

    PredicateRequired var5 = s_PredicateRequired;
         var5.fixer = var2;
         var5.brokenItem = var3;
         var5.uses = 0;
         var1.getInventory().getAllRecurse(var5, var4);
         return var5.uses >= var2.getNumberOfUse() ? var4 : nullptr;
      }
   }

   public std::vector<InventoryItem> getRequiredItems(IsoGameCharacter var1, Fixer var2, InventoryItem var3) {
    std::vector var4 = new std::vector();
      if (this.getRequiredFixerItems(var1, var2, var3, var4) == nullptr) {
         var4.clear();
    return nullptr;
      } else if (this.getGlobalItem() != nullptr && this.getRequiredFixerItems(var1, this.getGlobalItem(), var3, var4) == nullptr) {
         var4.clear();
    return nullptr;
      } else {
    return var4;
      }
   }

    Fixer getGlobalItem() {
      return this.globalItem;
   }

    void setGlobalItem(Fixer var1) {
      this.globalItem = var1;
   }

    float getConditionModifier() {
      return this.conditionModifier;
   }

    void setConditionModifier(float var1) {
      this.conditionModifier = var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
