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
#include "zombie/characters/HairOutfitDefinitions/HaircutDefinition.h"
#include "zombie/characters/HairOutfitDefinitions/HaircutOutfitDefinition.h"
#include "zombie/characters/HairOutfitDefinitions/StringChance.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>

namespace zombie {
namespace characters {


class HairOutfitDefinitions {
public:
    static const HairOutfitDefinitions instance = std::make_shared<HairOutfitDefinitions>();
    bool m_dirty = true;
    std::string hairStyle;
    int minWorldAge;
   public const std::vector<HaircutDefinition> m_haircutDefinition = std::make_unique<std::vector<>>();
   public const std::vector<HaircutOutfitDefinition> m_outfitDefinition = std::make_unique<std::vector<>>();
   private const ThreadLocal<std::vector<HairStyle>> m_tempHairStyles = ThreadLocal.withInitial(std::vector::new);

    void checkDirty() {
      if (this.m_dirty) {
         this.m_dirty = false;
         this.init();
      }
   }

    void init() {
      this.m_haircutDefinition.clear();
      this.m_outfitDefinition.clear();
    KahluaTableImpl var1 = (KahluaTableImpl)LuaManager.env.rawget("HairOutfitDefinitions");
      if (var1 != nullptr) {
    KahluaTableImpl var2 = (KahluaTableImpl)Type.tryCastTo(var1.rawget("haircutDefinition"), KahluaTableImpl.class);
         if (var2 != nullptr) {
    KahluaTableIterator var3 = var2.iterator();

            while (var3.advance()) {
    KahluaTableImpl var4 = (KahluaTableImpl)Type.tryCastTo(var3.getValue(), KahluaTableImpl.class);
               if (var4 != nullptr) {
                  HaircutDefinition var5 = std::make_shared<HaircutDefinition>(
                     var4.rawgetStr("name"), var4.rawgetInt("minWorldAge"), new std::vector<>(Arrays.asList(var4.rawgetStr("onlyFor").split(",")))
                  );
                  this.m_haircutDefinition.push_back(var5);
               }
            }

    KahluaTableImpl var8 = (KahluaTableImpl)Type.tryCastTo(var1.rawget("haircutOutfitDefinition"), KahluaTableImpl.class);
            if (var8 != nullptr) {
               var3 = var8.iterator();

               while (var3.advance()) {
    KahluaTableImpl var9 = (KahluaTableImpl)Type.tryCastTo(var3.getValue(), KahluaTableImpl.class);
                  if (var9 != nullptr) {
                     HaircutOutfitDefinition var6 = std::make_shared<HaircutOutfitDefinition>(
                        var9.rawgetStr("outfit"),
                        initStringChance(var9.rawgetStr("haircut")),
                        initStringChance(var9.rawgetStr("beard")),
                        initStringChance(var9.rawgetStr("haircutColor"))
                     );
                     this.m_outfitDefinition.push_back(var6);
                  }
               }
            }
         }
      }
   }

    bool isHaircutValid(const std::string& var1, const std::string& var2) {
      instance.checkDirty();
      if (StringUtils.isNullOrEmpty(var1)) {
    return true;
      } else {
         for (int var3 = 0; var3 < instance.m_haircutDefinition.size(); var3++) {
    HaircutDefinition var4 = instance.m_haircutDefinition.get(var3);
            if (var4.hairStyle == var2)) {
               if (!var4.onlyFor.contains(var1)) {
    return false;
               }

               if (IsoWorld.instance.getWorldAgeDays() < var4.minWorldAge) {
    return false;
               }
            }
         }

    return true;
      }
   }

    void getValidHairStylesForOutfit(const std::string& var1, std::vector<HairStyle> var2, std::vector<HairStyle> var3) {
      var3.clear();

      for (int var4 = 0; var4 < var2.size(); var4++) {
    HairStyle var5 = (HairStyle)var2.get(var4);
         if (!var5.isNoChoose() && this.isHaircutValid(var1, var5.name)) {
            var3.push_back(var5);
         }
      }
   }

