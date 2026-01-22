#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/skinnedmodel/population/DefaultClothing/Clothing.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class DefaultClothing {
public:
    static const DefaultClothing instance = std::make_shared<DefaultClothing>();
    const Clothing Pants = std::make_shared<Clothing>();
    const Clothing TShirt = std::make_shared<Clothing>();
    const Clothing TShirtDecal = std::make_shared<Clothing>();
    const Clothing Vest = std::make_shared<Clothing>();
    bool m_dirty = true;

    void checkDirty() {
      if (this.m_dirty) {
         this.m_dirty = false;
         this.init();
      }
   }

    void init() {
      this.Pants.clear();
      this.TShirt.clear();
      this.TShirtDecal.clear();
      this.Vest.clear();
    KahluaTable var1 = (KahluaTable)Type.tryCastTo(LuaManager.env.rawget("DefaultClothing"), KahluaTable.class);
      if (var1 != nullptr) {
         this.initClothing(var1, this.Pants, "Pants");
         this.initClothing(var1, this.TShirt, "TShirt");
         this.initClothing(var1, this.TShirtDecal, "TShirtDecal");
         this.initClothing(var1, this.Vest, "Vest");
      }
   }

    void initClothing(KahluaTable var1, Clothing var2, const std::string& var3) {
    KahluaTable var4 = (KahluaTable)Type.tryCastTo(var1.rawget(var3), KahluaTable.class);
      if (var4 != nullptr) {
         this.tableToArrayList(var4, "hue", var2.hue);
         this.tableToArrayList(var4, "texture", var2.texture);
         this.tableToArrayList(var4, "tint", var2.tint);
      }
   }

    void tableToArrayList(KahluaTable var1, const std::string& var2, std::vector<std::string> var3) {
    KahluaTableImpl var4 = (KahluaTableImpl)var1.rawget(var2);
      if (var4 != nullptr) {
    int var5 = 1;

         for (int var6 = var4.len(); var5 <= var6; var5++) {
    void* var7 = var4.rawget(var5);
            if (var7 != nullptr) {
               var3.push_back(var7);
            }
         }
      }
   }

    std::string pickPantsHue() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.Pants.hue);
   }

    std::string pickPantsTexture() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.Pants.texture);
   }

    std::string pickPantsTint() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.Pants.tint);
   }

    std::string pickTShirtTexture() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.TShirt.texture);
   }

    std::string pickTShirtTint() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.TShirt.tint);
   }

    std::string pickTShirtDecalTexture() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.TShirtDecal.texture);
   }

    std::string pickTShirtDecalTint() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.TShirtDecal.tint);
   }

    std::string pickVestTexture() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.Vest.texture);
   }

    std::string pickVestTint() {
      this.checkDirty();
      return (std::string)OutfitRNG.pickRandom(this.Vest.tint);
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
