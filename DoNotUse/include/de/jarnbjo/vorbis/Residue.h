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


class Residue {
public:
    int begin;
    int end;
    int partitionSize;
    int classifications;
    int classBook;
   protected int[] cascade;
   protected int[][] books;
    std::unordered_map looks = new std::unordered_map();

    protected Residue() {
   }

    protected Residue(BitInputStream var1, SetupHeader var2) {
      this.begin = var1.getInt(24);
      this.end = var1.getInt(24);
      this.partitionSize = var1.getInt(24) + 1;
      this.classifications = var1.getInt(6) + 1;
      this.classBook = var1.getInt(8);
      this.cascade = new int[this.classifications];
    int var3 = 0;

      for (int var4 = 0; var4 < this.classifications; var4++) {
    int var5 = 0;
    int var6 = 0;
         var6 = var1.getInt(3);
         if (var1.getBit()) {
            var5 = var1.getInt(5);
         }

         this.cascade[var4] = var5 << 3 | var6;
         var3 += Util.icount(this.cascade[var4]);
      }

      this.books = new int[this.classifications][8];

      for (int var7 = 0; var7 < this.classifications; var7++) {
         for (int var8 = 0; var8 < 8; var8++) {
            if ((this.cascade[var7] & 1 << var8) != 0) {
               this.books[var7][var8] = var1.getInt(8);
               if (this.books[var7][var8] > var2.getCodeBooks().length) {
                  throw VorbisFormatException("Reference to invalid codebook entry in residue header.");
               }
            }
         }
      }
   }

    static Residue createInstance(BitInputStream var0, SetupHeader var1) {
    int var2 = var0.getInt(16);
      switch (var2) {
         case 0:
            return std::make_shared<Residue0>(var0, var1);
         case 1:
            return std::make_shared<Residue2>(var0, var1);
         case 2:
            return std::make_shared<Residue2>(var0, var1);
         default:
            throw VorbisFormatException("Residue type " + var2 + " is not supported.");
      }
   }

   protected abstract int getType();

   protected abstract void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3, int var4, boolean[] var5, float[][] var6) throws VorbisFormatException, IOException;

    int getBegin() {
      return this.begin;
   }

    int getEnd() {
      return this.end;
   }

    int getPartitionSize() {
      return this.partitionSize;
   }

    int getClassifications() {
      return this.classifications;
   }

    int getClassBook() {
      return this.classBook;
   }

   protected int[] getCascade() {
      return this.cascade;
   }

   protected int[][] getBooks() {
      return this.books;
   }

    void fill(Residue var1) {
      var1.begin = this.begin;
      var1.books = this.books;
      var1.cascade = this.cascade;
      var1.classBook = this.classBook;
      var1.classifications = this.classifications;
      var1.end = this.end;
      var1.partitionSize = this.partitionSize;
   }

    Look getLook(VorbisStream var1, Mode var2) {
    Look var3 = (Look)this.looks.get(var2);
      if (var3 == nullptr) {
         var3 = std::make_shared<Look>(this, var1, var2);
         this.looks.put(var2, var3);
      }

    return var3;
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
