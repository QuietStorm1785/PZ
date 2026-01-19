package zombie.iso;

import java.util.ArrayList;

class IsoChunk$SanityCheck {
   public IsoChunk saveChunk;
   public String saveThread;
   public IsoChunk loadChunk;
   public String loadThread;
   public final ArrayList<String> loadFile = new ArrayList<>();
   public String saveFile;

   private IsoChunk$SanityCheck() {
   }

   public synchronized void beginSave(IsoChunk var1) {
      if (this.saveChunk != null) {
         this.log("trying to save while already saving, wx,wy=" + var1.wx + "," + var1.wy);
      }

      if (this.loadChunk == var1) {
         this.log("trying to save the same IsoChunk being loaded");
      }

      this.saveChunk = var1;
      this.saveThread = Thread.currentThread().getName();
   }

   public synchronized void endSave(IsoChunk var1) {
      this.saveChunk = null;
      this.saveThread = null;
   }

   public synchronized void beginLoad(IsoChunk var1) {
      if (this.loadChunk != null) {
         this.log("trying to load while already loading, wx,wy=" + var1.wx + "," + var1.wy);
      }

      if (this.saveChunk == var1) {
         this.log("trying to load the same IsoChunk being saved");
      }

      this.loadChunk = var1;
      this.loadThread = Thread.currentThread().getName();
   }

   public synchronized void endLoad(IsoChunk var1) {
      this.loadChunk = null;
      this.loadThread = null;
   }

   public synchronized void checkCRC(long var1, long var3) {
      if (var1 != var3) {
         this.log("CRC mismatch save=" + var1 + " load=" + var3);
      }
   }

   public synchronized void checkLength(long var1, long var3) {
      if (var1 != var3) {
         this.log("LENGTH mismatch save=" + var1 + " load=" + var3);
      }
   }

   public synchronized void beginLoadFile(String var1) {
      if (var1.equals(this.saveFile)) {
         this.log("attempted to load file being saved " + var1);
      }

      this.loadFile.add(var1);
   }

   public synchronized void endLoadFile(String var1) {
      this.loadFile.remove(var1);
   }

   public synchronized void beginSaveFile(String var1) {
      if (this.loadFile.contains(var1)) {
         this.log("attempted to save file being loaded " + var1);
      }

      this.saveFile = var1;
   }

   public synchronized void endSaveFile() {
      this.saveFile = null;
   }

   public synchronized void log(String var1) {
      StringBuilder var2 = new StringBuilder();
      var2.append("SANITY CHECK FAIL! thread=\"" + Thread.currentThread().getName() + "\"\n");
      if (var1 != null) {
         var2.append(var1 + "\n");
      }

      if (this.saveChunk != null && this.saveChunk == this.loadChunk) {
         var2.append("exact same IsoChunk being saved + loaded\n");
      }

      if (this.saveChunk != null) {
         var2.append("save wx,wy=" + this.saveChunk.wx + "," + this.saveChunk.wy + " thread=\"" + this.saveThread + "\"\n");
      } else {
         var2.append("save chunk=null\n");
      }

      if (this.loadChunk != null) {
         var2.append("load wx,wy=" + this.loadChunk.wx + "," + this.loadChunk.wy + " thread=\"" + this.loadThread + "\"\n");
      } else {
         var2.append("load chunk=null\n");
      }

      String var3 = var2.toString();
      throw new RuntimeException(var3);
   }
}
