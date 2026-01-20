#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace jarnbjo {
namespace vorbis {

class MdctFloat {
public:
    static const float cPI3_8 = 0.38268343F;
    static const float cPI2_8 = 0.70710677F;
    static const float cPI1_8 = 0.9238795F;
    int n;
    int log2n;
   private float[] trig;
   private int[] bitrev;
   private float[] equalizer;
    float scale;
    int itmp1;
    int itmp2;
    int itmp3;
    int itmp4;
    int itmp5;
    int itmp6;
    int itmp7;
    int itmp8;
    int itmp9;
    float dtmp1;
    float dtmp2;
    float dtmp3;
    float dtmp4;
    float dtmp5;
    float dtmp6;
    float dtmp7;
    float dtmp8;
    float dtmp9;
   private float[] _x = new float[1024];
   private float[] _w = new float[1024];

    protected MdctFloat(int var1) {
      this.bitrev = new int[var1 / 4];
      this.trig = new float[var1 + var1 / 4];
    int var2 = var1 >>> 1;
      this.log2n = (int)Math.rint(Math.log(var1) / Math.log(2.0));
      this.n = var1;
    uint8_t var3 = 0;
    uint8_t var4 = 1;
    int var5 = var3 + var1 / 2;
    int var6 = var5 + 1;
    int var7 = var5 + var1 / 2;
    int var8 = var7 + 1;

      for (int var9 = 0; var9 < var1 / 4; var9++) {
         this.trig[var3 + var9 * 2] = (float)Math.cos(Math.PI / var1 * (4 * var9));
         this.trig[var4 + var9 * 2] = (float)(-Math.sin(Math.PI / var1 * (4 * var9)));
         this.trig[var5 + var9 * 2] = (float)Math.cos(Math.PI / (2 * var1) * (2 * var9 + 1));
         this.trig[var6 + var9 * 2] = (float)Math.sin(Math.PI / (2 * var1) * (2 * var9 + 1));
      }

      for (int var14 = 0; var14 < var1 / 8; var14++) {
         this.trig[var7 + var14 * 2] = (float)Math.cos(Math.PI / var1 * (4 * var14 + 2));
         this.trig[var8 + var14 * 2] = (float)(-Math.sin(Math.PI / var1 * (4 * var14 + 2)));
      }

    int var15 = (1 << this.log2n - 1) - 1;
    int var10 = 1 << this.log2n - 2;

      for (int var11 = 0; var11 < var1 / 8; var11++) {
    int var12 = 0;

         for (int var13 = 0; var10 >>> var13 != 0; var13++) {
            if ((var10 >>> var13 & var11) != 0) {
               var12 |= 1 << var13;
            }
         }

         this.bitrev[var11 * 2] = ~var12 & var15;
         this.bitrev[var11 * 2 + 1] = var12;
      }

      this.scale = 4.0F / var1;
   }

    void setEqualizer(float[] var1) {
      this.equalizer = var1;
   }

   protected float[] getEqualizer() {
      return this.equalizer;
   }

   protected /* synchronized - TODO: add std::mutex */ void imdct(float[] var1, float[] var2, int[] var3) {
      float[] var4 = var1;
      if (this._x.length < this.n / 2) {
         this._x = new float[this.n / 2];
      }

      if (this._w.length < this.n / 2) {
         this._w = new float[this.n / 2];
      }

      float[] var5 = this._x;
      float[] var6 = this._w;
    int var7 = this.n >> 1;
    int var8 = this.n >> 2;
    int var9 = this.n >> 3;
      if (this.equalizer != nullptr) {
         for (int var10 = 0; var10 < this.n; var10++) {
            var1[var10] *= this.equalizer[var10];
         }
      }

    int var20 = -1;
    int var11 = 0;
    int var12 = var7;

      for (int var13 = 0; var13 < var9; var13++) {
    int var21 = var20 + 2;
         this.dtmp1 = var4[var21];
         var20 = var21 + 2;
         this.dtmp2 = var4[var20];
         this.dtmp3 = this.trig[--var12];
         this.dtmp4 = this.trig[--var12];
         var5[var11++] = -this.dtmp2 * this.dtmp3 - this.dtmp1 * this.dtmp4;
         var5[var11++] = this.dtmp1 * this.dtmp3 - this.dtmp2 * this.dtmp4;
      }

      var20 = var7;

      for (int var33 = 0; var33 < var9; var33++) {
    int var23 = var20 - 2;
         this.dtmp1 = var4[var23];
         var20 = var23 - 2;
         this.dtmp2 = var4[var20];
         this.dtmp3 = this.trig[--var12];
         this.dtmp4 = this.trig[--var12];
         var5[var11++] = this.dtmp2 * this.dtmp3 + this.dtmp1 * this.dtmp4;
         var5[var11++] = this.dtmp2 * this.dtmp4 - this.dtmp1 * this.dtmp3;
      }

      float[] var24 = this.kernel(var5, var6, this.n, var7, var8, var9);
      var11 = 0;
      var12 = var7;
    int var34 = var8;
    int var14 = var8 - 1;
    int var15 = var8 + var7;
    int var16 = var15 - 1;

      for (int var17 = 0; var17 < var8; var17++) {
         this.dtmp1 = var24[var11++];
         this.dtmp2 = var24[var11++];
         this.dtmp3 = this.trig[var12++];
         this.dtmp4 = this.trig[var12++];
    float var18 = this.dtmp1 * this.dtmp4 - this.dtmp2 * this.dtmp3;
    float var19 = -(this.dtmp1 * this.dtmp3 + this.dtmp2 * this.dtmp4);
         var3[var34] = (int)(-var18 * var2[var34]);
         var3[var14] = (int)(var18 * var2[var14]);
         var3[var15] = (int)(var19 * var2[var15]);
         var3[var16] = (int)(var19 * var2[var16]);
         var34++;
         var14--;
         var15++;
         var16--;
      }
   }

