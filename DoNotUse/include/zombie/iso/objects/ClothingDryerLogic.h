#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/IClothingWasherDryerLogic.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class ClothingDryerLogic {
public:
    const IsoObject m_object;
    bool bActivated;
    long soundInstance = -1L;
    float lastUpdate = -1.0F;
    bool cycleFinished = false;
    float startTime = 0.0F;
    float cycleLengthMinutes = 90.0F;
    bool alreadyExecuted = false;

    public ClothingDryerLogic(IsoObject var1) {
      this.m_object = var1;
   }

    IsoObject getObject() {
      return this.m_object;
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      this.bActivated = var1.get() == 1;
   }

    void save(ByteBuffer var1, bool var2) {
      var1.put((byte)(this.isActivated() ? 1 : 0));
   }

    void update() {
      if (this.getObject().getObjectIndex() != -1) {
         if (this.getContainer() != nullptr) {
            if (!this.getContainer().isPowered()) {
               this.setActivated(false);
            }

            this.cycleFinished();
            this.updateSound();
            if (GameClient.bClient) {
            }

            if (!this.isActivated()) {
               this.lastUpdate = -1.0F;
            } else {
    float var1 = (float)GameTime.getInstance().getWorldAgeHours();
               if (this.lastUpdate < 0.0F) {
                  this.lastUpdate = var1;
               } else if (this.lastUpdate > var1) {
                  this.lastUpdate = var1;
               }

    float var2 = var1 - this.lastUpdate;
    int var3 = (int)(var2 * 60.0F);
               if (var3 >= 1) {
                  this.lastUpdate = var1;

                  for (int var4 = 0; var4 < this.getContainer().getItems().size(); var4++) {
    InventoryItem var5 = (InventoryItem)this.getContainer().getItems().get(var4);
                     if (dynamic_cast<Clothing*>(var5) != nullptr var6) {
    float var7 = var6.getWetness();
                        if (var7 > 0.0F) {
                           var7 -= var3;
                           var6.setWetness(var7);
                           if (GameServer.bServer) {
                           }
                        }
                     }

                     if (var5.isWet() && var5.getItemWhenDry() != nullptr) {
                        var5.setWetCooldown(var5.getWetCooldown() - var3 * 250);
                        if (var5.getWetCooldown() <= 0.0F) {
    InventoryItem var8 = InventoryItemFactory.CreateItem(var5.getItemWhenDry());
                           this.getContainer().addItem(var8);
                           this.getContainer().Remove(var5);
                           var4--;
                           var5.setWet(false);
                           IsoWorld.instance.CurrentCell.addToProcessItemsRemove(var5);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      if ("dryer.state" == var1)) {
         var3.put((byte)(this.isActivated() ? 1 : 0));
      }
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      if ("dryer.state" == var1)) {
         this.setActivated(var2.get() == 1);
      }
   }

    ItemContainer getContainer() {
      return this.getObject().getContainerByType("clothingdryer");
   }

    void updateSound() {
      if (this.isActivated()) {
         if (!GameServer.bServer) {
            if (this.getObject().emitter != nullptr && this.getObject().emitter.isPlaying("ClothingDryerFinished")) {
               this.getObject().emitter.stopOrTriggerSoundByName("ClothingDryerFinished");
            }

            if (this.soundInstance == -1L) {
               this.getObject().emitter = IsoWorld.instance
                  .getFreeEmitter(this.getObject().getX() + 0.5F, this.getObject().getY() + 0.5F, (int)this.getObject().getZ());
               IsoWorld.instance.setEmitterOwner(this.getObject().emitter, this.getObject());
               this.soundInstance = this.getObject().emitter.playSoundLoopedImpl("ClothingDryerRunning");
            }
         }

         if (!GameClient.bClient) {
            WorldSoundManager.instance.addSoundRepeating(this, this.getObject().square.x, this.getObject().square.y, this.getObject().square.z, 10, 10, false);
         }
      } else if (this.soundInstance != -1L) {
         this.getObject().emitter.stopOrTriggerSound(this.soundInstance);
         this.soundInstance = -1L;
         if (this.cycleFinished) {
            this.cycleFinished = false;
            this.getObject().emitter.playSoundImpl("ClothingDryerFinished", this.getObject());
         }
      }
   }

    bool cycleFinished() {
      if (this.isActivated()) {
         if (!this.alreadyExecuted) {
            this.startTime = (float)GameTime.getInstance().getWorldAgeHours();
            this.alreadyExecuted = true;
         }

    float var1 = (float)GameTime.getInstance().getWorldAgeHours() - this.startTime;
    int var2 = (int)(var1 * 60.0F);
         if (var2 < this.cycleLengthMinutes) {
    return false;
         }

         this.cycleFinished = true;
         this.setActivated(false);
      }

    return true;
   }

    bool isItemAllowedInContainer(ItemContainer var1, InventoryItem var2) {
      return this.isActivated() ? false : this.getContainer() == var1;
   }

    bool isRemoveItemAllowedFromContainer(ItemContainer var1, InventoryItem var2) {
      return !this.getContainer().empty() && this.isActivated() ? false : this.getContainer() == var1;
   }

    bool isActivated() {
      return this.bActivated;
   }

    void setActivated(bool var1) {
    bool var2 = var1 != this.bActivated;
      this.bActivated = var1;
      this.alreadyExecuted = false;
      if (var2) {
    Thread var3 = Thread.currentThread();
         if (var3 == GameWindow.GameThread || var3 == GameServer.MainThread) {
            IsoGenerator.updateGenerator(this.getObject().getSquare());
         }
      }
   }

    void switchModeOn() {
   }

    void switchModeOff() {
      this.setActivated(false);
      this.updateSound();
      this.cycleFinished = false;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
