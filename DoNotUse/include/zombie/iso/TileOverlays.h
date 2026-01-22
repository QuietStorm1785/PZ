#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/TileOverlays/TileOverlay.h"
#include "zombie/iso/TileOverlays/TileOverlayEntry.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace iso {


class TileOverlays {
public:
    static const TileOverlays instance = std::make_shared<TileOverlays>();
   private static const THashMap<std::string, TileOverlay> overlayMap = std::make_unique<THashMap>();
   private static const std::vector<TileOverlayEntry> tempEntries = std::make_unique<std::vector<>>();

    void addOverlays(KahluaTableImpl var1) {
    KahluaTableIterator var2 = var1.iterator();

      while (var2.advance()) {
    std::string var3 = var2.getKey();
         if (!"VERSION".equalsIgnoreCase(var3)) {
    TileOverlay var4 = std::make_shared<TileOverlay>();
            var4.tile = var3;
    KahluaTableImpl var5 = (KahluaTableImpl)var2.getValue();
    KahluaTableIterator var6 = var5.iterator();

            while (var6.advance()) {
    KahluaTableImpl var7 = (KahluaTableImpl)var6.getValue();
    TileOverlayEntry var8 = std::make_shared<TileOverlayEntry>();
               var8.room = var7.rawgetStr("name");
               var8.chance = var7.rawgetInt("chance");
               var8.usage.parse(var7.rawgetStr("usage"));
    KahluaTableImpl var9 = (KahluaTableImpl)var7.rawget("tiles");
    KahluaTableIterator var10 = var9.iterator();

               while (var10.advance()) {
    std::string var11 = var10.getValue();
                  if (StringUtils.isNullOrWhitespace(var11) || "none".equalsIgnoreCase(var11)) {
                     var11 = "";
                  } else if (Core.bDebug && !GameServer.bServer && Texture.getSharedTexture(var11) == nullptr) {
                     System.out.println("BLANK OVERLAY TEXTURE. Set it to \"none\".: " + var11);
                  }

                  var8.tiles.push_back(var11);
               }

               var4.entries.push_back(var8);
            }

            overlayMap.put(var4.tile, var4);
         }
      }
   }

    bool hasOverlays(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr && overlayMap.containsKey(var1.sprite.name);
   }

    void updateTileOverlaySprite(IsoObject var1) {
      if (var1 != nullptr) {
    IsoGridSquare var2 = var1.getSquare();
         if (var2 != nullptr) {
    std::string var3 = nullptr;
    float var4 = -1.0F;
    float var5 = -1.0F;
    float var6 = -1.0F;
    float var7 = -1.0F;
            if (var1.sprite != nullptr && var1.sprite.name != nullptr) {
    TileOverlay var8 = (TileOverlay)overlayMap.get(var1.sprite.name);
               if (var8 != nullptr) {
    std::string var9 = "other";
                  if (var2.getRoom() != nullptr) {
                     var9 = var2.getRoom().getName();
                  }

    TileOverlayEntry var10 = var8.pickRandom(var9, var2);
                  if (var10 == nullptr) {
                     var10 = var8.pickRandom("other", var2);
                  }

                  if (var10 != nullptr) {
                     if (var10.usage.bTableTop && this.hasObjectOnTop(var1)) {
                        return;
                     }

                     var3 = var10.pickRandom(var2.x, var2.y, var2.z);
                     if (var10.usage.alpha >= 0.0F) {
                        var6 = 1.0F;
                        var5 = 1.0F;
                        var4 = 1.0F;
                        var7 = var10.usage.alpha;
                     }
                  }
               }
            }

            if (!StringUtils.isNullOrWhitespace(var3) && !GameServer.bServer && Texture.getSharedTexture(var3) == nullptr) {
               var3 = nullptr;
            }

            if (!StringUtils.isNullOrWhitespace(var3)) {
               if (var1.AttachedAnimSprite == nullptr) {
                  var1.AttachedAnimSprite = new std::vector(4);
               }

    IsoSprite var11 = IsoSpriteManager.instance.getSprite(var3);
               var11.name = var3;
    IsoSpriteInstance var12 = IsoSpriteInstance.get(var11);
               if (var7 > 0.0F) {
                  var12.tintr = var4;
                  var12.tintg = var5;
                  var12.tintb = var6;
                  var12.alpha = var7;
               }

               var12.bCopyTargetAlpha = false;
               var12.bMultiplyObjectAlpha = true;
               var1.AttachedAnimSprite.push_back(var12);
            }
         }
      }
   }

    bool hasObjectOnTop(IsoObject var1) {
      if (!var1.isTableSurface()) {
    return false;
      } else {
    IsoGridSquare var2 = var1.getSquare();

         for (int var3 = var1.getObjectIndex() + 1; var3 < var2.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var2.getObjects().get(var3);
            if (var4.isTableTopObject() || var4.isTableSurface()) {
    return true;
            }
         }

    return false;
      }
   }

    void fixTableTopOverlays(IsoGridSquare var1) {
      if (var1 != nullptr && !var1.getObjects().empty()) {
    bool var2 = false;

         for (int var3 = var1.getObjects().size() - 1; var3 >= 0; var3--) {
    IsoObject var4 = (IsoObject)var1.getObjects().get(var3);
            if (var2 && var4.isTableSurface()) {
               this.removeTableTopOverlays(var4);
            }

            if (var4.isTableSurface() || var4.isTableTopObject()) {
               var2 = true;
            }
         }
      }
   }

    void removeTableTopOverlays(IsoObject var1) {
      if (var1 != nullptr && var1.isTableSurface()) {
         if (var1.sprite != nullptr && var1.sprite.name != nullptr) {
            if (var1.AttachedAnimSprite != nullptr && !var1.AttachedAnimSprite.empty()) {
    TileOverlay var2 = (TileOverlay)overlayMap.get(var1.sprite.name);
               if (var2 != nullptr) {
    int var3 = var1.AttachedAnimSprite.size();

                  for (int var4 = 0; var4 < var2.entries.size(); var4++) {
    TileOverlayEntry var5 = (TileOverlayEntry)var2.entries.get(var4);
                     if (var5.usage.bTableTop) {
                        for (int var6 = 0; var6 < var5.tiles.size(); var6++) {
                           this.tryRemoveAttachedSprite(var1.AttachedAnimSprite, (std::string)var5.tiles.get(var6));
                        }
                     }
                  }

                  if (var3 != var1.AttachedAnimSprite.size()) {
                  }
               }
            }
         }
      }
   }

    void tryRemoveAttachedSprite(std::vector<IsoSpriteInstance> var1, const std::string& var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
    IsoSpriteInstance var4 = (IsoSpriteInstance)var1.get(var3);
         if (var2 == var4.getName())) {
            var1.remove(var3--);
            IsoSpriteInstance.push_back(var4);
         }
      }
   }

    void Reset() {
      overlayMap.clear();
   }
}
} // namespace iso
} // namespace zombie
