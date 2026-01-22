#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "org/joml/Vector4f.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace iso {


class IsoPuddlesCompute {
public:
    static const float Pi = 3.1415F;
    static float puddlesDirNE;
    static float puddlesDirNW;
    static float puddlesDirAll;
    static float puddlesDirNone;
    static float puddlesSize;
    static bool hd_quality = true;
    static const Vector2f add = std::make_shared<Vector2f>(1.0F, 0.0F);
    static const Vector3f add_xyy = std::make_shared<Vector3f>(1.0F, 0.0F, 0.0F);
    static const Vector3f add_xxy = std::make_shared<Vector3f>(1.0F, 1.0F, 0.0F);
    static const Vector3f add_xxx = std::make_shared<Vector3f>(1.0F, 1.0F, 1.0F);
    static const Vector3f add_xyx = std::make_shared<Vector3f>(1.0F, 0.0F, 1.0F);
    static const Vector3f add_yxy = std::make_shared<Vector3f>(0.0F, 1.0F, 0.0F);
    static const Vector3f add_yyx = std::make_shared<Vector3f>(0.0F, 0.0F, 1.0F);
    static const Vector3f add_yxx = std::make_shared<Vector3f>(0.0F, 1.0F, 1.0F);
    static const Vector3f HashVector31 = std::make_shared<Vector3f>(17.1F, 31.7F, 32.6F);
    static const Vector3f HashVector32 = std::make_shared<Vector3f>(29.5F, 13.3F, 42.6F);
   private static const ObjectPool<Vector3f> pool_vector3f = std::make_shared<ObjectPool>(Vector3f::new);
   private static const std::vector<Vector3f> allocated_vector3f = std::make_unique<std::vector<>>();
    static const Vector2f temp_vector2f = std::make_shared<Vector2f>();

    static Vector3f allocVector3f(float var0, float var1, float var2) {
    Vector3f var3 = ((Vector3f)pool_vector3f.alloc()).set(var0, var1, var2);
      allocated_vector3f.push_back(var3);
    return var3;
   }

    static Vector3f allocVector3f(Vector3f var0) {
    return allocVector3f();
   }

    static Vector3f floor(Vector3f var0) {
    return allocVector3f();
   }

    static Vector3f fract(Vector3f var0) {
    return allocVector3f();
   }

    static float fract(float var0) {
      return (float)(var0 - Math.floor(var0));
   }

    static float mix(float var0, float var1, float var2) {
      return var0 * (1.0F - var2) + var1 * var2;
   }

    static float FuncHash(Vector3f var0) {
    Vector3f var1 = allocVector3f(var0.dot(HashVector31), var0.dot(HashVector32), 0.0F);
    return fract();
   }

    static float FuncNoise(Vector3f var0) {
    Vector3f var1 = floor(var0);
    Vector3f var2 = fract(var0);
      Vector3f var3 = allocVector3f(
         var2.x * var2.x * (4.5F - 3.5F * var2.x), var2.y * var2.y * (4.5F - 3.5F * var2.y), var2.z * var2.z * (4.5F - 3.5F * var2.z)
      );
    float var4 = mix(FuncHash(var1), FuncHash(allocVector3f(var1).push_back(add_xyy)), var3.x);
    float var5 = mix(FuncHash(allocVector3f(var1).push_back(add_yxy)), FuncHash(allocVector3f(var1).push_back(add_xxy)), var3.x);
    float var6 = mix(FuncHash(allocVector3f(var1).push_back(add_yyx)), FuncHash(allocVector3f(var1).push_back(add_xyx)), var3.x);
    float var7 = mix(FuncHash(allocVector3f(var1).push_back(add_yxx)), FuncHash(allocVector3f(var1).push_back(add_xxx)), var3.x);
    float var8 = mix(var4, var5, var3.y);
    float var9 = mix(var6, var7, var3.y);
    return mix();
   }

    static float PerlinNoise(Vector3f var0) {
      if (hd_quality) {
         var0.mul(0.5F);
    float var1 = 0.5F * FuncNoise(var0);
         var0.mul(3.0F);
         var1 = (float)(var1 + 0.25 * FuncNoise(var0));
         var0.mul(3.0F);
         var1 = (float)(var1 + 0.125 * FuncNoise(var0));
         return (float)(var1 * Math.min(1.0, 2.0 * FuncNoise(allocVector3f(var0).mul(0.02F)) * Math.min(1.0, 1.0 * FuncNoise(allocVector3f(var0).mul(0.1F)))));
      } else {
    return FuncNoise();
      }
   }

