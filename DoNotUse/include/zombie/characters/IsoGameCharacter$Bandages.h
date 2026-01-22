#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "zombie/characters/BodyDamage/BodyDamage.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartLast.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace characters {


class IsoGameCharacter {
public:
   const std::unordered_map<std::string, std::string> bandageTypeMap = std::make_unique<std::unordered_map<>>();
   const THashMap<std::string, InventoryItem> itemMap = std::make_unique<THashMap>();

   private IsoGameCharacter$Bandages() {
   }

    std::string getBloodBandageType(const std::string& var1) {
    std::string var2 = this.bandageTypeMap.get(var1);
      if (var2 == nullptr) {
         this.bandageTypeMap.put(var1, var2 = var1 + "_Blood");
      }

    return var2;
   }

    void update(IsoGameCharacter var1) {
      if (!GameServer.bServer) {
    BodyDamage var2 = var1.getBodyDamage();
    WornItems var3 = var1.getWornItems();
         if (var2 != nullptr && var3 != nullptr) {
            if (!$assertionsDisabled && dynamic_cast<IsoZombie*>(var1) != nullptr) {
               throw std::make_unique<AssertionError>();
            } else {
               this.itemMap.clear();

               for (int var4 = 0; var4 < var3.size(); var4++) {
    InventoryItem var5 = var3.getItemByIndex(var4);
                  if (var5 != nullptr) {
                     this.itemMap.put(var5.getFullType(), var5);
                  }
               }

               for (int var10 = 0; var10 < BodyPartType.ToIndex(BodyPartType.MAX); var10++) {
    BodyPart var11 = var2.getBodyPart(BodyPartType.FromIndex(var10));
    BodyPartLast var6 = var2.getBodyPartsLastState(BodyPartType.FromIndex(var10));
    std::string var7 = var11.getType().getBandageModel();
                  if (!StringUtils.isNullOrWhitespace(var7)) {
    std::string var8 = this.getBloodBandageType(var7);
                     if (var11.bandaged() != var6.bandaged()) {
                        if (var11.bandaged()) {
                           if (var11.isBandageDirty()) {
                              this.removeBandageModel(var1, var7);
                              this.addBandageModel(var1, var8);
                           } else {
                              this.removeBandageModel(var1, var8);
                              this.addBandageModel(var1, var7);
                           }
                        } else {
                           this.removeBandageModel(var1, var7);
                           this.removeBandageModel(var1, var8);
                        }
                     }

                     if (var11.bitten() != var6.bitten()) {
                        if (var11.bitten()) {
    std::string var9 = var11.getType().getBiteWoundModel(var1.isFemale());
                           if (StringUtils.isNullOrWhitespace(var9)) {
                              continue;
                           }

                           this.addBandageModel(var1, var9);
                        } else {
                           this.removeBandageModel(var1, var11.getType().getBiteWoundModel(var1.isFemale()));
                        }
                     }

                     if (var11.scratched() != var6.scratched()) {
                        if (var11.scratched()) {
    std::string var12 = var11.getType().getScratchWoundModel(var1.isFemale());
                           if (StringUtils.isNullOrWhitespace(var12)) {
                              continue;
                           }

                           this.addBandageModel(var1, var12);
                        } else {
                           this.removeBandageModel(var1, var11.getType().getScratchWoundModel(var1.isFemale()));
                        }
                     }

                     if (var11.isCut() != var6.isCut()) {
                        if (var11.isCut()) {
    std::string var13 = var11.getType().getCutWoundModel(var1.isFemale());
                           if (!StringUtils.isNullOrWhitespace(var13)) {
                              this.addBandageModel(var1, var13);
                           }
                        } else {
                           this.removeBandageModel(var1, var11.getType().getCutWoundModel(var1.isFemale()));
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void addBandageModel(IsoGameCharacter var1, const std::string& var2) {
      if (!this.itemMap.containsKey(var2)) {
         if (InventoryItemFactory.CreateItem(var2) instanceof Clothing var4) {
            var1.getInventory().addItem(var4);
            var1.setWornItem(var4.getBodyLocation(), var4);
            var1.resetModelNextFrame();
         }
      }
   }

    void removeBandageModel(IsoGameCharacter var1, const std::string& var2) {
    InventoryItem var3 = (InventoryItem)this.itemMap.get(var2);
      if (var3 != nullptr) {
         var1.getWornItems().remove(var3);
         var1.getInventory().Remove(var3);
         var1.resetModelNextFrame();
         var1.onWornItemsChanged();
         if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
            GameClient.instance.sendClothing((IsoPlayer)var1, var3.getBodyLocation(), var3);
         }
      }
   }
}
} // namespace characters
} // namespace zombie
