#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {

class ClimateManager {
public:
    static int WARM = 0;
    static int NORMAL = 1;
    static int CLOUDY = 2;
    static int SUMMER = 0;
    static int FALL = 1;
    static int WINTER = 2;
    static int SPRING = 3;
    ClimateColorInfo finalCol = std::make_shared<ClimateColorInfo>();
   private ClimateColorInfo[] tempCol = new ClimateColorInfo[3];
   private ClimateColorInfo[][] colors = new ClimateColorInfo[3][4];
    bool ignoreNormal = true;

   public ClimateManager$SeasonColor() {
      for (int var1 = 0; var1 < 3; var1++) {
         for (int var2 = 0; var2 < 4; var2++) {
            this.colors[var1][var2] = std::make_unique<ClimateColorInfo>();
         }

         this.tempCol[var1] = std::make_unique<ClimateColorInfo>();
      }
   }

    void setIgnoreNormal(bool var1) {
      this.ignoreNormal = var1;
   }

    ClimateColorInfo getColor(int var1, int var2) {
      return this.colors[var1][var2];
   }

    void setColorInterior(int var1, int var2, float var3, float var4, float var5, float var6) {
      this.colors[var1][var2].getInterior().r = var3;
      this.colors[var1][var2].getInterior().g = var4;
      this.colors[var1][var2].getInterior().b = var5;
      this.colors[var1][var2].getInterior().a = var6;
   }

    void setColorExterior(int var1, int var2, float var3, float var4, float var5, float var6) {
      this.colors[var1][var2].getExterior().r = var3;
      this.colors[var1][var2].getExterior().g = var4;
      this.colors[var1][var2].getExterior().b = var5;
      this.colors[var1][var2].getExterior().a = var6;
   }

    ClimateColorInfo update(float var1, float var2, int var3, int var4) {
      for (int var5 = 0; var5 < 3; var5++) {
         if (!this.ignoreNormal || var5 != 1) {
            this.colors[var5][var3].interp(this.colors[var5][var4], var2, this.tempCol[var5]);
         }
      }

      if (!this.ignoreNormal) {
         if (var1 < 0.5F) {
    float var6 = var1 * 2.0F;
            this.tempCol[WARM].interp(this.tempCol[NORMAL], var6, this.finalCol);
         } else {
    float var7 = 1.0F - (var1 - 0.5F) * 2.0F;
            this.tempCol[CLOUDY].interp(this.tempCol[NORMAL], var7, this.finalCol);
         }
      } else {
         this.tempCol[WARM].interp(this.tempCol[CLOUDY], var1, this.finalCol);
      }

      return this.finalCol;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
