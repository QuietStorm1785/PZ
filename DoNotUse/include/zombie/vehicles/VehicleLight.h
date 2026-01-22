#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehicleLight {
public:
    bool active;
    const Vector3f offset = std::make_shared<Vector3f>();
    float dist = 16.0F;
    float intensity = 1.0F;
    float dot = 0.96F;
    int focusing = 0;

    bool getActive() {
      return this.active;
   }

    void setActive(bool var1) {
      this.active = var1;
   }

    int getFocusing() {
      return this.focusing;
   }

    float getIntensity() {
      return this.intensity;
   }

    float getDistanization() {
      return this.dist;
   }

    bool canFocusingUp() {
      return this.focusing != 0;
   }

    bool canFocusingDown() {
      return this.focusing != 1;
   }

    void setFocusingUp() {
      if (this.focusing != 0) {
         if (this.focusing < 4) {
            this.focusing = 4;
         } else if (this.focusing < 10) {
            this.focusing = 10;
         } else if (this.focusing < 30) {
            this.focusing = 30;
         } else if (this.focusing < 100) {
            this.focusing = 100;
         } else {
            this.focusing = 0;
         }
      }
   }

    void setFocusingDown() {
      if (this.focusing != 1) {
         if (this.focusing == 0) {
            this.focusing = 100;
         } else if (this.focusing > 30) {
            this.focusing = 30;
         } else if (this.focusing > 10) {
            this.focusing = 10;
         } else if (this.focusing > 4) {
            this.focusing = 4;
         } else {
            this.focusing = 1;
         }
      }
   }

    void save(ByteBuffer var1) {
      var1.put((byte)(this.active ? 1 : 0));
      var1.putFloat(this.offset.x);
      var1.putFloat(this.offset.y);
      var1.putFloat(this.intensity);
      var1.putFloat(this.dist);
      var1.putInt(this.focusing);
   }

    void load(ByteBuffer var1, int var2) {
      this.active = var1.get() == 1;
      if (var2 >= 135) {
         this.offset.x = var1.getFloat();
         this.offset.y = var1.getFloat();
         this.intensity = var1.getFloat();
         this.dist = var1.getFloat();
         this.focusing = var1.getInt();
      }
   }
}
} // namespace vehicles
} // namespace zombie
