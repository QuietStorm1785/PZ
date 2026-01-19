package zombie.iso.areas.isoregion.data;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import zombie.core.Colors;
import zombie.iso.areas.isoregion.IsoRegions;
import zombie.iso.areas.isoregion.data.DataRoot.SelectInfo;
import zombie.iso.areas.isoregion.regions.IsoChunkRegion;
import zombie.iso.areas.isoregion.regions.IsoRegionManager;
import zombie.iso.areas.isoregion.regions.IsoWorldRegion;

public final class DataRoot {
   private final Map<Integer, DataCell> cellMap = new HashMap<>();
   public final SelectInfo select = new SelectInfo(this);
   private final SelectInfo selectInternal = new SelectInfo(this);
   public final IsoRegionManager regionManager;
   private final ArrayList<IsoWorldRegion> dirtyIsoWorldRegions = new ArrayList<>();
   private final ArrayList<DataChunk> dirtyChunks = new ArrayList<>();
   protected static int recalcs;
   protected static int floodFills;
   protected static int merges;
   private static final long[] t_start = new long[5];
   private static final long[] t_end = new long[5];
   private static final long[] t_time = new long[5];

   public DataRoot() {
      this.regionManager = new IsoRegionManager(this);
   }

   public void getAllChunks(List<DataChunk> var1) {
      for (Entry var3 : this.cellMap.entrySet()) {
         ((DataCell)var3.getValue()).getAllChunks(var1);
      }
   }

   private DataCell getCell(int var1) {
      return this.cellMap.get(var1);
   }

   private DataCell addCell(int var1, int var2, int var3) {
      DataCell var4 = new DataCell(this, var1, var2, var3);
      this.cellMap.put(var3, var4);
      return var4;
   }

   public DataChunk getDataChunk(int var1, int var2) {
      int var3 = IsoRegions.hash(var1 / 30, var2 / 30);
      DataCell var4 = this.cellMap.get(var3);
      if (var4 != null) {
         int var5 = IsoRegions.hash(var1, var2);
         return var4.getChunk(var5);
      } else {
         return null;
      }
   }

   private void setDataChunk(DataChunk var1) {
      int var2 = IsoRegions.hash(var1.getChunkX() / 30, var1.getChunkY() / 30);
      DataCell var3 = this.cellMap.get(var2);
      if (var3 == null) {
         var3 = this.addCell(var1.getChunkX() / 30, var1.getChunkY() / 30, var2);
      }

      var3.setChunk(var1);
   }

   public IsoWorldRegion getIsoWorldRegion(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      if (this.selectInternal.chunk != null) {
         IsoChunkRegion var4 = this.selectInternal.chunk.getIsoChunkRegion(this.selectInternal.chunkSquareX, this.selectInternal.chunkSquareY, var3);
         if (var4 != null) {
            return var4.getIsoWorldRegion();
         }
      }

      return null;
   }

   public byte getSquareFlags(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      return this.selectInternal.square;
   }

   public IsoChunkRegion getIsoChunkRegion(int var1, int var2, int var3) {
      this.selectInternal.reset(var1, var2, var3, false);
      return this.selectInternal.chunk != null
         ? this.selectInternal.chunk.getIsoChunkRegion(this.selectInternal.chunkSquareX, this.selectInternal.chunkSquareY, var3)
         : null;
   }

   public void resetAllData() {
      ArrayList var1 = new ArrayList();

      for (Entry var3 : this.cellMap.entrySet()) {
         DataCell var4 = (DataCell)var3.getValue();

         for (Entry var6 : var4.dataChunks.entrySet()) {
            DataChunk var7 = (DataChunk)var6.getValue();

            for (int var8 = 0; var8 < 8; var8++) {
               for (IsoChunkRegion var10 : var7.getChunkRegions(var8)) {
                  if (var10.getIsoWorldRegion() != null && !var1.contains(var10.getIsoWorldRegion())) {
                     var1.add(var10.getIsoWorldRegion());
                  }

                  var10.setIsoWorldRegion(null);
                  this.regionManager.releaseIsoChunkRegion(var10);
               }
            }
         }

         var4.dataChunks.clear();
      }

      this.cellMap.clear();

      for (IsoWorldRegion var12 : var1) {
         this.regionManager.releaseIsoWorldRegion(var12);
      }
   }

   public void EnqueueDirtyDataChunk(DataChunk var1) {
      if (!this.dirtyChunks.contains(var1)) {
         this.dirtyChunks.add(var1);
      }
   }

   public void EnqueueDirtyIsoWorldRegion(IsoWorldRegion var1) {
      if (!this.dirtyIsoWorldRegions.contains(var1)) {
         this.dirtyIsoWorldRegions.add(var1);
      }
   }

