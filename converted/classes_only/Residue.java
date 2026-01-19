package de.jarnbjo.vorbis;

import de.jarnbjo.util.io.BitInputStream;
import de.jarnbjo.vorbis.Residue.Look;
import java.io.IOException;
import java.util.HashMap;

abstract class Residue {
   protected int begin;
   protected int end;
   protected int partitionSize;
   protected int classifications;
   protected int classBook;
   protected int[] cascade;
   protected int[][] books;
   protected HashMap looks = new HashMap();

   protected Residue() {
   }

   protected Residue(BitInputStream var1, SetupHeader var2) throws VorbisFormatException, IOException {
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
                  throw new VorbisFormatException("Reference to invalid codebook entry in residue header.");
               }
            }
         }
      }
   }

   protected static Residue createInstance(BitInputStream var0, SetupHeader var1) throws VorbisFormatException, IOException {
      int var2 = var0.getInt(16);
      switch (var2) {
         case 0:
            return new Residue0(var0, var1);
         case 1:
            return new Residue2(var0, var1);
         case 2:
            return new Residue2(var0, var1);
         default:
            throw new VorbisFormatException("Residue type " + var2 + " is not supported.");
      }
   }

   protected abstract int getType();

   protected abstract void decodeResidue(VorbisStream var1, BitInputStream var2, Mode var3, int var4, boolean[] var5, float[][] var6) throws VorbisFormatException, IOException;

   protected int getBegin() {
      return this.begin;
   }

   protected int getEnd() {
      return this.end;
   }

   protected int getPartitionSize() {
      return this.partitionSize;
   }

   protected int getClassifications() {
      return this.classifications;
   }

   protected int getClassBook() {
      return this.classBook;
   }

   protected int[] getCascade() {
      return this.cascade;
   }

   protected int[][] getBooks() {
      return this.books;
   }

   protected final void fill(Residue var1) {
      var1.begin = this.begin;
      var1.books = this.books;
      var1.cascade = this.cascade;
      var1.classBook = this.classBook;
      var1.classifications = this.classifications;
      var1.end = this.end;
      var1.partitionSize = this.partitionSize;
   }

   protected Look getLook(VorbisStream var1, Mode var2) {
      Look var3 = (Look)this.looks.get(var2);
      if (var3 == null) {
         var3 = new Look(this, var1, var2);
         this.looks.put(var2, var3);
      }

      return var3;
   }
}
