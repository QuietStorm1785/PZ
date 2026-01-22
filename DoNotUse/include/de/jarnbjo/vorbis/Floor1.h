#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace de {
namespace jarnbjo {
namespace vorbis {


class Floor1 : public Floor {
public:
   private int[] partitionClassList;
    int maximumClass;
    int multiplier;
    int rangeBits;
   private int[] classDimensions;
   private int[] classSubclasses;
   private int[] classMasterbooks;
   private int[][] subclassBooks;
   private int[] xList;
   private int[] yList;
   private int[] lowNeighbours;
   private int[] highNeighbours;
   private static const int[] RANGES = new int[]{256, 128, 86, 64};

    private Floor1() {
   }

    protected Floor1(BitInputStream var1, SetupHeader var2) {
      this.maximumClass = -1;
    int var3 = var1.getInt(5);
      this.partitionClassList = new int[var3];

      for (int var4 = 0; var4 < this.partitionClassList.length; var4++) {
         this.partitionClassList[var4] = var1.getInt(4);
         if (this.partitionClassList[var4] > this.maximumClass) {
            this.maximumClass = this.partitionClassList[var4];
         }
      }

      this.classDimensions = new int[this.maximumClass + 1];
      this.classSubclasses = new int[this.maximumClass + 1];
      this.classMasterbooks = new int[this.maximumClass + 1];
      this.subclassBooks = new int[this.maximumClass + 1][];
    int var9 = 2;

      for (int var5 = 0; var5 <= this.maximumClass; var5++) {
         this.classDimensions[var5] = var1.getInt(3) + 1;
         var9 += this.classDimensions[var5];
         this.classSubclasses[var5] = var1.getInt(2);
         if (this.classDimensions[var5] > var2.getCodeBooks().length || this.classSubclasses[var5] > var2.getCodeBooks().length) {
            throw VorbisFormatException("There is a class dimension or class subclasses entry higher than the number of codebooks in the setup header.");
         }

         if (this.classSubclasses[var5] != 0) {
            this.classMasterbooks[var5] = var1.getInt(8);
         }

         this.subclassBooks[var5] = new int[1 << this.classSubclasses[var5]];

         for (int var6 = 0; var6 < this.subclassBooks[var5].length; var6++) {
            this.subclassBooks[var5][var6] = var1.getInt(8) - 1;
         }
      }

      this.multiplier = var1.getInt(2) + 1;
      this.rangeBits = var1.getInt(4);
    bool var10 = false;
    std::vector var11 = new std::vector();
      var11.push_back(std::make_shared<int>(0));
      var11.push_back(std::make_shared<int>(1 << this.rangeBits));

      for (int var7 = 0; var7 < var3; var7++) {
         for (int var8 = 0; var8 < this.classDimensions[this.partitionClassList[var7]]; var8++) {
            var11.push_back(std::make_shared<int>(var1.getInt(this.rangeBits)));
         }
      }

      this.xList = new int[var11.size()];
      this.lowNeighbours = new int[this.xList.length];
      this.highNeighbours = new int[this.xList.length];
    Iterator var12 = var11.iterator();

      for (int var13 = 0; var13 < this.xList.length; var13++) {
         this.xList[var13] = (int)var12.next();
      }

      for (int var14 = 0; var14 < this.xList.length; var14++) {
         this.lowNeighbours[var14] = Util.lowNeighbour(this.xList, var14);
         this.highNeighbours[var14] = Util.highNeighbour(this.xList, var14);
      }
   }

    int getType() {
    return 1;
   }

    Floor decodeFloor(VorbisStream var1, BitInputStream var2) {
      if (!var2.getBit()) {
    return nullptr;
      } else {
    Floor1 var3 = (Floor1)this.clone();
         var3.yList = new int[this.xList.length];
    int var4 = RANGES[this.multiplier - 1];
         var3.yList[0] = var2.getInt(Util.ilog(var4 - 1));
         var3.yList[1] = var2.getInt(Util.ilog(var4 - 1));
    int var5 = 2;

         for (int var6 = 0; var6 < this.partitionClassList.length; var6++) {
    int var7 = this.partitionClassList[var6];
    int var8 = this.classDimensions[var7];
    int var9 = this.classSubclasses[var7];
    int var10 = (1 << var9) - 1;
    int var11 = 0;
            if (var9 > 0) {
               var11 = var2.getInt(var1.getSetupHeader().getCodeBooks()[this.classMasterbooks[var7]].getHuffmanRoot());
            }

            for (int var12 = 0; var12 < var8; var12++) {
    int var13 = this.subclassBooks[var7][var11 & var10];
               var11 >>>= var9;
               if (var13 >= 0) {
                  var3.yList[var12 + var5] = var2.getInt(var1.getSetupHeader().getCodeBooks()[var13].getHuffmanRoot());
               } else {
                  var3.yList[var12 + var5] = 0;
               }
            }

            var5 += var8;
         }

    return var3;
      }
   }

