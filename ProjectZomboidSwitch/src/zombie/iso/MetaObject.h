#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class MetaObject {
public:
    int type;
    int x;
    int y;
    RoomDef def;
    bool bUsed = false;

    public MetaObject(int var1, int var2, int var3, RoomDef var4) {
      this.type = var1;
      this.x = var2;
      this.y = var3;
      this.def = var4;
   }

    RoomDef getRoom() {
      return this.def;
   }

    bool getUsed() {
      return this.bUsed;
   }

    void setUsed(bool var1) {
      this.bUsed = var1;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getType() {
      return this.type;
   }
}
} // namespace iso
} // namespace zombie
