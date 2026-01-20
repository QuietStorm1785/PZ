#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/season/ErosionIceQueen/Sprite.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"

namespace zombie {
namespace erosion {
namespace season {


class ErosionIceQueen {
public:
    static ErosionIceQueen instance;
   private const std::vector<Sprite> sprites = std::make_unique<std::vector<>>();
    const IsoSpriteManager SprMngr;
    bool snowState;

    void addSprite(const std::string& var1, const std::string& var2) {
    IsoSprite var3 = this.SprMngr.getSprite(var1);
    IsoSprite var4 = this.SprMngr.getSprite(var2);
      if (var3 != nullptr && var4 != nullptr) {
         var3.setName(var1);
         this.sprites.push_back(std::make_shared<Sprite>(var3, var1, var2));
      }
   }

    void setSnow(bool var1) {
      if (this.snowState != var1) {
         this.snowState = var1;

         for (int var2 = 0; var2 < this.sprites.size(); var2++) {
    Sprite var3 = this.sprites.get(var2);
            var3.sprite.ReplaceCurrentAnimFrames(this.snowState ? var3.winter : var3.normal);
         }
      }
   }

    public ErosionIceQueen(IsoSpriteManager var1) {
      instance = this;
      this.SprMngr = var1;
      this.setRoofSnow();

      for (int var2 = 0; var2 < 10; var2++) {
         this.addSprite("vegetation_ornamental_01_" + var2, "f_bushes_2_" + (var2 + 10));
         this.addSprite("f_bushes_2_" + var2, "f_bushes_2_" + (var2 + 10));
      }
   }

    void setRoofSnowA() {
      for (int var1 = 0; var1 < 128; var1++) {
    std::string var2 = "e_roof_snow_1_" + var1;

         for (int var3 = 1; var3 <= 5; var3++) {
    std::string var4 = "roofs_0" + var3 + "_" + var1;
            this.addSprite(var4, var2);
         }
      }
   }

    void setRoofSnow() {
      for (int var1 = 1; var1 <= 5; var1++) {
         for (int var2 = 0; var2 < 128; var2++) {
    int var3 = var2;
            switch (var1) {
               case 1:
                  if (var2 >= 72 && var2 <= 79) {
                     var3 = var2 - 8;
                  }

                  if (var2 == 112 || var2 == 114) {
                     var3 = 0;
                  }

                  if (var2 == 113 || var2 == 115) {
                     var3 = 1;
                  }

                  if (var2 == 116 || var2 == 118) {
                     var3 = 4;
                  }

                  if (var2 == 117 || var2 == 119) {
                     var3 = 5;
                  }
                  break;
               case 2:
                  if (var2 == 50) {
                     var3 = 106;
                  }

                  if (var2 == 51) {
                     var3 = 107;
                  }

                  if (var2 >= 72 && var2 <= 79) {
                     var3 = var2 - 8;
                  }

                  if (var2 == 104 || var2 == 106) {
                     var3 = 0;
                  }

                  if (var2 == 105 || var2 == 107) {
                     var3 = 1;
                  }

                  if (var2 == 108 || var2 == 110) {
                     var3 = 4;
                  }

                  if (var2 == 109 || var2 == 111) {
                     var3 = 5;
                  }
                  break;
               case 3:
                  if (var2 == 72 || var2 == 74) {
                     var3 = 0;
                  }

                  if (var2 == 73 || var2 == 75) {
                     var3 = 1;
                  }

                  if (var2 == 76 || var2 == 78) {
                     var3 = 4;
                  }

                  if (var2 == 77 || var2 == 79) {
                     var3 = 5;
                  }

                  if (var2 == 102) {
                     var3 = 70;
                  }

                  if (var2 == 103) {
                     var3 = 71;
                  }

                  if (var2 == 104 || var2 == 106) {
                     var3 = 0;
                  }

                  if (var2 == 105 || var2 == 107) {
                     var3 = 1;
                  }

                  if (var2 == 108 || var2 == 110) {
                     var3 = 4;
                  }

                  if (var2 == 109 || var2 == 111) {
                     var3 = 5;
                  }

                  if (var2 >= 120 && var2 <= 127) {
                     var3 = var2 - 16;
                  }
                  break;
               case 4:
                  if (var2 == 48) {
                     var3 = 106;
                  }

                  if (var2 == 49) {
                     var3 = 107;
                  }

                  if (var2 == 50) {
                     var3 = 108;
                  }

                  if (var2 == 51) {
                     var3 = 109;
                  }

                  if (var2 == 72 || var2 == 74) {
                     var3 = 0;
                  }

                  if (var2 == 73 || var2 == 75) {
                     var3 = 1;
                  }

                  if (var2 == 76 || var2 == 78) {
                     var3 = 4;
                  }

                  if (var2 == 77 || var2 == 79) {
                     var3 = 5;
                  }

                  if (var2 == 102) {
                     var3 = 70;
                  }

                  if (var2 == 103) {
                     var3 = 71;
                  }

                  if (var2 == 104 || var2 == 106) {
                     var3 = 0;
                  }

                  if (var2 == 105 || var2 == 107) {
                     var3 = 1;
                  }

                  if (var2 == 108 || var2 == 110) {
                     var3 = 4;
                  }

                  if (var2 == 109 || var2 == 111) {
                     var3 = 5;
                  }
                  break;
               case 5:
                  if (var2 >= 72 && var2 <= 79) {
                     var3 = var2 - 8;
                  }

                  if (var2 == 104 || var2 == 106) {
                     var3 = 0;
                  }

                  if (var2 == 105 || var2 == 107) {
                     var3 = 1;
                  }

                  if (var2 == 108 || var2 == 110) {
                     var3 = 4;
                  }

                  if (var2 == 109 || var2 == 111) {
                     var3 = 5;
                  }

                  if (var2 >= 112 && var2 <= 119) {
                     var3 = var2 - 32;
                  }
            }

    std::string var4 = "roofs_0" + var1 + "_" + var2;
    std::string var5 = "e_roof_snow_1_" + var3;
            this.addSprite(var4, var5);
         }
      }

    uint8_t var6 = 5;

      for (int var7 = 128; var7 < 176; var7++) {
    int var8;
         if (var7 == 136 || var7 == 138) {
            var8 = 0;
         } else if (var7 == 137 || var7 == 139) {
            var8 = 1;
         } else if (var7 == 140 || var7 == 142) {
            var8 = 4;
         } else if (var7 != 141 && var7 != 143) {
            if (var7 < 128 || var7 > 135) {
               continue;
            }

            var8 = var7 - 128 + 96;
         } else {
            var8 = 5;
         }

    std::string var9 = "roofs_0" + var6 + "_" + var7;
    std::string var10 = "e_roof_snow_1_" + var8;
         this.addSprite(var9, var10);
      }
   }

