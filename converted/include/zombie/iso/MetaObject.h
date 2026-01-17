#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MetaObject {
public:
  int type;
  int x;
  int y;
  RoomDef def;
  bool bUsed = false;

public
  MetaObject(int _type, int _x, int _y, RoomDef _def) {
    this.type = _type;
    this.x = _x;
    this.y = _y;
    this.def = _def;
  }

  RoomDef getRoom() { return this.def; }

  bool getUsed() { return this.bUsed; }

  void setUsed(bool _bUsed) { this.bUsed = _bUsed; }

  int getX() { return this.x; }

  int getY() { return this.y; }

  int getType() { return this.type; }
}
} // namespace iso
} // namespace zombie
