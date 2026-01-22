#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/UnderwearDefinition/OutfitUnderwearDefinition.h"
#include "zombie/characters/UnderwearDefinition/StringChance.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace characters {


class UnderwearDefinition {
public:
    static const UnderwearDefinition instance = std::make_shared<UnderwearDefinition>();
    bool m_dirty = true;
   private static const std::vector<OutfitUnderwearDefinition> m_outfitDefinition = std::make_unique<std::vector<>>();
    static int baseChance = 50;

    void checkDirty() {
      this.init();
   }

    void init() {
      m_outfitDefinition.clear();
    KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("UnderwearDefinition");
      if (var1 != nullptr) {
         baseChance = var1.rawgetInt("baseChance");
    KahluaTableIterator var2 = var1.iterator();

         while (var2.advance()) {
    std::vector var3 = nullptr;
    KahluaTableImpl var4 = (KahluaTableImpl)Type.tryCastTo(var2.getValue(), KahluaTableImpl.class);
            if (var4 != nullptr) {
    KahluaTableImpl var5 = (KahluaTableImpl)Type.tryCastTo(var4.rawget("top"), KahluaTableImpl.class);
               if (var5 != nullptr) {
                  var3 = std::make_unique<std::vector>();
    KahluaTableIterator var6 = var5.iterator();

                  while (var6.advance()) {
    KahluaTableImpl var7 = (KahluaTableImpl)Type.tryCastTo(var6.getValue(), KahluaTableImpl.class);
                     if (var7 != nullptr) {
                        var3.push_back(std::make_shared<StringChance>(var7.rawgetStr("name"), var7.rawgetFloat("chance")));
                     }
                  }
               }

               OutfitUnderwearDefinition var8 = std::make_shared<OutfitUnderwearDefinition>(
                  var3, var4.rawgetStr("bottom"), var4.rawgetInt("chanceToSpawn"), var4.rawgetStr("gender")
               );
               m_outfitDefinition.push_back(var8);
            }
         }
      }
   }

    static void addRandomUnderwear(IsoZombie var0) {
      instance.checkDirty();
      if (Rand.Next(100) <= baseChance) {
    std::vector var1 = new std::vector();
    int var2 = 0;

         for (int var3 = 0; var3 < m_outfitDefinition.size(); var3++) {
    OutfitUnderwearDefinition var4 = m_outfitDefinition.get(var3);
            if (var0.isFemale() && var4.female || !var0.isFemale() && !var4.female) {
               var1.push_back(var4);
               var2 += var4.chanceToSpawn;
            }
         }

    int var11 = OutfitRNG.Next(var2);
    OutfitUnderwearDefinition var13 = nullptr;
    int var5 = 0;

         for (int var6 = 0; var6 < var1.size(); var6++) {
    OutfitUnderwearDefinition var7 = (OutfitUnderwearDefinition)var1.get(var6);
            var5 += var7.chanceToSpawn;
            if (var11 < var5) {
               var13 = var7;
               break;
            }
         }

         if (var13 != nullptr) {
    Item var15 = ScriptManager.instance.FindItem(var13.bottom);
    ItemVisual var17 = nullptr;
            if (var15 != nullptr) {
               var17 = var0.getHumanVisual().addClothingItem(var0.getItemVisuals(), var15);
            }

            if (var13.top != nullptr) {
    std::string var8 = nullptr;
               var11 = OutfitRNG.Next(var13.topTotalChance);
               var5 = 0;

               for (int var9 = 0; var9 < var13.top.size(); var9++) {
    StringChance var10 = (StringChance)var13.top.get(var9);
                  var5 = (int)(var5 + var10.chance);
                  if (var11 < var5) {
                     var8 = var10.str;
                     break;
                  }
               }

               if (var8 != nullptr) {
                  var15 = ScriptManager.instance.FindItem(var8);
                  if (var15 != nullptr) {
    ItemVisual var18 = var0.getHumanVisual().addClothingItem(var0.getItemVisuals(), var15);
                     if (Rand.Next(100) < 60 && var18 != nullptr && var17 != nullptr) {
                        var18.setTint(var17.getTint());
                     }
                  }
               }
            }
         }
      }
   }
}
} // namespace characters
} // namespace zombie
