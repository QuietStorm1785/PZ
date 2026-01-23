#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class GameTime {
public:
    float Elapsed;
    float Duration;
    bool Finished = true;
    int Ticks;

    void init(int var1) {
      this.Ticks = var1;
      this.Elapsed = 0.0F;
      this.Duration = var1 * 1 / 30.0F;
      this.Finished = false;
   }

    void update() {
      this.Elapsed = this.Elapsed + GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F / 30.0F;
      if (this.Elapsed >= this.Duration) {
         this.Elapsed = this.Duration;
         this.Finished = true;
      }
   }

    float ratio() {
      return this.Elapsed / this.Duration;
   }

    bool finished() {
      return this.Finished;
   }
}
} // namespace zombie
