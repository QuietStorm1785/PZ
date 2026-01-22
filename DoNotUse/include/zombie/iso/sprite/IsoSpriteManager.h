#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "zombie/core/Color.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace iso {
namespace sprite {


class IsoSpriteManager {
public:
    static const IsoSpriteManager instance = std::make_shared<IsoSpriteManager>();
   public const std::unordered_map<std::string, IsoSprite> NamedMap = std::make_unique<std::unordered_map<>>();
   public const TIntObjectHashMap<IsoSprite> IntMap = std::make_unique<TIntObjectHashMap>();
    const IsoSprite emptySprite = std::make_shared<IsoSprite>(this);

    public IsoSpriteManager() {
    IsoSprite var1 = this.emptySprite;
      var1.name = "";
      var1.ID = -1;
      var1.Properties.Set(IsoFlagType.invisible);
      var1.CurrentAnim = std::make_unique<IsoAnim>();
      var1.CurrentAnim.ID = var1.AnimStack.size();
      var1.AnimStack.push_back(var1.CurrentAnim);
      var1.AnimMap.put("default", var1.CurrentAnim);
      this.NamedMap.put(var1.name, var1);
   }

    void Dispose() {
      IsoSprite.DisposeAll();
      IsoAnim.DisposeAll();
      Object[] var1 = this.IntMap.values();

      for (int var2 = 0; var2 < var1.length; var2++) {
    IsoSprite var3 = (IsoSprite)var1[var2];
         var3.Dispose();
         var3.def = nullptr;
         var3.parentManager = nullptr;
      }

      this.IntMap.clear();
      this.NamedMap.clear();
      this.NamedMap.put(this.emptySprite.name, this.emptySprite);
   }

    IsoSprite getSprite(int var1) {
      return this.IntMap.containsKey(var1) ? (IsoSprite)this.IntMap.get(var1) : nullptr;
   }

    IsoSprite getSprite(const std::string& var1) {
      return this.NamedMap.containsKey(var1) ? this.NamedMap.get(var1) : this.AddSprite(var1);
   }

    IsoSprite getOrAddSpriteCache(const std::string& var1) {
      if (this.NamedMap.containsKey(var1)) {
         return this.NamedMap.get(var1);
      } else {
    IsoSprite var2 = std::make_shared<IsoSprite>(this);
         var2.LoadFramesNoDirPageSimple(var1);
         this.NamedMap.put(var1, var2);
    return var2;
      }
   }

    IsoSprite getOrAddSpriteCache(const std::string& var1, Color var2) {
    int var3 = (int)(var2.r * 255.0F);
    int var4 = (int)(var2.g * 255.0F);
    int var5 = (int)(var2.b * 255.0F);
    std::string var6 = var1 + "_" + var3 + "_" + var4 + "_" + var5;
      if (this.NamedMap.containsKey(var6)) {
         return this.NamedMap.get(var6);
      } else {
    IsoSprite var7 = std::make_shared<IsoSprite>(this);
         var7.LoadFramesNoDirPageSimple(var1);
         this.NamedMap.put(var6, var7);
    return var7;
      }
   }

    IsoSprite AddSprite(const std::string& var1) {
    IsoSprite var2 = std::make_shared<IsoSprite>(this);
      var2.LoadFramesNoDirPageSimple(var1);
      this.NamedMap.put(var1, var2);
    return var2;
   }

    IsoSprite AddSprite(const std::string& var1, int var2) {
    IsoSprite var3 = std::make_shared<IsoSprite>(this);
      var3.LoadFramesNoDirPageSimple(var1);
      if (this.NamedMap.containsKey(var1)) {
         DebugLog.log("duplicate texture " + var1 + " ignore ID=" + var2 + ", use ID=" + this.NamedMap.get(var1).ID);
         var2 = this.NamedMap.get(var1).ID;
      }

      this.NamedMap.put(var1, var3);
      var3.ID = var2;
      this.IntMap.put(var2, var3);
    return var3;
   }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
