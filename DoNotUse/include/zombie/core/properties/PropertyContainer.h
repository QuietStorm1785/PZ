#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntIntHashMap.h"
#include "gnu/trove/set/TIntSet.h"
#include "zombie/core/Collections/NonBlockingHashMap.h"
#include "zombie/core/TilePropertyAliasMap.h"
#include "zombie/core/TilePropertyAliasMap/TileProperty.h"
#include "zombie/core/properties/PropertyContainer/MostTested.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace core {
namespace properties {


class PropertyContainer {
public:
    long SpriteFlags1 = 0L;
    long SpriteFlags2 = 0L;
    const TIntIntHashMap Properties = std::make_shared<TIntIntHashMap>();
   private int[] keyArray;
   public static NonBlockingHashMap<IsoFlagType, MostTested> test = std::make_unique<NonBlockingHashMap>();
   public static List<Object> sorted = Collections.synchronizedList(std::make_unique<std::vector<>>());
    uint8_t Surface;
    uint8_t SurfaceFlags;
    short StackReplaceTileOffset;
    uint8_t ItemHeight;
    static const uint8_t SURFACE_VALID = 1;
    static const uint8_t SURFACE_ISOFFSET = 2;
    static const uint8_t SURFACE_ISTABLE = 4;
    static const uint8_t SURFACE_ISTABLETOP = 8;

    void CreateKeySet() {
    TIntSet var1 = this.Properties.keySet();
      this.keyArray = var1.toArray();
   }

    void AddProperties(PropertyContainer var1) {
      if (var1.keyArray != nullptr) {
         for (int var2 = 0; var2 < var1.keyArray.length; var2++) {
    int var3 = var1.keyArray[var2];
            this.Properties.put(var3, var1.Properties.get(var3));
         }

         this.SpriteFlags1 = this.SpriteFlags1 | var1.SpriteFlags1;
         this.SpriteFlags2 = this.SpriteFlags2 | var1.SpriteFlags2;
      }
   }

    void Clear() {
      this.SpriteFlags1 = 0L;
      this.SpriteFlags2 = 0L;
      this.Properties.clear();
      this.SurfaceFlags &= -2;
   }

    bool Is(IsoFlagType var1) {
    long var2 = var1.index() / 64 == 0 ? this.SpriteFlags1 : this.SpriteFlags2;
      return (var2 & 1L << var1.index() % 64) != 0L;
   }

    bool Is(double var1) {
      return this.Is(IsoFlagType.fromIndex(var1.intValue()));
   }

    void Set(const std::string& var1, const std::string& var2) {
      this.Set(var1, var2, true);
   }

    void Set(const std::string& var1, const std::string& var2, bool var3) {
      if (var1 != nullptr) {
         if (var3) {
    IsoFlagType var4 = IsoFlagType.FromString(var1);
            if (var4 != IsoFlagType.MAX) {
               this.Set(var4);
               return;
            }
         }

    int var6 = TilePropertyAliasMap.instance.getIDFromPropertyName(var1);
         if (var6 != -1) {
    int var5 = TilePropertyAliasMap.instance.getIDFromPropertyValue(var6, var2);
            this.SurfaceFlags &= -2;
            this.Properties.put(var6, var5);
         }
      }
   }

    void Set(IsoFlagType var1) {
      if (var1.index() / 64 == 0) {
         this.SpriteFlags1 = this.SpriteFlags1 | 1L << var1.index() % 64;
      } else {
         this.SpriteFlags2 = this.SpriteFlags2 | 1L << var1.index() % 64;
      }
   }

    void Set(IsoFlagType var1, const std::string& var2) {
      this.Set(var1);
   }

    void UnSet(const std::string& var1) {
    int var2 = TilePropertyAliasMap.instance.getIDFromPropertyName(var1);
      this.Properties.remove(var2);
   }

