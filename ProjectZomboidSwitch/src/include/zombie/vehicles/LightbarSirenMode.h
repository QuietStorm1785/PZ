#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/VehicleScript/LightBar.h"

namespace zombie {
namespace vehicles {


class LightbarSirenMode {
public:
    int mode = 0;
    const int modeMax = 3;

    int get() {
      return this.mode;
   }

    void set(int var1) {
      if (var1 > 3) {
         this.mode = 3;
      } else if (var1 < 0) {
         this.mode = 0;
      } else {
         this.mode = var1;
      }
   }

    bool isEnable() {
      return this.mode != 0;
   }

    std::string getSoundName(LightBar var1) {
      if (this.isEnable()) {
         if (this.mode == 1) {
            return var1.soundSiren0;
         }

         if (this.mode == 2) {
            return var1.soundSiren1;
         }

         if (this.mode == 3) {
            return var1.soundSiren2;
         }
      }

      return "";
   }
}
} // namespace vehicles
} // namespace zombie
