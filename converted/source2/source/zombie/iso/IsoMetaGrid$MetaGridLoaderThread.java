package zombie.iso;

import java.io.File;
import java.util.ArrayList;
import zombie.core.Rand;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.iso.RoomDef.RoomRect;
import zombie.util.BufferedRandomAccessFile;
import zombie.util.SharedStrings;

final class IsoMetaGrid$MetaGridLoaderThread extends Thread {
   final SharedStrings sharedStrings;
   final ArrayList<BuildingDef> Buildings;
   final ArrayList<RoomDef> tempRooms;
   int wY;

   IsoMetaGrid$MetaGridLoaderThread(IsoMetaGrid var1, int var2) {
      this.this$0 = var1;
      this.sharedStrings = new SharedStrings();
      this.Buildings = new ArrayList<>();
      this.tempRooms = new ArrayList<>();
      this.wY = var2;
   }

   @Override
   public void run() {
      try {
         this.runInner();
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }
   }

   void runInner() {
      for (int var1 = this.wY; var1 <= this.this$0.maxY; var1 += 8) {
         for (int var2 = this.this$0.minX; var2 <= this.this$0.maxX; var2++) {
            this.loadCell(var2, var1);
         }
      }
   }

   void loadCell(int var1, int var2) {
      IsoMetaCell var3 = new IsoMetaCell(var1, var2);
      this.this$0.Grid[var1 - this.this$0.minX][var2 - this.this$0.minY] = var3;
      String var4 = var1 + "_" + var2 + ".lotheader";
      if (IsoLot.InfoFileNames.containsKey(var4)) {
         LotHeader var5 = (LotHeader)IsoLot.InfoHeaders.get(var4);
         if (var5 != null) {
            File var6 = new File((String)IsoLot.InfoFileNames.get(var4));
            if (var6.exists()) {
               var3.info = var5;

               try {
                  BufferedRandomAccessFile var7 = new BufferedRandomAccessFile(var6.getAbsolutePath(), "r", 4096);

                  try {
                     var5.version = IsoLot.readInt(var7);
                     int var8 = IsoLot.readInt(var7);

                     for (int var9 = 0; var9 < var8; var9++) {
                        String var10 = IsoLot.readString(var7);
                        var5.tilesUsed.add(this.sharedStrings.get(var10.trim()));
                     }

                     var7.read();
                     var5.width = IsoLot.readInt(var7);
                     var5.height = IsoLot.readInt(var7);
                     var5.levels = IsoLot.readInt(var7);
                     int var22 = IsoLot.readInt(var7);

                     for (int var23 = 0; var23 < var22; var23++) {
                        String var11 = IsoLot.readString(var7);
                        RoomDef var12 = new RoomDef(var23, this.sharedStrings.get(var11));
                        var12.level = IsoLot.readInt(var7);
                        int var13 = IsoLot.readInt(var7);

                        for (int var14 = 0; var14 < var13; var14++) {
                           RoomRect var15 = new RoomRect(
                              IsoLot.readInt(var7) + var1 * 300, IsoLot.readInt(var7) + var2 * 300, IsoLot.readInt(var7), IsoLot.readInt(var7)
                           );
                           var12.rects.add(var15);
                        }

                        var12.CalculateBounds();
                        var12.metaID = var12.calculateMetaID(var1, var2);
                        var5.Rooms.put(var12.ID, var12);
                        if (var5.RoomByMetaID.contains(var12.metaID)) {
                           DebugLog.General.error("duplicate RoomDef.metaID for room at %d,%d,%d", new Object[]{var12.x, var12.y, var12.level});
                        }

                        var5.RoomByMetaID.put(var12.metaID, var12);
                        var5.RoomList.add(var12);
                        var3.addRoom(var12, var1 * 300, var2 * 300);
                        int var31 = IsoLot.readInt(var7);

                        for (int var34 = 0; var34 < var31; var34++) {
                           int var16 = IsoLot.readInt(var7);
                           int var17 = IsoLot.readInt(var7);
                           int var18 = IsoLot.readInt(var7);
                           var12.objects.add(new MetaObject(var16, var17 + var1 * 300 - var12.x, var18 + var2 * 300 - var12.y, var12));
                        }

                        var12.bLightsActive = Rand.Next(2) == 0;
                     }

                     int var24 = IsoLot.readInt(var7);

                     for (int var25 = 0; var25 < var24; var25++) {
                        BuildingDef var27 = new BuildingDef();
                        int var29 = IsoLot.readInt(var7);
                        var27.ID = var25;

                        for (int var32 = 0; var32 < var29; var32++) {
                           RoomDef var35 = (RoomDef)var5.Rooms.get(IsoLot.readInt(var7));
                           var35.building = var27;
                           if (var35.isEmptyOutside()) {
                              var27.emptyoutside.add(var35);
                           } else {
                              var27.rooms.add(var35);
                           }
                        }

                        var27.CalculateBounds(this.tempRooms);
                        var27.metaID = var27.calculateMetaID(var1, var2);
                        var5.Buildings.add(var27);
                        var5.BuildingByMetaID.put(var27.metaID, var27);
                        this.Buildings.add(var27);
                     }

                     for (int var26 = 0; var26 < 30; var26++) {
                        for (int var28 = 0; var28 < 30; var28++) {
                           int var30 = var7.read();
                           IsoMetaChunk var33 = var3.getChunk(var26, var28);
                           var33.setZombieIntensity(var30);
                        }
                     }
                  } catch (Throwable var20) {
                     try {
                        var7.close();
                     } catch (Throwable var19) {
                        var20.addSuppressed(var19);
                     }

                     throw var20;
                  }

                  var7.close();
               } catch (Exception var21) {
                  DebugLog.log("ERROR loading " + var6.getAbsolutePath());
                  ExceptionLogger.logException(var21);
               }
            }
         }
      }
   }

   void postLoad() {
      this.this$0.Buildings.addAll(this.Buildings);
      this.Buildings.clear();
      this.sharedStrings.clear();
      this.tempRooms.clear();
   }
}
