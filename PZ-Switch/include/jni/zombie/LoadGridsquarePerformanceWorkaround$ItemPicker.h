#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameServer.h"

namespace zombie {


class LoadGridsquarePerformanceWorkaround {
:
    static LoadGridsquarePerformanceWorkaround$ItemPicker instance = new LoadGridsquarePerformanceWorkaround$ItemPicker();
    IsoGridSquare square;

   private LoadGridsquarePerformanceWorkaround$ItemPicker() {
   }

    void init() {
   }

    bool begin(IsoGridSquare var1) {
      if (var1.isOverlayDone()) {
         this.square = nullptr;
    return false;
      } else {
         this.square = var1;
    return true;
      }
   }

    void checkObject(IsoObject var1) {
    IsoSprite var2 = var1.getSprite();
      if (var2 != nullptr && var2.getName() != nullptr) {
    ItemContainer var3 = var1.getContainer();
         if (var3 != nullptr && !var3.isExplored()) {
            ItemPickerJava.fillContainer(var3, IsoPlayer.getInstance());
            var3.setExplored(true);
            if (GameServer.bServer) {
               GameServer.sendItemsInContainer(var1, var3);
            }
         }

         if (var3 == nullptr || !var3.isEmpty()) {
            ItemPickerJava.updateOverlaySprite(var1);
         }
      }
   }

    void end(IsoGridSquare var1) {
      var1.setOverlayDone(true);
   }
}
} // namespace zombie
