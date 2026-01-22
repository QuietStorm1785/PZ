#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace core {


class PerformanceSettings {
public:
    static int ManualFrameSkips = 0;
    static int s_lockFPS = 60;
    static bool s_uncappedFPS = false;
    static int LightingFrameSkip = 0;
    static int WaterQuality = 0;
    static int PuddlesQuality = 0;
    static bool NewRoofHiding = true;
    static bool LightingThread = true;
    static int LightingFPS = 15;
    static bool auto3DZombies = false;
    static const PerformanceSettings instance = std::make_shared<PerformanceSettings>();
    static bool InterpolateAnims = true;
    static int AnimationSkip = 1;
    static bool ModelLighting = true;
    static int ZombieAnimationSpeedFalloffCount = 6;
    static int ZombieBonusFullspeedFalloff = 3;
    static int BaseStaticAnimFramerate = 60;
    static bool UseFBOs = false;
    static int numberZombiesBlended = 20;
    static int FogQuality = 0;

    static int getLockFPS() {
    return s_lockFPS;
   }

    static void setLockFPS(int var0) {
      s_lockFPS = var0;
   }

    static bool isUncappedFPS() {
    return s_uncappedFPS;
   }

    static void setUncappedFPS(bool var0) {
      s_uncappedFPS = var0;
   }

    int getFramerate() {
    return getLockFPS();
   }

    void setFramerate(int var1) {
      setLockFPS(var1);
   }

    bool isFramerateUncapped() {
    return isUncappedFPS();
   }

    void setFramerateUncapped(bool var1) {
      setUncappedFPS(var1);
   }

    void setLightingQuality(int var1) {
      LightingFrameSkip = var1;
   }

    int getLightingQuality() {
    return LightingFrameSkip;
   }

    void setWaterQuality(int var1) {
      WaterQuality = var1;
      IsoWater.getInstance().applyWaterQuality();
   }

    int getWaterQuality() {
    return WaterQuality;
   }

    void setPuddlesQuality(int var1) {
      PuddlesQuality = var1;
      if (var1 > 2 || var1 < 0) {
         PuddlesQuality = 0;
      }

      IsoPuddles.getInstance().applyPuddlesQuality();
   }

    int getPuddlesQuality() {
    return PuddlesQuality;
   }

    void setNewRoofHiding(bool var1) {
      NewRoofHiding = var1;
   }

    bool getNewRoofHiding() {
    return NewRoofHiding;
   }

    void setLightingFPS(int var1) {
      var1 = Math.max(1, Math.min(120, var1));
      LightingFPS = var1;
      System.out.println("LightingFPS set to " + LightingFPS);
   }

    int getLightingFPS() {
    return LightingFPS;
   }

    int getUIRenderFPS() {
      return UIManager.useUIFBO ? Core.OptionUIRenderFPS : s_lockFPS;
   }

    int getFogQuality() {
    return FogQuality;
   }

    void setFogQuality(int var1) {
      FogQuality = PZMath.clamp(var1, 0, 2);
   }
}
} // namespace core
} // namespace zombie
