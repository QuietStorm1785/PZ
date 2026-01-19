package zombie.network;

import java.util.ArrayList;
import java.util.HashSet;
import zombie.VirtualZombieManager;
import zombie.core.logger.LoggerManager;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.RoomDef;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehiclesDB2;

public class ServerMap$ServerCell {
   public int WX;
   public int WY;
   public boolean bLoaded = false;
   public boolean bPhysicsCheck = false;
   public final IsoChunk[][] chunks = new IsoChunk[5][5];
   private final HashSet<RoomDef> UnexploredRooms = new HashSet<>();
   private static final ServerChunkLoader chunkLoader = new ServerChunkLoader();
   private static final ArrayList<ServerMap$ServerCell> loaded = new ArrayList<>();
   private boolean startedLoading = false;
   public boolean bCancelLoading = false;
   public boolean bLoadingWasCancelled = false;
   private static final ArrayList<ServerMap$ServerCell> loaded2 = new ArrayList<>();
   private boolean doingRecalc = false;

   public boolean Load2() {
      chunkLoader.getRecalc(loaded2);

      for (int var1 = 0; var1 < loaded2.size(); var1++) {
         if (loaded2.get(var1) == this) {
            long var2 = System.nanoTime();
            this.RecalcAll2();
            loaded2.remove(var1);
            if (ServerMap.MapLoading) {
               DebugLog.log(DebugType.MapLoading, "loaded2=" + loaded2);
            }

            float var4 = (float)(System.nanoTime() - var2) / 1000000.0F;
            if (ServerMap.MapLoading) {
               DebugLog.log(DebugType.MapLoading, "finish loading cell " + this.WX + "," + this.WY + " ms=" + var4);
            }

            this.loadVehicles();
            return true;
         }
      }

      return false;
   }

   private void loadVehicles() {
      for (int var1 = 0; var1 < 5; var1++) {
         for (int var2 = 0; var2 < 5; var2++) {
            IsoChunk var3 = this.chunks[var1][var2];
            if (var3 != null && !var3.isNewChunk()) {
               VehiclesDB2.instance.loadChunkMain(var3);
            }
         }
      }
   }