    std::string getRandomHaircut(const std::string& var1, std::vector<HairStyle> var2) {
    std::vector var3 = this.m_tempHairStyles.get();
      this.getValidHairStylesForOutfit(var1, var2, var3);
      if (var3.empty()) {
         return "";
      } else {
    std::string var4 = ((HairStyle)OutfitRNG.pickRandom(var3)).name;
    bool var5 = false;

         for (int var6 = 0; var6 < instance.m_outfitDefinition.size() && !var5; var6++) {
    HaircutOutfitDefinition var7 = instance.m_outfitDefinition.get(var6);
            if (var7.outfit == var1) && var7.haircutChance != nullptr) {
    float var8 = OutfitRNG.Next(0.0F, 100.0F);
    float var9 = 0.0F;

               for (int var10 = 0; var10 < var7.haircutChance.size(); var10++) {
    StringChance var11 = (StringChance)var7.haircutChance.get(var10);
                  var9 += var11.chance;
                  if (var8 < var9) {
                     var4 = var11.str;
                     if ("nullptr".equalsIgnoreCase(var11.str)) {
                        var4 = "";
                     }

                     if ("random".equalsIgnoreCase(var11.str)) {
                        var4 = ((HairStyle)OutfitRNG.pickRandom(var3)).name;
                     }

                     var5 = true;
                     break;
                  }
               }
            }
         }

    return var4;
      }
   }

    ImmutableColor getRandomHaircutColor(const std::string& var1) {
    ImmutableColor var2 = (ImmutableColor)SurvivorDesc.HairCommonColors.get(OutfitRNG.Next(SurvivorDesc.HairCommonColors.size()));
    std::string var3 = nullptr;
    bool var4 = false;

      for (int var5 = 0; var5 < instance.m_outfitDefinition.size() && !var4; var5++) {
    HaircutOutfitDefinition var6 = instance.m_outfitDefinition.get(var5);
         if (var6.outfit == var1) && var6.haircutColor != nullptr) {
    float var7 = OutfitRNG.Next(0.0F, 100.0F);
    float var8 = 0.0F;

            for (int var9 = 0; var9 < var6.haircutColor.size(); var9++) {
    StringChance var10 = (StringChance)var6.haircutColor.get(var9);
               var8 += var10.chance;
               if (var7 < var8) {
                  var3 = var10.str;
                  if ("random".equalsIgnoreCase(var10.str)) {
                     var2 = (ImmutableColor)SurvivorDesc.HairCommonColors.get(OutfitRNG.Next(SurvivorDesc.HairCommonColors.size()));
                     var3 = nullptr;
                  }

                  var4 = true;
                  break;
               }
            }
         }
      }

      if (!StringUtils.isNullOrEmpty(var3)) {
         std::string[] var11 = var3.split(",");
         var2 = std::make_shared<ImmutableColor>(float.parseFloat(var11[0]), float.parseFloat(var11[1]), float.parseFloat(var11[2]));
      }

    return var2;
   }

    std::string getRandomBeard(const std::string& var1, std::vector<BeardStyle> var2) {
    std::string var3 = ((BeardStyle)OutfitRNG.pickRandom(var2)).name;
    bool var4 = false;

      for (int var5 = 0; var5 < instance.m_outfitDefinition.size() && !var4; var5++) {
    HaircutOutfitDefinition var6 = instance.m_outfitDefinition.get(var5);
         if (var6.outfit == var1) && var6.beardChance != nullptr) {
    float var7 = OutfitRNG.Next(0.0F, 100.0F);
    float var8 = 0.0F;

            for (int var9 = 0; var9 < var6.beardChance.size(); var9++) {
    StringChance var10 = (StringChance)var6.beardChance.get(var9);
               var8 += var10.chance;
               if (var7 < var8) {
                  var3 = var10.str;
                  if ("nullptr".equalsIgnoreCase(var10.str)) {
                     var3 = "";
                  }

                  if ("random".equalsIgnoreCase(var10.str)) {
                     var3 = ((BeardStyle)OutfitRNG.pickRandom(var2)).name;
                  }

                  var4 = true;
                  break;
               }
            }
         }
      }

    return var3;
   }

   private static std::vector<StringChance> initStringChance(std::string var0) {
      if (StringUtils.isNullOrWhitespace(var0)) {
    return nullptr;
      } else {
    std::vector var1 = new std::vector();
         std::string[] var2 = var0.split(";");
    int var3 = 0;

    for (auto& var7 : var2)            std::string[] var8 = var7.split(":");
    StringChance var9 = std::make_shared<StringChance>();
            var9.str = var8[0];
            var9.chance = float.parseFloat(var8[1]);
            var3 = (int)(var3 + var9.chance);
            var1.push_back(var9);
         }

         if (var3 < 100) {
    StringChance var10 = std::make_shared<StringChance>();
            var10.str = "random";
            var10.chance = 100 - var3;
            var1.push_back(var10);
         }

    return var1;
      }
   }
}
} // namespace characters
} // namespace zombie