   private float[] kernel(float[] var1, float[] var2, int var3, int var4, int var5, int var6) {
    int var7 = var5;
    int var8 = 0;
    int var9 = var5;
    int var10 = var4;

      for (int var11 = 0; var11 < var5; var11++) {
    float var12 = var1[var7] - var1[var8];
         var2[var9 + var11] = var1[var7++] + var1[var8++];
    float var13 = var1[var7] - var1[var8];
         var10 -= 4;
         var2[var11++] = var12 * this.trig[var10] + var13 * this.trig[var10 + 1];
         var2[var11] = var13 * this.trig[var10] - var12 * this.trig[var10 + 1];
         var2[var9 + var11] = var1[var7++] + var1[var8++];
      }

      for (int var32 = 0; var32 < this.log2n - 3; var32++) {
    int var35 = var3 >>> var32 + 2;
    int var39 = 1 << var32 + 3;
    int var14 = var4 - 2;
         var10 = 0;

         for (int var16 = 0; var16 < var35 >>> 2; var16++) {
    int var17 = var14;
            var9 = var14 - (var35 >> 1);
    float var18 = this.trig[var10];
    float var20 = this.trig[var10 + 1];
            var14 -= 2;
            var35++;

            for (int var22 = 0; var22 < 2 << var32; var22++) {
               this.dtmp1 = var2[var17];
               this.dtmp2 = var2[var9];
    float var21 = this.dtmp1 - this.dtmp2;
               var1[var17] = this.dtmp1 + this.dtmp2;
               this.dtmp1 = var2[++var17];
               this.dtmp2 = var2[++var9];
    float var19 = this.dtmp1 - this.dtmp2;
               var1[var17] = this.dtmp1 + this.dtmp2;
               var1[var9] = var19 * var18 - var21 * var20;
               var1[var9 - 1] = var21 * var18 + var19 * var20;
               var17 -= var35;
               var9 -= var35;
            }

            var35--;
            var10 += var39;
         }

         float[] var15 = var2;
         var2 = var1;
         var1 = var15;
      }

    int var33 = var3;
    int var37 = 0;
    int var40 = 0;
    int var42 = var4 - 1;

      for (int var44 = 0; var44 < var6; var44++) {
    int var45 = this.bitrev[var37++];
    int var47 = this.bitrev[var37++];
    float var48 = var2[var45] - var2[var47 + 1];
    float var49 = var2[var45 - 1] + var2[var47];
    float var50 = var2[var45] + var2[var47 + 1];
    float var51 = var2[var45 - 1] - var2[var47];
    float var52 = var48 * this.trig[var33];
    float var23 = var49 * this.trig[var33++];
    float var24 = var48 * this.trig[var33];
    float var25 = var49 * this.trig[var33++];
         var1[var40++] = (var50 + var24 + var23) * 16383.0F;
         var1[var42--] = (-var51 + var25 - var52) * 16383.0F;
         var1[var40++] = (var51 + var25 - var52) * 16383.0F;
         var1[var42--] = (var50 - var24 - var23) * 16383.0F;
      }

    return var1;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