    void UnSet(IsoFlagType var1) {
      if (var1.index() / 64 == 0) {
         this.SpriteFlags1 = this.SpriteFlags1 & ~(1L << var1.index() % 64);
      } else {
         this.SpriteFlags2 = this.SpriteFlags2 & ~(1L << var1.index() % 64);
      }
   }

    std::string Val(const std::string& var1) {
    int var2 = TilePropertyAliasMap.instance.getIDFromPropertyName(var1);
      return !this.Properties.containsKey(var2) ? nullptr : TilePropertyAliasMap.instance.getPropertyValueString(var2, this.Properties.get(var2));
   }

    bool Is(const std::string& var1) {
    int var2 = TilePropertyAliasMap.instance.getIDFromPropertyName(var1);
      return this.Properties.containsKey(var2);
   }

   public std::vector<IsoFlagType> getFlagsList() {
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < 64; var2++) {
         if ((this.SpriteFlags1 & 1L << var2) != 0L) {
            var1.push_back(IsoFlagType.fromIndex(var2));
         }
      }

      for (int var3 = 0; var3 < 64; var3++) {
         if ((this.SpriteFlags2 & 1L << var3) != 0L) {
            var1.push_back(IsoFlagType.fromIndex(64 + var3));
         }
      }

    return var1;
   }

   public std::vector<std::string> getPropertyNames() {
    std::vector var1 = new std::vector();
    TIntSet var2 = this.Properties.keySet();
      var2.forEach(var1x -> {
         var1.push_back(((TileProperty)TilePropertyAliasMap.instance.Properties.get(var1x)).propertyName);
    return true;
      });
      Collections.sort(var1);
    return var1;
   }

    void initSurface() {
      if ((this.SurfaceFlags & 1) == 0) {
         this.Surface = 0;
         this.StackReplaceTileOffset = 0;
         this.SurfaceFlags = 1;
         this.ItemHeight = 0;
         this.Properties.forEachEntry((var1, var2) -> {
    TileProperty var3 = (TileProperty)TilePropertyAliasMap.instance.Properties.get(var1);
    std::string var4 = var3.propertyName;
    std::string var5 = (std::string)var3.possibleValues.get(var2);
            if ("Surface" == var4) && var5 != nullptr) {
               try {
    int var10 = int.parseInt(var5);
                  if (var10 >= 0 && var10 <= 127) {
                     this.Surface = (byte)var10;
                  }
               } catch (NumberFormatException var9) {
               }
            } else if ("IsSurfaceOffset" == var4)) {
               this.SurfaceFlags = (byte)(this.SurfaceFlags | 2);
            } else if ("IsTable" == var4)) {
               this.SurfaceFlags = (byte)(this.SurfaceFlags | 4);
            } else if ("IsTableTop" == var4)) {
               this.SurfaceFlags = (byte)(this.SurfaceFlags | 8);
            } else if ("StackReplaceTileOffset" == var4)) {
               try {
                  this.StackReplaceTileOffset = (short)int.parseInt(var5);
               } catch (NumberFormatException var8) {
               }
            } else if ("ItemHeight" == var4)) {
               try {
    int var6 = int.parseInt(var5);
                  if (var6 >= 0 && var6 <= 127) {
                     this.ItemHeight = (byte)var6;
                  }
               } catch (NumberFormatException var7) {
               }
            }

    return true;
         });
      }
   }

    int getSurface() {
      this.initSurface();
      return this.Surface;
   }

    bool isSurfaceOffset() {
      this.initSurface();
      return (this.SurfaceFlags & 2) != 0;
   }

    bool isTable() {
      this.initSurface();
      return (this.SurfaceFlags & 4) != 0;
   }

    bool isTableTop() {
      this.initSurface();
      return (this.SurfaceFlags & 8) != 0;
   }

    int getStackReplaceTileOffset() {
      this.initSurface();
      return this.StackReplaceTileOffset;
   }

    int getItemHeight() {
      this.initSurface();
      return this.ItemHeight;
   }
}
} // namespace properties
} // namespace core
} // namespace zombie
