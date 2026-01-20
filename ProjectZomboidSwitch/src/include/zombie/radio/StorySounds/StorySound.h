#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace radio {
namespace StorySounds {


class StorySound {
public:
    std::string name = nullptr;
    float baseVolume = 1.0F;

    public StorySound(const std::string& var1, float var2) {
      this.name = var1;
      this.baseVolume = var2;
   }

    long playSound() {
    Vector2 var1 = SLSoundManager.getInstance().getRandomBorderPosition();
      return SLSoundManager.Emitter.playSound(this.name, this.baseVolume, var1.x, var1.y, 0.0F, 100.0F, SLSoundManager.getInstance().getRandomBorderRange());
   }

    long playSound(float var1) {
      return SLSoundManager.Emitter.playSound(this.name, var1, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, IsoPlayer.getInstance().z, 10.0F, 50.0F);
   }

    long playSound(float var1, float var2, float var3, float var4, float var5) {
      return this.playSound(this.baseVolume, var1, var2, var3, var4, var5);
   }

    long playSound(float var1, float var2, float var3, float var4, float var5, float var6) {
      return SLSoundManager.Emitter.playSound(this.name, this.baseVolume * var1, var2, var3, var4, var5, var6);
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    float getBaseVolume() {
      return this.baseVolume;
   }

    void setBaseVolume(float var1) {
      this.baseVolume = var1;
   }

    StorySound getClone() {
      return std::make_shared<StorySound>(this.name, this.baseVolume);
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
