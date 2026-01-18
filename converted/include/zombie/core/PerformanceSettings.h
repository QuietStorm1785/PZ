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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 static const PerformanceSettings instance = new PerformanceSettings();
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

 static void setLockFPS(int lockFPS) {
 s_lockFPS = lockFPS;
 }

 static bool isUncappedFPS() {
 return s_uncappedFPS;
 }

 static void setUncappedFPS(bool uncappedFPS) {
 s_uncappedFPS = uncappedFPS;
 }

 int getFramerate() {
 return getLockFPS();
 }

 void setFramerate(int framerate) {
 setLockFPS(framerate);
 }

 bool isFramerateUncapped() {
 return isUncappedFPS();
 }

 void setFramerateUncapped(bool val) {
 setUncappedFPS(val);
 }

 void setLightingQuality(int lighting) {
 LightingFrameSkip = lighting;
 }

 int getLightingQuality() {
 return LightingFrameSkip;
 }

 void setWaterQuality(int water) {
 WaterQuality = water;
 IsoWater.getInstance().applyWaterQuality();
 }

 int getWaterQuality() {
 return WaterQuality;
 }

 void setPuddlesQuality(int puddles) {
 PuddlesQuality = puddles;
 if (puddles > 2 || puddles < 0) {
 PuddlesQuality = 0;
 }

 IsoPuddles.getInstance().applyPuddlesQuality();
 }

 int getPuddlesQuality() {
 return PuddlesQuality;
 }

 void setNewRoofHiding(bool enabled) {
 NewRoofHiding = enabled;
 }

 bool getNewRoofHiding() {
 return NewRoofHiding;
 }

 void setLightingFPS(int fps) {
 fps = Math.max(1, Math.min(120, fps);
 LightingFPS = fps;
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

 void setFogQuality(int fogQuality) {
 FogQuality = PZMath.clamp(fogQuality, 0, 2);
 }
}
} // namespace core
} // namespace zombie
