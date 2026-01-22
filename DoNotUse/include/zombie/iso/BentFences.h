#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/MapCollisionData.h"
#include "zombie/iso/BentFences/Entry.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace iso {


class BentFences {
public:
    static const BentFences instance = std::make_shared<BentFences>();
   private const std::vector<Entry> m_entries = std::make_unique<std::vector<>>();
   private const std::unordered_map<std::string, std::vector<Entry>> m_bentMap = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, std::vector<Entry>> m_unbentMap = std::make_unique<std::unordered_map<>>();

    static BentFences getInstance() {
    return instance;
   }

    void tableToTiles(KahluaTableImpl var1, std::vector<std::string> var2) {
      if (var1 != nullptr) {
    KahluaTableIterator var3 = var1.iterator();

         while (var3.advance()) {
            var2.push_back(var3.getValue());
         }
      }
   }

    void tableToTiles(KahluaTable var1, std::vector<std::string> var2, const std::string& var3) {
      this.tableToTiles((KahluaTableImpl)var1.rawget(var3), var2);
   }

    void addFenceTiles(int var1, KahluaTableImpl var2) {
    KahluaTableIterator var3 = var2.iterator();

      while (var3.advance()) {
    KahluaTableImpl var4 = (KahluaTableImpl)var3.getValue();
    Entry var5 = std::make_shared<Entry>();
         var5.dir = IsoDirections.valueOf(var4.rawgetStr("dir"));
         this.tableToTiles(var4, var5.unbent, "unbent");
         this.tableToTiles(var4, var5.bent, "bent");
         if (!var5.unbent.empty() && var5.unbent.size() == var5.bent.size()) {
            this.m_entries.push_back(var5);

            for (std::string var7 : var5.unbent) {
    std::vector var8 = this.m_unbentMap.get(var7);
               if (var8 == nullptr) {
                  var8 = std::make_unique<std::vector>();
                  this.m_unbentMap.put(var7, var8);
               }

               var8.push_back(var5);
            }

            for (std::string var10 : var5.bent) {
    std::vector var11 = this.m_bentMap.get(var10);
               if (var11 == nullptr) {
                  var11 = std::make_unique<std::vector>();
                  this.m_bentMap.put(var10, var11);
               }

               var11.push_back(var5);
            }
         }
      }
   }

    bool isBentObject(IsoObject var1) {
      return this.getEntryForObject(var1, nullptr) != nullptr;
   }

    bool isUnbentObject(IsoObject var1) {
      return this.getEntryForObject(var1, IsoDirections.Max) != nullptr;
   }

    Entry getEntryForObject(IsoObject var1, IsoDirections var2) {
      if (var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr) {
    bool var3 = var2 != nullptr;
    std::vector var4 = var3 ? this.m_unbentMap.get(var1.sprite.name) : this.m_bentMap.get(var1.sprite.name);
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < var4.size(); var5++) {
    Entry var6 = (Entry)var4.get(var5);
               if ((!var3 || var2 == IsoDirections.Max || var2 == var6.dir) && this.isValidObject(var1, var6, var3)) {
    return var6;
               }
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    bool isValidObject(IsoObject var1, Entry var2, bool var3) {
    IsoCell var4 = IsoWorld.instance.CurrentCell;
    std::vector var5 = var3 ? var2.unbent : var2.bent;
    int var6 = ((std::string)var5.get(2)) == var1.sprite.name) ? 2 : (((std::string)var5.get(3)) == var1.sprite.name) ? 3 : -1);
      if (var6 == -1) {
    return false;
      } else {
         for (int var7 = 0; var7 < var5.size(); var7++) {
    int var8 = var1.square.x + (var2.isNorth() ? var7 - var6 : 0);
    int var9 = var1.square.y + (var2.isNorth() ? 0 : var7 - var6);
    IsoGridSquare var10 = var4.getGridSquare(var8, var9, var1.square.z);
            if (var10 == nullptr) {
    return false;
            }

            if (var6 != var7 && this.getObjectForEntry(var10, var5, var7) == nullptr) {
    return false;
            }
         }

    return true;
      }
   }

    IsoObject getObjectForEntry(IsoGridSquare var1, std::vector<std::string> var2, int var3) {
      for (int var4 = 0; var4 < var1.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)var1.getObjects().get(var4);
         if (var5.sprite != nullptr && var5.sprite.name != nullptr && ((std::string)var2.get(var3)) == var5.sprite.name)) {
    return var5;
         }
      }

    return nullptr;
   }

    void swapTiles(IsoObject var1, IsoDirections var2) {
    bool var3 = var2 != nullptr;
    Entry var4 = this.getEntryForObject(var1, var2);
      if (var4 != nullptr) {
         if (var3) {
            if (var4.isNorth() && var2 != IsoDirections.N && var2 != IsoDirections.S) {
               return;
            }

            if (!var4.isNorth() && var2 != IsoDirections.W && var2 != IsoDirections.E) {
               return;
            }
         }

    IsoCell var5 = IsoWorld.instance.CurrentCell;
    std::vector var6 = var3 ? var4.unbent : var4.bent;
    int var7 = ((std::string)var6.get(2)) == var1.sprite.name) ? 2 : (((std::string)var6.get(3)) == var1.sprite.name) ? 3 : -1);

         for (int var8 = 0; var8 < var6.size(); var8++) {
    int var9 = var1.square.x + (var4.isNorth() ? var8 - var7 : 0);
    int var10 = var1.square.y + (var4.isNorth() ? 0 : var8 - var7);
    IsoGridSquare var11 = var5.getGridSquare(var9, var10, var1.square.z);
            if (var11 != nullptr) {
    IsoObject var12 = this.getObjectForEntry(var11, var6, var8);
               if (var12 != nullptr) {
    std::string var13 = var3 ? (std::string)var4.bent.get(var8) : (std::string)var4.unbent.get(var8);
    IsoSprite var14 = IsoSpriteManager.instance.getSprite(var13);
                  var14.name = var13;
                  var12.setSprite(var14);
                  var12.transmitUpdatedSprite();
                  var11.RecalcAllWithNeighbours(true);
                  MapCollisionData.instance.squareChanged(var11);
                  PolygonalMap2.instance.squareChanged(var11);
                  IsoRegions.squareChanged(var11);
               }
            }
         }
      }
   }

    void bendFence(IsoObject var1, IsoDirections var2) {
      this.swapTiles(var1, var2);
   }

    void unbendFence(IsoObject var1) {
      this.swapTiles(var1, nullptr);
   }

    void Reset() {
      this.m_entries.clear();
      this.m_bentMap.clear();
      this.m_unbentMap.clear();
   }
}
} // namespace iso
} // namespace zombie
