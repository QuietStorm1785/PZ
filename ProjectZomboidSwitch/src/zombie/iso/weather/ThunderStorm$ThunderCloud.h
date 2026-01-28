#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"

namespace zombie {
namespace iso {
namespace weather {


class ThunderStorm {
public:
    int currentX;
    int currentY;
    int startX;
    int startY;
    int endX;
    int endY;
    double startTime;
    double endTime;
    double duration;
    float strength;
    float angle;
    float radius;
    float eventFrequency;
    float thunderRatio;
    float percentageOffset;
    bool isRunning = false;
    zombie::GameTime::AnimTimer suspendTimer;

    int getCurrentX() {
      return this.currentX;
   }

    int getCurrentY() {
      return this.currentY;
   }

    float getRadius() {
      return this.radius;
   }

    bool isRunning() {
      return this.isRunning;
   }

    float getStrength() {
      return this.strength;
   }

    double lifeTime() {
      return (this.startTime - this.endTime) / this.duration;
   }

    void setCenter(int var1, int var2, float var3) {
    int var4 = ThunderStorm.getMapDiagonal();
    float var5 = ThunderStorm.addToAngle(var3, 180.0F);
    int var6 = var4 + Rand.Next(1500, 7500);
    int var7 = (int)(var1 + var6 * Math.cos(Math.toRadians(var5)));
    int var8 = (int)(var2 + var6 * Math.sin(Math.toRadians(var5)));
      var6 = var4 + Rand.Next(1500, 7500);
    int var9 = (int)(var1 + var6 * Math.cos(Math.toRadians(var3)));
    int var10 = (int)(var2 + var6 * Math.sin(Math.toRadians(var3)));
      this.startX = var7;
      this.startY = var8;
      this.endX = var9;
      this.endY = var10;
      this.currentX = var7;
      this.currentY = var8;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
