#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/VehicleScript/Door.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehicleDoor {
public:
    VehiclePart part;
    bool open;
    bool locked;
    bool lockBroken;

    public VehicleDoor(VehiclePart var1) {
      this.part = var1;
   }

    void init(Door var1) {
      this.open = false;
      this.locked = false;
      this.lockBroken = false;
   }

    bool isOpen() {
      return this.open;
   }

    void setOpen(bool var1) {
      this.open = var1;
   }

    bool isLocked() {
      return this.locked;
   }

    void setLocked(bool var1) {
      this.locked = var1;
   }

    bool isLockBroken() {
      return this.lockBroken;
   }

    void setLockBroken(bool var1) {
      this.lockBroken = var1;
   }

    void save(ByteBuffer var1) {
      var1.put((byte)(this.open ? 1 : 0));
      var1.put((byte)(this.locked ? 1 : 0));
      var1.put((byte)(this.lockBroken ? 1 : 0));
   }

    void load(ByteBuffer var1, int var2) {
      this.open = var1.get() == 1;
      this.locked = var1.get() == 1;
      this.lockBroken = var1.get() == 1;
   }
}
} // namespace vehicles
} // namespace zombie
