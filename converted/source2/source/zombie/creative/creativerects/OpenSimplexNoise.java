package zombie.creative.creativerects;

public class OpenSimplexNoise {
   private static final double STRETCH_CONSTANT_2D = -0.211324865405187;
   private static final double SQUISH_CONSTANT_2D = 0.366025403784439;
   private static final double STRETCH_CONSTANT_3D = -0.16666666666666666;
   private static final double SQUISH_CONSTANT_3D = 0.3333333333333333;
   private static final double STRETCH_CONSTANT_4D = -0.138196601125011;
   private static final double SQUISH_CONSTANT_4D = 0.309016994374947;
   private static final double NORM_CONSTANT_2D = 47.0;
   private static final double NORM_CONSTANT_3D = 103.0;
   private static final double NORM_CONSTANT_4D = 30.0;
   private static final long DEFAULT_SEED = 0L;
   private short[] perm;
   private short[] permGradIndex3D;
   private static byte[] gradients2D = new byte[]{5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5};
   private static byte[] gradients3D = new byte[]{
      -11,
      4,
      4,
      -4,
      11,
      4,
      -4,
      4,
      11,
      11,
      4,
      4,
      4,
      11,
      4,
      4,
      4,
      11,
      -11,
      -4,
      4,
      -4,
      -11,
      4,
      -4,
      -4,
      11,
      11,
      -4,
      4,
      4,
      -11,
      4,
      4,
      -4,
      11,
      -11,
      4,
      -4,
      -4,
      11,
      -4,
      -4,
      4,
      -11,
      11,
      4,
      -4,
      4,
      11,
      -4,
      4,
      4,
      -11,
      -11,
      -4,
      -4,
      -4,
      -11,
      -4,
      -4,
      -4,
      -11,
      11,
      -4,
      -4,
      4,
      -11,
      -4,
      4,
      -4,
      -11
   };
   private static byte[] gradients4D = new byte[]{
      3,
      1,
      1,
      1,
      1,
      3,
      1,
      1,
      1,
      1,
      3,
      1,
      1,
      1,
      1,
      3,
      -3,
      1,
      1,
      1,
      -1,
      3,
      1,
      1,
      -1,
      1,
      3,
      1,
      -1,
      1,
      1,
      3,
      3,
      -1,
      1,
      1,
      1,
      -3,
      1,
      1,
      1,
      -1,
      3,
      1,
      1,
      -1,
      1,
      3,
      -3,
      -1,
      1,
      1,
      -1,
      -3,
      1,
      1,
      -1,
      -1,
      3,
      1,
      -1,
      -1,
      1,
      3,
      3,
      1,
      -1,
      1,
      1,
      3,
      -1,
      1,
      1,
      1,
      -3,
      1,
      1,
      1,
      -1,
      3,
      -3,
      1,
      -1,
      1,
      -1,
      3,
      -1,
      1,
      -1,
      1,
      -3,
      1,
      -1,
      1,
      -1,
      3,
      3,
      -1,
      -1,
      1,
      1,
      -3,
      -1,
      1,
      1,
      -1,
      -3,
      1,
      1,
      -1,
      -1,
      3,
      -3,
      -1,
      -1,
      1,
      -1,
      -3,
      -1,
      1,
      -1,
      -1,
      -3,
      1,
      -1,
      -1,
      -1,
      3,
      3,
      1,
      1,
      -1,
      1,
      3,
      1,
      -1,
      1,
      1,
      3,
      -1,
      1,
      1,
      1,
      -3,
      -3,
      1,
      1,
      -1,
      -1,
      3,
      1,
      -1,
      -1,
      1,
      3,
      -1,
      -1,
      1,
      1,
      -3,
      3,
      -1,
      1,
      -1,
      1,
      -3,
      1,
      -1,
      1,
      -1,
      3,
      -1,
      1,
      -1,
      1,
      -3,
      -3,
      -1,
      1,
      -1,
      -1,
      -3,
      1,
      -1,
      -1,
      -1,
      3,
      -1,
      -1,
      -1,
      1,
      -3,
      3,
      1,
      -1,
      -1,
      1,
      3,
      -1,
      -1,
      1,
      1,
      -3,
      -1,
      1,
      1,
      -1,
      -3,
      -3,
      1,
      -1,
      -1,
      -1,
      3,
      -1,
      -1,
      -1,
      1,
      -3,
      -1,
      -1,
      1,
      -1,
      -3,
      3,
      -1,
      -1,
      -1,
      1,
      -3,
      -1,
      -1,
      1,
      -1,
      -3,
      -1,
      1,
      -1,
      -1,
      -3,
      -3,
      -1,
      -1,
      -1,
      -1,
      -3,
      -1,
      -1,
      -1,
      -1,
      -3,
      -1,
      -1,
      -1,
      -1,
      -3
   };

   public OpenSimplexNoise() {
      this(0L);
   }

   public OpenSimplexNoise(short[] var1) {
      this.perm = var1;
      this.permGradIndex3D = new short[256];

      for (int var2 = 0; var2 < 256; var2++) {
         this.permGradIndex3D[var2] = (short)(var1[var2] % (gradients3D.length / 3) * 3);
      }
   }

   public OpenSimplexNoise(long var1) {
      this.perm = new short[256];
      this.permGradIndex3D = new short[256];
      short[] var3 = new short[256];
      short var4 = 0;

      while (var4 < 256) {
         var3[var4] = var4++;
      }

      var1 = var1 * 6364136223846793005L + 1442695040888963407L;
      var1 = var1 * 6364136223846793005L + 1442695040888963407L;
      var1 = var1 * 6364136223846793005L + 1442695040888963407L;

      for (int var9 = 255; var9 >= 0; var9--) {
         var1 = var1 * 6364136223846793005L + 1442695040888963407L;
         int var5 = (int)((var1 + 31L) % (var9 + 1));
         if (var5 < 0) {
            var5 += var9 + 1;
         }

         this.perm[var9] = var3[var5];
         this.permGradIndex3D[var9] = (short)(this.perm[var9] % (gradients3D.length / 3) * 3);
         var3[var5] = var3[var9];
      }
   }

   public double eval(double var1, double var3) {
      double var5 = (var1 + var3) * -0.211324865405187;
      double var7 = var1 + var5;
      double var9 = var3 + var5;
      int var11 = fastFloor(var7);
      int var12 = fastFloor(var9);
      double var13 = (var11 + var12) * 0.366025403784439;
      double var15 = var11 + var13;
      double var17 = var12 + var13;
      double var19 = var7 - var11;
      double var21 = var9 - var12;
      double var23 = var19 + var21;
      double var25 = var1 - var15;
      double var27 = var3 - var17;
      double var35 = 0.0;
      double var37 = var25 - 1.0 - 0.366025403784439;
      double var39 = var27 - 0.0 - 0.366025403784439;
      double var41 = 2.0 - var37 * var37 - var39 * var39;
      if (var41 > 0.0) {
         var41 *= var41;
         var35 += var41 * var41 * this.extrapolate(var11 + 1, var12 + 0, var37, var39);
      }

      double var43 = var25 - 0.0 - 0.366025403784439;
      double var45 = var27 - 1.0 - 0.366025403784439;
      double var47 = 2.0 - var43 * var43 - var45 * var45;
      if (var47 > 0.0) {
         var47 *= var47;
         var35 += var47 * var47 * this.extrapolate(var11 + 0, var12 + 1, var43, var45);
      }

      double var29;
      double var31;
      int var33;
      int var34;
      if (var23 <= 1.0) {
         double var49 = 1.0 - var23;
         if (!(var49 > var19) && !(var49 > var21)) {
            var33 = var11 + 1;
            var34 = var12 + 1;
            var29 = var25 - 1.0 - 0.732050807568878;
            var31 = var27 - 1.0 - 0.732050807568878;
         } else if (var19 > var21) {
            var33 = var11 + 1;
            var34 = var12 - 1;
            var29 = var25 - 1.0;
            var31 = var27 + 1.0;
         } else {
            var33 = var11 - 1;
            var34 = var12 + 1;
            var29 = var25 + 1.0;
            var31 = var27 - 1.0;
         }
      } else {
         double var55 = 2.0 - var23;
         if (!(var55 < var19) && !(var55 < var21)) {
            var29 = var25;
            var31 = var27;
            var33 = var11;
            var34 = var12;
         } else if (var19 > var21) {
            var33 = var11 + 2;
            var34 = var12 + 0;
            var29 = var25 - 2.0 - 0.732050807568878;
            var31 = var27 + 0.0 - 0.732050807568878;
         } else {
            var33 = var11 + 0;
            var34 = var12 + 2;
            var29 = var25 + 0.0 - 0.732050807568878;
            var31 = var27 - 2.0 - 0.732050807568878;
         }

         var11++;
         var12++;
         var25 = var25 - 1.0 - 0.732050807568878;
         var27 = var27 - 1.0 - 0.732050807568878;
      }

      double var56 = 2.0 - var25 * var25 - var27 * var27;
      if (var56 > 0.0) {
         var56 *= var56;
         var35 += var56 * var56 * this.extrapolate(var11, var12, var25, var27);
      }

      double var51 = 2.0 - var29 * var29 - var31 * var31;
      if (var51 > 0.0) {
         var51 *= var51;
         var35 += var51 * var51 * this.extrapolate(var33, var34, var29, var31);
      }

      return var35 / 47.0;
   }

