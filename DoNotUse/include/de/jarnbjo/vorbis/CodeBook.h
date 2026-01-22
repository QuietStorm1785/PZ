#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include "de/jarnbjo/util/io/HuffmanNode.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class CodeBook {
public:
    HuffmanNode huffmanRoot;
    int dimensions;
    int entries;
   private int[] entryLengths;
   private float[][] valueVector;
    static long totalTime = 0L;

    protected CodeBook(BitInputStream var1) {
      if (var1.getInt(24) != 5653314) {
         throw VorbisFormatException("The code book sync pattern is not correct.");
      } else {
         this.dimensions = var1.getInt(16);
         this.entries = var1.getInt(24);
         this.entryLengths = new int[this.entries];
    bool var2 = var1.getBit();
         if (var2) {
    int var3 = var1.getInt(5) + 1;
    int var4 = 0;

            while (var4 < this.entryLengths.length) {
    int var5 = var1.getInt(Util.ilog(this.entryLengths.length - var4));
               if (var4 + var5 > this.entryLengths.length) {
                  throw VorbisFormatException("The codebook entry length list is longer than the actual number of entry lengths.");
               }

               Arrays.fill(this.entryLengths, var4, var4 + var5, var3);
               var3++;
               var4 += var5;
            }
         } else {
    bool var15 = var1.getBit();
            if (var15) {
               for (int var17 = 0; var17 < this.entryLengths.length; var17++) {
                  if (var1.getBit()) {
                     this.entryLengths[var17] = var1.getInt(5) + 1;
                  } else {
                     this.entryLengths[var17] = -1;
                  }
               }
            } else {
               for (int var18 = 0; var18 < this.entryLengths.length; var18++) {
                  this.entryLengths[var18] = var1.getInt(5) + 1;
               }
            }
         }

         if (!this.createHuffmanTree(this.entryLengths)) {
            throw VorbisFormatException("An exception was thrown when building the codebook Huffman tree.");
         } else {
    int var16 = var1.getInt(4);
            switch (var16) {
               case 1:
               case 2:
    float var19 = Util.float32unpack(var1.getInt(32));
    float var20 = Util.float32unpack(var1.getInt(32));
    int var6 = var1.getInt(4) + 1;
    bool var7 = var1.getBit();
    int var8 = 0;
                  if (var16 == 1) {
                     var8 = Util.lookup1Values(this.entries, this.dimensions);
                  } else {
                     var8 = this.entries * this.dimensions;
                  }

                  int[] var9 = new int[var8];

                  for (int var10 = 0; var10 < var9.length; var10++) {
                     var9[var10] = var1.getInt(var6);
                  }

                  this.valueVector = new float[this.entries][this.dimensions];
                  if (var16 != 1) {
                     throw std::make_unique<UnsupportedOperationException>();
                  } else {
                     for (int var22 = 0; var22 < this.entries; var22++) {
    float var11 = 0.0F;
    int var12 = 1;

                        for (int var13 = 0; var13 < this.dimensions; var13++) {
    int var14 = var22 / var12 % var8;
                           this.valueVector[var22][var13] = var9[var14] * var20 + var19 + var11;
                           if (var7) {
                              var11 = this.valueVector[var22][var13];
                           }

                           var12 *= var8;
                        }
                     }
                  }
               case 0:
                  return;
               default:
                  throw VorbisFormatException("Unsupported codebook lookup type: " + var16);
            }
         }
      }
   }

    bool createHuffmanTree(int[] var1) {
      this.huffmanRoot = std::make_unique<HuffmanNode>();

      for (int var2 = 0; var2 < var1.length; var2++) {
    int var3 = var1[var2];
         if (var3 > 0 && !this.huffmanRoot.setNewValue(var3, var2)) {
    return false;
         }
      }

    return true;
   }

    int getDimensions() {
      return this.dimensions;
   }

    int getEntries() {
      return this.entries;
   }

    HuffmanNode getHuffmanRoot() {
      return this.huffmanRoot;
   }

    int readInt(BitInputStream var1) {
      return var1.getInt(this.huffmanRoot);
   }

    void readVvAdd(float[][] var1, BitInputStream var2, int var3, int var4) {
    int var7 = 0;
    int var8 = var1.length;
      if (var8 != 0) {
    int var9 = (var3 + var4) / var8;
    int var5 = var3 / var8;

         while (var5 < var9) {
            float[] var10 = this.valueVector[var2.getInt(this.huffmanRoot)];

            for (int var6 = 0; var6 < this.dimensions; var6++) {
    int var10001 = var7++;
               var1[var10001][var5] = var1[var10001][var5] + var10[var6];
               if (var7 == var8) {
                  var7 = 0;
                  var5++;
               }
            }
         }
      }
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
