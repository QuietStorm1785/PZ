#pragma once
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

class VehicleDoor {
public:
  VehiclePart part;
  bool open;
  bool locked;
  bool lockBroken;

public
  VehicleDoor(VehiclePart _part) { this.part = _part; }

  void init(VehicleScript.Door scriptDoor) {
    this.open = false;
    this.locked = false;
    this.lockBroken = false;
  }

  bool isOpen() { return this.open; }

  void setOpen(bool _open) { this.open = _open; }

  bool isLocked() { return this.locked; }

  void setLocked(bool _locked) { this.locked = _locked; }

  bool isLockBroken() { return this.lockBroken; }

  void setLockBroken(bool broken) { this.lockBroken = broken; }

  void save(ByteBuffer output) {
    output.put((byte)(this.open ? 1 : 0));
    output.put((byte)(this.locked ? 1 : 0));
    output.put((byte)(this.lockBroken ? 1 : 0));
  }

  void load(ByteBuffer input, int WorldVersion) {
    this.open = input.get() == 1;
    this.locked = input.get() == 1;
    this.lockBroken = input.get() == 1;
  }
}
} // namespace vehicles
} // namespace zombie
