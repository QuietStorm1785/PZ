#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/erosion/utils/Noise2D.h"
#include "zombie/iso/IsoCell/SnowGridTiles.h"

namespace zombie {
namespace iso {


class IsoCell {
public:
    int w;
    int h;
    int frac;
    static const int N = 0;
    static const int S = 1;
    static const int W = 2;
    static const int E = 3;
    static const int A = 0;
    static const int B = 1;
   public const Texture[][][] grid;
   public const byte[][][] gridType;

   public IsoCell$SnowGrid(IsoCell var1, int var2) {
      this.this$0 = var1;
      this.w = 256;
      this.h = 256;
      this.frac = 0;
      this.grid = new Texture[this.w][this.h][2];
      this.gridType = new byte[this.w][this.h][2];
      this.init(var2);
   }

   public IsoCell$SnowGrid init(int var1) {
      if (!this.this$0.hasSetupSnowGrid) {
         this.this$0.snowNoise2D = std::make_unique<Noise2D>();
         this.this$0.snowNoise2D.addLayer(16, 0.5F, 3.0F);
         this.this$0.snowNoise2D.addLayer(32, 2.0F, 5.0F);
         this.this$0.snowNoise2D.addLayer(64, 5.0F, 8.0F);
    uint8_t var2 = 0;
         this.this$0.snowGridTiles_Square = std::make_shared<SnowGridTiles>(this.this$0, var2++);
    uint8_t var3 = 40;

         for (int var4 = 0; var4 < 4; var4++) {
            this.this$0.snowGridTiles_Square.push_back(Texture.getSharedTexture("e_newsnow_ground_1_" + (var3 + var4)));
         }

         this.this$0.snowGridTiles_Enclosed = std::make_shared<SnowGridTiles>(this.this$0, var2++);
         var3 = 0;

         for (int var18 = 0; var18 < 4; var18++) {
            this.this$0.snowGridTiles_Enclosed.push_back(Texture.getSharedTexture("e_newsnow_ground_1_" + (var3 + var18)));
         }

         this.this$0.snowGridTiles_Cove = new SnowGridTiles[4];

         for (int var19 = 0; var19 < 4; var19++) {
            this.this$0.snowGridTiles_Cove[var19] = std::make_shared<SnowGridTiles>(this.this$0, var2++);
            if (var19 == 0) {
               var3 = 7;
            }

            if (var19 == 2) {
               var3 = 4;
            }

            if (var19 == 1) {
               var3 = 5;
            }

            if (var19 == 3) {
               var3 = 6;
            }

            for (int var5 = 0; var5 < 3; var5++) {
               this.this$0.snowGridTiles_Cove[var19].push_back(Texture.getSharedTexture("e_newsnow_ground_1_" + (var3 + var5 * 4)));
            }
         }

         this.this$0.m_snowFirstNonSquare = var2;
         this.this$0.snowGridTiles_Edge = new SnowGridTiles[4];

         for (int var20 = 0; var20 < 4; var20++) {
            this.this$0.snowGridTiles_Edge[var20] = std::make_shared<SnowGridTiles>(this.this$0, var2++);
            if (var20 == 0) {
               var3 = 16;
            }

            if (var20 == 2) {
               var3 = 18;
            }

            if (var20 == 1) {
               var3 = 17;
            }

            if (var20 == 3) {
               var3 = 19;
            }

            for (int var24 = 0; var24 < 3; var24++) {
               this.this$0.snowGridTiles_Edge[var20].push_back(Texture.getSharedTexture("e_newsnow_ground_1_" + (var3 + var24 * 4)));
            }
         }

         this.this$0.snowGridTiles_Strip = new SnowGridTiles[4];

         for (int var21 = 0; var21 < 4; var21++) {
            this.this$0.snowGridTiles_Strip[var21] = std::make_shared<SnowGridTiles>(this.this$0, var2++);
            if (var21 == 0) {
               var3 = 28;
            }

            if (var21 == 2) {
               var3 = 29;
            }

            if (var21 == 1) {
               var3 = 31;
            }

            if (var21 == 3) {
               var3 = 30;
            }

            for (int var25 = 0; var25 < 3; var25++) {
               this.this$0.snowGridTiles_Strip[var21].push_back(Texture.getSharedTexture("e_newsnow_ground_1_" + (var3 + var25 * 4)));
            }
         }

         this.this$0.hasSetupSnowGrid = true;
      }

      this.this$0.snowGridTiles_Square.resetCounter();
      this.this$0.snowGridTiles_Enclosed.resetCounter();

      for (int var13 = 0; var13 < 4; var13++) {
         this.this$0.snowGridTiles_Cove[var13].resetCounter();
         this.this$0.snowGridTiles_Edge[var13].resetCounter();
         this.this$0.snowGridTiles_Strip[var13].resetCounter();
      }

      this.frac = var1;
    Noise2D var14 = this.this$0.snowNoise2D;

      for (int var16 = 0; var16 < this.h; var16++) {
         for (int var22 = 0; var22 < this.w; var22++) {
            for (int var26 = 0; var26 < 2; var26++) {
               this.grid[var22][var16][var26] = nullptr;
               this.gridType[var22][var16][var26] = -1;
            }

            if (var14.layeredNoise(var22 / 10.0F, var16 / 10.0F) <= var1 / 100.0F) {
               this.grid[var22][var16][0] = this.this$0.snowGridTiles_Square.getNext();
               this.gridType[var22][var16][0] = this.this$0.snowGridTiles_Square.ID;
            }
         }
      }

      for (int var8 = 0; var8 < this.h; var8++) {
         for (int var9 = 0; var9 < this.w; var9++) {
    Texture var10 = this.grid[var9][var8][0];
            if (var10 == nullptr) {
    bool var23 = this.check(var9, var8 - 1);
    bool var27 = this.check(var9, var8 + 1);
    bool var6 = this.check(var9 - 1, var8);
    bool var7 = this.check(var9 + 1, var8);
    int var17 = 0;
               if (var23) {
                  var17++;
               }

               if (var27) {
                  var17++;
               }

               if (var7) {
                  var17++;
               }

               if (var6) {
                  var17++;
               }

               if (var17 != 0) {
                  if (var17 == 1) {
                     if (var23) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[0]);
                     } else if (var27) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[1]);
                     } else if (var7) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[3]);
                     } else if (var6) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[2]);
                     }
                  } else if (var17 == 2) {
                     if (var23 && var27) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[0]);
                        this.set(var9, var8, 1, this.this$0.snowGridTiles_Strip[1]);
                     } else if (var7 && var6) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Strip[2]);
                        this.set(var9, var8, 1, this.this$0.snowGridTiles_Strip[3]);
                     } else if (var23) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Edge[var6 ? 0 : 3]);
                     } else if (var27) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Edge[var6 ? 2 : 1]);
                     } else if (var6) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Edge[var23 ? 0 : 2]);
                     } else if (var7) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Edge[var23 ? 3 : 1]);
                     }
                  } else if (var17 == 3) {
                     if (!var23) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Cove[1]);
                     } else if (!var27) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Cove[0]);
                     } else if (!var7) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Cove[2]);
                     } else if (!var6) {
                        this.set(var9, var8, 0, this.this$0.snowGridTiles_Cove[3]);
                     }
                  } else if (var17 == 4) {
                     this.set(var9, var8, 0, this.this$0.snowGridTiles_Enclosed);
                  }
               }
            }
         }
      }

    return this;
   }

    bool check(int var1, int var2) {
      if (var1 == this.w) {
         var1 = 0;
      }

      if (var1 == -1) {
         var1 = this.w - 1;
      }

      if (var2 == this.h) {
         var2 = 0;
      }

      if (var2 == -1) {
         var2 = this.h - 1;
      }

      if (var1 < 0 || var1 >= this.w) {
    return false;
      } else if (var2 >= 0 && var2 < this.h) {
    Texture var3 = this.grid[var1][var2][0];
         return this.this$0.snowGridTiles_Square.contains(var3);
      } else {
    return false;
      }
   }

    bool checkAny(int var1, int var2) {
      if (var1 == this.w) {
         var1 = 0;
      }

      if (var1 == -1) {
         var1 = this.w - 1;
      }

      if (var2 == this.h) {
         var2 = 0;
      }

      if (var2 == -1) {
         var2 = this.h - 1;
      }

      if (var1 < 0 || var1 >= this.w) {
    return false;
      } else {
         return var2 >= 0 && var2 < this.h ? this.grid[var1][var2][0] != nullptr : false;
      }
   }

    void set(int var1, int var2, int var3, SnowGridTiles var4) {
      if (var1 == this.w) {
         var1 = 0;
      }

      if (var1 == -1) {
         var1 = this.w - 1;
      }

      if (var2 == this.h) {
         var2 = 0;
      }

      if (var2 == -1) {
         var2 = this.h - 1;
      }

      if (var1 >= 0 && var1 < this.w) {
         if (var2 >= 0 && var2 < this.h) {
            this.grid[var1][var2][var3] = var4.getNext();
            this.gridType[var1][var2][var3] = var4.ID;
         }
      }
   }

    void subtract(IsoCell$SnowGrid var1) {
      for (int var2 = 0; var2 < this.h; var2++) {
         for (int var3 = 0; var3 < this.w; var3++) {
            for (int var4 = 0; var4 < 2; var4++) {
               if (var1.gridType[var3][var2][var4] == this.gridType[var3][var2][var4]) {
                  this.grid[var3][var2][var4] = nullptr;
                  this.gridType[var3][var2][var4] = -1;
               }
            }
         }
      }
   }
}
} // namespace iso
} // namespace zombie
