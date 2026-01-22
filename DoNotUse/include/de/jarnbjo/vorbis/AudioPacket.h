#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class AudioPacket {
public:
    int modeNumber;
    Mode mode;
    Mapping mapping;
    int n;
    bool blockFlag;
    bool previousWindowFlag;
    bool nextWindowFlag;
    int windowCenter;
    int leftWindowStart;
    int leftWindowEnd;
    int leftN;
    int rightWindowStart;
    int rightWindowEnd;
    int rightN;
   private float[] window;
   private float[][] pcm;
   private int[][] pcmInt;
   private Floor[] channelFloors;
   private boolean[] noResidues;
   private static const float[][] windows = new float[8][];

    protected AudioPacket(VorbisStream var1, BitInputStream var2) {
    SetupHeader var3 = var1.getSetupHeader();
    IdentificationHeader var4 = var1.getIdentificationHeader();
      Mode[] var5 = var3.getModes();
      Mapping[] var6 = var3.getMappings();
      Residue[] var7 = var3.getResidues();
    int var8 = var4.getChannels();
      if (var2.getInt(1) != 0) {
         throw VorbisFormatException("Packet type mismatch when trying to create an audio packet.");
      } else {
         this.modeNumber = var2.getInt(Util.ilog(var5.length - 1));

         try {
            this.mode = var5[this.modeNumber];
         } catch (ArrayIndexOutOfBoundsException var25) {
            throw VorbisFormatException("Reference to invalid mode in audio packet.");
         }

         this.mapping = var6[this.mode.getMapping()];
         int[] var9 = this.mapping.getMagnitudes();
         int[] var10 = this.mapping.getAngles();
         this.blockFlag = this.mode.getBlockFlag();
    int var11 = var4.getBlockSize0();
    int var12 = var4.getBlockSize1();
         this.n = this.blockFlag ? var12 : var11;
         if (this.blockFlag) {
            this.previousWindowFlag = var2.getBit();
            this.nextWindowFlag = var2.getBit();
         }

         this.windowCenter = this.n / 2;
         if (this.blockFlag && !this.previousWindowFlag) {
            this.leftWindowStart = this.n / 4 - var11 / 4;
            this.leftWindowEnd = this.n / 4 + var11 / 4;
            this.leftN = var11 / 2;
         } else {
            this.leftWindowStart = 0;
            this.leftWindowEnd = this.n / 2;
            this.leftN = this.windowCenter;
         }

         if (this.blockFlag && !this.nextWindowFlag) {
            this.rightWindowStart = this.n * 3 / 4 - var11 / 4;
            this.rightWindowEnd = this.n * 3 / 4 + var11 / 4;
            this.rightN = var11 / 2;
         } else {
            this.rightWindowStart = this.windowCenter;
            this.rightWindowEnd = this.n;
            this.rightN = this.n / 2;
         }

         this.window = this.getComputedWindow();
         this.channelFloors = new Floor[var8];
         this.noResidues = new boolean[var8];
         this.pcm = new float[var8][this.n];
         this.pcmInt = new int[var8][this.n];
    bool var13 = true;

         for (int var14 = 0; var14 < var8; var14++) {
    int var15 = this.mapping.getMux()[var14];
    int var16 = this.mapping.getSubmapFloors()[var15];
    Floor var17 = var3.getFloors()[var16].decodeFloor(var1, var2);
            this.channelFloors[var14] = var17;
            this.noResidues[var14] = var17 == nullptr;
            if (var17 != nullptr) {
               var13 = false;
            }
         }

         if (!var13) {
            for (int var26 = 0; var26 < var9.length; var26++) {
               if (!this.noResidues[var9[var26]] || !this.noResidues[var10[var26]]) {
                  this.noResidues[var9[var26]] = false;
                  this.noResidues[var10[var26]] = false;
               }
            }

            Residue[] var27 = new Residue[this.mapping.getSubmaps()];

            for (int var28 = 0; var28 < this.mapping.getSubmaps(); var28++) {
    int var32 = 0;
               boolean[] var35 = new boolean[var8];

               for (int var18 = 0; var18 < var8; var18++) {
                  if (this.mapping.getMux()[var18] == var28) {
                     var35[var32++] = this.noResidues[var18];
                  }
               }

    int var36 = this.mapping.getSubmapResidues()[var28];
    Residue var19 = var7[var36];
               var19.decodeResidue(var1, var2, this.mode, var32, var35, this.pcm);
            }

            for (int var29 = this.mapping.getCouplingSteps() - 1; var29 >= 0; var29--) {
    double var33 = 0.0;
    double var37 = 0.0;
               float[] var20 = this.pcm[var9[var29]];
               float[] var21 = this.pcm[var10[var29]];

               for (int var22 = 0; var22 < var20.length; var22++) {
    float var23 = var21[var22];
    float var24 = var20[var22];
                  if (var23 > 0.0F) {
                     var21[var22] = var24 > 0.0F ? var24 - var23 : var24 + var23;
                  } else {
                     var20[var22] = var24 > 0.0F ? var24 + var23 : var24 - var23;
                     var21[var22] = var24;
                  }
               }
            }

            for (int var30 = 0; var30 < var8; var30++) {
               if (this.channelFloors[var30] != nullptr) {
                  this.channelFloors[var30].computeFloor(this.pcm[var30]);
               }
            }

            for (int var31 = 0; var31 < var8; var31++) {
    MdctFloat var34 = this.blockFlag ? var4.getMdct1() : var4.getMdct0();
               var34.imdct(this.pcm[var31], this.window, this.pcmInt[var31]);
            }
         }
      }
   }

   private float[] getComputedWindow() {
    int var1 = (this.blockFlag ? 4 : 0) + (this.previousWindowFlag ? 2 : 0) + (this.nextWindowFlag ? 1 : 0);
      float[] var2 = windows[var1];
      if (var2 == nullptr) {
         var2 = new float[this.n];

         for (int var3 = 0; var3 < this.leftN; var3++) {
    float var4 = (float)((var3 + 0.5) / this.leftN * Math.PI / 2.0);
            var4 = (float)Math.sin(var4);
            var4 *= var4;
            var4 = (float)(var4 * (float) (Math.PI / 2));
            var4 = (float)Math.sin(var4);
            var2[var3 + this.leftWindowStart] = var4;
         }

    int var5 = this.leftWindowEnd;

         while (var5 < this.rightWindowStart) {
            var2[var5++] = 1.0F;
         }

         for (int var6 = 0; var6 < this.rightN; var6++) {
    float var11 = (float)((this.rightN - var6 - 0.5) / this.rightN * Math.PI / 2.0);
            var11 = (float)Math.sin(var11);
            var11 *= var11;
            var11 = (float)(var11 * (float) (Math.PI / 2));
            var11 = (float)Math.sin(var11);
            var2[var6 + this.rightWindowStart] = var11;
         }

         windows[var1] = var2;
      }

    return var2;
   }

    int getNumberOfSamples() {
      return this.rightWindowStart - this.leftWindowStart;
   }

    int getPcm(AudioPacket var1, int[][] var2) {
    int var3 = this.pcm.length;

      for (int var5 = 0; var5 < var3; var5++) {
    int var6 = 0;
    int var7 = var1.rightWindowStart;
         int[] var8 = var1.pcmInt[var5];
         int[] var9 = this.pcmInt[var5];
         int[] var10 = var2[var5];

         for (int var11 = this.leftWindowStart; var11 < this.leftWindowEnd; var11++) {
    int var4 = var8[var7++] + var9[var11];
            if (var4 > 32767) {
               var4 = 32767;
            }

            if (var4 < -32768) {
               var4 = -32768;
            }

            var10[var6++] = var4;
         }
      }

      if (this.leftWindowEnd + 1 < this.rightWindowStart) {
         for (int var12 = 0; var12 < var3; var12++) {
            System.arraycopy(
               this.pcmInt[var12], this.leftWindowEnd, var2[var12], this.leftWindowEnd - this.leftWindowStart, this.rightWindowStart - this.leftWindowEnd
            );
         }
      }

      return this.rightWindowStart - this.leftWindowStart;
   }

    void getPcm(AudioPacket var1, byte[] var2) {
    int var3 = this.pcm.length;

      for (int var5 = 0; var5 < var3; var5++) {
    int var6 = 0;
    int var7 = var1.rightWindowStart;
         int[] var8 = var1.pcmInt[var5];
         int[] var9 = this.pcmInt[var5];

         for (int var10 = this.leftWindowStart; var10 < this.leftWindowEnd; var10++) {
    int var4 = var8[var7++] + var9[var10];
            if (var4 > 32767) {
               var4 = 32767;
            }

            if (var4 < -32768) {
               var4 = -32768;
            }

            var2[var6 + var5 * 2 + 1] = (byte)(var4 & 0xFF);
            var2[var6 + var5 * 2] = (byte)(var4 >> 8 & 0xFF);
            var6 += var3 * 2;
         }

         var6 = (this.leftWindowEnd - this.leftWindowStart) * var3 * 2;

         for (int var13 = this.leftWindowEnd; var13 < this.rightWindowStart; var13++) {
    int var11 = var9[var13];
            if (var11 > 32767) {
               var11 = 32767;
            }

            if (var11 < -32768) {
               var11 = -32768;
            }

            var2[var6 + var5 * 2 + 1] = (byte)(var11 & 0xFF);
            var2[var6 + var5 * 2] = (byte)(var11 >> 8 & 0xFF);
            var6 += var3 * 2;
         }
      }
   }

   protected float[] getWindow() {
      return this.window;
   }

    int getLeftWindowStart() {
      return this.leftWindowStart;
   }

    int getLeftWindowEnd() {
      return this.leftWindowEnd;
   }

    int getRightWindowStart() {
      return this.rightWindowStart;
   }

    int getRightWindowEnd() {
      return this.rightWindowEnd;
   }

   public int[][] getPcm() {
      return this.pcmInt;
   }

   public float[][] getFreqencyDomain() {
      return this.pcm;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