   public double eval(double var1, double var3, double var5) {
      double var7 = (var1 + var3 + var5) * -0.16666666666666666;
      double var9 = var1 + var7;
      double var11 = var3 + var7;
      double var13 = var5 + var7;
      int var15 = fastFloor(var9);
      int var16 = fastFloor(var11);
      int var17 = fastFloor(var13);
      double var18 = (var15 + var16 + var17) * 0.3333333333333333;
      double var20 = var15 + var18;
      double var22 = var16 + var18;
      double var24 = var17 + var18;
      double var26 = var9 - var15;
      double var28 = var11 - var16;
      double var30 = var13 - var17;
      double var32 = var26 + var28 + var30;
      double var34 = var1 - var20;
      double var36 = var3 - var22;
      double var38 = var5 - var24;
      double var58 = 0.0;
      double var40;
      double var42;
      double var44;
      double var46;
      double var48;
      double var50;
      int var52;
      int var53;
      int var54;
      int var55;
      int var56;
      int var57;
      if (var32 <= 1.0) {
         byte var60 = 1;
         double var61 = var26;
         byte var63 = 2;
         double var64 = var28;
         if (var26 >= var28 && var30 > var28) {
            var64 = var30;
            var63 = 4;
         } else if (var26 < var28 && var30 > var26) {
            var61 = var30;
            var60 = 4;
         }

         double var66 = 1.0 - var32;
         if (!(var66 > var61) && !(var66 > var64)) {
            byte var138 = (byte)(var60 | var63);
            if ((var138 & 1) == 0) {
               var52 = var15;
               var55 = var15 - 1;
               var40 = var34 - 0.6666666666666666;
               var46 = var34 + 1.0 - 0.3333333333333333;
            } else {
               var52 = var55 = var15 + 1;
               var40 = var34 - 1.0 - 0.6666666666666666;
               var46 = var34 - 1.0 - 0.3333333333333333;
            }

            if ((var138 & 2) == 0) {
               var53 = var16;
               var56 = var16 - 1;
               var42 = var36 - 0.6666666666666666;
               var48 = var36 + 1.0 - 0.3333333333333333;
            } else {
               var53 = var56 = var16 + 1;
               var42 = var36 - 1.0 - 0.6666666666666666;
               var48 = var36 - 1.0 - 0.3333333333333333;
            }

            if ((var138 & 4) == 0) {
               var54 = var17;
               var57 = var17 - 1;
               var44 = var38 - 0.6666666666666666;
               var50 = var38 + 1.0 - 0.3333333333333333;
            } else {
               var54 = var57 = var17 + 1;
               var44 = var38 - 1.0 - 0.6666666666666666;
               var50 = var38 - 1.0 - 0.3333333333333333;
            }
         } else {
            byte var68 = var64 > var61 ? var63 : var60;
            if ((var68 & 1) == 0) {
               var52 = var15 - 1;
               var55 = var15;
               var40 = var34 + 1.0;
               var46 = var34;
            } else {
               var52 = var55 = var15 + 1;
               var40 = var46 = var34 - 1.0;
            }

            if ((var68 & 2) == 0) {
               var56 = var16;
               var53 = var16;
               var48 = var36;
               var42 = var36;
               if ((var68 & 1) == 0) {
                  var56 = var16 - 1;
                  var48 = var36 + 1.0;
               } else {
                  var53 = var16 - 1;
                  var42 = var36 + 1.0;
               }
            } else {
               var53 = var56 = var16 + 1;
               var42 = var48 = var36 - 1.0;
            }

            if ((var68 & 4) == 0) {
               var54 = var17;
               var57 = var17 - 1;
               var44 = var38;
               var50 = var38 + 1.0;
            } else {
               var54 = var57 = var17 + 1;
               var44 = var50 = var38 - 1.0;
            }
         }

         double var139 = 2.0 - var34 * var34 - var36 * var36 - var38 * var38;
         if (var139 > 0.0) {
            var139 *= var139;
            var58 += var139 * var139 * this.extrapolate(var15 + 0, var16 + 0, var17 + 0, var34, var36, var38);
         }

         double var70 = var34 - 1.0 - 0.3333333333333333;
         double var72 = var36 - 0.0 - 0.3333333333333333;
         double var74 = var38 - 0.0 - 0.3333333333333333;
         double var76 = 2.0 - var70 * var70 - var72 * var72 - var74 * var74;
         if (var76 > 0.0) {
            var76 *= var76;
            var58 += var76 * var76 * this.extrapolate(var15 + 1, var16 + 0, var17 + 0, var70, var72, var74);
         }

         double var78 = var34 - 0.0 - 0.3333333333333333;
         double var80 = var36 - 1.0 - 0.3333333333333333;
         double var84 = 2.0 - var78 * var78 - var80 * var80 - var74 * var74;
         if (var84 > 0.0) {
            var84 *= var84;
            var58 += var84 * var84 * this.extrapolate(var15 + 0, var16 + 1, var17 + 0, var78, var80, var74);
         }

         double var90 = var38 - 1.0 - 0.3333333333333333;
         double var92 = 2.0 - var78 * var78 - var72 * var72 - var90 * var90;
         if (var92 > 0.0) {
            var92 *= var92;
            var58 += var92 * var92 * this.extrapolate(var15 + 0, var16 + 0, var17 + 1, var78, var72, var90);
         }
      } else if (var32 >= 2.0) {
         byte var125 = 6;
         double var129 = var26;
         byte var132 = 5;
         double var134 = var28;
         if (var26 <= var28 && var30 < var28) {
            var134 = var30;
            var132 = 3;
         } else if (var26 > var28 && var30 < var26) {
            var129 = var30;
            var125 = 3;
         }

         double var136 = 3.0 - var32;
         if (!(var136 < var129) && !(var136 < var134)) {
            byte var142 = (byte)(var125 & var132);
            if ((var142 & 1) != 0) {
               var52 = var15 + 1;
               var55 = var15 + 2;
               var40 = var34 - 1.0 - 0.3333333333333333;
               var46 = var34 - 2.0 - 0.6666666666666666;
            } else {
               var55 = var15;
               var52 = var15;
               var40 = var34 - 0.3333333333333333;
               var46 = var34 - 0.6666666666666666;
            }

            if ((var142 & 2) != 0) {
               var53 = var16 + 1;
               var56 = var16 + 2;
               var42 = var36 - 1.0 - 0.3333333333333333;
               var48 = var36 - 2.0 - 0.6666666666666666;
            } else {
               var56 = var16;
               var53 = var16;
               var42 = var36 - 0.3333333333333333;
               var48 = var36 - 0.6666666666666666;
            }

            if ((var142 & 4) != 0) {
               var54 = var17 + 1;
               var57 = var17 + 2;
               var44 = var38 - 1.0 - 0.3333333333333333;
               var50 = var38 - 2.0 - 0.6666666666666666;
            } else {
               var57 = var17;
               var54 = var17;
               var44 = var38 - 0.3333333333333333;
               var50 = var38 - 0.6666666666666666;
            }
         } else {
            byte var141 = var134 < var129 ? var132 : var125;
            if ((var141 & 1) != 0) {
               var52 = var15 + 2;
               var55 = var15 + 1;
               var40 = var34 - 2.0 - 1.0;
               var46 = var34 - 1.0 - 1.0;
            } else {
               var55 = var15;
               var52 = var15;
               var40 = var46 = var34 - 1.0;
            }

            if ((var141 & 2) != 0) {
               var53 = var56 = var16 + 1;
               var42 = var48 = var36 - 1.0 - 1.0;
               if ((var141 & 1) != 0) {
                  var56++;
                  var48--;
               } else {
                  var53++;
                  var42--;
               }
            } else {
               var56 = var16;
               var53 = var16;
               var42 = var48 = var36 - 1.0;
            }

            if ((var141 & 4) != 0) {
               var54 = var17 + 1;
               var57 = var17 + 2;
               var44 = var38 - 1.0 - 1.0;
               var50 = var38 - 2.0 - 1.0;
            } else {
               var57 = var17;
               var54 = var17;
               var44 = var50 = var38 - 1.0;
            }
         }

         double var143 = var34 - 1.0 - 0.6666666666666666;
         double var145 = var36 - 1.0 - 0.6666666666666666;
         double var147 = var38 - 0.0 - 0.6666666666666666;
         double var149 = 2.0 - var143 * var143 - var145 * var145 - var147 * var147;
         if (var149 > 0.0) {
            var149 *= var149;
            var58 += var149 * var149 * this.extrapolate(var15 + 1, var16 + 1, var17 + 0, var143, var145, var147);
         }

         double var159 = var36 - 0.0 - 0.6666666666666666;
         double var161 = var38 - 1.0 - 0.6666666666666666;
         double var82 = 2.0 - var143 * var143 - var159 * var159 - var161 * var161;
         if (var82 > 0.0) {
            var82 *= var82;
            var58 += var82 * var82 * this.extrapolate(var15 + 1, var16 + 0, var17 + 1, var143, var159, var161);
         }

         double var167 = var34 - 0.0 - 0.6666666666666666;
         double var170 = 2.0 - var167 * var167 - var145 * var145 - var161 * var161;
         if (var170 > 0.0) {
            var170 *= var170;
            var58 += var170 * var170 * this.extrapolate(var15 + 0, var16 + 1, var17 + 1, var167, var145, var161);
         }

         var34 = var34 - 1.0 - 1.0;
         var36 = var36 - 1.0 - 1.0;
         var38 = var38 - 1.0 - 1.0;
         double var173 = 2.0 - var34 * var34 - var36 * var36 - var38 * var38;
         if (var173 > 0.0) {
            var173 *= var173;
            var58 += var173 * var173 * this.extrapolate(var15 + 1, var16 + 1, var17 + 1, var34, var36, var38);
         }
      } else {
         double var144 = var26 + var28;
         byte var62;
         double var126;
         boolean var133;
         if (var144 > 1.0) {
            var126 = var144 - 1.0;
            var62 = 3;
            var133 = true;
         } else {
            var126 = 1.0 - var144;
            var62 = 4;
            var133 = false;
         }

         double var146 = var26 + var30;
         boolean var67;
         double var135;
         byte var137;
         if (var146 > 1.0) {
            var135 = var146 - 1.0;
            var137 = 5;
            var67 = true;
         } else {
            var135 = 1.0 - var146;
            var137 = 2;
            var67 = false;
         }

         double var148 = var28 + var30;
         if (var148 > 1.0) {
            double var152 = var148 - 1.0;
            if (var126 <= var135 && var126 < var152) {
               var62 = 6;
               var133 = true;
            } else if (var126 > var135 && var135 < var152) {
               var137 = 6;
               var67 = true;
            }
         } else {
            double var151 = 1.0 - var148;
            if (var126 <= var135 && var126 < var151) {
               var62 = 1;
               var133 = false;
            } else if (var126 > var135 && var135 < var151) {
               var137 = 1;
               var67 = false;
            }
         }

         if (var133 == var67) {
            if (var133) {
               var40 = var34 - 1.0 - 1.0;
               var42 = var36 - 1.0 - 1.0;
               var44 = var38 - 1.0 - 1.0;
               var52 = var15 + 1;
               var53 = var16 + 1;
               var54 = var17 + 1;
               byte var153 = (byte)(var62 & var137);
               if ((var153 & 1) != 0) {
                  var46 = var34 - 2.0 - 0.6666666666666666;
                  var48 = var36 - 0.6666666666666666;
                  var50 = var38 - 0.6666666666666666;
                  var55 = var15 + 2;
                  var56 = var16;
                  var57 = var17;
               } else if ((var153 & 2) != 0) {
                  var46 = var34 - 0.6666666666666666;
                  var48 = var36 - 2.0 - 0.6666666666666666;
                  var50 = var38 - 0.6666666666666666;
                  var55 = var15;
                  var56 = var16 + 2;
                  var57 = var17;
               } else {
                  var46 = var34 - 0.6666666666666666;
                  var48 = var36 - 0.6666666666666666;
                  var50 = var38 - 2.0 - 0.6666666666666666;
                  var55 = var15;
                  var56 = var16;
                  var57 = var17 + 2;
               }
            } else {
               var40 = var34;
               var42 = var36;
               var44 = var38;
               var52 = var15;
               var53 = var16;
               var54 = var17;
               byte var154 = (byte)(var62 | var137);
               if ((var154 & 1) == 0) {
                  var46 = var34 + 1.0 - 0.3333333333333333;
                  var48 = var36 - 1.0 - 0.3333333333333333;
                  var50 = var38 - 1.0 - 0.3333333333333333;
                  var55 = var15 - 1;
                  var56 = var16 + 1;
                  var57 = var17 + 1;
               } else if ((var154 & 2) == 0) {
                  var46 = var34 - 1.0 - 0.3333333333333333;
                  var48 = var36 + 1.0 - 0.3333333333333333;
                  var50 = var38 - 1.0 - 0.3333333333333333;
                  var55 = var15 + 1;
                  var56 = var16 - 1;
                  var57 = var17 + 1;
               } else {
                  var46 = var34 - 1.0 - 0.3333333333333333;
                  var48 = var36 - 1.0 - 0.3333333333333333;
                  var50 = var38 + 1.0 - 0.3333333333333333;
                  var55 = var15 + 1;
                  var56 = var16 + 1;
                  var57 = var17 - 1;
               }
            }
         } else {
            byte var75;
            byte var155;
            if (var133) {
               var155 = var62;
               var75 = var137;
            } else {
               var155 = var137;
               var75 = var62;
            }

            if ((var155 & 1) == 0) {
               var40 = var34 + 1.0 - 0.3333333333333333;
               var42 = var36 - 1.0 - 0.3333333333333333;
               var44 = var38 - 1.0 - 0.3333333333333333;
               var52 = var15 - 1;
               var53 = var16 + 1;
               var54 = var17 + 1;
            } else if ((var155 & 2) == 0) {
               var40 = var34 - 1.0 - 0.3333333333333333;
               var42 = var36 + 1.0 - 0.3333333333333333;
               var44 = var38 - 1.0 - 0.3333333333333333;
               var52 = var15 + 1;
               var53 = var16 - 1;
               var54 = var17 + 1;
            } else {
               var40 = var34 - 1.0 - 0.3333333333333333;
               var42 = var36 - 1.0 - 0.3333333333333333;
               var44 = var38 + 1.0 - 0.3333333333333333;
               var52 = var15 + 1;
               var53 = var16 + 1;
               var54 = var17 - 1;
            }

            var46 = var34 - 0.6666666666666666;
            var48 = var36 - 0.6666666666666666;
            var50 = var38 - 0.6666666666666666;
            var55 = var15;
            var56 = var16;
            var57 = var17;
            if ((var75 & 1) != 0) {
               var46 -= 2.0;
               var55 = var15 + 2;
            } else if ((var75 & 2) != 0) {
               var48 -= 2.0;
               var56 = var16 + 2;
            } else {
               var50 -= 2.0;
               var57 = var17 + 2;
            }
         }

         double var156 = var34 - 1.0 - 0.3333333333333333;
         double var158 = var36 - 0.0 - 0.3333333333333333;
         double var160 = var38 - 0.0 - 0.3333333333333333;
         double var162 = 2.0 - var156 * var156 - var158 * var158 - var160 * var160;
         if (var162 > 0.0) {
            var162 *= var162;
            var58 += var162 * var162 * this.extrapolate(var15 + 1, var16 + 0, var17 + 0, var156, var158, var160);
         }

         double var165 = var34 - 0.0 - 0.3333333333333333;
         double var168 = var36 - 1.0 - 0.3333333333333333;
         double var88 = 2.0 - var165 * var165 - var168 * var168 - var160 * var160;
         if (var88 > 0.0) {
            var88 *= var88;
            var58 += var88 * var88 * this.extrapolate(var15 + 0, var16 + 1, var17 + 0, var165, var168, var160);
         }

         double var94 = var38 - 1.0 - 0.3333333333333333;
         double var96 = 2.0 - var165 * var165 - var158 * var158 - var94 * var94;
         if (var96 > 0.0) {
            var96 *= var96;
            var58 += var96 * var96 * this.extrapolate(var15 + 0, var16 + 0, var17 + 1, var165, var158, var94);
         }

         double var98 = var34 - 1.0 - 0.6666666666666666;
         double var100 = var36 - 1.0 - 0.6666666666666666;
         double var102 = var38 - 0.0 - 0.6666666666666666;
         double var104 = 2.0 - var98 * var98 - var100 * var100 - var102 * var102;
         if (var104 > 0.0) {
            var104 *= var104;
            var58 += var104 * var104 * this.extrapolate(var15 + 1, var16 + 1, var17 + 0, var98, var100, var102);
         }

         double var108 = var36 - 0.0 - 0.6666666666666666;
         double var110 = var38 - 1.0 - 0.6666666666666666;
         double var112 = 2.0 - var98 * var98 - var108 * var108 - var110 * var110;
         if (var112 > 0.0) {
            var112 *= var112;
            var58 += var112 * var112 * this.extrapolate(var15 + 1, var16 + 0, var17 + 1, var98, var108, var110);
         }

         double var114 = var34 - 0.0 - 0.6666666666666666;
         double var120 = 2.0 - var114 * var114 - var100 * var100 - var110 * var110;
         if (var120 > 0.0) {
            var120 *= var120;
            var58 += var120 * var120 * this.extrapolate(var15 + 0, var16 + 1, var17 + 1, var114, var100, var110);
         }
      }

      double var127 = 2.0 - var40 * var40 - var42 * var42 - var44 * var44;
      if (var127 > 0.0) {
         var127 *= var127;
         var58 += var127 * var127 * this.extrapolate(var52, var53, var54, var40, var42, var44);
      }

      double var130 = 2.0 - var46 * var46 - var48 * var48 - var50 * var50;
      if (var130 > 0.0) {
         var130 *= var130;
         var58 += var130 * var130 * this.extrapolate(var55, var56, var57, var46, var48, var50);
      }

      return var58 / 103.0;
   }

