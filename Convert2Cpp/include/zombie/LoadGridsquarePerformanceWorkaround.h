#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/LoadGridsquarePerformanceWorkaround/ItemPicker.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"

namespace zombie {


class LoadGridsquarePerformanceWorkaround {
public:
    static void init(int var0, int var1) {
      if (!GameClient.bClient) {
         ItemPicker.instance.init();
      }
   }

    static void LoadGridsquare(IsoGridSquare var0) {
      if (ItemPicker.instance.begin(var0)) {
         std::vector<IsoObject> var1 = (IsoObject[])var0.getObjects().getElements();
    int var2 = var0.getObjects().size();

         for (int var3 = 0; var3 < var2; var3++) {
    IsoObject var4 = var1[var3];
            if (!(var4 instanceof IsoWorldInventoryObject)) {
               if (!GameClient.bClient) {
                  ItemPicker.instance.checkObject(var4);
               }

               if (var4.sprite != nullptr && var4.sprite.name != nullptr && !ContainerOverlays.instance.hasOverlays(var4)) {
                  TileOverlays.instance.updateTileOverlaySprite(var4);
               }
            }
         }
      }

      ItemPicker.instance.end(var0);
   }
}
} // namespace zombie
