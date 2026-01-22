#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/BrokenFences/1.h"
#include "zombie/iso/BrokenFences/Tile.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/PolygonalMap2.h"

namespace zombie {
namespace iso {


class BrokenFences {
public:
    static const BrokenFences instance = std::make_shared<BrokenFences>();
   private const THashMap<std::string, Tile> s_unbrokenMap = std::make_unique<THashMap>();
   private const THashMap<std::string, Tile> s_brokenLeftMap = std::make_unique<THashMap>();
   private const THashMap<std::string, Tile> s_brokenRightMap = std::make_unique<THashMap>();
   private const THashMap<std::string, Tile> s_allMap = std::make_unique<THashMap>();

    static BrokenFences getInstance() {
    return instance;
   }

   private std::vector<std::string> tableToTiles(KahluaTableImpl var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    std::vector var2 = nullptr;

         for (KahluaTableIterator var3 = var1.iterator(); var3.advance(); var2.push_back(var3.getValue())) {
            if (var2 == nullptr) {
               var2 = std::make_unique<std::vector>();
            }
         }

    return var2;
      }
   }

   private std::vector<std::string> tableToTiles(KahluaTable var1, std::string var2) {
      return this.tableToTiles((KahluaTableImpl)var1.rawget(var2));
   }

    void addBrokenTiles(KahluaTableImpl var1) {
    KahluaTableIterator var2 = var1.iterator();

      while (var2.advance()) {
    std::string var3 = var2.getKey();
         if (!"VERSION".equalsIgnoreCase(var3)) {
    KahluaTableImpl var4 = (KahluaTableImpl)var2.getValue();
    Tile var5 = std::make_shared<Tile>();
            var5.self = this.tableToTiles(var4, "self");
            var5.left = this.tableToTiles(var4, "left");
            var5.right = this.tableToTiles(var4, "right");
            this.s_unbrokenMap.put(var3, var5);
            PZArrayUtil.forEach(var5.left, var2x -> this.s_brokenLeftMap.put(var2x, var5));
            PZArrayUtil.forEach(var5.right, var2x -> this.s_brokenRightMap.put(var2x, var5));
         }
      }

      this.s_allMap.putAll(this.s_unbrokenMap);
      this.s_allMap.putAll(this.s_brokenLeftMap);
      this.s_allMap.putAll(this.s_brokenRightMap);
   }

    void addDebrisTiles(KahluaTableImpl var1) {
    KahluaTableIterator var2 = var1.iterator();

      while (var2.advance()) {
    std::string var3 = var2.getKey();
         if (!"VERSION".equalsIgnoreCase(var3)) {
    KahluaTableImpl var4 = (KahluaTableImpl)var2.getValue();
    Tile var5 = (Tile)this.s_unbrokenMap.get(var3);
            if (var5 == nullptr) {
               throw IllegalArgumentException("addDebrisTiles() with unknown tile");
            }

            var5.debrisN = this.tableToTiles(var4, "north");
            var5.debrisS = this.tableToTiles(var4, "south");
            var5.debrisW = this.tableToTiles(var4, "west");
            var5.debrisE = this.tableToTiles(var4, "east");
         }
      }
   }

    void setDestroyed(IsoObject var1) {
      var1.RemoveAttachedAnims();
      var1.getSquare().removeBlood(false, true);
      this.updateSprite(var1, true, true);
   }

    void setDamagedLeft(IsoObject var1) {
      this.updateSprite(var1, true, false);
   }

    void setDamagedRight(IsoObject var1) {
      this.updateSprite(var1, false, true);
   }

    void updateSprite(IsoObject var1, bool var2, bool var3) {
      if (this.isBreakableObject(var1)) {
    Tile var4 = (Tile)this.s_allMap.get(var1.sprite.name);
    std::string var5 = nullptr;
         if (var2 && var3) {
            var5 = var4.pickRandom(var4.self);
         } else if (var2) {
            var5 = var4.pickRandom(var4.left);
         } else if (var3) {
            var5 = var4.pickRandom(var4.right);
         }

         if (var5 != nullptr) {
    IsoSprite var6 = IsoSpriteManager.instance.getSprite(var5);
            var6.name = var5;
            var1.setSprite(var6);
            var1.transmitUpdatedSprite();
            var1.getSquare().RecalcAllWithNeighbours(true);
            MapCollisionData.instance.squareChanged(var1.getSquare());
            PolygonalMap2.instance.squareChanged(var1.getSquare());
            IsoRegions.squareChanged(var1.getSquare());
         }
      }
   }

    bool isNW(IsoObject var1) {
    PropertyContainer var2 = var1.getProperties();
      return var2.Is(IsoFlagType.collideN) && var2.Is(IsoFlagType.collideW);
   }

    void damageAdjacent(IsoGridSquare var1, IsoDirections var2, IsoDirections var3) {
    IsoGridSquare var4 = var1.getAdjacentSquare(var2);
      if (var4 != nullptr) {
    bool var5 = var2 == IsoDirections.W || var2 == IsoDirections.E;
    IsoObject var6 = this.getBreakableObject(var4, var5);
         if (var6 != nullptr) {
    bool var7 = var2 == IsoDirections.N || var2 == IsoDirections.E;
    bool var8 = var2 == IsoDirections.S || var2 == IsoDirections.W;
            if (!this.isNW(var6) || var2 != IsoDirections.S && var2 != IsoDirections.E) {
               if (var7 && this.isBrokenRight(var6)) {
                  this.destroyFence(var6, var3);
               } else if (var8 && this.isBrokenLeft(var6)) {
                  this.destroyFence(var6, var3);
               } else {
                  this.updateSprite(var6, var7, var8);
               }
            }
         }
      }
   }

