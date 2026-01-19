package zombie.iso;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import zombie.core.properties.PropertyContainer;
import zombie.iso.IsoRoofFixer.1;
import zombie.iso.IsoRoofFixer.PlaceFloorInfo;
import zombie.iso.RoomDef.RoomRect;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.SpriteDetails.IsoObjectType;
import zombie.iso.areas.IsoRoom;
import zombie.iso.sprite.IsoSprite;

public final class IsoRoofFixer {
   private static final boolean PER_ROOM_MODE = true;
   private static final int MAX_Z = 8;
   private static final int SCAN_RANGE = 3;
   private static final boolean ALWAYS_INVIS_FLOORS = false;
   private static boolean roofTileGlassCacheDirty = true;
   private static boolean roofTileIsGlass = false;
   private static IsoSprite roofTileCache;
   private static int roofTilePlaceFloorIndexCache = 0;
   private static String invisFloor = "invisible_01_0";
   private static Map<Integer, String> roofGroups = new HashMap<>();
   private static PlaceFloorInfo[] placeFloorInfos = new PlaceFloorInfo[10000];
   private static int floorInfoIndex = 0;
   private static IsoGridSquare[] sqCache;
   private static IsoRoom workingRoom;
   private static int[] interiorAirSpaces;
   private static final int I_UNCHECKED = 0;
   private static final int I_TRUE = 1;
   private static final int I_FALSE = 2;

   private static void ensureCapacityFloorInfos() {
      if (floorInfoIndex == placeFloorInfos.length) {
         PlaceFloorInfo[] var0 = placeFloorInfos;
         placeFloorInfos = new PlaceFloorInfo[placeFloorInfos.length + 400];
         System.arraycopy(var0, 0, placeFloorInfos, 0, var0.length);
      }
   }

   private static void setRoofTileCache(IsoObject var0) {
      IsoSprite var1 = var0 != null ? var0.sprite : null;
      if (roofTileCache != var1) {
         roofTileCache = var1;
         roofTilePlaceFloorIndexCache = 0;
         if (var1 != null && var1.getProperties() != null && var1.getProperties().Val("RoofGroup") != null) {
            try {
               int var2 = Integer.parseInt(var1.getProperties().Val("RoofGroup"));
               if (roofGroups.containsKey(var2)) {
                  roofTilePlaceFloorIndexCache = var2;
               }
            } catch (Exception var3) {
            }
         }

         roofTileGlassCacheDirty = true;
      }
   }

   private static boolean isRoofTileCacheGlass() {
      if (roofTileGlassCacheDirty) {
         roofTileIsGlass = false;
         if (roofTileCache != null) {
            PropertyContainer var0 = roofTileCache.getProperties();
            if (var0 != null) {
               String var1 = var0.Val("Material");
               roofTileIsGlass = var1 != null && var1.equalsIgnoreCase("glass");
            }
         }

         roofTileGlassCacheDirty = false;
      }

      return roofTileIsGlass;
   }

   public static void FixRoofsAt(IsoGridSquare var0) {
      try {
         FixRoofsPerRoomAt(var0);
      } catch (Exception var2) {
         var2.printStackTrace();
      }
   }

   private static void FixRoofsPerRoomAt(IsoGridSquare var0) {
      floorInfoIndex = 0;
      if (var0.getZ() > 0 && !var0.TreatAsSolidFloor() && var0.getRoom() == null) {
         IsoRoom var1 = getRoomBelow(var0);
         if (var1 != null && !var1.def.isRoofFixed()) {
            resetInteriorSpaceCache();
            workingRoom = var1;
            ArrayList var2 = var1.getSquares();

            for (int var5 = 0; var5 < var2.size(); var5++) {
               IsoGridSquare var3 = (IsoGridSquare)var2.get(var5);
               IsoGridSquare var4 = getRoofFloorForColumn(var3);
               if (var4 != null) {
                  ensureCapacityFloorInfos();
                  placeFloorInfos[floorInfoIndex++].set(var4, roofTilePlaceFloorIndexCache);
               }
            }

            var1.def.setRoofFixed(true);
         }
      }

      for (int var6 = 0; var6 < floorInfoIndex; var6++) {
         placeFloorInfos[var6].square.addFloor(roofGroups.get(placeFloorInfos[var6].floorType));
      }
   }

