#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/LosUtil/TestResults.h"

namespace zombie {
namespace iso {


class LosUtil {
public:
    static int XSIZE = 200;
    static int YSIZE = 200;
    static int ZSIZE = 16;
   public static byte[][][][] cachedresults = new byte[XSIZE][YSIZE][ZSIZE][4];
   public static boolean[] cachecleared = new boolean[4];

    static void init(int var0, int var1) {
      XSIZE = Math.min(var0, 200);
      YSIZE = Math.min(var1, 200);
      cachedresults = new byte[XSIZE][YSIZE][ZSIZE][4];
   }

    static TestResults lineClear(IsoCell var0, int var1, int var2, int var3, int var4, int var5, int var6, bool var7) {
    return lineClear();
   }

    static TestResults lineClear(IsoCell var0, int var1, int var2, int var3, int var4, int var5, int var6, bool var7, int var8) {
      if (var6 == var3 - 1) {
    IsoGridSquare var9 = var0.getGridSquare(var4, var5, var6);
         if (var9 != nullptr && var9.HasElevatedFloor()) {
            var6 = var3;
         }
      }

    TestResults var25 = TestResults.Clear;
    int var10 = var5 - var2;
    int var11 = var4 - var1;
    int var12 = var6 - var3;
    float var13 = 0.5F;
    float var14 = 0.5F;
    IsoGridSquare var18 = var0.getGridSquare(var1, var2, var3);
    int var19 = 0;
    bool var20 = false;
      if (Math.abs(var11) > Math.abs(var10) && Math.abs(var11) > Math.abs(var12)) {
    float var41 = (float)var10 / var11;
    float var46 = (float)var12 / var11;
         var13 += var2;
         var14 += var3;
         var11 = var11 < 0 ? -1 : 1;
         var41 *= var11;

         for (float var47 = var46 * var11; var1 != var4; var20 = false) {
            var1 += var11;
            var13 += var41;
            var14 += var47;
    IsoGridSquare var49 = var0.getGridSquare(var1, (int)var13, (int)var14);
            if (var49 != nullptr && var18 != nullptr) {
    TestResults var51 = var49.testVisionAdjacent(var18.getX() - var49.getX(), var18.getY() - var49.getY(), var18.getZ() - var49.getZ(), true, var7);
               if (var51 == TestResults.ClearThroughWindow) {
                  var20 = true;
               }

               if (var51 != TestResults.Blocked
                  && var25 != TestResults.Clear
                  && (var51 != TestResults.ClearThroughWindow || var25 != TestResults.ClearThroughOpenDoor)) {
                  if (var51 == TestResults.ClearThroughClosedDoor && var25 == TestResults.ClearThroughOpenDoor) {
                     var25 = var51;
                  }
               } else {
                  var25 = var51;
               }

               if (var25 == TestResults.Blocked) {
                  return TestResults.Blocked;
               }

               if (var20) {
                  if (var19 > var8) {
                     return TestResults.Blocked;
                  }

                  var19 = 0;
               }
            }

            var18 = var49;
    int var36 = (int)var13;
    int var37 = (int)var14;
            var19++;
         }
      } else if (Math.abs(var10) >= Math.abs(var11) && Math.abs(var10) > Math.abs(var12)) {
    float var39 = (float)var11 / var10;
    float var44 = (float)var12 / var10;
         var13 += var1;
         var14 += var3;
         var10 = var10 < 0 ? -1 : 1;
         var39 *= var10;

         for (float var45 = var44 * var10; var2 != var5; var20 = false) {
            var2 += var10;
            var13 += var39;
            var14 += var45;
    IsoGridSquare var48 = var0.getGridSquare((int)var13, var2, (int)var14);
            if (var48 != nullptr && var18 != nullptr) {
    TestResults var50 = var48.testVisionAdjacent(var18.getX() - var48.getX(), var18.getY() - var48.getY(), var18.getZ() - var48.getZ(), true, var7);
               if (var50 == TestResults.ClearThroughWindow) {
                  var20 = true;
               }

               if (var50 != TestResults.Blocked
                  && var25 != TestResults.Clear
                  && (var50 != TestResults.ClearThroughWindow || var25 != TestResults.ClearThroughOpenDoor)) {
                  if (var50 == TestResults.ClearThroughClosedDoor && var25 == TestResults.ClearThroughOpenDoor) {
                     var25 = var50;
                  }
               } else {
                  var25 = var50;
               }

               if (var25 == TestResults.Blocked) {
                  return TestResults.Blocked;
               }

               if (var20) {
                  if (var19 > var8) {
                     return TestResults.Blocked;
                  }

                  var19 = 0;
               }
            }

            var18 = var48;
    int var35 = (int)var13;
    int var17 = (int)var14;
            var19++;
         }
      } else {
    float var21 = (float)var11 / var12;
    float var22 = (float)var10 / var12;
         var13 += var1;
         var14 += var2;
         var12 = var12 < 0 ? -1 : 1;
         var21 *= var12;

         for (float var43 = var22 * var12; var3 != var6; var20 = false) {
            var3 += var12;
            var13 += var21;
            var14 += var43;
    IsoGridSquare var23 = var0.getGridSquare((int)var13, (int)var14, var3);
            if (var23 != nullptr && var18 != nullptr) {
    TestResults var24 = var23.testVisionAdjacent(var18.getX() - var23.getX(), var18.getY() - var23.getY(), var18.getZ() - var23.getZ(), true, var7);
               if (var24 == TestResults.ClearThroughWindow) {
                  var20 = true;
               }

               if (var24 != TestResults.Blocked
                  && var25 != TestResults.Clear
                  && (var24 != TestResults.ClearThroughWindow || var25 != TestResults.ClearThroughOpenDoor)) {
                  if (var24 == TestResults.ClearThroughClosedDoor && var25 == TestResults.ClearThroughOpenDoor) {
                     var25 = var24;
                  }
               } else {
                  var25 = var24;
               }

               if (var25 == TestResults.Blocked) {
                  return TestResults.Blocked;
               }

               if (var20) {
                  if (var19 > var8) {
                     return TestResults.Blocked;
                  }

                  var19 = 0;
               }
            }

            var18 = var23;
    int var15 = (int)var13;
    int var16 = (int)var14;
            var19++;
         }
      }

    return var25;
   }

