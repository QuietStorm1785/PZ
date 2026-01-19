package de.jarnbjo.vorbis;

class Residue$Look {
   int map;
   int parts;
   int stages;
   CodeBook[] fullbooks;
   CodeBook phrasebook;
   int[][] partbooks;
   int partvals;
   int[][] decodemap;
   int postbits;
   int phrasebits;
   int frames;

   protected Residue$Look(Residue var1, VorbisStream var2, Mode var3) {
      this.this$0 = var1;
      int var4 = 0;
      boolean var5 = false;
      int var6 = 0;
      this.map = var3.getMapping();
      this.parts = var1.getClassifications();
      this.fullbooks = var2.getSetupHeader().getCodeBooks();
      this.phrasebook = this.fullbooks[var1.getClassBook()];
      var4 = this.phrasebook.getDimensions();
      this.partbooks = new int[this.parts][];

      for (int var7 = 0; var7 < this.parts; var7++) {
         int var8 = Util.ilog(var1.getCascade()[var7]);
         if (var8 != 0) {
            if (var8 > var6) {
               var6 = var8;
            }

            this.partbooks[var7] = new int[var8];

            for (int var9 = 0; var9 < var8; var9++) {
               if ((var1.getCascade()[var7] & 1 << var9) != 0) {
                  this.partbooks[var7][var9] = var1.getBooks()[var7][var9];
               }
            }
         }
      }

      this.partvals = (int)Math.rint(Math.pow(this.parts, var4));
      this.stages = var6;
      this.decodemap = new int[this.partvals][];

      for (int var13 = 0; var13 < this.partvals; var13++) {
         int var14 = var13;
         int var15 = this.partvals / this.parts;
         this.decodemap[var13] = new int[var4];

         for (int var10 = 0; var10 < var4; var10++) {
            int var11 = var14 / var15;
            var14 -= var11 * var15;
            var15 /= this.parts;
            this.decodemap[var13][var10] = var11;
         }
      }
   }

   protected int[][] getDecodeMap() {
      return this.decodemap;
   }

   protected int getFrames() {
      return this.frames;
   }

   protected int getMap() {
      return this.map;
   }

   protected int[][] getPartBooks() {
      return this.partbooks;
   }

   protected int getParts() {
      return this.parts;
   }

   protected int getPartVals() {
      return this.partvals;
   }

   protected int getPhraseBits() {
      return this.phrasebits;
   }

   protected CodeBook getPhraseBook() {
      return this.phrasebook;
   }

   protected int getPostBits() {
      return this.postbits;
   }

   protected int getStages() {
      return this.stages;
   }
}
