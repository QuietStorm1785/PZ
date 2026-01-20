#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jogg/Buffer.h"
#include "com/jcraft/jorbis/Floor0/EchstateFloor0.h"
#include "com/jcraft/jorbis/Floor0/InfoFloor0.h"
#include "com/jcraft/jorbis/Floor0/LookFloor0.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Floor0 : public FuncFloor {
public:
   float[] lsp = nullptr;

    static float fromdB(float var0) {
      return (float)Math.exp(var0 * 0.11512925);
   }

    static void lpc_to_curve(float[] var0, float[] var1, float var2, LookFloor0 var3, const std::string& var4, int var5) {
      float[] var6 = new float[Math.max(var3.ln * 2, var3.m * 2 + 2)];
      if (var2 == 0.0F) {
         for (int var8 = 0; var8 < var3.n; var8++) {
            var0[var8] = 0.0F;
         }
      } else {
         var3.lpclook.lpc_to_curve(var6, var1, var2);

         for (int var7 = 0; var7 < var3.n; var7++) {
            var0[var7] = var6[var3.linearmap[var7]];
         }
      }
   }

    static void lsp_to_lpc(float[] var0, float[] var1, int var2) {
    int var5 = var2 / 2;
      float[] var6 = new float[var5];
      float[] var7 = new float[var5];
      float[] var9 = new float[var5 + 1];
      float[] var10 = new float[var5 + 1];
      float[] var12 = new float[var5];
      float[] var13 = new float[var5];

      for (int var3 = 0; var3 < var5; var3++) {
         var6[var3] = (float)(-2.0 * Math.cos(var0[var3 * 2]));
         var7[var3] = (float)(-2.0 * Math.cos(var0[var3 * 2 + 1]));
      }

    int var4;
      for (var4 = 0; var4 < var5; var4++) {
         var9[var4] = 0.0F;
         var10[var4] = 1.0F;
         var12[var4] = 0.0F;
         var13[var4] = 1.0F;
      }

      var10[var4] = 1.0F;
      var9[var4] = 1.0F;

      for (int var15 = 1; var15 < var2 + 1; var15++) {
    float var11 = 0.0F;
    float var8 = 0.0F;

         for (var4 = 0; var4 < var5; var4++) {
    float var14 = var6[var4] * var10[var4] + var9[var4];
            var9[var4] = var10[var4];
            var10[var4] = var8;
            var8 += var14;
            var14 = var7[var4] * var13[var4] + var12[var4];
            var12[var4] = var13[var4];
            var13[var4] = var11;
            var11 += var14;
         }

         var1[var15 - 1] = (var8 + var10[var4] + var11 - var9[var4]) / 2.0F;
         var10[var4] = var8;
         var9[var4] = var11;
      }
   }

    static float toBARK(float var0) {
      return (float)(13.1 * Math.atan(7.4E-4 * var0) + 2.24 * Math.atan(var0 * var0 * 1.85E-8) + 1.0E-4 * var0);
   }

    int forward(Block var1, void* var2, float[] var3, float[] var4, void* var5) {
    return 0;
   }

    void free_info(void* var1) {
   }

    void free_look(void* var1) {
   }

    void free_state(void* var1) {
   }

    int inverse(Block var1, void* var2, float[] var3) {
    LookFloor0 var4 = (LookFloor0)var2;
    InfoFloor0 var5 = var4.vi;
    int var6 = var1.opb.read(var5.ampbits);
      if (var6 > 0) {
    int var7 = (1 << var5.ampbits) - 1;
    float var8 = (float)var6 / var7 * var5.ampdB;
    int var9 = var1.opb.read(Util.ilog(var5.numbooks));
         if (var9 != -1 && var9 < var5.numbooks) {
            /* synchronized - TODO: add std::mutex */ (this) {
               if (this.lsp != nullptr && this.lsp.length >= var4.m) {
                  for (int var11 = 0; var11 < var4.m; var11++) {
                     this.lsp[var11] = 0.0F;
                  }
               } else {
                  this.lsp = new float[var4.m];
               }

    CodeBook var17 = var1.vd.fullbooks[var5.books[var9]];
    float var12 = 0.0F;

               for (int var13 = 0; var13 < var4.m; var13++) {
                  var3[var13] = 0.0F;
               }

               for (int var18 = 0; var18 < var4.m; var18 += var17.dim) {
                  if (var17.decodevs(this.lsp, var18, var1.opb, 1, -1) == -1) {
                     for (int var14 = 0; var14 < var4.n; var14++) {
                        var3[var14] = 0.0F;
                     }

    return 0;
                  }
               }

               for (int var19 = 0; var19 < var4.m; var12 = this.lsp[var19 - 1]) {
                  for (int var20 = 0; var20 < var17.dim; var19++) {
                     this.lsp[var19] = this.lsp[var19] + var12;
                     var20++;
                  }
               }

               Lsp.lsp_to_curve(var3, var4.linearmap, var4.n, var4.ln, this.lsp, var4.m, var8, var5.ampdB);
    return 1;
            }
         }
      }

    return 0;
   }

    void* inverse1(Block var1, void* var2, void* var3) {
    LookFloor0 var4 = (LookFloor0)var2;
    InfoFloor0 var5 = var4.vi;
      float[] var6 = nullptr;
      if (dynamic_cast<float*>(var3) != nullptr[]) {
         var6 = (float[])var3;
      }

    int var7 = var1.opb.read(var5.ampbits);
      if (var7 > 0) {
    int var8 = (1 << var5.ampbits) - 1;
    float var9 = (float)var7 / var8 * var5.ampdB;
    int var10 = var1.opb.read(Util.ilog(var5.numbooks));
         if (var10 != -1 && var10 < var5.numbooks) {
    CodeBook var11 = var1.vd.fullbooks[var5.books[var10]];
    float var12 = 0.0F;
            if (var6 != nullptr && var6.length >= var4.m + 1) {
               for (int var13 = 0; var13 < var6.length; var13++) {
                  var6[var13] = 0.0F;
               }
            } else {
               var6 = new float[var4.m + 1];
            }

            for (int var15 = 0; var15 < var4.m; var15 += var11.dim) {
               if (var11.decodev_set(var6, var15, var1.opb, var11.dim) == -1) {
    return nullptr;
               }
            }

            for (int var16 = 0; var16 < var4.m; var12 = var6[var16 - 1]) {
               for (int var14 = 0; var14 < var11.dim; var16++) {
                  var6[var16] += var12;
                  var14++;
               }
            }

            var6[var4.m] = var9;
    return var6;
         }
      }

    return nullptr;
   }

    int inverse2(Block var1, void* var2, void* var3, float[] var4) {
    LookFloor0 var5 = (LookFloor0)var2;
    InfoFloor0 var6 = var5.vi;
      if (var3 != nullptr) {
         float[] var9 = (float[])var3;
    float var8 = var9[var5.m];
         Lsp.lsp_to_curve(var4, var5.linearmap, var5.n, var5.ln, var9, var5.m, var8, var6.ampdB);
    return 1;
      } else {
         for (int var7 = 0; var7 < var5.n; var7++) {
            var4[var7] = 0.0F;
         }

    return 0;
      }
   }

    void* look(DspState var1, InfoMode var2, void* var3) {
    Info var5 = var1.vi;
    InfoFloor0 var6 = (InfoFloor0)var3;
    LookFloor0 var7 = std::make_shared<LookFloor0>(this);
      var7.m = var6.order;
      var7.n = var5.blocksizes[var2.blockflag] / 2;
      var7.ln = var6.barkmap;
      var7.vi = var6;
      var7.lpclook.init(var7.ln, var7.m);
    float var4 = var7.ln / toBARK((float)(var6.rate / 2.0));
      var7.linearmap = new int[var7.n];

      for (int var8 = 0; var8 < var7.n; var8++) {
    int var9 = (int)Math.floor(toBARK((float)(var6.rate / 2.0 / var7.n * var8)) * var4);
         if (var9 >= var7.ln) {
            var9 = var7.ln;
         }

         var7.linearmap[var8] = var9;
      }

    return var7;
   }

    void pack(void* var1, Buffer var2) {
    InfoFloor0 var3 = (InfoFloor0)var1;
      var2.write(var3.order, 8);
      var2.write(var3.rate, 16);
      var2.write(var3.barkmap, 16);
      var2.write(var3.ampbits, 6);
      var2.write(var3.ampdB, 8);
      var2.write(var3.numbooks - 1, 4);

      for (int var4 = 0; var4 < var3.numbooks; var4++) {
         var2.write(var3.books[var4], 8);
      }
   }

    void* state(void* var1) {
    EchstateFloor0 var2 = std::make_shared<EchstateFloor0>(this);
    InfoFloor0 var3 = (InfoFloor0)var1;
      var2.codewords = new int[var3.order];
      var2.curve = new float[var3.barkmap];
      var2.frameno = -1L;
    return var2;
   }

    void* unpack(Info var1, Buffer var2) {
    InfoFloor0 var3 = std::make_shared<InfoFloor0>(this);
      var3.order = var2.read(8);
      var3.rate = var2.read(16);
      var3.barkmap = var2.read(16);
      var3.ampbits = var2.read(6);
      var3.ampdB = var2.read(8);
      var3.numbooks = var2.read(4) + 1;
      if (var3.order >= 1 && var3.rate >= 1 && var3.barkmap >= 1 && var3.numbooks >= 1) {
         for (int var4 = 0; var4 < var3.numbooks; var4++) {
            var3.books[var4] = var2.read(8);
            if (var3.books[var4] < 0 || var3.books[var4] >= var1.books) {
    return nullptr;
            }
         }

    return var3;
      } else {
    return nullptr;
      }
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