    void setRoofSnowOneX() {
      for (int var1 = 1; var1 <= 5; var1++) {
         for (int var2 = 0; var2 < 128; var2++) {
    int var3 = var2;
            switch (var1) {
               case 1:
                  if (var2 >= 96 && var2 <= 98) {
                     var3 = var2 - 16;
                  }

                  if (var2 == 99) {
                     var3 = var2 - 19;
                  }

                  if (var2 == 100) {
                     var3 = var2 - 13;
                  }

                  if (var2 >= 101 && var2 <= 103) {
                     var3 = var2 - 16;
                  }

                  if (var2 >= 112 && var2 <= 113) {
                     var3 = var2 - 112;
                  }

                  if (var2 >= 114 && var2 <= 115) {
                     var3 = var2 - 114;
                  }

                  if (var2 == 116 || var2 == 118) {
                     var3 = 5;
                  }

                  if (var2 == 117 || var2 == 119) {
                     var3 = 4;
                  }
                  break;
               case 2:
                  if (var2 >= 96 && var2 <= 98) {
                     var3 = var2 - 16;
                  }

                  if (var2 == 99) {
                     var3 = var2 - 19;
                  }

                  if (var2 == 100) {
                     var3 = var2 - 13;
                  }

                  if (var2 >= 101 && var2 <= 103) {
                     var3 = var2 - 16;
                  }

                  if (var2 >= 104 && var2 <= 105) {
                     var3 = var2 - 104;
                  }

                  if (var2 >= 106 && var2 <= 107) {
                     var3 = var2 - 106;
                  }

                  if (var2 >= 108 && var2 <= 109) {
                     var3 = var2 - 104;
                  }

                  if (var2 >= 110 && var2 <= 111) {
                     var3 = var2 - 106;
                  }
                  break;
               case 3:
                  if (var2 >= 18 && var2 <= 19) {
                     var3 = var2 - 12;
                  }

                  if (var2 >= 50 && var2 <= 51) {
                     var3 = var2 - 44;
                  }

                  if (var2 >= 72 && var2 <= 73) {
                     var3 = var2 - 72;
                  }

                  if (var2 >= 74 && var2 <= 75) {
                     var3 = var2 - 74;
                  }

                  if (var2 >= 76 && var2 <= 77) {
                     var3 = var2 - 72;
                  }

                  if (var2 >= 78 && var2 <= 79) {
                     var3 = var2 - 74;
                  }

                  if (var2 >= 102 && var2 <= 103) {
                     var3 = var2 - 88;
                  }

                  if (var2 >= 122 && var2 <= 125) {
                     var3 = var2 - 16;
                  }
                  break;
               case 4:
                  if (var2 >= 18 && var2 <= 19) {
                     var3 = var2 - 12;
                  }
                  break;
               case 5:
                  if (var2 >= 72 && var2 <= 74) {
                     var3 = var2 + 8;
                  }

                  if (var2 == 75) {
                     var3 = var2 + 7;
                  }

                  if (var2 == 76) {
                     var3 = var2 + 11;
                  }

                  if (var2 >= 77 && var2 <= 79) {
                     var3 = var2 + 8;
                  }

                  if (var2 >= 112 && var2 <= 113) {
                     var3 = var2 - 112;
                  }

                  if (var2 >= 114 && var2 <= 115) {
                     var3 = var2 - 114;
                  }

                  if (var2 == 116 || var2 == 118) {
                     var3 = 5;
                  }

                  if (var2 == 117 || var2 == 119) {
                     var3 = 4;
                  }
            }

    std::string var4 = "roofs_0" + var1 + "_" + var2;
    std::string var5 = "e_roof_snow_1_" + var3;
            this.addSprite(var4, var5);
         }
      }
   }

    static void Reset() {
      if (instance != nullptr) {
         instance.sprites.clear();
         instance = nullptr;
      }
   }
}
} // namespace season
} // namespace erosion
} // namespace zombie
