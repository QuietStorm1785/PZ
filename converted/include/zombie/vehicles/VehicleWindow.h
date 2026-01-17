#pragma once
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleWindow {
public:
  VehiclePart part;
  int health;
  bool openable;
  bool open;
  float openDelta = 0.0F;

  VehicleWindow(VehiclePart partx) { this.part = partx; }

  void init(VehicleScript.Window scriptWindow) {
    this.health = 100;
    this.openable = scriptWindow.openable;
    this.open = false;
  }

  int getHealth() { return this.part.getCondition(); }

  void setHealth(int _health) {
    _health = Math.max(_health, 0);
    _health = Math.min(_health, 100);
    this.health = _health;
  }

  bool isDestroyed() { return this.getHealth() == 0; }

  bool isOpenable() { return this.openable; }

  bool isOpen() { return this.open; }

  void setOpen(bool _open) {
    this.open = _open;
    this.part.getVehicle().bDoDamageOverlay = true;
  }

  void setOpenDelta(float delta) { this.openDelta = delta; }

  float getOpenDelta() { return this.openDelta; }

  bool isHittable() {
    if (this.isDestroyed()) {
      return false;
    } else {
      return this.isOpen() ? false
                           : this.part.getItemType() == nullptr ||
                                 this.part.getInventoryItem() != nullptr;
    }
  }

  void hit(IsoGameCharacter chr) {
    this.damage(this.getHealth());
    this.part.setCondition(0);
  }

  void damage(int amount) {
    if (amount > 0) {
      if (this.isHittable()) {
        if (GameClient.bClient) {
          GameClient.instance.sendClientCommandV(
              nullptr, "vehicle", "damageWindow", "vehicle",
              this.part.vehicle.getId(), "part", this.part.getId(), "amount",
              amount);
        } else {
          if (this.part.getVehicle().isAlarmed()) {
            this.part.getVehicle().triggerAlarm();
          }

          this.part.setCondition(this.part.getCondition() - amount);
          if (this.isDestroyed()) {
            if (this.part.getInventoryItem() != nullptr) {
              this.part.setInventoryItem(nullptr);
              this.part.getVehicle().transmitPartItem(this.part);
            }

            IsoGridSquare square = this.part.vehicle.square;
            if (GameServer.bServer) {
              GameServer.PlayWorldSoundServer("SmashWindow", false, square,
                                              0.2F, 20.0F, 1.1F, true);
            } else {
              SoundManager.instance.PlayWorldSound("SmashWindow", square, 0.2F,
                                                   20.0F, 1.0F, true);
            }

            this.part.getVehicle().getSquare().addBrokenGlass();
            WorldSoundManager.instance.addSound(nullptr, square.getX(),
                                                square.getY(), square.getZ(),
                                                10, 20, true, 4.0F, 15.0F);
          }

          this.part.getVehicle().transmitPartWindow(this.part);
        }
      }
    }
  }

  void save(ByteBuffer output) {
    output.put((byte)this.part.getCondition());
    output.put((byte)(this.open ? 1 : 0));
  }

  void load(ByteBuffer input, int WorldVersion) {
    this.part.setCondition(input.get());
    this.health = this.part.getCondition();
    this.open = input.get() == 1;
    this.openDelta = this.open ? 1.0F : 0.0F;
  }
}
} // namespace vehicles
} // namespace zombie