    static bool lineClearCollide(int var0, int var1, int var2, int var3, int var4, int var5, bool var6) {
    IsoCell var7 = IsoWorld.instance.CurrentCell;
    int var8 = var1 - var4;
    int var9 = var0 - var3;
    int var10 = var2 - var5;
    float var11 = 0.5F;
    float var12 = 0.5F;
    IsoGridSquare var16 = var7.getGridSquare(var3, var4, var5);
      if (Math.abs(var9) > Math.abs(var8) && Math.abs(var9) > Math.abs(var10)) {
    float var36 = (float)var8 / var9;
    float var41 = (float)var10 / var9;
         var11 += var4;
         var12 += var5;
         var9 = var9 < 0 ? -1 : 1;
         var36 *= var9;
         var41 *= var9;

         while (var3 != var0) {
            var3 += var9;
            var11 += var36;
            var12 += var41;
    IsoGridSquare var44 = var7.getGridSquare(var3, (int)var11, (int)var12);
            if (var44 != nullptr && var16 != nullptr) {
    bool var46 = var44.CalculateCollide(var16, false, false, true, true);
               if (!var6 && var44.isDoorBlockedTo(var16)) {
                  var46 = true;
               }

               if (var46) {
    return true;
               }
            }

            var16 = var44;
    int var31 = (int)var11;
    int var32 = (int)var12;
         }
      } else if (Math.abs(var8) >= Math.abs(var9) && Math.abs(var8) > Math.abs(var10)) {
    float var34 = (float)var9 / var8;
    float var39 = (float)var10 / var8;
         var11 += var3;
         var12 += var5;
         var8 = var8 < 0 ? -1 : 1;
         var34 *= var8;
         var39 *= var8;

         while (var4 != var1) {
            var4 += var8;
            var11 += var34;
            var12 += var39;
    IsoGridSquare var43 = var7.getGridSquare((int)var11, var4, (int)var12);
            if (var43 != nullptr && var16 != nullptr) {
    bool var45 = var43.CalculateCollide(var16, false, false, true, true);
               if (!var6 && var43.isDoorBlockedTo(var16)) {
                  var45 = true;
               }

               if (var45) {
    return true;
               }
            }

            var16 = var43;
    int var30 = (int)var11;
    int var15 = (int)var12;
         }
      } else {
    float var17 = (float)var9 / var10;
    float var18 = (float)var8 / var10;
         var11 += var3;
         var12 += var4;
         var10 = var10 < 0 ? -1 : 1;
         var17 *= var10;
         var18 *= var10;

         while (var5 != var2) {
            var5 += var10;
            var11 += var17;
            var12 += var18;
    IsoGridSquare var19 = var7.getGridSquare((int)var11, (int)var12, var5);
            if (var19 != nullptr && var16 != nullptr) {
    bool var20 = var19.CalculateCollide(var16, false, false, true, true);
               if (var20) {
    return true;
               }
            }

            var16 = var19;
    int var13 = (int)var11;
    int var14 = (int)var12;
         }
      }

    return false;
   }

