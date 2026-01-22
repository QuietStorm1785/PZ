#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/objects/VehicleScript/Window.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehicleWindow {
public:
    VehiclePart part;
    int health;
    bool openable;
    bool open;
    float openDelta = 0.0F;

   VehicleWindow(VehiclePart var1) {
      this.part = var1;
   }

    void init(Window var1) {
      this.health = 100;
      this.openable = var1.openable;
      this.open = false;
   }

    int getHealth() {
      return this.part.getCondition();
   }

    void setHealth(int var1) {
      var1 = Math.max(var1, 0);
      var1 = Math.min(var1, 100);
      this.health = var1;
   }

    bool isDestroyed() {
      return this.getHealth() == 0;
   }

    bool isOpenable() {
      return this.openable;
   }

    bool isOpen() {
      return this.open;
   }

    void setOpen(bool var1) {
      this.open = var1;
      this.part.getVehicle().bDoDamageOverlay = true;
   }

    void setOpenDelta(float var1) {
      this.openDelta = var1;
   }

    float getOpenDelta() {
      return this.openDelta;
   }

    bool isHittable() {
      if (this.isDestroyed()) {
    return false;
      } else {
         return this.isOpen() ? false : this.part.getItemType() == nullptr || this.part.getInventoryItem() != nullptr;
      }
   }

    void hit(IsoGameCharacter var1) {
      this.damage(this.getHealth());
      this.part.setCondition(0);
   }

    void damage(int var1) {
      if (var1 > 0) {
         if (this.isHittable()) {
            if (GameClient.bClient) {
               GameClient.instance
                  .sendClientCommandV(
                     nullptr, "vehicle", "damageWindow", new Object[]{"vehicle", this.part.vehicle.getId(), "part", this.part.getId(), "amount", var1}
                  );
            } else {
               if (this.part.getVehicle().isAlarmed()) {
                  this.part.getVehicle().triggerAlarm();
               }

               this.part.setCondition(this.part.getCondition() - var1);
               if (this.isDestroyed()) {
                  if (this.part.getInventoryItem() != nullptr) {
                     this.part.setInventoryItem(nullptr);
                     this.part.getVehicle().transmitPartItem(this.part);
                  }

    IsoGridSquare var2 = this.part.vehicle.square;
                  if (GameServer.bServer) {
                     GameServer.PlayWorldSoundServer("SmashWindow", false, var2, 0.2F, 20.0F, 1.1F, true);
                  } else {
                     SoundManager.instance.PlayWorldSound("SmashWindow", var2, 0.2F, 20.0F, 1.0F, true);
                  }

                  this.part.getVehicle().getSquare().addBrokenGlass();
                  WorldSoundManager.instance.addSound(nullptr, var2.getX(), var2.getY(), var2.getZ(), 10, 20, true, 4.0F, 15.0F);
               }

               this.part.getVehicle().transmitPartWindow(this.part);
            }
         }
      }
   }

    void save(ByteBuffer var1) {
      var1.put((byte)this.part.getCondition());
      var1.put((byte)(this.open ? 1 : 0));
   }

    void load(ByteBuffer var1, int var2) {
      this.part.setCondition(var1.get());
      this.health = this.part.getCondition();
      this.open = var1.get() == 1;
      this.openDelta = this.open ? 1.0F : 0.0F;
   }
}
} // namespace vehicles
} // namespace zombie
