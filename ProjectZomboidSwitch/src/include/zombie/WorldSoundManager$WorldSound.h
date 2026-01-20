#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoZombie.h"

namespace zombie {


class WorldSoundManager {
public:
    void* source;
    int life;
    int radius;
    bool stresshumans;
    int volume;
    int x;
    int y;
    int z;
    float zombieIgnoreDist;
    bool sourceIsZombie;
    float stressMod;
    bool bRepeating;

   public WorldSoundManager$WorldSound(WorldSoundManager var1) {
      this.this$0 = var1;
      this.source = nullptr;
      this.life = 1;
      this.zombieIgnoreDist = 0.0F;
      this.stressMod = 1.0F;
   }

   public WorldSoundManager$WorldSound init(Object var1, int var2, int var3, int var4, int var5, int var6) {
      return this.init(var1, var2, var3, var4, var5, var6, false, 0.0F, 1.0F);
   }

   public WorldSoundManager$WorldSound init(Object var1, int var2, int var3, int var4, int var5, int var6, boolean var7) {
      return this.init(var1, var2, var3, var4, var5, var6, var7, 0.0F, 1.0F);
   }

   public WorldSoundManager$WorldSound init(Object var1, int var2, int var3, int var4, int var5, int var6, boolean var7, float var8, float var9) {
      this.source = var1;
      this.life = 1;
      this.x = var2;
      this.y = var3;
      this.z = var4;
      this.radius = var5;
      this.volume = var6;
      this.stresshumans = var7;
      this.zombieIgnoreDist = var8;
      this.stressMod = var9;
      this.sourceIsZombie = dynamic_cast<IsoZombie*>(var1) != nullptr;
      this.bRepeating = false;
      LuaEventManager.triggerEvent("OnWorldSound", var2, var3, var4, var5, var6, var1);
    return this;
   }

   public WorldSoundManager$WorldSound init(boolean var1, int var2, int var3, int var4, int var5, int var6, boolean var7, float var8, float var9) {
      WorldSoundManager$WorldSound var10 = this.init(nullptr, var2, var3, var4, var5, var6, var7, var8, var9);
      var10.sourceIsZombie = var1;
    return var10;
   }
}
} // namespace zombie