    static int lineClearCollideCount(IsoGameCharacter var0, IsoCell var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    int var8 = 0;
    int var9 = var3 - var6;
    int var10 = var2 - var5;
    int var11 = var4 - var7;
    float var12 = 0.5F;
    float var13 = 0.5F;
    IsoGridSquare var17 = var1.getGridSquare(var5, var6, var7);
      if (Math.abs(var10) > Math.abs(var9) && Math.abs(var10) > Math.abs(var11)) {
    float var37 = (float)var9 / var10;
    float var42 = (float)var11 / var10;
         var12 += var6;
         var13 += var7;
         var10 = var10 < 0 ? -1 : 1;
         var37 *= var10;
         var42 *= var10;

         while (var5 != var2) {
            var5 += var10;
            var12 += var37;
            var13 += var42;
    IsoGridSquare var45 = var1.getGridSquare(var5, (int)var12, (int)var13);
            if (var45 != nullptr && var17 != nullptr) {
    bool var47 = var17.testCollideAdjacent(var0, var45.getX() - var17.getX(), var45.getY() - var17.getY(), var45.getZ() - var17.getZ());
               if (var47) {
    return var8;
               }
            }

            var8++;
            var17 = var45;
    int var32 = (int)var12;
    int var33 = (int)var13;
         }
      } else if (Math.abs(var9) >= Math.abs(var10) && Math.abs(var9) > Math.abs(var11)) {
    float var35 = (float)var10 / var9;
    float var40 = (float)var11 / var9;
         var12 += var5;
         var13 += var7;
         var9 = var9 < 0 ? -1 : 1;
         var35 *= var9;
         var40 *= var9;

         while (var6 != var3) {
            var6 += var9;
            var12 += var35;
            var13 += var40;
    IsoGridSquare var44 = var1.getGridSquare((int)var12, var6, (int)var13);
            if (var44 != nullptr && var17 != nullptr) {
    bool var46 = var17.testCollideAdjacent(var0, var44.getX() - var17.getX(), var44.getY() - var17.getY(), var44.getZ() - var17.getZ());
               if (var46) {
    return var8;
               }
            }

            var8++;
            var17 = var44;
    int var31 = (int)var12;
    int var16 = (int)var13;
         }
      } else {
    float var18 = (float)var10 / var11;
    float var19 = (float)var9 / var11;
         var12 += var5;
         var13 += var6;
         var11 = var11 < 0 ? -1 : 1;
         var18 *= var11;
         var19 *= var11;

         while (var7 != var4) {
            var7 += var11;
            var12 += var18;
            var13 += var19;
    IsoGridSquare var20 = var1.getGridSquare((int)var12, (int)var13, var7);
            if (var20 != nullptr && var17 != nullptr) {
    bool var21 = var17.testCollideAdjacent(var0, var20.getX() - var17.getX(), var20.getY() - var17.getY(), var20.getZ() - var17.getZ());
               if (var21) {
    return var8;
               }
            }

            var8++;
            var17 = var20;
    int var14 = (int)var12;
    int var15 = (int)var13;
         }
      }

    return var8;
   }