   private static void clearSqCache() {
      for (int var0 = 0; var0 < sqCache.length; var0++) {
         sqCache[var0] = null;
      }
   }

   private static IsoGridSquare getRoofFloorForColumn(IsoGridSquare var0) {
      if (var0 == null) {
         return null;
      } else {
         IsoCell var1 = IsoCell.getInstance();
         int var3 = 0;
         boolean var4 = false;
         int var5 = 7;

         while (true) {
            label163: {
               if (var5 >= var0.getZ() + 1) {
                  IsoGridSquare var2 = var1.getGridSquare(var0.x, var0.y, var5);
                  if (var2 == null) {
                     if (var5 == var0.getZ() + 1 && var5 > 0 && !isStairsBelow(var0.x, var0.y, var5)) {
                        var2 = IsoGridSquare.getNew(var1, null, var0.x, var0.y, var5);
                        var1.ConnectNewSquare(var2, false);
                        var2.EnsureSurroundNotNull();
                        var2.RecalcAllWithNeighbours(true);
                        sqCache[var3++] = var2;
                     }

                     var4 = true;
                     break label163;
                  }

                  if (var2.TreatAsSolidFloor()) {
                     if (var2.getRoom() == null) {
                        IsoObject var6 = var2.getFloor();
                        if (var6 == null || !isObjectRoof(var6) || var6.getProperties() == null) {
                           break;
                        }

                        PropertyContainer var7 = var6.getProperties();
                        if (var7.Is(IsoFlagType.FloorHeightOneThird) || var7.Is(IsoFlagType.FloorHeightTwoThirds)) {
                           break;
                        }

                        IsoGridSquare var8 = var1.getGridSquare(var0.x, var0.y, var5 - 1);
                        if (var8 == null || var8.getRoom() != null) {
                           break;
                        }

                        var4 = false;
                        break label163;
                     }

                     if (var4) {
                        var2 = IsoGridSquare.getNew(var1, null, var0.x, var0.y, var5 + 1);
                        var1.ConnectNewSquare(var2, false);
                        var2.EnsureSurroundNotNull();
                        var2.RecalcAllWithNeighbours(true);
                        sqCache[var3++] = var2;
                     }
                  } else if (!var2.HasStairsBelow()) {
                     var4 = false;
                     sqCache[var3++] = var2;
                     break label163;
                  }
               }

               if (var3 == 0) {
                  return null;
               }

               for (int var17 = 0; var17 < var3; var17++) {
                  IsoGridSquare var13 = sqCache[var17];
                  if (var13.getRoom() == null && isInteriorAirSpace(var13.getX(), var13.getY(), var13.getZ())) {
                     return null;
                  }

                  if (isRoofAt(var13, true)) {
                     return var13;
                  }

                  for (int var18 = var13.x - 3; var18 <= var13.x + 3; var18++) {
                     for (int var19 = var13.y - 3; var19 <= var13.y + 3; var19++) {
                        if (var18 != var13.x || var19 != var13.y) {
                           IsoGridSquare var9 = var1.getGridSquare(var18, var19, var13.z);
                           if (var9 != null) {
                              for (int var10 = 0; var10 < var9.getObjects().size(); var10++) {
                                 IsoObject var15 = (IsoObject)var9.getObjects().get(var10);
                                 if (isObjectRoofNonFlat(var15)) {
                                    setRoofTileCache(var15);
                                    return var13;
                                 }
                              }

                              IsoGridSquare var20 = var1.getGridSquare(var9.x, var9.y, var9.z + 1);
                              if (var20 != null && var20.getObjects().size() > 0) {
                                 for (int var11 = 0; var11 < var20.getObjects().size(); var11++) {
                                    IsoObject var16 = (IsoObject)var20.getObjects().get(var11);
                                    if (isObjectRoofFlatFloor(var16)) {
                                       setRoofTileCache(var16);
                                       return var13;
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }

               return null;
            }

            var5--;
         }

         return null;
      }
   }

   private static void FixRoofsPerTileAt(IsoGridSquare var0) {
      if (var0.getZ() > 0 && !var0.TreatAsSolidFloor() && var0.getRoom() == null && hasRoomBelow(var0) && (isRoofAt(var0, true) || scanIsRoofAt(var0, true))) {
         if (isRoofTileCacheGlass()) {
            var0.addFloor(invisFloor);
         } else {
            var0.addFloor("carpentry_02_58");
         }
      }
   }

   private static boolean scanIsRoofAt(IsoGridSquare var0, boolean var1) {
      if (var0 == null) {
         return false;
      } else {
         for (int var2 = var0.x - 3; var2 <= var0.x + 3; var2++) {
            for (int var3 = var0.y - 3; var3 <= var0.y + 3; var3++) {
               if (var2 != var0.x || var3 != var0.y) {
                  IsoGridSquare var4 = var0.getCell().getGridSquare(var2, var3, var0.z);
                  if (var4 != null && isRoofAt(var4, var1)) {
                     return true;
                  }
               }
            }
         }

         return false;
      }
   }

   private static boolean isRoofAt(IsoGridSquare var0, boolean var1) {
      if (var0 == null) {
         return false;
      } else {
         for (int var3 = 0; var3 < var0.getObjects().size(); var3++) {
            IsoObject var2 = (IsoObject)var0.getObjects().get(var3);
            if (isObjectRoofNonFlat(var2)) {
               setRoofTileCache(var2);
               return true;
            }
         }

         if (var1) {
            IsoGridSquare var6 = var0.getCell().getGridSquare(var0.x, var0.y, var0.z + 1);
            if (var6 != null && var6.getObjects().size() > 0) {
               for (int var4 = 0; var4 < var6.getObjects().size(); var4++) {
                  IsoObject var5 = (IsoObject)var6.getObjects().get(var4);
                  if (isObjectRoofFlatFloor(var5)) {
                     setRoofTileCache(var5);
                     return true;
                  }
               }
            }
         }

         return false;
      }
   }

   private static boolean isObjectRoof(IsoObject var0) {
      return var0 != null
         && (var0.getType() == IsoObjectType.WestRoofT || var0.getType() == IsoObjectType.WestRoofB || var0.getType() == IsoObjectType.WestRoofM);
   }

   private static boolean isObjectRoofNonFlat(IsoObject var0) {
      if (isObjectRoof(var0)) {
         PropertyContainer var1 = var0.getProperties();
         if (var1 != null) {
            return !var1.Is(IsoFlagType.solidfloor) || var1.Is(IsoFlagType.FloorHeightOneThird) || var1.Is(IsoFlagType.FloorHeightTwoThirds);
         }
      }

      return false;
   }

   private static boolean isObjectRoofFlatFloor(IsoObject var0) {
      if (isObjectRoof(var0)) {
         PropertyContainer var1 = var0.getProperties();
         if (var1 != null && var1.Is(IsoFlagType.solidfloor)) {
            return !var1.Is(IsoFlagType.FloorHeightOneThird) && !var1.Is(IsoFlagType.FloorHeightTwoThirds);
         }
      }

      return false;
   }

   private static boolean hasRoomBelow(IsoGridSquare var0) {
      return getRoomBelow(var0) != null;
   }

   private static IsoRoom getRoomBelow(IsoGridSquare var0) {
      if (var0 == null) {
         return null;
      } else {
         for (int var2 = var0.z - 1; var2 >= 0; var2--) {
            IsoGridSquare var1 = var0.getCell().getGridSquare(var0.x, var0.y, var2);
            if (var1 != null) {
               if (var1.TreatAsSolidFloor() && var1.getRoom() == null) {
                  return null;
               }

               if (var1.getRoom() != null) {
                  return var1.getRoom();
               }
            }
         }

         return null;
      }
   }

   private static boolean isStairsBelow(int var0, int var1, int var2) {
      if (var2 == 0) {
         return false;
      } else {
         IsoCell var3 = IsoCell.getInstance();
         IsoGridSquare var4 = var3.getGridSquare(var0, var1, var2 - 1);
         return var4 != null && var4.HasStairs();
      }
   }

   private static void resetInteriorSpaceCache() {
      for (int var0 = 0; var0 < interiorAirSpaces.length; var0++) {
         interiorAirSpaces[var0] = 0;
      }
   }

   private static boolean isInteriorAirSpace(int var0, int var1, int var2) {
      if (interiorAirSpaces[var2] != 0) {
         return interiorAirSpaces[var2] == 1;
      } else {
         ArrayList var3 = workingRoom.getSquares();
         boolean var4 = false;
         if (var3.size() > 0 && var2 > ((IsoGridSquare)var3.get(0)).getZ()) {
            for (int var5 = 0; var5 < workingRoom.rects.size(); var5++) {
               RoomRect var6 = (RoomRect)workingRoom.rects.get(var5);

               for (int var7 = var6.getX(); var7 < var6.getX2(); var7++) {
                  if (hasRailing(var7, var6.getY(), var2, IsoDirections.N) || hasRailing(var7, var6.getY2() - 1, var2, IsoDirections.S)) {
                     var4 = true;
                     break;
                  }
               }

               if (var4) {
                  break;
               }

               for (int var8 = var6.getY(); var8 < var6.getY2(); var8++) {
                  if (hasRailing(var6.getX(), var8, var2, IsoDirections.W) || hasRailing(var6.getX2() - 1, var8, var2, IsoDirections.E)) {
                     var4 = true;
                     break;
                  }
               }
            }
         }

         interiorAirSpaces[var2] = var4 ? 1 : 2;
         return var4;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private static boolean hasRailing(int var0, int var1, int var2, IsoDirections var3) {
      IsoCell var4 = IsoCell.getInstance();
      IsoGridSquare var5 = var4.getGridSquare(var0, var1, var2);
      if (var5 == null) {
         return false;
      } else {
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var3.ordinal()]) {
            case 1:
               return var5.isHoppableTo(var4.getGridSquare(var0, var1 - 1, var2));
            case 2:
               return var5.isHoppableTo(var4.getGridSquare(var0 + 1, var1, var2));
            case 3:
               return var5.isHoppableTo(var4.getGridSquare(var0, var1 + 1, var2));
            case 4:
               return var5.isHoppableTo(var4.getGridSquare(var0 - 1, var1, var2));
            default:
               return false;
         }
      }
   }

   static {
      roofGroups.put(0, "carpentry_02_57");
      roofGroups.put(1, "roofs_01_22");
      roofGroups.put(2, "roofs_01_54");
      roofGroups.put(3, "roofs_02_22");
      roofGroups.put(4, invisFloor);
      roofGroups.put(5, "roofs_03_22");
      roofGroups.put(6, "roofs_03_54");
      roofGroups.put(7, "roofs_04_22");
      roofGroups.put(8, "roofs_04_54");
      roofGroups.put(9, "roofs_05_22");
      roofGroups.put(10, "roofs_05_54");

      for (int var0 = 0; var0 < placeFloorInfos.length; var0++) {
         placeFloorInfos[var0] = new PlaceFloorInfo();
      }

      sqCache = new IsoGridSquare[8];
      interiorAirSpaces = new int[8];
   }
}
