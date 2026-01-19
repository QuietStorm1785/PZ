#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {


class ZomboidBitFlag {
:
   EnumSet<IsoFlagType> isoFlagTypeES = EnumSet.noneOf(IsoFlagType.class);

     ZomboidBitFlag(int var1) {
   }

     ZomboidBitFlag(ZomboidBitFlag var1) {
      if (var1 != nullptr) {
         this.isoFlagTypeES.addAll(var1.isoFlagTypeES);
      }
   }

    void set(int var1, bool var2) {
      if (var1 < IsoFlagType.MAX.index()) {
         if (var2) {
            this.isoFlagTypeES.add(IsoFlagType.fromIndex(var1));
         } else {
            this.isoFlagTypeES.remove(IsoFlagType.fromIndex(var1));
         }
      }
   }

    void clear() {
      this.isoFlagTypeES.clear();
   }

    bool isSet(int var1) {
      return this.isoFlagTypeES.contains(IsoFlagType.fromIndex(var1));
   }

    bool isSet(IsoFlagType var1) {
      return this.isoFlagTypeES.contains(var1);
   }

    void set(IsoFlagType var1, bool var2) {
      if (var2) {
         this.isoFlagTypeES.add(var1);
      } else {
         this.isoFlagTypeES.remove(var1);
      }
   }

    bool isSet(IsoObjectType var1) {
      return this.isSet(var1.index());
   }

    void set(IsoObjectType var1, bool var2) {
      this.set(var1.index(), var2);
   }

    void Or(ZomboidBitFlag var1) {
      this.isoFlagTypeES.addAll(var1.isoFlagTypeES);
   }

    void save(DataOutputStream var1) {
   }

    void load(DataInputStream var1) {
   }

    void getFromLong(long var1) {
   }
}
} // namespace zombie