    static TestResults lineClearCached(IsoCell var0, int var1, int var2, int var3, int var4, int var5, int var6, bool var7, int var8) {
      if (var3 == var6 - 1) {
    IsoGridSquare var9 = var0.getGridSquare(var1, var2, var3);
         if (var9 != nullptr && var9.HasElevatedFloor()) {
            var3 = var6;
         }
      }

    int var32 = var4;
    int var10 = var5;
    int var11 = var6;
    int var12 = var2 - var5;
    int var13 = var1 - var4;
    int var14 = var3 - var6;
    int var15 = var13 + XSIZE / 2;
    int var16 = var12 + YSIZE / 2;
    int var17 = var14 + ZSIZE / 2;
      if (var15 >= 0 && var16 >= 0 && var17 >= 0 && var15 < XSIZE && var16 < YSIZE && var17 < ZSIZE) {
    TestResults var18 = TestResults.Clear;
    uint8_t var19 = 1;
         if (cachedresults[var15][var16][var17][var8] != 0) {
            if (cachedresults[var15][var16][var17][var8] == 1) {
               var18 = TestResults.Clear;
            }

            if (cachedresults[var15][var16][var17][var8] == 2) {
               var18 = TestResults.ClearThroughOpenDoor;
            }

            if (cachedresults[var15][var16][var17][var8] == 3) {
               var18 = TestResults.ClearThroughWindow;
            }

            if (cachedresults[var15][var16][var17][var8] == 4) {
               var18 = TestResults.Blocked;
            }

            if (cachedresults[var15][var16][var17][var8] == 5) {
               var18 = TestResults.ClearThroughClosedDoor;
            }

    return var18;
         } else {
    float var20 = 0.5F;
    float var21 = 0.5F;
    IsoGridSquare var25 = var0.getGridSquare(var4, var5, var6);
            if (Math.abs(var13) > Math.abs(var12) && Math.abs(var13) > Math.abs(var14)) {
    float var48 = (float)var12 / var13;
    float var53 = (float)var14 / var13;
               var20 += var5;
               var21 += var6;
               var13 = var13 < 0 ? -1 : 1;
               var48 *= var13;
               var53 *= var13;

               while (var4 != var1) {
                  var4 += var13;
                  var20 += var48;
                  var21 += var53;
    IsoGridSquare var56 = var0.getGridSquare(var4, (int)var20, (int)var21);
                  if (var56 != nullptr && var25 != nullptr) {
                     if (var19 != 4
                        && var56.testVisionAdjacent(var25.getX() - var56.getX(), var25.getY() - var56.getY(), var25.getZ() - var56.getZ(), true, var7)
                           == TestResults.Blocked) {
                        var19 = 4;
                     }

    int var66 = var4 - var32;
    int var77 = (int)var20 - var10;
    int var88 = (int)var21 - var11;
                     var66 += XSIZE / 2;
                     var77 += YSIZE / 2;
                     var88 += ZSIZE / 2;
                     if (cachedresults[var66][var77][var88][var8] == 0) {
                        cachedresults[var66][var77][var88][var8] = (byte)var19;
                     }
                  } else {
    int var64 = var4 - var32;
    int var75 = (int)var20 - var10;
    int var86 = (int)var21 - var11;
                     var64 += XSIZE / 2;
                     var75 += YSIZE / 2;
                     var86 += ZSIZE / 2;
                     if (cachedresults[var64][var75][var86][var8] == 0) {
                        cachedresults[var64][var75][var86][var8] = (byte)var19;
                     }
                  }

                  var25 = var56;
    int var43 = (int)var20;
    int var44 = (int)var21;
               }
            } else if (Math.abs(var12) >= Math.abs(var13) && Math.abs(var12) > Math.abs(var14)) {
    float var46 = (float)var13 / var12;
    float var51 = (float)var14 / var12;
               var20 += var4;
               var21 += var6;
               var12 = var12 < 0 ? -1 : 1;
               var46 *= var12;
               var51 *= var12;

               while (var5 != var2) {
                  var5 += var12;
                  var20 += var46;
                  var21 += var51;
    IsoGridSquare var55 = var0.getGridSquare((int)var20, var5, (int)var21);
                  if (var55 != nullptr && var25 != nullptr) {
                     if (var19 != 4
                        && var55.testVisionAdjacent(var25.getX() - var55.getX(), var25.getY() - var55.getY(), var25.getZ() - var55.getZ(), true, var7)
                           == TestResults.Blocked) {
                        var19 = 4;
                     }

    int var62 = (int)var20 - var32;
    int var73 = var5 - var10;
    int var84 = (int)var21 - var11;
                     var62 += XSIZE / 2;
                     var73 += YSIZE / 2;
                     var84 += ZSIZE / 2;
                     if (cachedresults[var62][var73][var84][var8] == 0) {
                        cachedresults[var62][var73][var84][var8] = (byte)var19;
                     }
                  } else {
    int var60 = (int)var20 - var32;
    int var71 = var5 - var10;
    int var82 = (int)var21 - var11;
                     var60 += XSIZE / 2;
                     var71 += YSIZE / 2;
                     var82 += ZSIZE / 2;
                     if (cachedresults[var60][var71][var82][var8] == 0) {
                        cachedresults[var60][var71][var82][var8] = (byte)var19;
                     }
                  }

                  var25 = var55;
    int var42 = (int)var20;
    int var24 = (int)var21;
               }
            } else {
    float var26 = (float)var13 / var14;
    float var27 = (float)var12 / var14;
               var20 += var4;
               var21 += var5;
               var14 = var14 < 0 ? -1 : 1;
               var26 *= var14;
               var27 *= var14;

               while (var6 != var3) {
                  var6 += var14;
                  var20 += var26;
                  var21 += var27;
    IsoGridSquare var28 = var0.getGridSquare((int)var20, (int)var21, var6);
                  if (var28 != nullptr && var25 != nullptr) {
                     if (var19 != 4
                        && var28.testVisionAdjacent(var25.getX() - var28.getX(), var25.getY() - var28.getY(), var25.getZ() - var28.getZ(), true, var7)
                           == TestResults.Blocked) {
                        var19 = 4;
                     }

    int var58 = (int)var20 - var32;
    int var69 = (int)var21 - var10;
    int var80 = var6 - var11;
                     var58 += XSIZE / 2;
                     var69 += YSIZE / 2;
                     var80 += ZSIZE / 2;
                     if (cachedresults[var58][var69][var80][var8] == 0) {
                        cachedresults[var58][var69][var80][var8] = (byte)var19;
                     }
                  } else {
    int var29 = (int)var20 - var32;
    int var30 = (int)var21 - var10;
    int var31 = var6 - var11;
                     var29 += XSIZE / 2;
                     var30 += YSIZE / 2;
                     var31 += ZSIZE / 2;
                     if (cachedresults[var29][var30][var31][var8] == 0) {
                        cachedresults[var29][var30][var31][var8] = (byte)var19;
                     }
                  }

                  var25 = var28;
    int var22 = (int)var20;
    int var23 = (int)var21;
               }
            }

            if (var19 == 1) {
               cachedresults[var15][var16][var17][var8] = (byte)var19;
               return TestResults.Clear;
            } else if (var19 == 2) {
               cachedresults[var15][var16][var17][var8] = (byte)var19;
               return TestResults.ClearThroughOpenDoor;
            } else if (var19 == 3) {
               cachedresults[var15][var16][var17][var8] = (byte)var19;
               return TestResults.ClearThroughWindow;
            } else if (var19 == 4) {
               cachedresults[var15][var16][var17][var8] = (byte)var19;
               return TestResults.Blocked;
            } else if (var19 == 5) {
               cachedresults[var15][var16][var17][var8] = (byte)var19;
               return TestResults.ClearThroughClosedDoor;
            } else {
               return TestResults.Blocked;
            }
         }
      } else {
         return TestResults.Blocked;
      }
   }

   static {
      for (int var0 = 0; var0 < 4; var0++) {
         cachecleared[var0] = true;
      }
   }
}
} // namespace iso
} // namespace zombie
