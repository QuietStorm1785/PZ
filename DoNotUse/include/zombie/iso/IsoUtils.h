#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace iso {


class IsoUtils {
public:
    static float clamp(float var0, float var1, float var2) {
      return Math.min(Math.max(var0, var1), var2);
   }

    static float lerp(float var0, float var1, float var2) {
    return var2 = = var1 ? var1 : (clamp(var0, var1, var2) - var1) / (var2 - var1);
   }

    static float smoothstep(float var0, float var1, float var2) {
    float var3 = clamp((var2 - var0) / (var1 - var0), 0.0F, 1.0F);
      return var3 * var3 * (3.0F - 2.0F * var3);
   }

    static float DistanceTo(float var0, float var1, float var2, float var3) {
      return (float)Math.sqrt(Math.pow(var2 - var0, 2.0) + Math.pow(var3 - var1, 2.0));
   }

    static float DistanceTo2D(float var0, float var1, float var2, float var3) {
      return (float)Math.sqrt(Math.pow(var2 - var0, 2.0) + Math.pow(var3 - var1, 2.0));
   }

    static float DistanceTo(float var0, float var1, float var2, float var3, float var4, float var5) {
      return (float)Math.sqrt(Math.pow(var3 - var0, 2.0) + Math.pow(var4 - var1, 2.0) + Math.pow(var5 - var2, 2.0));
   }

    static float DistanceToSquared(float var0, float var1, float var2, float var3, float var4, float var5) {
      return (float)(Math.pow(var3 - var0, 2.0) + Math.pow(var4 - var1, 2.0) + Math.pow(var5 - var2, 2.0));
   }

    static float DistanceToSquared(float var0, float var1, float var2, float var3) {
      return (float)(Math.pow(var2 - var0, 2.0) + Math.pow(var3 - var1, 2.0));
   }

    static float DistanceManhatten(float var0, float var1, float var2, float var3) {
      return Math.abs(var2 - var0) + Math.abs(var3 - var1);
   }

    static float DistanceManhatten(float var0, float var1, float var2, float var3, float var4, float var5) {
      return Math.abs(var2 - var0) + Math.abs(var3 - var1) + Math.abs(var5 - var4) * 2.0F;
   }

    static float DistanceManhattenSquare(float var0, float var1, float var2, float var3) {
      return Math.max(Math.abs(var2 - var0), Math.abs(var3 - var1));
   }

    static float XToIso(float var0, float var1, float var2) {
    float var3 = var0 + IsoCamera.getOffX();
    float var4 = var1 + IsoCamera.getOffY();
    float var5 = (var3 + 2.0F * var4) / (64.0F * Core.TileScale);
    float var6 = (var3 - 2.0F * var4) / (-64.0F * Core.TileScale);
      var5 += 3.0F * var2;
      var6 += 3.0F * var2;
    return var5;
   }

    static float XToIsoTrue(float var0, float var1, int var2) {
    float var3 = var0 + (int)IsoCamera.cameras[IsoPlayer.getPlayerIndex()].OffX;
    float var4 = var1 + (int)IsoCamera.cameras[IsoPlayer.getPlayerIndex()].OffY;
    float var5 = (var3 + 2.0F * var4) / (64.0F * Core.TileScale);
    float var6 = (var3 - 2.0F * var4) / (-64.0F * Core.TileScale);
      var5 += 3 * var2;
      var6 += 3 * var2;
    return var5;
   }

    static float XToScreen(float var0, float var1, float var2, int var3) {
    float var4 = 0.0F;
      var4 += var0 * (32 * Core.TileScale);
      return var4 - var1 * (32 * Core.TileScale);
   }

    static float XToScreenInt(int var0, int var1, int var2, int var3) {
    return XToScreen();
   }

    static float YToScreenExact(float var0, float var1, float var2, int var3) {
    float var4 = YToScreen(var0, var1, var2, var3);
      return var4 - IsoCamera.getOffY();
   }

    static float XToScreenExact(float var0, float var1, float var2, int var3) {
    float var4 = XToScreen(var0, var1, var2, var3);
      return var4 - IsoCamera.getOffX();
   }

    static float YToIso(float var0, float var1, float var2) {
    float var3 = var0 + IsoCamera.getOffX();
    float var4 = var1 + IsoCamera.getOffY();
    float var5 = (var3 + 2.0F * var4) / (64.0F * Core.TileScale);
    float var6 = (var3 - 2.0F * var4) / (-64.0F * Core.TileScale);
      var5 += 3.0F * var2;
      return var6 + 3.0F * var2;
   }

    static float YToScreen(float var0, float var1, float var2, int var3) {
    float var4 = 0.0F;
      var4 += var1 * (16 * Core.TileScale);
      var4 += var0 * (16 * Core.TileScale);
      return var4 + (var3 - var2) * (96 * Core.TileScale);
   }

    static float YToScreenInt(int var0, int var1, int var2, int var3) {
    return YToScreen();
   }

    static bool isSimilarDirection(IsoGameCharacter var0, float var1, float var2, float var3, float var4, float var5) {
    Vector2f var6 = std::make_shared<Vector2f>(var1 - var0.x, var2 - var0.y);
      var6.normalize();
    Vector2f var7 = std::make_shared<Vector2f>(var0.x - var3, var0.y - var4);
      var7.normalize();
      var6.push_back(var7);
      return var6.length() < var5;
   }
}
} // namespace iso
} // namespace zombie
