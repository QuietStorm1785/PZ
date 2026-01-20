#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/iso/IsoGridSquare/PuddlesDirection.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace iso {


class IsoPuddlesGeometry {
public:
   const float[] x = new float[4];
   const float[] y = new float[4];
   const float[] pdne = new float[4];
   const float[] pdnw = new float[4];
   const float[] pda = new float[4];
   const float[] pnon = new float[4];
   const int[] color = new int[4];
    IsoGridSquare square = nullptr;
    bool bRecalc = true;
    bool interiorCalc = false;
   public static const ObjectPool<IsoPuddlesGeometry> pool = std::make_shared<ObjectPool>(IsoPuddlesGeometry::new);

    IsoPuddlesGeometry init(IsoGridSquare var1) {
      this.interiorCalc = false;
      this.x[0] = IsoUtils.XToScreen(var1.x - var1.z * 3, var1.y - var1.z * 3, var1.z, var1.z);
      this.y[0] = IsoUtils.YToScreen(var1.x - var1.z * 3, var1.y - var1.z * 3, var1.z, var1.z);
      this.x[1] = IsoUtils.XToScreen(var1.x - var1.z * 3, var1.y - var1.z * 3 + 1, 0.0F, 0);
      this.y[1] = IsoUtils.YToScreen(var1.x - var1.z * 3, var1.y - var1.z * 3 + 1, 0.0F, 0);
      this.x[2] = IsoUtils.XToScreen(var1.x - var1.z * 3 + 1, var1.y - var1.z * 3 + 1, 0.0F, 0);
      this.y[2] = IsoUtils.YToScreen(var1.x - var1.z * 3 + 1, var1.y - var1.z * 3 + 1, 0.0F, 0);
      this.x[3] = IsoUtils.XToScreen(var1.x - var1.z * 3 + 1, var1.y - var1.z * 3, 0.0F, 0);
      this.y[3] = IsoUtils.YToScreen(var1.x - var1.z * 3 + 1, var1.y - var1.z * 3, 0.0F, 0);
      this.square = var1;
      if (!var1.getProperties().Is(IsoFlagType.water) && var1.getProperties().Is(IsoFlagType.exterior)) {
         for (int var11 = 0; var11 < 4; var11++) {
            this.pdne[var11] = 0.0F;
            this.pdnw[var11] = 0.0F;
            this.pda[var11] = 1.0F;
            this.pnon[var11] = 0.0F;
         }

         if (Core.getInstance().getPerfPuddles() > 1) {
    return this;
         } else {
    IsoCell var12 = var1.getCell();
    IsoGridSquare var3 = var12.getGridSquare(var1.x - 1, var1.y, var1.z);
    IsoGridSquare var4 = var12.getGridSquare(var1.x - 1, var1.y - 1, var1.z);
    IsoGridSquare var5 = var12.getGridSquare(var1.x, var1.y - 1, var1.z);
    IsoGridSquare var6 = var12.getGridSquare(var1.x - 1, var1.y + 1, var1.z);
    IsoGridSquare var7 = var12.getGridSquare(var1.x, var1.y + 1, var1.z);
    IsoGridSquare var8 = var12.getGridSquare(var1.x + 1, var1.y + 1, var1.z);
    IsoGridSquare var9 = var12.getGridSquare(var1.x + 1, var1.y, var1.z);
    IsoGridSquare var10 = var12.getGridSquare(var1.x + 1, var1.y - 1, var1.z);
            if (var5 != nullptr && var4 != nullptr && var3 != nullptr && var6 != nullptr && var7 != nullptr && var8 != nullptr && var9 != nullptr && var10 != nullptr) {
               this.setFlags(0, var3.getPuddlesDir() | var4.getPuddlesDir() | var5.getPuddlesDir());
               this.setFlags(1, var3.getPuddlesDir() | var6.getPuddlesDir() | var7.getPuddlesDir());
               this.setFlags(2, var7.getPuddlesDir() | var8.getPuddlesDir() | var9.getPuddlesDir());
               this.setFlags(3, var9.getPuddlesDir() | var10.getPuddlesDir() | var5.getPuddlesDir());
    return this;
            } else {
    return this;
            }
         }
      } else {
         for (int var2 = 0; var2 < 4; var2++) {
            this.pdne[var2] = 0.0F;
            this.pdnw[var2] = 0.0F;
            this.pda[var2] = 0.0F;
            this.pnon[var2] = 0.0F;
         }

    return this;
      }
   }

    void setFlags(int var1, int var2) {
      this.pdne[var1] = 0.0F;
      this.pdnw[var1] = 0.0F;
      this.pda[var1] = 0.0F;
      this.pnon[var1] = 0.0F;
      if ((var2 & PuddlesDirection.PUDDLES_DIR_NE) != 0) {
         this.pdne[var1] = 1.0F;
      }

      if ((var2 & PuddlesDirection.PUDDLES_DIR_NW) != 0) {
         this.pdnw[var1] = 1.0F;
      }

      if ((var2 & PuddlesDirection.PUDDLES_DIR_ALL) != 0) {
         this.pda[var1] = 1.0F;
      }
   }