    void computeFloor(float[] var1) {
    int var2 = var1.length;
    int var3 = this.xList.length;
      boolean[] var4 = new boolean[var3];
    int var5 = RANGES[this.multiplier - 1];

      for (int var6 = 2; var6 < var3; var6++) {
    int var7 = this.lowNeighbours[var6];
    int var8 = this.highNeighbours[var6];
    int var9 = Util.renderPoint(this.xList[var7], this.xList[var8], this.yList[var7], this.yList[var8], this.xList[var6]);
    int var10 = this.yList[var6];
    int var11 = var5 - var9;
    int var13 = var11 < var9 ? var11 * 2 : var9 * 2;
         if (var10 != 0) {
            var4[var7] = true;
            var4[var8] = true;
            var4[var6] = true;
            if (var10 >= var13) {
               this.yList[var6] = var11 > var9 ? var10 - var9 + var9 : -var10 + var11 + var9 - 1;
            } else {
               this.yList[var6] = (var10 & 1) == 1 ? var9 - (var10 + 1 >> 1) : var9 + (var10 >> 1);
            }
         } else {
            var4[var6] = false;
            this.yList[var6] = var9;
         }
      }

      int[] var14 = new int[var3];
      System.arraycopy(this.xList, 0, var14, 0, var3);
      sort(var14, this.yList, var4);
    int var15 = 0;
    int var16 = 0;
    int var17 = 0;
    int var18 = this.yList[0] * this.multiplier;
      float[] var19 = new float[var1.length];
      float[] var12 = new float[var1.length];
      Arrays.fill(var19, 1.0F);
      System.arraycopy(var1, 0, var12, 0, var1.length);

      for (int var20 = 1; var20 < var3; var20++) {
         if (var4[var20]) {
            var16 = this.yList[var20] * this.multiplier;
            var15 = var14[var20];
            Util.renderLine(var17, var18, var15, var16, var1);
            Util.renderLine(var17, var18, var15, var16, var19);
            var17 = var15;
            var18 = var16;
         }
      }

    float var21 = DB_STATIC_TABLE[var16];

      while (var15 < var2 / 2) {
         var1[var15++] = var21;
      }
   }

    void* clone() {
    Floor1 var1 = std::make_shared<Floor1>();
      var1.classDimensions = this.classDimensions;
      var1.classMasterbooks = this.classMasterbooks;
      var1.classSubclasses = this.classSubclasses;
      var1.maximumClass = this.maximumClass;
      var1.multiplier = this.multiplier;
      var1.partitionClassList = this.partitionClassList;
      var1.rangeBits = this.rangeBits;
      var1.subclassBooks = this.subclassBooks;
      var1.xList = this.xList;
      var1.yList = this.yList;
      var1.lowNeighbours = this.lowNeighbours;
      var1.highNeighbours = this.highNeighbours;
    return var1;
   }

    static void sort(int[] var0, int[] var1, boolean[] var2) {
    uint8_t var3 = 0;
    int var4 = var0.length;
    int var5 = var4 + var3;

      for (int var8 = var3; var8 < var5; var8++) {
         for (int var9 = var8; var9 > var3 && var0[var9 - 1] > var0[var9]; var9--) {
    int var6 = var0[var9];
            var0[var9] = var0[var9 - 1];
            var0[var9 - 1] = var6;
            var6 = var1[var9];
            var1[var9] = var1[var9 - 1];
            var1[var9 - 1] = var6;
    bool var7 = var2[var9];
            var2[var9] = var2[var9 - 1];
            var2[var9 - 1] = var7;
         }
      }
   }

    static void swap(int[] var0, int var1, int var2) {
    int var3 = var0[var1];
      var0[var1] = var0[var2];
      var0[var2] = var3;
   }

    static void swap(boolean[] var0, int var1, int var2) {
    bool var3 = var0[var1];
      var0[var1] = var0[var2];
      var0[var2] = var3;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