    void destroyFence(IsoObject var1, IsoDirections var2) {
      if (this.isBreakableObject(var1)) {
    IsoGridSquare var3 = var1.getSquare();
         if (GameServer.bServer) {
            GameServer.PlayWorldSoundServer("BreakObject", false, var3, 1.0F, 20.0F, 1.0F, true);
         } else {
            SoundManager.instance.PlayWorldSound("BreakObject", var3, 1.0F, 20.0F, 1.0F, true);
         }

    bool var4 = var1.getProperties().Is(IsoFlagType.collideN);
    bool var5 = var1.getProperties().Is(IsoFlagType.collideW);
         if (dynamic_cast<IsoThumpable*>(var1) != nullptr) {
    IsoObject var6 = IsoObject.getNew();
            var6.setSquare(var3);
            var6.setSprite(var1.getSprite());
    int var7 = var1.getObjectIndex();
            var3.transmitRemoveItemFromSquare(var1);
            var3.transmitAddObjectToSquare(var6, var7);
            var1 = var6;
         }

         this.addDebrisObject(var1, var2);
         this.setDestroyed(var1);
         if (var4 && var5) {
            this.damageAdjacent(var3, IsoDirections.S, var2);
            this.damageAdjacent(var3, IsoDirections.E, var2);
         } else if (var4) {
            this.damageAdjacent(var3, IsoDirections.W, var2);
            this.damageAdjacent(var3, IsoDirections.E, var2);
         } else if (var5) {
            this.damageAdjacent(var3, IsoDirections.N, var2);
            this.damageAdjacent(var3, IsoDirections.S, var2);
         }

         var3.RecalcAllWithNeighbours(true);
         MapCollisionData.instance.squareChanged(var3);
         PolygonalMap2.instance.squareChanged(var3);
         IsoRegions.squareChanged(var3);
      }
   }

    bool isUnbroken(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr ? this.s_unbrokenMap.contains(var1.sprite.name) : false;
   }

    bool isBrokenLeft(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr ? this.s_brokenLeftMap.contains(var1.sprite.name) : false;
   }

    bool isBrokenRight(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr ? this.s_brokenRightMap.contains(var1.sprite.name) : false;
   }

    bool isBreakableObject(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr ? this.s_allMap.containsKey(var1.sprite.name) : false;
   }

    IsoObject getBreakableObject(IsoGridSquare var1, bool var2) {
      for (int var3 = 0; var3 < var1.Objects.size(); var3++) {
    IsoObject var4 = (IsoObject)var1.Objects.get(var3);
         if (this.isBreakableObject(var4) && (var2 && var4.getProperties().Is(IsoFlagType.collideN) || !var2 && var4.getProperties().Is(IsoFlagType.collideW))) {
    return var4;
         }
      }

    return nullptr;
   }

    void addItems(IsoObject var1, IsoGridSquare var2) {
    PropertyContainer var3 = var1.getProperties();
      if (var3 != nullptr) {
    std::string var4 = var3.Val("Material");
    std::string var5 = var3.Val("Material2");
    std::string var6 = var3.Val("Material3");
         if ("Wood" == var4) || "Wood" == var5) || "Wood" == var6)) {
            var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Plank"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
            if (Rand.NextBool(5)) {
               var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Plank"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
            }
         }

         if (("MetalBars" == var4) || "MetalBars" == var5) || "MetalBars" == var6)) && Rand.NextBool(2)) {
            var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.MetalBar"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("MetalWire" == var4) || "MetalWire" == var5) || "MetalWire" == var6)) && Rand.NextBool(3)) {
            var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Wire"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("Nails" == var4) || "Nails" == var5) || "Nails" == var6)) && Rand.NextBool(2)) {
            var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Nails"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }

         if (("Screws" == var4) || "Screws" == var5) || "Screws" == var6)) && Rand.NextBool(2)) {
            var2.AddWorldInventoryItem(InventoryItemFactory.CreateItem("Base.Screws"), Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void addDebrisObject(IsoObject var1, IsoDirections var2) {
      if (this.isBreakableObject(var1)) {
    Tile var3 = (Tile)this.s_allMap.get(var1.sprite.name);
    IsoGridSquare var5 = var1.getSquare();
    std::string var4;
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var2.ordinal()]) {
            case 1:
               var4 = var3.pickRandom(var3.debrisN);
               var5 = var5.getAdjacentSquare(var2);
               break;
            case 2:
               var4 = var3.pickRandom(var3.debrisS);
               break;
            case 3:
               var4 = var3.pickRandom(var3.debrisW);
               var5 = var5.getAdjacentSquare(var2);
               break;
            case 4:
               var4 = var3.pickRandom(var3.debrisE);
               break;
            default:
               throw IllegalArgumentException("invalid direction");
         }

         if (var4 != nullptr && var5 != nullptr && var5.TreatAsSolidFloor()) {
    IsoObject var6 = IsoObject.getNew(var5, var4, nullptr, false);
            var5.transmitAddObjectToSquare(var6, var5 == var1.getSquare() ? var1.getObjectIndex() : -1);
            this.addItems(var1, var5);
         }
      }
   }

    void Reset() {
      this.s_unbrokenMap.clear();
      this.s_brokenLeftMap.clear();
      this.s_brokenRightMap.clear();
      this.s_allMap.clear();
   }
}
} // namespace iso
} // namespace zombie