   public void DequeueDirtyIsoWorldRegion(IsoWorldRegion var1) {
      this.dirtyIsoWorldRegions.remove(var1);
   }

   public void updateExistingSquare(int var1, int var2, int var3, byte var4) {
      this.select.reset(var1, var2, var3, false);
      if (this.select.chunk != null) {
         byte var5 = -1;
         if (this.select.square != -1) {
            var5 = this.select.square;
         }

         if (var4 == var5) {
            return;
         }

         this.select.chunk.setOrAddSquare(this.select.chunkSquareX, this.select.chunkSquareY, this.select.z, var4, true);
      } else {
         IsoRegions.warn("DataRoot.updateExistingSquare -> trying to change a square on a unknown chunk");
      }
   }

   public void processDirtyChunks() {
      if (this.dirtyChunks.size() > 0) {
         long var1 = System.nanoTime();
         recalcs = 0;
         floodFills = 0;
         merges = 0;
         t_start[0] = System.nanoTime();

         for (int var4 = 0; var4 < this.dirtyChunks.size(); var4++) {
            DataChunk var3 = this.dirtyChunks.get(var4);
            var3.recalculate();
            recalcs++;
         }

         t_end[0] = System.nanoTime();
         t_start[1] = System.nanoTime();

         for (int var12 = 0; var12 < this.dirtyChunks.size(); var12++) {
            DataChunk var9 = this.dirtyChunks.get(var12);
            DataChunk var5 = this.getDataChunk(var9.getChunkX(), var9.getChunkY() - 1);
            DataChunk var6 = this.getDataChunk(var9.getChunkX() - 1, var9.getChunkY());
            DataChunk var7 = this.getDataChunk(var9.getChunkX(), var9.getChunkY() + 1);
            DataChunk var8 = this.getDataChunk(var9.getChunkX() + 1, var9.getChunkY());
            var9.link(var5, var6, var7, var8);
         }

         t_end[1] = System.nanoTime();
         t_start[2] = System.nanoTime();

         for (int var13 = 0; var13 < this.dirtyChunks.size(); var13++) {
            DataChunk var10 = this.dirtyChunks.get(var13);
            var10.interConnect();
         }

         t_end[2] = System.nanoTime();
         t_start[3] = System.nanoTime();

         for (int var14 = 0; var14 < this.dirtyChunks.size(); var14++) {
            DataChunk var11 = this.dirtyChunks.get(var14);
            var11.recalcRoofs();
            var11.unsetDirtyAll();
         }

         t_end[3] = System.nanoTime();
         t_start[4] = System.nanoTime();
         if (this.dirtyIsoWorldRegions.size() > 0) {
            for (int var18 = 0; var18 < this.dirtyIsoWorldRegions.size(); var18++) {
               IsoWorldRegion var15 = this.dirtyIsoWorldRegions.get(var18);
               var15.unlinkNeighbors();
            }

            for (int var19 = 0; var19 < this.dirtyIsoWorldRegions.size(); var19++) {
               IsoWorldRegion var16 = this.dirtyIsoWorldRegions.get(var19);
               var16.linkNeighbors();
            }

            this.dirtyIsoWorldRegions.clear();
         }

         t_end[4] = System.nanoTime();
         this.dirtyChunks.clear();
         long var17 = System.nanoTime();
         long var20 = var17 - var1;
         if (IsoRegions.PRINT_D) {
            t_time[0] = t_end[0] - t_start[0];
            t_time[1] = t_end[1] - t_start[1];
            t_time[2] = t_end[2] - t_start[2];
            t_time[3] = t_end[3] - t_start[3];
            t_time[4] = t_end[4] - t_start[4];
            IsoRegions.log(
               "--- IsoRegion update: "
                  + String.format("%.6f", var20 / 1000000.0)
                  + " ms, recalc: "
                  + String.format("%.6f", t_time[0] / 1000000.0)
                  + " ms, link: "
                  + String.format("%.6f", t_time[1] / 1000000.0)
                  + " ms, interconnect: "
                  + String.format("%.6f", t_time[2] / 1000000.0)
                  + " ms, roofs: "
                  + String.format("%.6f", t_time[3] / 1000000.0)
                  + " ms, worldRegion: "
                  + String.format("%.6f", t_time[4] / 1000000.0)
                  + " ms, recalcs = "
                  + recalcs
                  + ", merges = "
                  + merges
                  + ", floodfills = "
                  + floodFills,
               Colors.CornFlowerBlue
            );
         }
      }
   }
}
