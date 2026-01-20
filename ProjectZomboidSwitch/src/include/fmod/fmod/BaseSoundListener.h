#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace fmod {
namespace fmod {

class BaseSoundListener {
public:
    int index;
    float x;
    float y;
    float z;

    public BaseSoundListener(int var1) {
      this.index = var1;
   }

    void setPos(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public abstract void tick();
}
} // namespace fmod
} // namespace fmod