    static float getPuddles(Vector2f var0) {
    float var1 = puddlesDirNE;
    float var2 = puddlesDirNW;
    float var3 = puddlesDirAll;
      var0.mul(10.0F);
    float var4 = 1.02F * puddlesSize;
      var4 = (float)(var4 + var1 * Math.sin((var0.x * 1.0 + var0.y * 2.0) * 3.1415F * 1.0) * Math.cos((var0.x * 1.0 + var0.y * 2.0) * 3.1415F * 1.0) * 2.0);
      var4 = (float)(var4 + var2 * Math.sin((var0.x * 1.0 - var0.y * 2.0) * 3.1415F * 1.0) * Math.cos((var0.x * 1.0 - var0.y * 2.0) * 3.1415F * 1.0) * 2.0);
      var4 = (float)(var4 + var3 * 0.3);
    float var5 = PerlinNoise(allocVector3f(var0.x * 1.0F, 0.0F, var0.y * 2.0F));
    float var6 = Math.min(0.7F, var4 * var5);
      var5 = Math.min(0.7F, PerlinNoise(allocVector3f(var0.x * 0.7F, 1.0F, var0.y * 0.7F)));
      return var6 + var5;
   }

    static float computePuddle(IsoGridSquare var0) {
      pool_vector3f.release(allocated_vector3f);
      allocated_vector3f.clear();
      hd_quality = PerformanceSettings.PuddlesQuality == 0;
      if (!Core.getInstance().getUseShaders()) {
         return -0.1F;
      } else if (Core.getInstance().getPerfPuddlesOnLoad() == 3 || Core.getInstance().getPerfPuddles() == 3) {
         return -0.1F;
      } else if (Core.getInstance().getPerfPuddles() > 0 && var0.z > 0) {
         return -0.1F;
      } else {
    IsoPuddles var1 = IsoPuddles.getInstance();
         puddlesSize = var1.getPuddlesSize();
         if (puddlesSize <= 0.0F) {
            return -0.1F;
         } else {
    Vector4f var2 = var1.getShaderOffsetMain();
            var2.x -= 90000.0F;
            var2.y -= 640000.0F;
    int var3 = (int)IsoCamera.frameState.OffX;
    int var4 = (int)IsoCamera.frameState.OffY;
    float var5 = IsoUtils.XToScreen(var0.x + 0.5F - var0.z * 3.0F, var0.y + 0.5F - var0.z * 3.0F, 0.0F, 0) - var3;
    float var6 = IsoUtils.YToScreen(var0.x + 0.5F - var0.z * 3.0F, var0.y + 0.5F - var0.z * 3.0F, 0.0F, 0) - var4;
            var5 /= IsoCamera.frameState.OffscreenWidth;
            var6 /= IsoCamera.frameState.OffscreenHeight;
            if (Core.getInstance().getPerfPuddles() <= 1) {
               var0.getPuddles().recalcIfNeeded();
               puddlesDirNE = (var0.getPuddles().pdne[0] + var0.getPuddles().pdne[2]) * 0.5F;
               puddlesDirNW = (var0.getPuddles().pdnw[0] + var0.getPuddles().pdnw[2]) * 0.5F;
               puddlesDirAll = (var0.getPuddles().pda[0] + var0.getPuddles().pda[2]) * 0.5F;
               puddlesDirNone = (var0.getPuddles().pnon[0] + var0.getPuddles().pnon[2]) * 0.5F;
            } else {
               puddlesDirNE = 0.0F;
               puddlesDirNW = 0.0F;
               puddlesDirAll = 1.0F;
               puddlesDirNone = 0.0F;
            }

    Vector2f var9 = temp_vector2f.set((var5 * var2.z + var2.x) * 8.0E-4F + var0.z * 7.0F, (var6 * var2.w + var2.y) * 8.0E-4F + var0.z * 7.0F);
    float var10 = (float)Math.pow(getPuddles(var9), 2.0);
    float var11 = (float)Math.min(Math.pow(var10, 0.3), 1.0) + var10;
            return var11 * puddlesSize - 0.34F;
         }
      }
   }
}
} // namespace iso
} // namespace zombie
