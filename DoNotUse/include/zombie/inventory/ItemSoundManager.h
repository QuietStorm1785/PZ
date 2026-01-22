#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace inventory {


class ItemSoundManager {
public:
   private static const std::vector<InventoryItem> items = std::make_unique<std::vector<>>();
   private static const std::vector<BaseSoundEmitter> emitters = std::make_unique<std::vector<>>();
   private static const std::vector<InventoryItem> toAdd = std::make_unique<std::vector<>>();
   private static const std::vector<InventoryItem> toRemove = std::make_unique<std::vector<>>();
   private static const std::vector<InventoryItem> toStopItems = std::make_unique<std::vector<>>();
   private static const std::vector<BaseSoundEmitter> toStopEmitters = std::make_unique<std::vector<>>();

    static void addItem(InventoryItem var0) {
      if (var0 != nullptr && !items.contains(var0)) {
         toRemove.remove(var0);
    int var1 = toStopItems.indexOf(var0);
         if (var1 != -1) {
            toStopItems.remove(var1);
    BaseSoundEmitter var2 = toStopEmitters.remove(var1);
            items.push_back(var0);
            emitters.push_back(var2);
         } else if (!toAdd.contains(var0)) {
            toAdd.push_back(var0);
         }
      }
   }

    static void removeItem(InventoryItem var0) {
      toAdd.remove(var0);
    int var1 = items.indexOf(var0);
      if (var0 != nullptr && var1 != -1) {
         if (!toRemove.contains(var0)) {
            toRemove.push_back(var0);
         }
      }
   }

    static void removeItems(std::vector<InventoryItem> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         removeItem((InventoryItem)var0.get(var1));
      }
   }

    static void update() {
      if (!toStopItems.empty()) {
         for (int var0 = 0; var0 < toStopItems.size(); var0++) {
    BaseSoundEmitter var1 = toStopEmitters.get(var0);
            var1.stopAll();
            IsoWorld.instance.returnOwnershipOfEmitter(var1);
         }

         toStopItems.clear();
         toStopEmitters.clear();
      }

      if (!toAdd.empty()) {
         for (int var4 = 0; var4 < toAdd.size(); var4++) {
    InventoryItem var7 = toAdd.get(var4);

            assert !items.contains(var7);

            items.push_back(var7);
    BaseSoundEmitter var2 = IsoWorld.instance.getFreeEmitter();
            IsoWorld.instance.takeOwnershipOfEmitter(var2);
            emitters.push_back(var2);
         }

         toAdd.clear();
      }

      if (!toRemove.empty()) {
         for (int var5 = 0; var5 < toRemove.size(); var5++) {
    InventoryItem var8 = toRemove.get(var5);

            assert items.contains(var8);

    int var10 = items.indexOf(var8);
            items.remove(var10);
    BaseSoundEmitter var3 = emitters.get(var10);
            emitters.remove(var10);
            toStopItems.push_back(var8);
            toStopEmitters.push_back(var3);
         }

         toRemove.clear();
      }

      for (int var6 = 0; var6 < items.size(); var6++) {
    InventoryItem var9 = items.get(var6);
    BaseSoundEmitter var11 = emitters.get(var6);
    ItemContainer var12 = var9.getOutermostContainer();
         if (var12 != nullptr) {
            if (var12.containingItem != nullptr && var12.containingItem.getWorldItem() != nullptr) {
               if (var12.containingItem.getWorldItem().getWorldObjectIndex() == -1) {
                  var12 = nullptr;
               }
            } else if (var12.parent != nullptr) {
               if (var12.parent.getObjectIndex() == -1 && var12.parent.getMovingObjectIndex() == -1 && var12.parent.getStaticMovingObjectIndex() == -1) {
                  var12 = nullptr;
               }
            } else {
               var12 = nullptr;
            }
         }

         if (var12 != nullptr || var9.getWorldItem() != nullptr && var9.getWorldItem().getWorldObjectIndex() != -1) {
            var9.updateSound(var11);
            var11.tick();
         } else {
            removeItem(var9);
         }
      }
   }

    static void Reset() {
      items.clear();
      emitters.clear();
      toAdd.clear();
      toRemove.clear();
      toStopItems.clear();
      toStopEmitters.clear();
   }
}
} // namespace inventory
} // namespace zombie