   public void RecalcAll2() {
      int var1 = this.WX * 5 * 10;
      int var2 = this.WY * 5 * 10;
      int var3 = var1 + 50;
      int var4 = var2 + 50;

      for (RoomDef var6 : this.UnexploredRooms) {
         var6.IndoorZombies--;
      }

      this.UnexploredRooms.clear();
      this.bLoaded = true;

      for (int var13 = 1; var13 < 8; var13++) {
         for (int var16 = -1; var16 < 51; var16++) {
            IsoGridSquare var7 = ServerMap.instance.getGridSquare(var1 + var16, var2 - 1, var13);
            if (var7 != null && !var7.getObjects().isEmpty()) {
               IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var7.x, var7.y, var13);
            } else if (var16 >= 0 && var16 < 50) {
               var7 = ServerMap.instance.getGridSquare(var1 + var16, var2, var13);
               if (var7 != null && !var7.getObjects().isEmpty()) {
                  IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var7.x, var7.y, var13);
               }
            }

            var7 = ServerMap.instance.getGridSquare(var1 + var16, var2 + 50, var13);
            if (var7 != null && !var7.getObjects().isEmpty()) {
               IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var7.x, var7.y, var13);
            } else if (var16 >= 0 && var16 < 50) {
               ServerMap.instance.getGridSquare(var1 + var16, var2 + 50 - 1, var13);
               if (var7 != null && !var7.getObjects().isEmpty()) {
                  IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var7.x, var7.y, var13);
               }
            }
         }

         for (int var17 = 0; var17 < 50; var17++) {
            IsoGridSquare var25 = ServerMap.instance.getGridSquare(var1 - 1, var2 + var17, var13);
            if (var25 != null && !var25.getObjects().isEmpty()) {
               IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var25.x, var25.y, var13);
            } else {
               var25 = ServerMap.instance.getGridSquare(var1, var2 + var17, var13);
               if (var25 != null && !var25.getObjects().isEmpty()) {
                  IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var25.x, var25.y, var13);
               }
            }

            var25 = ServerMap.instance.getGridSquare(var1 + 50, var2 + var17, var13);
            if (var25 != null && !var25.getObjects().isEmpty()) {
               IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var25.x, var25.y, var13);
            } else {
               var25 = ServerMap.instance.getGridSquare(var1 + 50 - 1, var2 + var17, var13);
               if (var25 != null && !var25.getObjects().isEmpty()) {
                  IsoWorld.instance.CurrentCell.EnsureSurroundNotNull(var25.x, var25.y, var13);
               }
            }
         }
      }

      for (int var14 = 0; var14 < 8; var14++) {
         for (int var18 = 0; var18 < 50; var18++) {
            IsoGridSquare var29 = ServerMap.instance.getGridSquare(var1 + var18, var2 + 0, var14);
            if (var29 != null) {
               var29.RecalcAllWithNeighbours(true);
            }

            var29 = ServerMap.instance.getGridSquare(var1 + var18, var4 - 1, var14);
            if (var29 != null) {
               var29.RecalcAllWithNeighbours(true);
            }
         }

         for (int var19 = 0; var19 < 50; var19++) {
            IsoGridSquare var31 = ServerMap.instance.getGridSquare(var1 + 0, var2 + var19, var14);
            if (var31 != null) {
               var31.RecalcAllWithNeighbours(true);
            }

            var31 = ServerMap.instance.getGridSquare(var3 - 1, var2 + var19, var14);
            if (var31 != null) {
               var31.RecalcAllWithNeighbours(true);
            }
         }
      }

      byte var15 = 100;

      for (int var20 = 0; var20 < 5; var20++) {
         for (int var33 = 0; var33 < 5; var33++) {
            IsoChunk var8 = this.chunks[var20][var33];
            if (var8 != null) {
               var8.bLoaded = true;

               for (int var9 = 0; var9 < var15; var9++) {
                  for (int var10 = 0; var10 <= var8.maxLevel; var10++) {
                     IsoGridSquare var11 = var8.squares[var10][var9];
                     if (var11 != null) {
                        if (var11.getRoom() != null && !var11.getRoom().def.bExplored) {
                           this.UnexploredRooms.add(var11.getRoom().def);
                        }

                        var11.propertiesDirty = true;
                     }
                  }
               }
            }
         }
      }

      for (int var21 = 0; var21 < 5; var21++) {
         for (int var34 = 0; var34 < 5; var34++) {
            if (this.chunks[var21][var34] != null) {
               this.chunks[var21][var34].doLoadGridsquare();
            }
         }
      }

      for (RoomDef var35 : this.UnexploredRooms) {
         var35.IndoorZombies++;
         if (var35.IndoorZombies == 1) {
            try {
               VirtualZombieManager.instance.tryAddIndoorZombies(var35, false);
            } catch (Exception var12) {
               var12.printStackTrace();
            }
         }
      }

      this.bLoaded = true;
   }

   public void Unload() {
      if (this.bLoaded) {
         if (ServerMap.MapLoading) {
            DebugLog.log(
               DebugType.MapLoading,
               "Unloading cell: "
                  + this.WX
                  + ", "
                  + this.WY
                  + " ("
                  + ServerMap.instance.toWorldCellX(this.WX)
                  + ", "
                  + ServerMap.instance.toWorldCellX(this.WY)
                  + ")"
            );
         }

         for (int var1 = 0; var1 < 5; var1++) {
            for (int var2 = 0; var2 < 5; var2++) {
               IsoChunk var3 = this.chunks[var1][var2];
               if (var3 != null) {
                  var3.removeFromWorld();
                  var3.m_loadVehiclesObject = null;

                  for (int var4 = 0; var4 < var3.vehicles.size(); var4++) {
                     BaseVehicle var5 = (BaseVehicle)var3.vehicles.get(var4);
                     VehiclesDB2.instance.updateVehicle(var5);
                  }

                  chunkLoader.addSaveUnloadedJob(var3);
                  this.chunks[var1][var2] = null;
               }
            }
         }

         for (RoomDef var7 : this.UnexploredRooms) {
            if (var7.IndoorZombies == 1) {
            }

            var7.IndoorZombies--;
         }
      }
   }

   public void Save() {
      if (this.bLoaded) {
         for (int var1 = 0; var1 < 5; var1++) {
            for (int var2 = 0; var2 < 5; var2++) {
               IsoChunk var3 = this.chunks[var1][var2];
               if (var3 != null) {
                  try {
                     chunkLoader.addSaveLoadedJob(var3);

                     for (int var4 = 0; var4 < var3.vehicles.size(); var4++) {
                        BaseVehicle var5 = (BaseVehicle)var3.vehicles.get(var4);
                        VehiclesDB2.instance.updateVehicle(var5);
                     }
                  } catch (Exception var6) {
                     var6.printStackTrace();
                     LoggerManager.getLogger("map").write(var6);
                  }
               }
            }
         }

         chunkLoader.updateSaved();
      }
   }

   public void update() {
      for (int var1 = 0; var1 < 5; var1++) {
         for (int var2 = 0; var2 < 5; var2++) {
            IsoChunk var3 = this.chunks[var1][var2];
            if (var3 != null) {
               var3.update();
            }
         }
      }

      this.bPhysicsCheck = false;
   }

   public IsoChunk getChunk(int var1, int var2) {
      if (var1 >= 0 && var1 < 5 && var2 >= 0 && var2 < 5) {
         IsoChunk var3 = this.chunks[var1][var2];
         if (var3 != null) {
            return var3;
         }
      }

      return null;
   }

   public int getWX() {
      return this.WX;
   }

   public int getWY() {
      return this.WY;
   }
}