   public double eval(double var1, double var3, double var5, double var7) {
      double var9 = (var1 + var3 + var5 + var7) * -0.138196601125011;
      double var11 = var1 + var9;
      double var13 = var3 + var9;
      double var15 = var5 + var9;
      double var17 = var7 + var9;
      int var19 = fastFloor(var11);
      int var20 = fastFloor(var13);
      int var21 = fastFloor(var15);
      int var22 = fastFloor(var17);
      double var23 = (var19 + var20 + var21 + var22) * 0.309016994374947;
      double var25 = var19 + var23;
      double var27 = var20 + var23;
      double var29 = var21 + var23;
      double var31 = var22 + var23;
      double var33 = var11 - var19;
      double var35 = var13 - var20;
      double var37 = var15 - var21;
      double var39 = var17 - var22;
      double var41 = var33 + var35 + var37 + var39;
      double var43 = var1 - var25;
      double var45 = var3 - var27;
      double var47 = var5 - var29;
      double var49 = var7 - var31;
      double var87 = 0.0;
      double var51;
      double var53;
      double var55;
      double var57;
      double var59;
      double var61;
      double var63;
      double var65;
      double var67;
      double var69;
      double var71;
      double var73;
      int var75;
      int var76;
      int var77;
      int var78;
      int var79;
      int var80;
      int var81;
      int var82;
      int var83;
      int var84;
      int var85;
      int var86;
      if (var41 <= 1.0) {
         byte var89 = 1;
         double var90 = var33;
         byte var92 = 2;
         double var93 = var35;
         if (var33 >= var35 && var37 > var35) {
            var93 = var37;
            var92 = 4;
         } else if (var33 < var35 && var37 > var33) {
            var90 = var37;
            var89 = 4;
         }

         if (var90 >= var93 && var39 > var93) {
            var93 = var39;
            var92 = 8;
         } else if (var90 < var93 && var39 > var90) {
            var90 = var39;
            var89 = 8;
         }

         double var95 = 1.0 - var41;
         if (!(var95 > var90) && !(var95 > var93)) {
            byte var230 = (byte)(var89 | var92);
            if ((var230 & 1) == 0) {
               var83 = var19;
               var75 = var19;
               var79 = var19 - 1;
               var51 = var43 - 0.618033988749894;
               var59 = var43 + 1.0 - 0.309016994374947;
               var67 = var43 - 0.309016994374947;
            } else {
               var75 = var79 = var83 = var19 + 1;
               var51 = var43 - 1.0 - 0.618033988749894;
               var59 = var67 = var43 - 1.0 - 0.309016994374947;
            }

            if ((var230 & 2) == 0) {
               var84 = var20;
               var80 = var20;
               var76 = var20;
               var53 = var45 - 0.618033988749894;
               var61 = var69 = var45 - 0.309016994374947;
               if ((var230 & 1) == 1) {
                  var80 = var20 - 1;
                  var61++;
               } else {
                  var84 = var20 - 1;
                  var69++;
               }
            } else {
               var76 = var80 = var84 = var20 + 1;
               var53 = var45 - 1.0 - 0.618033988749894;
               var61 = var69 = var45 - 1.0 - 0.309016994374947;
            }

            if ((var230 & 4) == 0) {
               var85 = var21;
               var81 = var21;
               var77 = var21;
               var55 = var47 - 0.618033988749894;
               var63 = var71 = var47 - 0.309016994374947;
               if ((var230 & 3) == 3) {
                  var81 = var21 - 1;
                  var63++;
               } else {
                  var85 = var21 - 1;
                  var71++;
               }
            } else {
               var77 = var81 = var85 = var21 + 1;
               var55 = var47 - 1.0 - 0.618033988749894;
               var63 = var71 = var47 - 1.0 - 0.309016994374947;
            }

            if ((var230 & 8) == 0) {
               var82 = var22;
               var78 = var22;
               var86 = var22 - 1;
               var57 = var49 - 0.618033988749894;
               var65 = var49 - 0.309016994374947;
               var73 = var49 + 1.0 - 0.309016994374947;
            } else {
               var78 = var82 = var86 = var22 + 1;
               var57 = var49 - 1.0 - 0.618033988749894;
               var65 = var73 = var49 - 1.0 - 0.309016994374947;
            }
         } else {
            byte var97 = var93 > var90 ? var92 : var89;
            if ((var97 & 1) == 0) {
               var75 = var19 - 1;
               var83 = var19;
               var79 = var19;
               var51 = var43 + 1.0;
               var67 = var43;
               var59 = var43;
            } else {
               var75 = var79 = var83 = var19 + 1;
               var51 = var59 = var67 = var43 - 1.0;
            }

            if ((var97 & 2) == 0) {
               var84 = var20;
               var80 = var20;
               var76 = var20;
               var69 = var45;
               var61 = var45;
               var53 = var45;
               if ((var97 & 1) == 1) {
                  var76 = var20 - 1;
                  var53 = var45 + 1.0;
               } else {
                  var80 = var20 - 1;
                  var61 = var45 + 1.0;
               }
            } else {
               var76 = var80 = var84 = var20 + 1;
               var53 = var61 = var69 = var45 - 1.0;
            }

            if ((var97 & 4) == 0) {
               var85 = var21;
               var81 = var21;
               var77 = var21;
               var71 = var47;
               var63 = var47;
               var55 = var47;
               if ((var97 & 3) != 0) {
                  if ((var97 & 3) == 3) {
                     var77 = var21 - 1;
                     var55 = var47 + 1.0;
                  } else {
                     var81 = var21 - 1;
                     var63 = var47 + 1.0;
                  }
               } else {
                  var85 = var21 - 1;
                  var71 = var47 + 1.0;
               }
            } else {
               var77 = var81 = var85 = var21 + 1;
               var55 = var63 = var71 = var47 - 1.0;
            }

            if ((var97 & 8) == 0) {
               var82 = var22;
               var78 = var22;
               var86 = var22 - 1;
               var65 = var49;
               var57 = var49;
               var73 = var49 + 1.0;
            } else {
               var78 = var82 = var86 = var22 + 1;
               var57 = var65 = var73 = var49 - 1.0;
            }
         }

         double var231 = 2.0 - var43 * var43 - var45 * var45 - var47 * var47 - var49 * var49;
         if (var231 > 0.0) {
            var231 *= var231;
            var87 += var231 * var231 * this.extrapolate(var19 + 0, var20 + 0, var21 + 0, var22 + 0, var43, var45, var47, var49);
         }

         double var99 = var43 - 1.0 - 0.309016994374947;
         double var101 = var45 - 0.0 - 0.309016994374947;
         double var103 = var47 - 0.0 - 0.309016994374947;
         double var105 = var49 - 0.0 - 0.309016994374947;
         double var107 = 2.0 - var99 * var99 - var101 * var101 - var103 * var103 - var105 * var105;
         if (var107 > 0.0) {
            var107 *= var107;
            var87 += var107 * var107 * this.extrapolate(var19 + 1, var20 + 0, var21 + 0, var22 + 0, var99, var101, var103, var105);
         }

         double var109 = var43 - 0.0 - 0.309016994374947;
         double var111 = var45 - 1.0 - 0.309016994374947;
         double var117 = 2.0 - var109 * var109 - var111 * var111 - var103 * var103 - var105 * var105;
         if (var117 > 0.0) {
            var117 *= var117;
            var87 += var117 * var117 * this.extrapolate(var19 + 0, var20 + 1, var21 + 0, var22 + 0, var109, var111, var103, var105);
         }

         double var123 = var47 - 1.0 - 0.309016994374947;
         double var127 = 2.0 - var109 * var109 - var101 * var101 - var123 * var123 - var105 * var105;
         if (var127 > 0.0) {
            var127 *= var127;
            var87 += var127 * var127 * this.extrapolate(var19 + 0, var20 + 0, var21 + 1, var22 + 0, var109, var101, var123, var105);
         }

         double var135 = var49 - 1.0 - 0.309016994374947;
         double var137 = 2.0 - var109 * var109 - var101 * var101 - var103 * var103 - var135 * var135;
         if (var137 > 0.0) {
            var137 *= var137;
            var87 += var137 * var137 * this.extrapolate(var19 + 0, var20 + 0, var21 + 0, var22 + 1, var109, var101, var103, var135);
         }
      } else if (var41 >= 3.0) {
         byte var209 = 14;
         double var214 = var33;
         byte var218 = 13;
         double var221 = var35;
         if (var33 <= var35 && var37 < var35) {
            var221 = var37;
            var218 = 11;
         } else if (var33 > var35 && var37 < var33) {
            var214 = var37;
            var209 = 11;
         }

         if (var214 <= var221 && var39 < var221) {
            var221 = var39;
            var218 = 7;
         } else if (var214 > var221 && var39 < var214) {
            var214 = var39;
            var209 = 7;
         }

         double var226 = 4.0 - var41;
         if (!(var226 < var214) && !(var226 < var221)) {
            byte var234 = (byte)(var209 & var218);
            if ((var234 & 1) != 0) {
               var75 = var83 = var19 + 1;
               var79 = var19 + 2;
               var51 = var43 - 1.0 - 0.618033988749894;
               var59 = var43 - 2.0 - 0.927050983124841;
               var67 = var43 - 1.0 - 0.927050983124841;
            } else {
               var83 = var19;
               var79 = var19;
               var75 = var19;
               var51 = var43 - 0.618033988749894;
               var59 = var67 = var43 - 0.927050983124841;
            }

            if ((var234 & 2) != 0) {
               var76 = var80 = var84 = var20 + 1;
               var53 = var45 - 1.0 - 0.618033988749894;
               var61 = var69 = var45 - 1.0 - 0.927050983124841;
               if ((var234 & 1) != 0) {
                  var84++;
                  var69--;
               } else {
                  var80++;
                  var61--;
               }
            } else {
               var84 = var20;
               var80 = var20;
               var76 = var20;
               var53 = var45 - 0.618033988749894;
               var61 = var69 = var45 - 0.927050983124841;
            }

            if ((var234 & 4) != 0) {
               var77 = var81 = var85 = var21 + 1;
               var55 = var47 - 1.0 - 0.618033988749894;
               var63 = var71 = var47 - 1.0 - 0.927050983124841;
               if ((var234 & 3) != 0) {
                  var85++;
                  var71--;
               } else {
                  var81++;
                  var63--;
               }
            } else {
               var85 = var21;
               var81 = var21;
               var77 = var21;
               var55 = var47 - 0.618033988749894;
               var63 = var71 = var47 - 0.927050983124841;
            }

            if ((var234 & 8) != 0) {
               var78 = var82 = var22 + 1;
               var86 = var22 + 2;
               var57 = var49 - 1.0 - 0.618033988749894;
               var65 = var49 - 1.0 - 0.927050983124841;
               var73 = var49 - 2.0 - 0.927050983124841;
            } else {
               var86 = var22;
               var82 = var22;
               var78 = var22;
               var57 = var49 - 0.618033988749894;
               var65 = var73 = var49 - 0.927050983124841;
            }
         } else {
            byte var233 = var221 < var214 ? var218 : var209;
            if ((var233 & 1) != 0) {
               var75 = var19 + 2;
               var79 = var83 = var19 + 1;
               var51 = var43 - 2.0 - 1.236067977499788;
               var59 = var67 = var43 - 1.0 - 1.236067977499788;
            } else {
               var83 = var19;
               var79 = var19;
               var75 = var19;
               var51 = var59 = var67 = var43 - 1.236067977499788;
            }

            if ((var233 & 2) != 0) {
               var76 = var80 = var84 = var20 + 1;
               var53 = var61 = var69 = var45 - 1.0 - 1.236067977499788;
               if ((var233 & 1) != 0) {
                  var80++;
                  var61--;
               } else {
                  var76++;
                  var53--;
               }
            } else {
               var84 = var20;
               var80 = var20;
               var76 = var20;
               var53 = var61 = var69 = var45 - 1.236067977499788;
            }

            if ((var233 & 4) != 0) {
               var77 = var81 = var85 = var21 + 1;
               var55 = var63 = var71 = var47 - 1.0 - 1.236067977499788;
               if ((var233 & 3) != 3) {
                  if ((var233 & 3) == 0) {
                     var77++;
                     var55--;
                  } else {
                     var81++;
                     var63--;
                  }
               } else {
                  var85++;
                  var71--;
               }
            } else {
               var85 = var21;
               var81 = var21;
               var77 = var21;
               var55 = var63 = var71 = var47 - 1.236067977499788;
            }

            if ((var233 & 8) != 0) {
               var78 = var82 = var22 + 1;
               var86 = var22 + 2;
               var57 = var65 = var49 - 1.0 - 1.236067977499788;
               var73 = var49 - 2.0 - 1.236067977499788;
            } else {
               var86 = var22;
               var82 = var22;
               var78 = var22;
               var57 = var65 = var73 = var49 - 1.236067977499788;
            }
         }

         double var235 = var43 - 1.0 - 0.927050983124841;
         double var242 = var45 - 1.0 - 0.927050983124841;
         double var245 = var47 - 1.0 - 0.927050983124841;
         double var248 = var49 - 0.927050983124841;
         double var251 = 2.0 - var235 * var235 - var242 * var242 - var245 * var245 - var248 * var248;
         if (var251 > 0.0) {
            var251 *= var251;
            var87 += var251 * var251 * this.extrapolate(var19 + 1, var20 + 1, var21 + 1, var22 + 0, var235, var242, var245, var248);
         }

         double var269 = var47 - 0.927050983124841;
         double var113 = var49 - 1.0 - 0.927050983124841;
         double var115 = 2.0 - var235 * var235 - var242 * var242 - var269 * var269 - var113 * var113;
         if (var115 > 0.0) {
            var115 *= var115;
            var87 += var115 * var115 * this.extrapolate(var19 + 1, var20 + 1, var21 + 0, var22 + 1, var235, var242, var269, var113);
         }

         double var119 = var45 - 0.927050983124841;
         double var125 = 2.0 - var235 * var235 - var119 * var119 - var245 * var245 - var113 * var113;
         if (var125 > 0.0) {
            var125 *= var125;
            var87 += var125 * var125 * this.extrapolate(var19 + 1, var20 + 0, var21 + 1, var22 + 1, var235, var119, var245, var113);
         }

         double var287 = var43 - 0.927050983124841;
         double var292 = 2.0 - var287 * var287 - var242 * var242 - var245 * var245 - var113 * var113;
         if (var292 > 0.0) {
            var292 *= var292;
            var87 += var292 * var292 * this.extrapolate(var19 + 0, var20 + 1, var21 + 1, var22 + 1, var287, var242, var245, var113);
         }

         var43 = var43 - 1.0 - 1.236067977499788;
         var45 = var45 - 1.0 - 1.236067977499788;
         var47 = var47 - 1.0 - 1.236067977499788;
         var49 = var49 - 1.0 - 1.236067977499788;
         double var296 = 2.0 - var43 * var43 - var45 * var45 - var47 * var47 - var49 * var49;
         if (var296 > 0.0) {
            var296 *= var296;
            var87 += var296 * var296 * this.extrapolate(var19 + 1, var20 + 1, var21 + 1, var22 + 1, var43, var45, var47, var49);
         }
      } else if (var41 <= 2.0) {
         boolean var219 = true;
         boolean var96 = true;
         byte var91;
         double var210;
         if (var33 + var35 > var37 + var39) {
            var210 = var33 + var35;
            var91 = 3;
         } else {
            var210 = var37 + var39;
            var91 = 12;
         }

         double var222;
         byte var227;
         if (var33 + var37 > var35 + var39) {
            var222 = var33 + var37;
            var227 = 5;
         } else {
            var222 = var35 + var39;
            var227 = 10;
         }

         if (var33 + var39 > var35 + var37) {
            double var237 = var33 + var39;
            if (var210 >= var222 && var237 > var222) {
               var222 = var237;
               var227 = 9;
            } else if (var210 < var222 && var237 > var210) {
               var210 = var237;
               var91 = 9;
            }
         } else {
            double var236 = var35 + var37;
            if (var210 >= var222 && var236 > var222) {
               var222 = var236;
               var227 = 6;
            } else if (var210 < var222 && var236 > var210) {
               var210 = var236;
               var91 = 6;
            }
         }

         double var238 = 2.0 - var41 + var33;
         if (var210 >= var222 && var238 > var222) {
            var222 = var238;
            var227 = 1;
            var96 = false;
         } else if (var210 < var222 && var238 > var210) {
            var210 = var238;
            var91 = 1;
            var219 = false;
         }

         double var243 = 2.0 - var41 + var35;
         if (var210 >= var222 && var243 > var222) {
            var222 = var243;
            var227 = 2;
            var96 = false;
         } else if (var210 < var222 && var243 > var210) {
            var210 = var243;
            var91 = 2;
            var219 = false;
         }

         double var246 = 2.0 - var41 + var37;
         if (var210 >= var222 && var246 > var222) {
            var222 = var246;
            var227 = 4;
            var96 = false;
         } else if (var210 < var222 && var246 > var210) {
            var210 = var246;
            var91 = 4;
            var219 = false;
         }

         double var249 = 2.0 - var41 + var39;
         if (var210 >= var222 && var249 > var222) {
            var227 = 8;
            var96 = false;
         } else if (var210 < var222 && var249 > var210) {
            var91 = 8;
            var219 = false;
         }

         if (var219 == var96) {
            if (var219) {
               byte var253 = (byte)(var91 | var227);
               byte var106 = (byte)(var91 & var227);
               if ((var253 & 1) == 0) {
                  var75 = var19;
                  var79 = var19 - 1;
                  var51 = var43 - 0.927050983124841;
                  var59 = var43 + 1.0 - 0.618033988749894;
               } else {
                  var75 = var79 = var19 + 1;
                  var51 = var43 - 1.0 - 0.927050983124841;
                  var59 = var43 - 1.0 - 0.618033988749894;
               }

               if ((var253 & 2) == 0) {
                  var76 = var20;
                  var80 = var20 - 1;
                  var53 = var45 - 0.927050983124841;
                  var61 = var45 + 1.0 - 0.618033988749894;
               } else {
                  var76 = var80 = var20 + 1;
                  var53 = var45 - 1.0 - 0.927050983124841;
                  var61 = var45 - 1.0 - 0.618033988749894;
               }

               if ((var253 & 4) == 0) {
                  var77 = var21;
                  var81 = var21 - 1;
                  var55 = var47 - 0.927050983124841;
                  var63 = var47 + 1.0 - 0.618033988749894;
               } else {
                  var77 = var81 = var21 + 1;
                  var55 = var47 - 1.0 - 0.927050983124841;
                  var63 = var47 - 1.0 - 0.618033988749894;
               }

               if ((var253 & 8) == 0) {
                  var78 = var22;
                  var82 = var22 - 1;
                  var57 = var49 - 0.927050983124841;
                  var65 = var49 + 1.0 - 0.618033988749894;
               } else {
                  var78 = var82 = var22 + 1;
                  var57 = var49 - 1.0 - 0.927050983124841;
                  var65 = var49 - 1.0 - 0.618033988749894;
               }

               var83 = var19;
               var84 = var20;
               var85 = var21;
               var86 = var22;
               var67 = var43 - 0.618033988749894;
               var69 = var45 - 0.618033988749894;
               var71 = var47 - 0.618033988749894;
               var73 = var49 - 0.618033988749894;
               if ((var106 & 1) != 0) {
                  var83 = var19 + 2;
                  var67 -= 2.0;
               } else if ((var106 & 2) != 0) {
                  var84 = var20 + 2;
                  var69 -= 2.0;
               } else if ((var106 & 4) != 0) {
                  var85 = var21 + 2;
                  var71 -= 2.0;
               } else {
                  var86 = var22 + 2;
                  var73 -= 2.0;
               }
            } else {
               var83 = var19;
               var84 = var20;
               var85 = var21;
               var86 = var22;
               var67 = var43;
               var69 = var45;
               var71 = var47;
               var73 = var49;
               byte var254 = (byte)(var91 | var227);
               if ((var254 & 1) == 0) {
                  var75 = var19 - 1;
                  var79 = var19;
                  var51 = var43 + 1.0 - 0.309016994374947;
                  var59 = var43 - 0.309016994374947;
               } else {
                  var75 = var79 = var19 + 1;
                  var51 = var59 = var43 - 1.0 - 0.309016994374947;
               }

               if ((var254 & 2) == 0) {
                  var80 = var20;
                  var76 = var20;
                  var53 = var61 = var45 - 0.309016994374947;
                  if ((var254 & 1) == 1) {
                     var76 = var20 - 1;
                     var53++;
                  } else {
                     var80 = var20 - 1;
                     var61++;
                  }
               } else {
                  var76 = var80 = var20 + 1;
                  var53 = var61 = var45 - 1.0 - 0.309016994374947;
               }

               if ((var254 & 4) == 0) {
                  var81 = var21;
                  var77 = var21;
                  var55 = var63 = var47 - 0.309016994374947;
                  if ((var254 & 3) == 3) {
                     var77 = var21 - 1;
                     var55++;
                  } else {
                     var81 = var21 - 1;
                     var63++;
                  }
               } else {
                  var77 = var81 = var21 + 1;
                  var55 = var63 = var47 - 1.0 - 0.309016994374947;
               }

               if ((var254 & 8) == 0) {
                  var78 = var22;
                  var82 = var22 - 1;
                  var57 = var49 - 0.309016994374947;
                  var65 = var49 + 1.0 - 0.309016994374947;
               } else {
                  var78 = var82 = var22 + 1;
                  var57 = var65 = var49 - 1.0 - 0.309016994374947;
               }
            }
         } else {
            byte var255;
            byte var261;
            if (var219) {
               var255 = var91;
               var261 = var227;
            } else {
               var255 = var227;
               var261 = var91;
            }

            if ((var255 & 1) == 0) {
               var75 = var19 - 1;
               var79 = var19;
               var51 = var43 + 1.0 - 0.309016994374947;
               var59 = var43 - 0.309016994374947;
            } else {
               var75 = var79 = var19 + 1;
               var51 = var59 = var43 - 1.0 - 0.309016994374947;
            }

            if ((var255 & 2) == 0) {
               var80 = var20;
               var76 = var20;
               var53 = var61 = var45 - 0.309016994374947;
               if ((var255 & 1) == 1) {
                  var76 = var20 - 1;
                  var53++;
               } else {
                  var80 = var20 - 1;
                  var61++;
               }
            } else {
               var76 = var80 = var20 + 1;
               var53 = var61 = var45 - 1.0 - 0.309016994374947;
            }

            if ((var255 & 4) == 0) {
               var81 = var21;
               var77 = var21;
               var55 = var63 = var47 - 0.309016994374947;
               if ((var255 & 3) == 3) {
                  var77 = var21 - 1;
                  var55++;
               } else {
                  var81 = var21 - 1;
                  var63++;
               }
            } else {
               var77 = var81 = var21 + 1;
               var55 = var63 = var47 - 1.0 - 0.309016994374947;
            }

            if ((var255 & 8) == 0) {
               var78 = var22;
               var82 = var22 - 1;
               var57 = var49 - 0.309016994374947;
               var65 = var49 + 1.0 - 0.309016994374947;
            } else {
               var78 = var82 = var22 + 1;
               var57 = var65 = var49 - 1.0 - 0.309016994374947;
            }

            var83 = var19;
            var84 = var20;
            var85 = var21;
            var86 = var22;
            var67 = var43 - 0.618033988749894;
            var69 = var45 - 0.618033988749894;
            var71 = var47 - 0.618033988749894;
            var73 = var49 - 0.618033988749894;
            if ((var261 & 1) != 0) {
               var83 = var19 + 2;
               var67 -= 2.0;
            } else if ((var261 & 2) != 0) {
               var84 = var20 + 2;
               var69 -= 2.0;
            } else if ((var261 & 4) != 0) {
               var85 = var21 + 2;
               var71 -= 2.0;
            } else {
               var86 = var22 + 2;
               var73 -= 2.0;
            }
         }

         double var256 = var43 - 1.0 - 0.309016994374947;
         double var265 = var45 - 0.0 - 0.309016994374947;
         double var267 = var47 - 0.0 - 0.309016994374947;
         double var270 = var49 - 0.0 - 0.309016994374947;
         double var272 = 2.0 - var256 * var256 - var265 * var265 - var267 * var267 - var270 * var270;
         if (var272 > 0.0) {
            var272 *= var272;
            var87 += var272 * var272 * this.extrapolate(var19 + 1, var20 + 0, var21 + 0, var22 + 0, var256, var265, var267, var270);
         }

         double var277 = var43 - 0.0 - 0.309016994374947;
         double var279 = var45 - 1.0 - 0.309016994374947;
         double var281 = 2.0 - var277 * var277 - var279 * var279 - var267 * var267 - var270 * var270;
         if (var281 > 0.0) {
            var281 *= var281;
            var87 += var281 * var281 * this.extrapolate(var19 + 0, var20 + 1, var21 + 0, var22 + 0, var277, var279, var267, var270);
         }

         double var129 = var47 - 1.0 - 0.309016994374947;
         double var133 = 2.0 - var277 * var277 - var265 * var265 - var129 * var129 - var270 * var270;
         if (var133 > 0.0) {
            var133 *= var133;
            var87 += var133 * var133 * this.extrapolate(var19 + 0, var20 + 0, var21 + 1, var22 + 0, var277, var265, var129, var270);
         }

         double var141 = var49 - 1.0 - 0.309016994374947;
         double var143 = 2.0 - var277 * var277 - var265 * var265 - var267 * var267 - var141 * var141;
         if (var143 > 0.0) {
            var143 *= var143;
            var87 += var143 * var143 * this.extrapolate(var19 + 0, var20 + 0, var21 + 0, var22 + 1, var277, var265, var267, var141);
         }

         double var145 = var43 - 1.0 - 0.618033988749894;
         double var147 = var45 - 1.0 - 0.618033988749894;
         double var149 = var47 - 0.0 - 0.618033988749894;
         double var151 = var49 - 0.0 - 0.618033988749894;
         double var153 = 2.0 - var145 * var145 - var147 * var147 - var149 * var149 - var151 * var151;
         if (var153 > 0.0) {
            var153 *= var153;
            var87 += var153 * var153 * this.extrapolate(var19 + 1, var20 + 1, var21 + 0, var22 + 0, var145, var147, var149, var151);
         }

         double var155 = var43 - 1.0 - 0.618033988749894;
         double var157 = var45 - 0.0 - 0.618033988749894;
         double var159 = var47 - 1.0 - 0.618033988749894;
         double var161 = var49 - 0.0 - 0.618033988749894;
         double var163 = 2.0 - var155 * var155 - var157 * var157 - var159 * var159 - var161 * var161;
         if (var163 > 0.0) {
            var163 *= var163;
            var87 += var163 * var163 * this.extrapolate(var19 + 1, var20 + 0, var21 + 1, var22 + 0, var155, var157, var159, var161);
         }

         double var165 = var43 - 1.0 - 0.618033988749894;
         double var167 = var45 - 0.0 - 0.618033988749894;
         double var169 = var47 - 0.0 - 0.618033988749894;
         double var171 = var49 - 1.0 - 0.618033988749894;
         double var173 = 2.0 - var165 * var165 - var167 * var167 - var169 * var169 - var171 * var171;
         if (var173 > 0.0) {
            var173 *= var173;
            var87 += var173 * var173 * this.extrapolate(var19 + 1, var20 + 0, var21 + 0, var22 + 1, var165, var167, var169, var171);
         }

         double var175 = var43 - 0.0 - 0.618033988749894;
         double var177 = var45 - 1.0 - 0.618033988749894;
         double var179 = var47 - 1.0 - 0.618033988749894;
         double var181 = var49 - 0.0 - 0.618033988749894;
         double var183 = 2.0 - var175 * var175 - var177 * var177 - var179 * var179 - var181 * var181;
         if (var183 > 0.0) {
            var183 *= var183;
            var87 += var183 * var183 * this.extrapolate(var19 + 0, var20 + 1, var21 + 1, var22 + 0, var175, var177, var179, var181);
         }

         double var185 = var43 - 0.0 - 0.618033988749894;
         double var187 = var45 - 1.0 - 0.618033988749894;
         double var189 = var47 - 0.0 - 0.618033988749894;
         double var191 = var49 - 1.0 - 0.618033988749894;
         double var193 = 2.0 - var185 * var185 - var187 * var187 - var189 * var189 - var191 * var191;
         if (var193 > 0.0) {
            var193 *= var193;
            var87 += var193 * var193 * this.extrapolate(var19 + 0, var20 + 1, var21 + 0, var22 + 1, var185, var187, var189, var191);
         }

         double var195 = var43 - 0.0 - 0.618033988749894;
         double var197 = var45 - 0.0 - 0.618033988749894;
         double var199 = var47 - 1.0 - 0.618033988749894;
         double var201 = var49 - 1.0 - 0.618033988749894;
         double var203 = 2.0 - var195 * var195 - var197 * var197 - var199 * var199 - var201 * var201;
         if (var203 > 0.0) {
            var203 *= var203;
            var87 += var203 * var203 * this.extrapolate(var19 + 0, var20 + 0, var21 + 1, var22 + 1, var195, var197, var199, var201);
         }
      } else {
         boolean var220 = true;
         boolean var229 = true;
         double var211;
         byte var215;
         if (var33 + var35 < var37 + var39) {
            var211 = var33 + var35;
            var215 = 12;
         } else {
            var211 = var37 + var39;
            var215 = 3;
         }

         double var223;
         byte var228;
         if (var33 + var37 < var35 + var39) {
            var223 = var33 + var37;
            var228 = 10;
         } else {
            var223 = var35 + var39;
            var228 = 5;
         }

         if (var33 + var39 < var35 + var37) {
            double var240 = var33 + var39;
            if (var211 <= var223 && var240 < var223) {
               var223 = var240;
               var228 = 6;
            } else if (var211 > var223 && var240 < var211) {
               var211 = var240;
               var215 = 6;
            }
         } else {
            double var239 = var35 + var37;
            if (var211 <= var223 && var239 < var223) {
               var223 = var239;
               var228 = 9;
            } else if (var211 > var223 && var239 < var211) {
               var211 = var239;
               var215 = 9;
            }
         }

         double var241 = 3.0 - var41 + var33;
         if (var211 <= var223 && var241 < var223) {
            var223 = var241;
            var228 = 14;
            var229 = false;
         } else if (var211 > var223 && var241 < var211) {
            var211 = var241;
            var215 = 14;
            var220 = false;
         }

         double var244 = 3.0 - var41 + var35;
         if (var211 <= var223 && var244 < var223) {
            var223 = var244;
            var228 = 13;
            var229 = false;
         } else if (var211 > var223 && var244 < var211) {
            var211 = var244;
            var215 = 13;
            var220 = false;
         }

         double var247 = 3.0 - var41 + var37;
         if (var211 <= var223 && var247 < var223) {
            var223 = var247;
            var228 = 11;
            var229 = false;
         } else if (var211 > var223 && var247 < var211) {
            var211 = var247;
            var215 = 11;
            var220 = false;
         }

         double var250 = 3.0 - var41 + var39;
         if (var211 <= var223 && var250 < var223) {
            var228 = 7;
            var229 = false;
         } else if (var211 > var223 && var250 < var211) {
            var215 = 7;
            var220 = false;
         }

         if (var220 == var229) {
            if (var220) {
               byte var257 = (byte)(var215 & var228);
               byte var262 = (byte)(var215 | var228);
               var79 = var19;
               var75 = var19;
               var80 = var20;
               var76 = var20;
               var81 = var21;
               var77 = var21;
               var82 = var22;
               var78 = var22;
               var51 = var43 - 0.309016994374947;
               var53 = var45 - 0.309016994374947;
               var55 = var47 - 0.309016994374947;
               var57 = var49 - 0.309016994374947;
               var59 = var43 - 0.618033988749894;
               var61 = var45 - 0.618033988749894;
               var63 = var47 - 0.618033988749894;
               var65 = var49 - 0.618033988749894;
               if ((var257 & 1) != 0) {
                  var75 = var19 + 1;
                  var51--;
                  var79 = var19 + 2;
                  var59 -= 2.0;
               } else if ((var257 & 2) != 0) {
                  var76 = var20 + 1;
                  var53--;
                  var80 = var20 + 2;
                  var61 -= 2.0;
               } else if ((var257 & 4) != 0) {
                  var77 = var21 + 1;
                  var55--;
                  var81 = var21 + 2;
                  var63 -= 2.0;
               } else {
                  var78 = var22 + 1;
                  var57--;
                  var82 = var22 + 2;
                  var65 -= 2.0;
               }

               var83 = var19 + 1;
               var84 = var20 + 1;
               var85 = var21 + 1;
               var86 = var22 + 1;
               var67 = var43 - 1.0 - 0.618033988749894;
               var69 = var45 - 1.0 - 0.618033988749894;
               var71 = var47 - 1.0 - 0.618033988749894;
               var73 = var49 - 1.0 - 0.618033988749894;
               if ((var262 & 1) == 0) {
                  var83 -= 2;
                  var67 += 2.0;
               } else if ((var262 & 2) == 0) {
                  var84 -= 2;
                  var69 += 2.0;
               } else if ((var262 & 4) == 0) {
                  var85 -= 2;
                  var71 += 2.0;
               } else {
                  var86 -= 2;
                  var73 += 2.0;
               }
            } else {
               var83 = var19 + 1;
               var84 = var20 + 1;
               var85 = var21 + 1;
               var86 = var22 + 1;
               var67 = var43 - 1.0 - 1.236067977499788;
               var69 = var45 - 1.0 - 1.236067977499788;
               var71 = var47 - 1.0 - 1.236067977499788;
               var73 = var49 - 1.0 - 1.236067977499788;
               byte var258 = (byte)(var215 & var228);
               if ((var258 & 1) != 0) {
                  var75 = var19 + 2;
                  var79 = var19 + 1;
                  var51 = var43 - 2.0 - 0.927050983124841;
                  var59 = var43 - 1.0 - 0.927050983124841;
               } else {
                  var79 = var19;
                  var75 = var19;
                  var51 = var59 = var43 - 0.927050983124841;
               }

               if ((var258 & 2) != 0) {
                  var76 = var80 = var20 + 1;
                  var53 = var61 = var45 - 1.0 - 0.927050983124841;
                  if ((var258 & 1) == 0) {
                     var76++;
                     var53--;
                  } else {
                     var80++;
                     var61--;
                  }
               } else {
                  var80 = var20;
                  var76 = var20;
                  var53 = var61 = var45 - 0.927050983124841;
               }

               if ((var258 & 4) != 0) {
                  var77 = var81 = var21 + 1;
                  var55 = var63 = var47 - 1.0 - 0.927050983124841;
                  if ((var258 & 3) == 0) {
                     var77++;
                     var55--;
                  } else {
                     var81++;
                     var63--;
                  }
               } else {
                  var81 = var21;
                  var77 = var21;
                  var55 = var63 = var47 - 0.927050983124841;
               }

               if ((var258 & 8) != 0) {
                  var78 = var22 + 1;
                  var82 = var22 + 2;
                  var57 = var49 - 1.0 - 0.927050983124841;
                  var65 = var49 - 2.0 - 0.927050983124841;
               } else {
                  var82 = var22;
                  var78 = var22;
                  var57 = var65 = var49 - 0.927050983124841;
               }
            }
         } else {
            byte var259;
            byte var263;
            if (var220) {
               var259 = var215;
               var263 = var228;
            } else {
               var259 = var228;
               var263 = var215;
            }

            if ((var259 & 1) != 0) {
               var75 = var19 + 2;
               var79 = var19 + 1;
               var51 = var43 - 2.0 - 0.927050983124841;
               var59 = var43 - 1.0 - 0.927050983124841;
            } else {
               var79 = var19;
               var75 = var19;
               var51 = var59 = var43 - 0.927050983124841;
            }

            if ((var259 & 2) != 0) {
               var76 = var80 = var20 + 1;
               var53 = var61 = var45 - 1.0 - 0.927050983124841;
               if ((var259 & 1) == 0) {
                  var76++;
                  var53--;
               } else {
                  var80++;
                  var61--;
               }
            } else {
               var80 = var20;
               var76 = var20;
               var53 = var61 = var45 - 0.927050983124841;
            }

            if ((var259 & 4) != 0) {
               var77 = var81 = var21 + 1;
               var55 = var63 = var47 - 1.0 - 0.927050983124841;
               if ((var259 & 3) == 0) {
                  var77++;
                  var55--;
               } else {
                  var81++;
                  var63--;
               }
            } else {
               var81 = var21;
               var77 = var21;
               var55 = var63 = var47 - 0.927050983124841;
            }

            if ((var259 & 8) != 0) {
               var78 = var22 + 1;
               var82 = var22 + 2;
               var57 = var49 - 1.0 - 0.927050983124841;
               var65 = var49 - 2.0 - 0.927050983124841;
            } else {
               var82 = var22;
               var78 = var22;
               var57 = var65 = var49 - 0.927050983124841;
            }

            var83 = var19 + 1;
            var84 = var20 + 1;
            var85 = var21 + 1;
            var86 = var22 + 1;
            var67 = var43 - 1.0 - 0.618033988749894;
            var69 = var45 - 1.0 - 0.618033988749894;
            var71 = var47 - 1.0 - 0.618033988749894;
            var73 = var49 - 1.0 - 0.618033988749894;
            if ((var263 & 1) == 0) {
               var83 -= 2;
               var67 += 2.0;
            } else if ((var263 & 2) == 0) {
               var84 -= 2;
               var69 += 2.0;
            } else if ((var263 & 4) == 0) {
               var85 -= 2;
               var71 += 2.0;
            } else {
               var86 -= 2;
               var73 += 2.0;
            }
         }

         double var260 = var43 - 1.0 - 0.927050983124841;
         double var266 = var45 - 1.0 - 0.927050983124841;
         double var268 = var47 - 1.0 - 0.927050983124841;
         double var271 = var49 - 0.927050983124841;
         double var274 = 2.0 - var260 * var260 - var266 * var266 - var268 * var268 - var271 * var271;
         if (var274 > 0.0) {
            var274 *= var274;
            var87 += var274 * var274 * this.extrapolate(var19 + 1, var20 + 1, var21 + 1, var22 + 0, var260, var266, var268, var271);
         }

         double var280 = var47 - 0.927050983124841;
         double var121 = var49 - 1.0 - 0.927050983124841;
         double var283 = 2.0 - var260 * var260 - var266 * var266 - var280 * var280 - var121 * var121;
         if (var283 > 0.0) {
            var283 *= var283;
            var87 += var283 * var283 * this.extrapolate(var19 + 1, var20 + 1, var21 + 0, var22 + 1, var260, var266, var280, var121);
         }

         double var288 = var45 - 0.927050983124841;
         double var290 = 2.0 - var260 * var260 - var288 * var288 - var268 * var268 - var121 * var121;
         if (var290 > 0.0) {
            var290 *= var290;
            var87 += var290 * var290 * this.extrapolate(var19 + 1, var20 + 0, var21 + 1, var22 + 1, var260, var288, var268, var121);
         }

         double var294 = var43 - 0.927050983124841;
         double var299 = 2.0 - var294 * var294 - var266 * var266 - var268 * var268 - var121 * var121;
         if (var299 > 0.0) {
            var299 *= var299;
            var87 += var299 * var299 * this.extrapolate(var19 + 0, var20 + 1, var21 + 1, var22 + 1, var294, var266, var268, var121);
         }

         double var301 = var43 - 1.0 - 0.618033988749894;
         double var302 = var45 - 1.0 - 0.618033988749894;
         double var303 = var47 - 0.0 - 0.618033988749894;
         double var304 = var49 - 0.0 - 0.618033988749894;
         double var306 = 2.0 - var301 * var301 - var302 * var302 - var303 * var303 - var304 * var304;
         if (var306 > 0.0) {
            var306 *= var306;
            var87 += var306 * var306 * this.extrapolate(var19 + 1, var20 + 1, var21 + 0, var22 + 0, var301, var302, var303, var304);
         }

         double var308 = var43 - 1.0 - 0.618033988749894;
         double var309 = var45 - 0.0 - 0.618033988749894;
         double var310 = var47 - 1.0 - 0.618033988749894;
         double var311 = var49 - 0.0 - 0.618033988749894;
         double var313 = 2.0 - var308 * var308 - var309 * var309 - var310 * var310 - var311 * var311;
         if (var313 > 0.0) {
            var313 *= var313;
            var87 += var313 * var313 * this.extrapolate(var19 + 1, var20 + 0, var21 + 1, var22 + 0, var308, var309, var310, var311);
         }

         double var315 = var43 - 1.0 - 0.618033988749894;
         double var316 = var45 - 0.0 - 0.618033988749894;
         double var317 = var47 - 0.0 - 0.618033988749894;
         double var318 = var49 - 1.0 - 0.618033988749894;
         double var320 = 2.0 - var315 * var315 - var316 * var316 - var317 * var317 - var318 * var318;
         if (var320 > 0.0) {
            var320 *= var320;
            var87 += var320 * var320 * this.extrapolate(var19 + 1, var20 + 0, var21 + 0, var22 + 1, var315, var316, var317, var318);
         }

         double var322 = var43 - 0.0 - 0.618033988749894;
         double var323 = var45 - 1.0 - 0.618033988749894;
         double var324 = var47 - 1.0 - 0.618033988749894;
         double var325 = var49 - 0.0 - 0.618033988749894;
         double var327 = 2.0 - var322 * var322 - var323 * var323 - var324 * var324 - var325 * var325;
         if (var327 > 0.0) {
            var327 *= var327;
            var87 += var327 * var327 * this.extrapolate(var19 + 0, var20 + 1, var21 + 1, var22 + 0, var322, var323, var324, var325);
         }

         double var329 = var43 - 0.0 - 0.618033988749894;
         double var330 = var45 - 1.0 - 0.618033988749894;
         double var331 = var47 - 0.0 - 0.618033988749894;
         double var332 = var49 - 1.0 - 0.618033988749894;
         double var334 = 2.0 - var329 * var329 - var330 * var330 - var331 * var331 - var332 * var332;
         if (var334 > 0.0) {
            var334 *= var334;
            var87 += var334 * var334 * this.extrapolate(var19 + 0, var20 + 1, var21 + 0, var22 + 1, var329, var330, var331, var332);
         }

         double var336 = var43 - 0.0 - 0.618033988749894;
         double var337 = var45 - 0.0 - 0.618033988749894;
         double var338 = var47 - 1.0 - 0.618033988749894;
         double var339 = var49 - 1.0 - 0.618033988749894;
         double var341 = 2.0 - var336 * var336 - var337 * var337 - var338 * var338 - var339 * var339;
         if (var341 > 0.0) {
            var341 *= var341;
            var87 += var341 * var341 * this.extrapolate(var19 + 0, var20 + 0, var21 + 1, var22 + 1, var336, var337, var338, var339);
         }
      }

      double var212 = 2.0 - var51 * var51 - var53 * var53 - var55 * var55 - var57 * var57;
      if (var212 > 0.0) {
         var212 *= var212;
         var87 += var212 * var212 * this.extrapolate(var75, var76, var77, var78, var51, var53, var55, var57);
      }

      double var216 = 2.0 - var59 * var59 - var61 * var61 - var63 * var63 - var65 * var65;
      if (var216 > 0.0) {
         var216 *= var216;
         var87 += var216 * var216 * this.extrapolate(var79, var80, var81, var82, var59, var61, var63, var65);
      }

      double var224 = 2.0 - var67 * var67 - var69 * var69 - var71 * var71 - var73 * var73;
      if (var224 > 0.0) {
         var224 *= var224;
         var87 += var224 * var224 * this.extrapolate(var83, var84, var85, var86, var67, var69, var71, var73);
      }

      return var87 / 30.0;
   }

