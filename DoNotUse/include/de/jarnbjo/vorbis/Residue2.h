#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "de/jarnbjo/util/io/BitInputStream.h"
#include "de/jarnbjo/vorbis/Residue/Look.h"
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace vorbis {


class Residue2 : public Residue {
public:
   private double[][] decodedVectors;

    private Residue2() {
   }

    protected Residue2(BitInputStream var1, SetupHeader var2) {
      super(var1, var2);
   }

    int getType() {
    return 2;
   }

    void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3, int var4, boolean[] var5, float[][] var6) {
    Look var7 = this.getLook(var1, var3);
    CodeBook var8 = var1.getSetupHeader().getCodeBooks()[this.getClassBook()];
    int var9 = var8.getDimensions();
    int var10 = this.getEnd() - this.getBegin();
    int var11 = var10 / this.getPartitionSize();
    int var12 = this.getPartitionSize();
    int var13 = var7.getPhraseBook().getDimensions();
    int var14 = (var11 + var13 - 1) / var13;
    int var15 = 0;

      for (int var16 = 0; var16 < var5.length; var16++) {
         if (!var5[var16]) {
            var15++;
         }
      }

      float[][] var25 = new float[var15][];
      var15 = 0;

      for (int var17 = 0; var17 < var5.length; var17++) {
         if (!var5[var17]) {
            var25[var15++] = var6[var17];
         }
      }

      int[][] var26 = new int[var14][];

      for (int var18 = 0; var18 < var7.getStages(); var18++) {
    int var19 = 0;

         for (int var20 = 0; var19 < var11; var20++) {
            if (var18 == 0) {
    int var21 = var2.getInt(var7.getPhraseBook().getHuffmanRoot());
               if (var21 == -1) {
                  throw VorbisFormatException("");
               }

               var26[var20] = var7.getDecodeMap()[var21];
               if (var26[var20] == nullptr) {
                  throw VorbisFormatException("");
               }
            }

            for (int var27 = 0; var27 < var13 && var19 < var11; var19++) {
    int var22 = this.begin + var19 * var12;
               if ((this.cascade[var26[var20][var27]] & 1 << var18) != 0) {
    CodeBook var23 = var1.getSetupHeader().getCodeBooks()[var7.getPartBooks()[var26[var20][var27]][var18]];
                  if (var23 != nullptr) {
                     var23.readVvAdd(var25, var2, var22, var12);
                  }
               }

               var27++;
            }
         }
      }
   }

    void* clone() {
    Residue2 var1 = std::make_shared<Residue2>();
      this.fill(var1);
    return var1;
   }

   protected double[][] getDecodedVectors() {
      return this.decodedVectors;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
