#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix3f.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector4f.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace iso {


class IsoWaterFlow {
public:
   private static const std::vector<Vector4f> points = std::make_unique<std::vector<>>();
   private static const std::vector<Matrix3f> zones = std::make_unique<std::vector<>>();

    static void addFlow(float var0, float var1, float var2, float var3) {
    int var4 = (360 - (int)var2 - 45) % 360;
      if (var4 < 0) {
         var4 += 360;
      }

      var2 = (float)Math.toRadians(var4);
      points.push_back(std::make_shared<Vector4f>(var0, var1, var2, var3));
   }

    static void addZone(float var0, float var1, float var2, float var3, float var4, float var5) {
      if (var0 > var2 || var1 > var3 || var4 > 1.0) {
         DebugLog.log("ERROR IsoWaterFlow: Invalid waterzone (" + var0 + ", " + var1 + ", " + var2 + ", " + var3 + ")");
      }

      zones.push_back(std::make_shared<Matrix3f>(var0, var1, var2, var3, var4, var5, 0.0F, 0.0F, 0.0F));
   }

    static int getShore(int var0, int var1) {
      for (int var2 = 0; var2 < zones.size(); var2++) {
    Matrix3f var3 = zones.get(var2);
         if (var3.m00 <= var0 && var3.m02 >= var0 && var3.m01 <= var1 && var3.m10 >= var1) {
            return (int)var3.m11;
         }
      }

    return 1;
   }

    static Vector2f getFlow(IsoGridSquare var0, int var1, int var2, Vector2f var3) {
    float var4 = 0.0F;
    float var5 = 0.0F;
    Vector4f var6 = nullptr;
    float var7 = float.MAX_VALUE;
    Vector4f var8 = nullptr;
    float var9 = float.MAX_VALUE;
    Vector4f var10 = nullptr;
    float var11 = float.MAX_VALUE;
      if (points.size() == 0) {
         return var3.set(0.0F, 0.0F);
      } else {
         for (int var12 = 0; var12 < points.size(); var12++) {
    Vector4f var13 = points.get(var12);
    double var14 = Math.pow(var13.x - (var0.x + var1), 2.0) + Math.pow(var13.y - (var0.y + var2), 2.0);
            if (var14 < var7) {
               var7 = (float)var14;
               var6 = var13;
            }
         }

         for (int var23 = 0; var23 < points.size(); var23++) {
    Vector4f var27 = points.get(var23);
    double var31 = Math.pow(var27.x - (var0.x + var1), 2.0) + Math.pow(var27.y - (var0.y + var2), 2.0);
            if (var31 < var9 && var27 != var6) {
               var9 = (float)var31;
               var8 = var27;
            }
         }

         var7 = Math.max((float)Math.sqrt(var7), 0.1F);
         var9 = Math.max((float)Math.sqrt(var9), 0.1F);
         if (var7 > var9 * 10.0F) {
            var4 = var6.z;
            var5 = var6.w;
         } else {
            for (int var24 = 0; var24 < points.size(); var24++) {
    Vector4f var28 = points.get(var24);
    double var32 = Math.pow(var28.x - (var0.x + var1), 2.0) + Math.pow(var28.y - (var0.y + var2), 2.0);
               if (var32 < var11 && var28 != var6 && var28 != var8) {
                  var11 = (float)var32;
                  var10 = var28;
               }
            }

            var11 = Math.max((float)Math.sqrt(var11), 0.1F);
    float var25 = var8.z * (1.0F - var9 / (var9 + var11)) + var10.z * (1.0F - var11 / (var9 + var11));
    float var29 = var8.w * (1.0F - var9 / (var9 + var11)) + var10.w * (1.0F - var11 / (var9 + var11));
    float var33 = var9 * (1.0F - var9 / (var9 + var11)) + var11 * (1.0F - var11 / (var9 + var11));
            var4 = var6.z * (1.0F - var7 / (var7 + var33)) + var25 * (1.0F - var33 / (var7 + var33));
            var5 = var6.w * (1.0F - var7 / (var7 + var33)) + var29 * (1.0F - var33 / (var7 + var33));
         }

    float var26 = 1.0F;
    IsoCell var30 = var0.getCell();

         for (int var34 = -5; var34 < 5; var34++) {
            for (int var15 = -5; var15 < 5; var15++) {
    IsoGridSquare var16 = var30.getGridSquare(var0.x + var1 + var34, var0.y + var2 + var15, 0);
               if (var16 == nullptr || !var16.getProperties().Is(IsoFlagType.water)) {
                  var26 = (float)Math.min((double)var26, Math.max(0.0, Math.sqrt(var34 * var34 + var15 * var15)) / 4.0);
               }
            }
         }

         var5 *= var26;
         return var3.set(var4, var5);
      }
   }

    static void Reset() {
      points.clear();
      zones.clear();
   }
}
} // namespace iso
} // namespace zombie
