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
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/ContainerOverlays/ContainerOverlay.h"
#include "zombie/iso/ContainerOverlays/ContainerOverlayEntry.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {
namespace iso {


class ContainerOverlays {
public:
    static const ContainerOverlays instance = std::make_shared<ContainerOverlays>();
   private static const std::vector<ContainerOverlayEntry> tempEntries = std::make_unique<std::vector<>>();
   private const THashMap<std::string, ContainerOverlay> overlayMap = std::make_unique<THashMap>();

    void parseContainerOverlayMapV0(KahluaTableImpl var1) {
      for (Entry var3 : var1.delegate.entrySet()) {
    std::string var4 = var3.getKey();
    ContainerOverlay var5 = std::make_shared<ContainerOverlay>();
         var5.name = var4;
         this.overlayMap.put(var5.name, var5);
    KahluaTableImpl var6 = (KahluaTableImpl)var3.getValue();

         for (Entry var8 : var6.delegate.entrySet()) {
    std::string var9 = var8.getKey();
    KahluaTableImpl var10 = (KahluaTableImpl)var8.getValue();
    std::string var11 = nullptr;
            if (var10.delegate.containsKey(1.0)) {
               var11 = var10.rawget(1.0);
            }

    std::string var12 = nullptr;
            if (var10.delegate.containsKey(2.0)) {
               var12 = var10.rawget(2.0);
            }

    ContainerOverlayEntry var13 = std::make_shared<ContainerOverlayEntry>();
            var13.manyItems = var11;
            var13.fewItems = var12;
            var13.room = var9;
            var5.entries.push_back(var13);
         }
      }
   }

    void parseContainerOverlayMapV1(KahluaTableImpl var1) {
    KahluaTableIterator var2 = var1.iterator();

      while (var2.advance()) {
    std::string var3 = var2.getKey();
         if (!"VERSION".equalsIgnoreCase(var3)) {
    ContainerOverlay var4 = std::make_shared<ContainerOverlay>();
            var4.name = var3;
    KahluaTableImpl var5 = (KahluaTableImpl)var2.getValue();
    KahluaTableIterator var6 = var5.iterator();

            while (var6.advance()) {
    KahluaTableImpl var7 = (KahluaTableImpl)var6.getValue();
    std::string var8 = var7.rawgetStr("name");
    KahluaTableImpl var9 = (KahluaTableImpl)var7.rawget("tiles");
    ContainerOverlayEntry var10 = std::make_shared<ContainerOverlayEntry>();
               var10.manyItems = (std::string)var9.rawget(1);
               var10.fewItems = (std::string)var9.rawget(2);
               if (StringUtils.isNullOrWhitespace(var10.manyItems) || "none".equalsIgnoreCase(var10.manyItems)) {
                  var10.manyItems = nullptr;
               }

               if (StringUtils.isNullOrWhitespace(var10.fewItems) || "none".equalsIgnoreCase(var10.fewItems)) {
                  var10.fewItems = nullptr;
               }

               var10.room = var8;
               var4.entries.push_back(var10);
            }

            this.overlayMap.put(var4.name, var4);
         }
      }
   }

    void addOverlays(KahluaTableImpl var1) {
    int var2 = var1.rawgetInt("VERSION");
      if (var2 == -1) {
         this.parseContainerOverlayMapV0(var1);
      } else {
         if (var2 != 1) {
            throw RuntimeException("unknown overlayMap.VERSION " + var2);
         }

         this.parseContainerOverlayMapV1(var1);
      }
   }

    bool hasOverlays(IsoObject var1) {
      return var1 != nullptr && var1.sprite != nullptr && var1.sprite.name != nullptr && this.overlayMap.containsKey(var1.sprite.name);
   }

    void updateContainerOverlaySprite(IsoObject var1) {
      if (var1 != nullptr) {
         if (!(dynamic_cast<IsoStove*>(var1) != nullptr)) {
    IsoGridSquare var2 = var1.getSquare();
            if (var2 != nullptr) {
    std::string var3 = nullptr;
    ItemContainer var4 = var1.getContainer();
               if (var1.sprite != nullptr && var1.sprite.name != nullptr && var4 != nullptr && var4.getItems() != nullptr && !var4.empty()) {
    ContainerOverlay var5 = (ContainerOverlay)this.overlayMap.get(var1.sprite.name);
                  if (var5 != nullptr) {
    std::string var6 = "other";
                     if (var2.getRoom() != nullptr) {
                        var6 = var2.getRoom().getName();
                     }

    ContainerOverlayEntry var7 = var5.pickRandom(var6, var2.x, var2.y, var2.z);
                     if (var7 == nullptr) {
                        var7 = var5.pickRandom("other", var2.x, var2.y, var2.z);
                     }

                     if (var7 != nullptr) {
                        var3 = var7.manyItems;
                        if (var7.fewItems != nullptr && var4.getItems().size() < 7) {
                           var3 = var7.fewItems;
                        }
                     }
                  }
               }

               if (!StringUtils.isNullOrWhitespace(var3) && !GameServer.bServer && Texture.getSharedTexture(var3) == nullptr) {
                  var3 = nullptr;
               }

               var1.setOverlaySprite(var3);
            }
         }
      }
   }

    void Reset() {
      this.overlayMap.clear();
   }
}
} // namespace iso
} // namespace zombie