   private double extrapolate(int var1, int var2, double var3, double var5) {
      int var7 = this.perm[this.perm[var1 & 0xFF] + var2 & 0xFF] & 14;
      return gradients2D[var7] * var3 + gradients2D[var7 + 1] * var5;
   }

   private double extrapolate(int var1, int var2, int var3, double var4, double var6, double var8) {
      short var10 = this.permGradIndex3D[this.perm[this.perm[var1 & 0xFF] + var2 & 0xFF] + var3 & 0xFF];
      return gradients3D[var10] * var4 + gradients3D[var10 + 1] * var6 + gradients3D[var10 + 2] * var8;
   }

   private double extrapolate(int var1, int var2, int var3, int var4, double var5, double var7, double var9, double var11) {
      int var13 = this.perm[this.perm[this.perm[this.perm[var1 & 0xFF] + var2 & 0xFF] + var3 & 0xFF] + var4 & 0xFF] & 252;
      return gradients4D[var13] * var5 + gradients4D[var13 + 1] * var7 + gradients4D[var13 + 2] * var9 + gradients4D[var13 + 3] * var11;
   }

   private static int fastFloor(double var0) {
      int var2 = (int)var0;
      return var0 < var2 ? var2 - 1 : var2;
   }

   public double evalOct(float var1, float var2, int var3) {
      boolean var4 = true;
      double var5 = this.eval(var1, var2, var3);

      for (int var7 = 2; var7 <= 64; var7++) {
         var5 += this.eval(var1 * var7 * var1, var2 * var7 * var2, var3 * var7 * var3);
      }

      return var5;
   }
}