    void recalcIfNeeded() {
      if (this.bRecalc) {
         this.bRecalc = false;

         try {
            this.init(this.square);
         } catch (Throwable var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

    bool shouldRender() {
      this.recalcIfNeeded();

      for (int var1 = 0; var1 < 4; var1++) {
         if (this.pdne[var1] + this.pdnw[var1] + this.pda[var1] + this.pnon[var1] > 0.0F) {
    return true;
         }
      }

      if (this.square.getProperties().Is(IsoFlagType.water)) {
    return false;
      } else {
         if (IsoPuddles.leakingPuddlesInTheRoom && !this.interiorCalc && this.square != nullptr) {
            for (int var10 = 0; var10 < 4; var10++) {
               this.pdne[var10] = 0.0F;
               this.pdnw[var10] = 0.0F;
               this.pda[var10] = 0.0F;
               this.pnon[var10] = 1.0F;
            }

    IsoGridSquare var11 = this.square.getAdjacentSquare(IsoDirections.W);
    IsoGridSquare var2 = this.square.getAdjacentSquare(IsoDirections.NW);
    IsoGridSquare var3 = this.square.getAdjacentSquare(IsoDirections.N);
    IsoGridSquare var4 = this.square.getAdjacentSquare(IsoDirections.SW);
    IsoGridSquare var5 = this.square.getAdjacentSquare(IsoDirections.S);
    IsoGridSquare var6 = this.square.getAdjacentSquare(IsoDirections.SE);
    IsoGridSquare var7 = this.square.getAdjacentSquare(IsoDirections.E);
    IsoGridSquare var8 = this.square.getAdjacentSquare(IsoDirections.NE);
            if (var11 == nullptr
               || var3 == nullptr
               || var5 == nullptr
               || var7 == nullptr
               || var2 == nullptr
               || var8 == nullptr
               || var4 == nullptr
               || var6 == nullptr
               || !var11.getProperties().Is(IsoFlagType.exterior)
                  && !var3.getProperties().Is(IsoFlagType.exterior)
                  && !var5.getProperties().Is(IsoFlagType.exterior)
                  && !var7.getProperties().Is(IsoFlagType.exterior)) {
    return false;
            }

            if (!this.square.getProperties().Is(IsoFlagType.collideW) && var11.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[0] = 0.0F;
               this.pnon[1] = 0.0F;

               for (int var9 = 0; var9 < 4; var9++) {
                  this.pda[var9] = 1.0F;
               }
            }

            if (!var5.getProperties().Is(IsoFlagType.collideN) && var5.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[1] = 0.0F;
               this.pnon[2] = 0.0F;

               for (int var12 = 0; var12 < 4; var12++) {
                  this.pda[var12] = 1.0F;
               }
            }

            if (!var7.getProperties().Is(IsoFlagType.collideW) && var7.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[2] = 0.0F;
               this.pnon[3] = 0.0F;

               for (int var13 = 0; var13 < 4; var13++) {
                  this.pda[var13] = 1.0F;
               }
            }

            if (!this.square.getProperties().Is(IsoFlagType.collideN) && var3.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[3] = 0.0F;
               this.pnon[0] = 0.0F;

               for (int var14 = 0; var14 < 4; var14++) {
                  this.pda[var14] = 1.0F;
               }
            }

            if (var3.getProperties().Is(IsoFlagType.collideW) || !var2.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[0] = 1.0F;

               for (int var15 = 0; var15 < 4; var15++) {
                  this.pda[var15] = 1.0F;
               }
            }

            if (var5.getProperties().Is(IsoFlagType.collideW) || !var4.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[1] = 1.0F;

               for (int var16 = 0; var16 < 4; var16++) {
                  this.pda[var16] = 1.0F;
               }
            }

            if (var4.getProperties().Is(IsoFlagType.collideN) || !var4.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[1] = 1.0F;

               for (int var17 = 0; var17 < 4; var17++) {
                  this.pda[var17] = 1.0F;
               }
            }

            if (var6.getProperties().Is(IsoFlagType.collideN) || !var6.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[2] = 1.0F;

               for (int var18 = 0; var18 < 4; var18++) {
                  this.pda[var18] = 1.0F;
               }
            }

            if (var6.getProperties().Is(IsoFlagType.collideW) || !var6.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[2] = 1.0F;

               for (int var19 = 0; var19 < 4; var19++) {
                  this.pda[var19] = 1.0F;
               }
            }

            if (var8.getProperties().Is(IsoFlagType.collideW) || !var8.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[3] = 1.0F;

               for (int var20 = 0; var20 < 4; var20++) {
                  this.pda[var20] = 1.0F;
               }
            }

            if (var7.getProperties().Is(IsoFlagType.collideN) || !var8.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[3] = 1.0F;

               for (int var21 = 0; var21 < 4; var21++) {
                  this.pda[var21] = 1.0F;
               }
            }

            if (var11.getProperties().Is(IsoFlagType.collideN) || !var2.getProperties().Is(IsoFlagType.exterior)) {
               this.pnon[0] = 1.0F;

               for (int var22 = 0; var22 < 4; var22++) {
                  this.pda[var22] = 1.0F;
               }
            }

            this.interiorCalc = true;

            for (int var23 = 0; var23 < 4; var23++) {
               if (this.pdne[var23] + this.pdnw[var23] + this.pda[var23] + this.pnon[var23] > 0.0F) {
    return true;
               }
            }
         }

    return false;
      }
   }

    void updateLighting(int var1) {
      this.setLightingAtVert(0, this.square.getVertLight(0, var1));
      this.setLightingAtVert(1, this.square.getVertLight(3, var1));
      this.setLightingAtVert(2, this.square.getVertLight(2, var1));
      this.setLightingAtVert(3, this.square.getVertLight(1, var1));
   }

    void setLightingAtVert(int var1, int var2) {
      this.color[var1] = var2;
   }
}
} // namespace iso
} // namespace zombie
