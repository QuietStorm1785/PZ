#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"

namespace zombie {


class AmbientSoundManager {
public:
    float x;
    float y;
    std::string name;
    float radius;
    float volume;
    long startTime;
    int duration;
    int worldSoundDelay;

   public AmbientSoundManager$Ambient(AmbientSoundManager var1, std::string var2, float var3, float var4, float var5, float var6) {
      this.this$0 = var1;
      this.worldSoundDelay = 0;
      this.name = var2;
      this.x = var3;
      this.y = var4;
      this.radius = var5;
      this.volume = var6;
      this.startTime = System.currentTimeMillis() / 1000L;
      this.duration = 2;
      this.update();
      LuaEventManager.triggerEvent("OnAmbientSound", var2, var3, var4);
   }

    bool finished() {
    long var1 = System.currentTimeMillis() / 1000L;
      return var1 - this.startTime >= this.duration;
   }

    void update() {
    long var1 = System.currentTimeMillis() / 1000L;
      if (var1 - this.startTime >= this.worldSoundDelay) {
         WorldSoundManager.instance.addSound(nullptr, (int)this.x, (int)this.y, 0, 600, 600);
      }
   }
}
} // namespace zombie
