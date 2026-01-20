#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {


class Matrix3d {
public:
    static const long serialVersionUID = 6837536777072402710L;
    double m00;
    double m01;
    double m02;
    double m10;
    double m11;
    double m12;
    double m20;
    double m21;
    double m22;
    static const double EPS = 1.110223024E-16;
    static const double ERR_EPS = 1.0E-8;
    static double xin;
    static double yin;
    static double zin;
    static double xout;
    static double yout;
    static double zout;

    public Matrix3d(double var1, double var3, double var5, double var7, double var9, double var11, double var13, double var15, double var17) {
      this.m00 = var1;
      this.m01 = var3;
      this.m02 = var5;
      this.m10 = var7;
      this.m11 = var9;
      this.m12 = var11;
      this.m20 = var13;
      this.m21 = var15;
      this.m22 = var17;
   }

    public Matrix3d(double[] var1) {
      this.m00 = var1[0];
      this.m01 = var1[1];
      this.m02 = var1[2];
      this.m10 = var1[3];
      this.m11 = var1[4];
      this.m12 = var1[5];
      this.m20 = var1[6];
      this.m21 = var1[7];
      this.m22 = var1[8];
   }

    public Matrix3d(Matrix3d var1) {
      this.m00 = var1.m00;
      this.m01 = var1.m01;
      this.m02 = var1.m02;
      this.m10 = var1.m10;
      this.m11 = var1.m11;
      this.m12 = var1.m12;
      this.m20 = var1.m20;
      this.m21 = var1.m21;
      this.m22 = var1.m22;
   }

    public Matrix3d(Matrix3f var1) {
      this.m00 = var1.m00;
      this.m01 = var1.m01;
      this.m02 = var1.m02;
      this.m10 = var1.m10;
      this.m11 = var1.m11;
      this.m12 = var1.m12;
      this.m20 = var1.m20;
      this.m21 = var1.m21;
      this.m22 = var1.m22;
   }

    public Matrix3d() {
      this.m00 = 0.0;
      this.m01 = 0.0;
      this.m02 = 0.0;
      this.m10 = 0.0;
      this.m11 = 0.0;
      this.m12 = 0.0;
      this.m20 = 0.0;
      this.m21 = 0.0;
      this.m22 = 0.0;
   }

    std::string toString() {
      return this.m00
         + ", "
         + this.m01
         + ", "
         + this.m02
         + "\n"
         + this.m10
         + ", "
         + this.m11
         + ", "
         + this.m12
         + "\n"
         + this.m20
         + ", "
         + this.m21
         + ", "
         + this.m22
         + "\n";
   }

    void setIdentity() {
      this.m00 = 1.0;
      this.m01 = 0.0;
      this.m02 = 0.0;
      this.m10 = 0.0;
      this.m11 = 1.0;
      this.m12 = 0.0;
      this.m20 = 0.0;
      this.m21 = 0.0;
      this.m22 = 1.0;
   }

    void setScale(double var1) {
      double[] var3 = new double[9];
      double[] var4 = new double[3];
      this.getScaleRotate(var4, var3);
      this.m00 = var3[0] * var1;
      this.m01 = var3[1] * var1;
      this.m02 = var3[2] * var1;
      this.m10 = var3[3] * var1;
      this.m11 = var3[4] * var1;
      this.m12 = var3[5] * var1;
      this.m20 = var3[6] * var1;
      this.m21 = var3[7] * var1;
      this.m22 = var3[8] * var1;
   }

    void setElement(int var1, int var2, double var3) {
      switch (var1) {
         case 0:
            switch (var2) {
               case 0:
                  this.m00 = var3;
                  return;
               case 1:
                  this.m01 = var3;
                  return;
               case 2:
                  this.m02 = var3;
                  return;
               default:
                  throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d0"));
            }
         case 1:
            switch (var2) {
               case 0:
                  this.m10 = var3;
                  return;
               case 1:
                  this.m11 = var3;
                  return;
               case 2:
                  this.m12 = var3;
                  return;
               default:
                  throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d0"));
            }
         case 2:
            switch (var2) {
               case 0:
                  this.m20 = var3;
                  return;
               case 1:
                  this.m21 = var3;
                  return;
               case 2:
                  this.m22 = var3;
                  return;
               default:
                  throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d0"));
            }
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d0"));
      }
   }

    double getElement(int var1, int var2) {
      switch (var1) {
         case 0:
            switch (var2) {
               case 0:
                  return this.m00;
               case 1:
                  return this.m01;
               case 2:
                  return this.m02;
               default:
                  throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d1"));
            }
         case 1:
            switch (var2) {
               case 0:
                  return this.m10;
               case 1:
                  return this.m11;
               case 2:
                  return this.m12;
               default:
                  throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d1"));
            }
         case 2:
            switch (var2) {
               case 0:
                  return this.m20;
               case 1:
                  return this.m21;
               case 2:
                  return this.m22;
            }
      }

      throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d1"));
   }

    void getRow(int var1, Vector3d var2) {
      if (var1 == 0) {
         var2.x = this.m00;
         var2.y = this.m01;
         var2.z = this.m02;
      } else if (var1 == 1) {
         var2.x = this.m10;
         var2.y = this.m11;
         var2.z = this.m12;
      } else {
         if (var1 != 2) {
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d2"));
         }

         var2.x = this.m20;
         var2.y = this.m21;
         var2.z = this.m22;
      }
   }

    void getRow(int var1, double[] var2) {
      if (var1 == 0) {
         var2[0] = this.m00;
         var2[1] = this.m01;
         var2[2] = this.m02;
      } else if (var1 == 1) {
         var2[0] = this.m10;
         var2[1] = this.m11;
         var2[2] = this.m12;
      } else {
         if (var1 != 2) {
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d2"));
         }

         var2[0] = this.m20;
         var2[1] = this.m21;
         var2[2] = this.m22;
      }
   }

    void getColumn(int var1, Vector3d var2) {
      if (var1 == 0) {
         var2.x = this.m00;
         var2.y = this.m10;
         var2.z = this.m20;
      } else if (var1 == 1) {
         var2.x = this.m01;
         var2.y = this.m11;
         var2.z = this.m21;
      } else {
         if (var1 != 2) {
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d4"));
         }

         var2.x = this.m02;
         var2.y = this.m12;
         var2.z = this.m22;
      }
   }

    void getColumn(int var1, double[] var2) {
      if (var1 == 0) {
         var2[0] = this.m00;
         var2[1] = this.m10;
         var2[2] = this.m20;
      } else if (var1 == 1) {
         var2[0] = this.m01;
         var2[1] = this.m11;
         var2[2] = this.m21;
      } else {
         if (var1 != 2) {
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d4"));
         }

         var2[0] = this.m02;
         var2[1] = this.m12;
         var2[2] = this.m22;
      }
   }

    void setRow(int var1, double var2, double var4, double var6) {
      switch (var1) {
         case 0:
            this.m00 = var2;
            this.m01 = var4;
            this.m02 = var6;
            break;
         case 1:
            this.m10 = var2;
            this.m11 = var4;
            this.m12 = var6;
            break;
         case 2:
            this.m20 = var2;
            this.m21 = var4;
            this.m22 = var6;
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d6"));
      }
   }

    void setRow(int var1, Vector3d var2) {
      switch (var1) {
         case 0:
            this.m00 = var2.x;
            this.m01 = var2.y;
            this.m02 = var2.z;
            break;
         case 1:
            this.m10 = var2.x;
            this.m11 = var2.y;
            this.m12 = var2.z;
            break;
         case 2:
            this.m20 = var2.x;
            this.m21 = var2.y;
            this.m22 = var2.z;
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d6"));
      }
   }

    void setRow(int var1, double[] var2) {
      switch (var1) {
         case 0:
            this.m00 = var2[0];
            this.m01 = var2[1];
            this.m02 = var2[2];
            break;
         case 1:
            this.m10 = var2[0];
            this.m11 = var2[1];
            this.m12 = var2[2];
            break;
         case 2:
            this.m20 = var2[0];
            this.m21 = var2[1];
            this.m22 = var2[2];
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d6"));
      }
   }

    void setColumn(int var1, double var2, double var4, double var6) {
      switch (var1) {
         case 0:
            this.m00 = var2;
            this.m10 = var4;
            this.m20 = var6;
            break;
         case 1:
            this.m01 = var2;
            this.m11 = var4;
            this.m21 = var6;
            break;
         case 2:
            this.m02 = var2;
            this.m12 = var4;
            this.m22 = var6;
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d9"));
      }
   }

    void setColumn(int var1, Vector3d var2) {
      switch (var1) {
         case 0:
            this.m00 = var2.x;
            this.m10 = var2.y;
            this.m20 = var2.z;
            break;
         case 1:
            this.m01 = var2.x;
            this.m11 = var2.y;
            this.m21 = var2.z;
            break;
         case 2:
            this.m02 = var2.x;
            this.m12 = var2.y;
            this.m22 = var2.z;
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d9"));
      }
   }

    void setColumn(int var1, double[] var2) {
      switch (var1) {
         case 0:
            this.m00 = var2[0];
            this.m10 = var2[1];
            this.m20 = var2[2];
            break;
         case 1:
            this.m01 = var2[0];
            this.m11 = var2[1];
            this.m21 = var2[2];
            break;
         case 2:
            this.m02 = var2[0];
            this.m12 = var2[1];
            this.m22 = var2[2];
            break;
         default:
            throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix3d9"));
      }
   }

    double getScale() {
      double[] var1 = new double[3];
      double[] var2 = new double[9];
      this.getScaleRotate(var1, var2);
    return max3();
   }

    void add(double var1) {
      this.m00 += var1;
      this.m01 += var1;
      this.m02 += var1;
      this.m10 += var1;
      this.m11 += var1;
      this.m12 += var1;
      this.m20 += var1;
      this.m21 += var1;
      this.m22 += var1;
   }

    void add(double var1, Matrix3d var3) {
      this.m00 = var3.m00 + var1;
      this.m01 = var3.m01 + var1;
      this.m02 = var3.m02 + var1;
      this.m10 = var3.m10 + var1;
      this.m11 = var3.m11 + var1;
      this.m12 = var3.m12 + var1;
      this.m20 = var3.m20 + var1;
      this.m21 = var3.m21 + var1;
      this.m22 = var3.m22 + var1;
   }

    void add(Matrix3d var1, Matrix3d var2) {
      this.m00 = var1.m00 + var2.m00;
      this.m01 = var1.m01 + var2.m01;
      this.m02 = var1.m02 + var2.m02;
      this.m10 = var1.m10 + var2.m10;
      this.m11 = var1.m11 + var2.m11;
      this.m12 = var1.m12 + var2.m12;
      this.m20 = var1.m20 + var2.m20;
      this.m21 = var1.m21 + var2.m21;
      this.m22 = var1.m22 + var2.m22;
   }

    void add(Matrix3d var1) {
      this.m00 = this.m00 + var1.m00;
      this.m01 = this.m01 + var1.m01;
      this.m02 = this.m02 + var1.m02;
      this.m10 = this.m10 + var1.m10;
      this.m11 = this.m11 + var1.m11;
      this.m12 = this.m12 + var1.m12;
      this.m20 = this.m20 + var1.m20;
      this.m21 = this.m21 + var1.m21;
      this.m22 = this.m22 + var1.m22;
   }

    void sub(Matrix3d var1, Matrix3d var2) {
      this.m00 = var1.m00 - var2.m00;
      this.m01 = var1.m01 - var2.m01;
      this.m02 = var1.m02 - var2.m02;
      this.m10 = var1.m10 - var2.m10;
      this.m11 = var1.m11 - var2.m11;
      this.m12 = var1.m12 - var2.m12;
      this.m20 = var1.m20 - var2.m20;
      this.m21 = var1.m21 - var2.m21;
      this.m22 = var1.m22 - var2.m22;
   }

    void sub(Matrix3d var1) {
      this.m00 = this.m00 - var1.m00;
      this.m01 = this.m01 - var1.m01;
      this.m02 = this.m02 - var1.m02;
      this.m10 = this.m10 - var1.m10;
      this.m11 = this.m11 - var1.m11;
      this.m12 = this.m12 - var1.m12;
      this.m20 = this.m20 - var1.m20;
      this.m21 = this.m21 - var1.m21;
      this.m22 = this.m22 - var1.m22;
   }

    void transpose() {
    double var1 = this.m10;
      this.m10 = this.m01;
      this.m01 = var1;
      var1 = this.m20;
      this.m20 = this.m02;
      this.m02 = var1;
      var1 = this.m21;
      this.m21 = this.m12;
      this.m12 = var1;
   }

    void transpose(Matrix3d var1) {
      if (this != var1) {
         this.m00 = var1.m00;
         this.m01 = var1.m10;
         this.m02 = var1.m20;
         this.m10 = var1.m01;
         this.m11 = var1.m11;
         this.m12 = var1.m21;
         this.m20 = var1.m02;
         this.m21 = var1.m12;
         this.m22 = var1.m22;
      } else {
         this.transpose();
      }
   }

    void set(Quat4d var1) {
      this.m00 = 1.0 - 2.0 * var1.y * var1.y - 2.0 * var1.z * var1.z;
      this.m10 = 2.0 * (var1.x * var1.y + var1.w * var1.z);
      this.m20 = 2.0 * (var1.x * var1.z - var1.w * var1.y);
      this.m01 = 2.0 * (var1.x * var1.y - var1.w * var1.z);
      this.m11 = 1.0 - 2.0 * var1.x * var1.x - 2.0 * var1.z * var1.z;
      this.m21 = 2.0 * (var1.y * var1.z + var1.w * var1.x);
      this.m02 = 2.0 * (var1.x * var1.z + var1.w * var1.y);
      this.m12 = 2.0 * (var1.y * var1.z - var1.w * var1.x);
      this.m22 = 1.0 - 2.0 * var1.x * var1.x - 2.0 * var1.y * var1.y;
   }

    void set(AxisAngle4d var1) {
    double var2 = Math.sqrt(var1.x * var1.x + var1.y * var1.y + var1.z * var1.z);
      if (var2 < 1.110223024E-16) {
         this.m00 = 1.0;
         this.m01 = 0.0;
         this.m02 = 0.0;
         this.m10 = 0.0;
         this.m11 = 1.0;
         this.m12 = 0.0;
         this.m20 = 0.0;
         this.m21 = 0.0;
         this.m22 = 1.0;
      } else {
         var2 = 1.0 / var2;
    double var4 = var1.x * var2;
    double var6 = var1.y * var2;
    double var8 = var1.z * var2;
    double var10 = Math.sin(var1.angle);
    double var12 = Math.cos(var1.angle);
    double var14 = 1.0 - var12;
    double var16 = var4 * var8;
    double var18 = var4 * var6;
    double var20 = var6 * var8;
         this.m00 = var14 * var4 * var4 + var12;
         this.m01 = var14 * var18 - var10 * var8;
         this.m02 = var14 * var16 + var10 * var6;
         this.m10 = var14 * var18 + var10 * var8;
         this.m11 = var14 * var6 * var6 + var12;
         this.m12 = var14 * var20 - var10 * var4;
         this.m20 = var14 * var16 - var10 * var6;
         this.m21 = var14 * var20 + var10 * var4;
         this.m22 = var14 * var8 * var8 + var12;
      }
   }

    void set(Quat4f var1) {
      this.m00 = 1.0 - 2.0 * var1.y * var1.y - 2.0 * var1.z * var1.z;
      this.m10 = 2.0 * (var1.x * var1.y + var1.w * var1.z);
      this.m20 = 2.0 * (var1.x * var1.z - var1.w * var1.y);
      this.m01 = 2.0 * (var1.x * var1.y - var1.w * var1.z);
      this.m11 = 1.0 - 2.0 * var1.x * var1.x - 2.0 * var1.z * var1.z;
      this.m21 = 2.0 * (var1.y * var1.z + var1.w * var1.x);
      this.m02 = 2.0 * (var1.x * var1.z + var1.w * var1.y);
      this.m12 = 2.0 * (var1.y * var1.z - var1.w * var1.x);
      this.m22 = 1.0 - 2.0 * var1.x * var1.x - 2.0 * var1.y * var1.y;
   }

    void set(AxisAngle4f var1) {
    double var2 = Math.sqrt(var1.x * var1.x + var1.y * var1.y + var1.z * var1.z);
      if (var2 < 1.110223024E-16) {
         this.m00 = 1.0;
         this.m01 = 0.0;
         this.m02 = 0.0;
         this.m10 = 0.0;
         this.m11 = 1.0;
         this.m12 = 0.0;
         this.m20 = 0.0;
         this.m21 = 0.0;
         this.m22 = 1.0;
      } else {
         var2 = 1.0 / var2;
    double var4 = var1.x * var2;
    double var6 = var1.y * var2;
    double var8 = var1.z * var2;
    double var10 = Math.sin(var1.angle);
    double var12 = Math.cos(var1.angle);
    double var14 = 1.0 - var12;
    double var16 = var4 * var8;
    double var18 = var4 * var6;
    double var20 = var6 * var8;
         this.m00 = var14 * var4 * var4 + var12;
         this.m01 = var14 * var18 - var10 * var8;
         this.m02 = var14 * var16 + var10 * var6;
         this.m10 = var14 * var18 + var10 * var8;
         this.m11 = var14 * var6 * var6 + var12;
         this.m12 = var14 * var20 - var10 * var4;
         this.m20 = var14 * var16 - var10 * var6;
         this.m21 = var14 * var20 + var10 * var4;
         this.m22 = var14 * var8 * var8 + var12;
      }
   }

    void set(Matrix3f var1) {
      this.m00 = var1.m00;
      this.m01 = var1.m01;
      this.m02 = var1.m02;
      this.m10 = var1.m10;
      this.m11 = var1.m11;
      this.m12 = var1.m12;
      this.m20 = var1.m20;
      this.m21 = var1.m21;
      this.m22 = var1.m22;
   }

    void set(Matrix3d var1) {
      this.m00 = var1.m00;
      this.m01 = var1.m01;
      this.m02 = var1.m02;
      this.m10 = var1.m10;
      this.m11 = var1.m11;
      this.m12 = var1.m12;
      this.m20 = var1.m20;
      this.m21 = var1.m21;
      this.m22 = var1.m22;
   }

    void set(double[] var1) {
      this.m00 = var1[0];
      this.m01 = var1[1];
      this.m02 = var1[2];
      this.m10 = var1[3];
      this.m11 = var1[4];
      this.m12 = var1[5];
      this.m20 = var1[6];
      this.m21 = var1[7];
      this.m22 = var1[8];
   }

    void invert(Matrix3d var1) {
      this.invertGeneral(var1);
   }

    void invert() {
      this.invertGeneral(this);
   }

    void invertGeneral(Matrix3d var1) {
      double[] var2 = new double[9];
      int[] var3 = new int[3];
      double[] var7 = new double[]{var1.m00, var1.m01, var1.m02, var1.m10, var1.m11, var1.m12, var1.m20, var1.m21, var1.m22};
      if (!luDecomposition(var7, var3)) {
         throw SingularMatrixException(VecMathI18N.getString("Matrix3d12"));
      } else {
         for (int var4 = 0; var4 < 9; var4++) {
            var2[var4] = 0.0;
         }

         var2[0] = 1.0;
         var2[4] = 1.0;
         var2[8] = 1.0;
         luBacksubstitution(var7, var3, var2);
         this.m00 = var2[0];
         this.m01 = var2[1];
         this.m02 = var2[2];
         this.m10 = var2[3];
         this.m11 = var2[4];
         this.m12 = var2[5];
         this.m20 = var2[6];
         this.m21 = var2[7];
         this.m22 = var2[8];
      }
   }

    static bool luDecomposition(double[] var0, int[] var1) {
      double[] var2 = new double[3];
    int var5 = 0;
    int var6 = 0;
    int var3 = 3;

      while (var3-- != 0) {
    double var7 = 0.0;
    int var4 = 3;

         while (var4-- != 0) {
    double var9 = var0[var5++];
            var9 = Math.abs(var9);
            if (var9 > var7) {
               var7 = var9;
            }
         }

         if (var7 == 0.0) {
    return false;
         }

         var2[var6++] = 1.0 / var7;
      }

    uint8_t var18 = 0;

      for (int var17 = 0; var17 < 3; var17++) {
         for (int var19 = 0; var19 < var17; var19++) {
    int var8 = var18 + 3 * var19 + var17;
    double var11 = var0[var8];
    int var23 = var19;
    int var29 = var18 + 3 * var19;

            for (int var10 = var18 + var17; var23-- != 0; var10 += 3) {
               var11 -= var0[var29] * var0[var10];
               var29++;
            }

            var0[var8] = var11;
         }

    double var13 = 0.0;
         var6 = -1;

         for (int var20 = var17; var20 < 3; var20++) {
    int var26 = var18 + 3 * var20 + var17;
    double var34 = var0[var26];
    int var24 = var17;
    int var30 = var18 + 3 * var20;

            for (int var32 = var18 + var17; var24-- != 0; var32 += 3) {
               var34 -= var0[var30] * var0[var32];
               var30++;
            }

            var0[var26] = var34;
    double var15;
            if ((var15 = var2[var20] * Math.abs(var34)) >= var13) {
               var13 = var15;
               var6 = var20;
            }
         }

         if (var6 < 0) {
            throw RuntimeException(VecMathI18N.getString("Matrix3d13"));
         }

         if (var17 != var6) {
    int var25 = 3;
    int var31 = var18 + 3 * var6;
    int var33 = var18 + 3 * var17;

            while (var25-- != 0) {
    double var35 = var0[var31];
               var0[var31++] = var0[var33];
               var0[var33++] = var35;
            }

            var2[var6] = var2[var17];
         }

         var1[var17] = var6;
         if (var0[var18 + 3 * var17 + var17] == 0.0) {
    return false;
         }

         if (var17 != 2) {
    double var36 = 1.0 / var0[var18 + 3 * var17 + var17];
    int var27 = var18 + 3 * (var17 + 1) + var17;

            for (int var21 = 2 - var17; var21-- != 0; var27 += 3) {
               var0[var27] *= var36;
            }
         }
      }

    return true;
   }

    static void luBacksubstitution(double[] var0, int[] var1, double[] var2) {
    uint8_t var8 = 0;

      for (int var7 = 0; var7 < 3; var7++) {
    int var9 = var7;
    int var4 = -1;

         for (int var3 = 0; var3 < 3; var3++) {
    int var5 = var1[var8 + var3];
    double var11 = var2[var9 + 3 * var5];
            var2[var9 + 3 * var5] = var2[var9 + 3 * var3];
            if (var4 >= 0) {
    int var10 = var3 * 3;

               for (int var6 = var4; var6 <= var3 - 1; var6++) {
                  var11 -= var0[var10 + var6] * var2[var9 + 3 * var6];
               }
            } else if (var11 != 0.0) {
               var4 = var3;
            }

            var2[var9 + 3 * var3] = var11;
         }

    int var13 = 6;
         var2[var9 + 6] = var2[var9 + 6] / var0[var13 + 2];
         var13 -= 3;
         var2[var9 + 3] = (var2[var9 + 3] - var0[var13 + 2] * var2[var9 + 6]) / var0[var13 + 1];
         var13 -= 3;
         var2[var9 + 0] = (var2[var9 + 0] - var0[var13 + 1] * var2[var9 + 3] - var0[var13 + 2] * var2[var9 + 6]) / var0[var13 + 0];
      }
   }

    double determinant() {
      return this.m00 * (this.m11 * this.m22 - this.m12 * this.m21)
         + this.m01 * (this.m12 * this.m20 - this.m10 * this.m22)
         + this.m02 * (this.m10 * this.m21 - this.m11 * this.m20);
   }

    void set(double var1) {
      this.m00 = var1;
      this.m01 = 0.0;
      this.m02 = 0.0;
      this.m10 = 0.0;
      this.m11 = var1;
      this.m12 = 0.0;
      this.m20 = 0.0;
      this.m21 = 0.0;
      this.m22 = var1;
   }

    void rotX(double var1) {
    double var3 = Math.sin(var1);
    double var5 = Math.cos(var1);
      this.m00 = 1.0;
      this.m01 = 0.0;
      this.m02 = 0.0;
      this.m10 = 0.0;
      this.m11 = var5;
      this.m12 = -var3;
      this.m20 = 0.0;
      this.m21 = var3;
      this.m22 = var5;
   }

    void rotY(double var1) {
    double var3 = Math.sin(var1);
    double var5 = Math.cos(var1);
      this.m00 = var5;
      this.m01 = 0.0;
      this.m02 = var3;
      this.m10 = 0.0;
      this.m11 = 1.0;
      this.m12 = 0.0;
      this.m20 = -var3;
      this.m21 = 0.0;
      this.m22 = var5;
   }

    void rotZ(double var1) {
    double var3 = Math.sin(var1);
    double var5 = Math.cos(var1);
      this.m00 = var5;
      this.m01 = -var3;
      this.m02 = 0.0;
      this.m10 = var3;
      this.m11 = var5;
      this.m12 = 0.0;
      this.m20 = 0.0;
      this.m21 = 0.0;
      this.m22 = 1.0;
   }

    void mul(double var1) {
      this.m00 *= var1;
      this.m01 *= var1;
      this.m02 *= var1;
      this.m10 *= var1;
      this.m11 *= var1;
      this.m12 *= var1;
      this.m20 *= var1;
      this.m21 *= var1;
      this.m22 *= var1;
   }

    void mul(double var1, Matrix3d var3) {
      this.m00 = var1 * var3.m00;
      this.m01 = var1 * var3.m01;
      this.m02 = var1 * var3.m02;
      this.m10 = var1 * var3.m10;
      this.m11 = var1 * var3.m11;
      this.m12 = var1 * var3.m12;
      this.m20 = var1 * var3.m20;
      this.m21 = var1 * var3.m21;
      this.m22 = var1 * var3.m22;
   }

    void mul(Matrix3d var1) {
    double var2 = this.m00 * var1.m00 + this.m01 * var1.m10 + this.m02 * var1.m20;
    double var4 = this.m00 * var1.m01 + this.m01 * var1.m11 + this.m02 * var1.m21;
    double var6 = this.m00 * var1.m02 + this.m01 * var1.m12 + this.m02 * var1.m22;
    double var8 = this.m10 * var1.m00 + this.m11 * var1.m10 + this.m12 * var1.m20;
    double var10 = this.m10 * var1.m01 + this.m11 * var1.m11 + this.m12 * var1.m21;
    double var12 = this.m10 * var1.m02 + this.m11 * var1.m12 + this.m12 * var1.m22;
    double var14 = this.m20 * var1.m00 + this.m21 * var1.m10 + this.m22 * var1.m20;
    double var16 = this.m20 * var1.m01 + this.m21 * var1.m11 + this.m22 * var1.m21;
    double var18 = this.m20 * var1.m02 + this.m21 * var1.m12 + this.m22 * var1.m22;
      this.m00 = var2;
      this.m01 = var4;
      this.m02 = var6;
      this.m10 = var8;
      this.m11 = var10;
      this.m12 = var12;
      this.m20 = var14;
      this.m21 = var16;
      this.m22 = var18;
   }

    void mul(Matrix3d var1, Matrix3d var2) {
      if (this != var1 && this != var2) {
         this.m00 = var1.m00 * var2.m00 + var1.m01 * var2.m10 + var1.m02 * var2.m20;
         this.m01 = var1.m00 * var2.m01 + var1.m01 * var2.m11 + var1.m02 * var2.m21;
         this.m02 = var1.m00 * var2.m02 + var1.m01 * var2.m12 + var1.m02 * var2.m22;
         this.m10 = var1.m10 * var2.m00 + var1.m11 * var2.m10 + var1.m12 * var2.m20;
         this.m11 = var1.m10 * var2.m01 + var1.m11 * var2.m11 + var1.m12 * var2.m21;
         this.m12 = var1.m10 * var2.m02 + var1.m11 * var2.m12 + var1.m12 * var2.m22;
         this.m20 = var1.m20 * var2.m00 + var1.m21 * var2.m10 + var1.m22 * var2.m20;
         this.m21 = var1.m20 * var2.m01 + var1.m21 * var2.m11 + var1.m22 * var2.m21;
         this.m22 = var1.m20 * var2.m02 + var1.m21 * var2.m12 + var1.m22 * var2.m22;
      } else {
    double var3 = var1.m00 * var2.m00 + var1.m01 * var2.m10 + var1.m02 * var2.m20;
    double var5 = var1.m00 * var2.m01 + var1.m01 * var2.m11 + var1.m02 * var2.m21;
    double var7 = var1.m00 * var2.m02 + var1.m01 * var2.m12 + var1.m02 * var2.m22;
    double var9 = var1.m10 * var2.m00 + var1.m11 * var2.m10 + var1.m12 * var2.m20;
    double var11 = var1.m10 * var2.m01 + var1.m11 * var2.m11 + var1.m12 * var2.m21;
    double var13 = var1.m10 * var2.m02 + var1.m11 * var2.m12 + var1.m12 * var2.m22;
    double var15 = var1.m20 * var2.m00 + var1.m21 * var2.m10 + var1.m22 * var2.m20;
    double var17 = var1.m20 * var2.m01 + var1.m21 * var2.m11 + var1.m22 * var2.m21;
    double var19 = var1.m20 * var2.m02 + var1.m21 * var2.m12 + var1.m22 * var2.m22;
         this.m00 = var3;
         this.m01 = var5;
         this.m02 = var7;
         this.m10 = var9;
         this.m11 = var11;
         this.m12 = var13;
         this.m20 = var15;
         this.m21 = var17;
         this.m22 = var19;
      }
   }

    void mulNormalize(Matrix3d var1) {
      double[] var2 = new double[9];
      double[] var3 = new double[9];
      double[] var4 = new double[3];
      var2[0] = this.m00 * var1.m00 + this.m01 * var1.m10 + this.m02 * var1.m20;
      var2[1] = this.m00 * var1.m01 + this.m01 * var1.m11 + this.m02 * var1.m21;
      var2[2] = this.m00 * var1.m02 + this.m01 * var1.m12 + this.m02 * var1.m22;
      var2[3] = this.m10 * var1.m00 + this.m11 * var1.m10 + this.m12 * var1.m20;
      var2[4] = this.m10 * var1.m01 + this.m11 * var1.m11 + this.m12 * var1.m21;
      var2[5] = this.m10 * var1.m02 + this.m11 * var1.m12 + this.m12 * var1.m22;
      var2[6] = this.m20 * var1.m00 + this.m21 * var1.m10 + this.m22 * var1.m20;
      var2[7] = this.m20 * var1.m01 + this.m21 * var1.m11 + this.m22 * var1.m21;
      var2[8] = this.m20 * var1.m02 + this.m21 * var1.m12 + this.m22 * var1.m22;
      compute_svd(var2, var4, var3);
      this.m00 = var3[0];
      this.m01 = var3[1];
      this.m02 = var3[2];
      this.m10 = var3[3];
      this.m11 = var3[4];
      this.m12 = var3[5];
      this.m20 = var3[6];
      this.m21 = var3[7];
      this.m22 = var3[8];
   }

    void mulNormalize(Matrix3d var1, Matrix3d var2) {
      double[] var3 = new double[9];
      double[] var4 = new double[9];
      double[] var5 = new double[3];
      var3[0] = var1.m00 * var2.m00 + var1.m01 * var2.m10 + var1.m02 * var2.m20;
      var3[1] = var1.m00 * var2.m01 + var1.m01 * var2.m11 + var1.m02 * var2.m21;
      var3[2] = var1.m00 * var2.m02 + var1.m01 * var2.m12 + var1.m02 * var2.m22;
      var3[3] = var1.m10 * var2.m00 + var1.m11 * var2.m10 + var1.m12 * var2.m20;
      var3[4] = var1.m10 * var2.m01 + var1.m11 * var2.m11 + var1.m12 * var2.m21;
      var3[5] = var1.m10 * var2.m02 + var1.m11 * var2.m12 + var1.m12 * var2.m22;
      var3[6] = var1.m20 * var2.m00 + var1.m21 * var2.m10 + var1.m22 * var2.m20;
      var3[7] = var1.m20 * var2.m01 + var1.m21 * var2.m11 + var1.m22 * var2.m21;
      var3[8] = var1.m20 * var2.m02 + var1.m21 * var2.m12 + var1.m22 * var2.m22;
      compute_svd(var3, var5, var4);
      this.m00 = var4[0];
      this.m01 = var4[1];
      this.m02 = var4[2];
      this.m10 = var4[3];
      this.m11 = var4[4];
      this.m12 = var4[5];
      this.m20 = var4[6];
      this.m21 = var4[7];
      this.m22 = var4[8];
   }

    void mulTransposeBoth(Matrix3d var1, Matrix3d var2) {
      if (this != var1 && this != var2) {
         this.m00 = var1.m00 * var2.m00 + var1.m10 * var2.m01 + var1.m20 * var2.m02;
         this.m01 = var1.m00 * var2.m10 + var1.m10 * var2.m11 + var1.m20 * var2.m12;
         this.m02 = var1.m00 * var2.m20 + var1.m10 * var2.m21 + var1.m20 * var2.m22;
         this.m10 = var1.m01 * var2.m00 + var1.m11 * var2.m01 + var1.m21 * var2.m02;
         this.m11 = var1.m01 * var2.m10 + var1.m11 * var2.m11 + var1.m21 * var2.m12;
         this.m12 = var1.m01 * var2.m20 + var1.m11 * var2.m21 + var1.m21 * var2.m22;
         this.m20 = var1.m02 * var2.m00 + var1.m12 * var2.m01 + var1.m22 * var2.m02;
         this.m21 = var1.m02 * var2.m10 + var1.m12 * var2.m11 + var1.m22 * var2.m12;
         this.m22 = var1.m02 * var2.m20 + var1.m12 * var2.m21 + var1.m22 * var2.m22;
      } else {
    double var3 = var1.m00 * var2.m00 + var1.m10 * var2.m01 + var1.m20 * var2.m02;
    double var5 = var1.m00 * var2.m10 + var1.m10 * var2.m11 + var1.m20 * var2.m12;
    double var7 = var1.m00 * var2.m20 + var1.m10 * var2.m21 + var1.m20 * var2.m22;
    double var9 = var1.m01 * var2.m00 + var1.m11 * var2.m01 + var1.m21 * var2.m02;
    double var11 = var1.m01 * var2.m10 + var1.m11 * var2.m11 + var1.m21 * var2.m12;
    double var13 = var1.m01 * var2.m20 + var1.m11 * var2.m21 + var1.m21 * var2.m22;
    double var15 = var1.m02 * var2.m00 + var1.m12 * var2.m01 + var1.m22 * var2.m02;
    double var17 = var1.m02 * var2.m10 + var1.m12 * var2.m11 + var1.m22 * var2.m12;
    double var19 = var1.m02 * var2.m20 + var1.m12 * var2.m21 + var1.m22 * var2.m22;
         this.m00 = var3;
         this.m01 = var5;
         this.m02 = var7;
         this.m10 = var9;
         this.m11 = var11;
         this.m12 = var13;
         this.m20 = var15;
         this.m21 = var17;
         this.m22 = var19;
      }
   }

    void mulTransposeRight(Matrix3d var1, Matrix3d var2) {
      if (this != var1 && this != var2) {
         this.m00 = var1.m00 * var2.m00 + var1.m01 * var2.m01 + var1.m02 * var2.m02;
         this.m01 = var1.m00 * var2.m10 + var1.m01 * var2.m11 + var1.m02 * var2.m12;
         this.m02 = var1.m00 * var2.m20 + var1.m01 * var2.m21 + var1.m02 * var2.m22;
         this.m10 = var1.m10 * var2.m00 + var1.m11 * var2.m01 + var1.m12 * var2.m02;
         this.m11 = var1.m10 * var2.m10 + var1.m11 * var2.m11 + var1.m12 * var2.m12;
         this.m12 = var1.m10 * var2.m20 + var1.m11 * var2.m21 + var1.m12 * var2.m22;
         this.m20 = var1.m20 * var2.m00 + var1.m21 * var2.m01 + var1.m22 * var2.m02;
         this.m21 = var1.m20 * var2.m10 + var1.m21 * var2.m11 + var1.m22 * var2.m12;
         this.m22 = var1.m20 * var2.m20 + var1.m21 * var2.m21 + var1.m22 * var2.m22;
      } else {
    double var3 = var1.m00 * var2.m00 + var1.m01 * var2.m01 + var1.m02 * var2.m02;
    double var5 = var1.m00 * var2.m10 + var1.m01 * var2.m11 + var1.m02 * var2.m12;
    double var7 = var1.m00 * var2.m20 + var1.m01 * var2.m21 + var1.m02 * var2.m22;
    double var9 = var1.m10 * var2.m00 + var1.m11 * var2.m01 + var1.m12 * var2.m02;
    double var11 = var1.m10 * var2.m10 + var1.m11 * var2.m11 + var1.m12 * var2.m12;
    double var13 = var1.m10 * var2.m20 + var1.m11 * var2.m21 + var1.m12 * var2.m22;
    double var15 = var1.m20 * var2.m00 + var1.m21 * var2.m01 + var1.m22 * var2.m02;
    double var17 = var1.m20 * var2.m10 + var1.m21 * var2.m11 + var1.m22 * var2.m12;
    double var19 = var1.m20 * var2.m20 + var1.m21 * var2.m21 + var1.m22 * var2.m22;
         this.m00 = var3;
         this.m01 = var5;
         this.m02 = var7;
         this.m10 = var9;
         this.m11 = var11;
         this.m12 = var13;
         this.m20 = var15;
         this.m21 = var17;
         this.m22 = var19;
      }
   }

    void mulTransposeLeft(Matrix3d var1, Matrix3d var2) {
      if (this != var1 && this != var2) {
         this.m00 = var1.m00 * var2.m00 + var1.m10 * var2.m10 + var1.m20 * var2.m20;
         this.m01 = var1.m00 * var2.m01 + var1.m10 * var2.m11 + var1.m20 * var2.m21;
         this.m02 = var1.m00 * var2.m02 + var1.m10 * var2.m12 + var1.m20 * var2.m22;
         this.m10 = var1.m01 * var2.m00 + var1.m11 * var2.m10 + var1.m21 * var2.m20;
         this.m11 = var1.m01 * var2.m01 + var1.m11 * var2.m11 + var1.m21 * var2.m21;
         this.m12 = var1.m01 * var2.m02 + var1.m11 * var2.m12 + var1.m21 * var2.m22;
         this.m20 = var1.m02 * var2.m00 + var1.m12 * var2.m10 + var1.m22 * var2.m20;
         this.m21 = var1.m02 * var2.m01 + var1.m12 * var2.m11 + var1.m22 * var2.m21;
         this.m22 = var1.m02 * var2.m02 + var1.m12 * var2.m12 + var1.m22 * var2.m22;
      } else {
    double var3 = var1.m00 * var2.m00 + var1.m10 * var2.m10 + var1.m20 * var2.m20;
    double var5 = var1.m00 * var2.m01 + var1.m10 * var2.m11 + var1.m20 * var2.m21;
    double var7 = var1.m00 * var2.m02 + var1.m10 * var2.m12 + var1.m20 * var2.m22;
    double var9 = var1.m01 * var2.m00 + var1.m11 * var2.m10 + var1.m21 * var2.m20;
    double var11 = var1.m01 * var2.m01 + var1.m11 * var2.m11 + var1.m21 * var2.m21;
    double var13 = var1.m01 * var2.m02 + var1.m11 * var2.m12 + var1.m21 * var2.m22;
    double var15 = var1.m02 * var2.m00 + var1.m12 * var2.m10 + var1.m22 * var2.m20;
    double var17 = var1.m02 * var2.m01 + var1.m12 * var2.m11 + var1.m22 * var2.m21;
    double var19 = var1.m02 * var2.m02 + var1.m12 * var2.m12 + var1.m22 * var2.m22;
         this.m00 = var3;
         this.m01 = var5;
         this.m02 = var7;
         this.m10 = var9;
         this.m11 = var11;
         this.m12 = var13;
         this.m20 = var15;
         this.m21 = var17;
         this.m22 = var19;
      }
   }

    void normalize() {
      double[] var1 = new double[9];
      double[] var2 = new double[3];
      this.getScaleRotate(var2, var1);
      this.m00 = var1[0];
      this.m01 = var1[1];
      this.m02 = var1[2];
      this.m10 = var1[3];
      this.m11 = var1[4];
      this.m12 = var1[5];
      this.m20 = var1[6];
      this.m21 = var1[7];
      this.m22 = var1[8];
   }

    void normalize(Matrix3d var1) {
      double[] var2 = new double[9];
      double[] var3 = new double[9];
      double[] var4 = new double[3];
      var2[0] = var1.m00;
      var2[1] = var1.m01;
      var2[2] = var1.m02;
      var2[3] = var1.m10;
      var2[4] = var1.m11;
      var2[5] = var1.m12;
      var2[6] = var1.m20;
      var2[7] = var1.m21;
      var2[8] = var1.m22;
      compute_svd(var2, var4, var3);
      this.m00 = var3[0];
      this.m01 = var3[1];
      this.m02 = var3[2];
      this.m10 = var3[3];
      this.m11 = var3[4];
      this.m12 = var3[5];
      this.m20 = var3[6];
      this.m21 = var3[7];
      this.m22 = var3[8];
   }

    void normalizeCP() {
    double var1 = 1.0 / Math.sqrt(this.m00 * this.m00 + this.m10 * this.m10 + this.m20 * this.m20);
      this.m00 *= var1;
      this.m10 *= var1;
      this.m20 *= var1;
      var1 = 1.0 / Math.sqrt(this.m01 * this.m01 + this.m11 * this.m11 + this.m21 * this.m21);
      this.m01 *= var1;
      this.m11 *= var1;
      this.m21 *= var1;
      this.m02 = this.m10 * this.m21 - this.m11 * this.m20;
      this.m12 = this.m01 * this.m20 - this.m00 * this.m21;
      this.m22 = this.m00 * this.m11 - this.m01 * this.m10;
   }

    void normalizeCP(Matrix3d var1) {
    double var2 = 1.0 / Math.sqrt(var1.m00 * var1.m00 + var1.m10 * var1.m10 + var1.m20 * var1.m20);
      this.m00 = var1.m00 * var2;
      this.m10 = var1.m10 * var2;
      this.m20 = var1.m20 * var2;
      var2 = 1.0 / Math.sqrt(var1.m01 * var1.m01 + var1.m11 * var1.m11 + var1.m21 * var1.m21);
      this.m01 = var1.m01 * var2;
      this.m11 = var1.m11 * var2;
      this.m21 = var1.m21 * var2;
      this.m02 = this.m10 * this.m21 - this.m11 * this.m20;
      this.m12 = this.m01 * this.m20 - this.m00 * this.m21;
      this.m22 = this.m00 * this.m11 - this.m01 * this.m10;
   }

    bool equals(Matrix3d var1) {
      try {
         return this.m00 == var1.m00
            && this.m01 == var1.m01
            && this.m02 == var1.m02
            && this.m10 == var1.m10
            && this.m11 == var1.m11
            && this.m12 == var1.m12
            && this.m20 == var1.m20
            && this.m21 == var1.m21
            && this.m22 == var1.m22;
      } catch (NullPointerException var3) {
    return false;
      }
   }

    bool equals(void* var1) {
      try {
    Matrix3d var2 = (Matrix3d)var1;
         return this.m00 == var2.m00
            && this.m01 == var2.m01
            && this.m02 == var2.m02
            && this.m10 == var2.m10
            && this.m11 == var2.m11
            && this.m12 == var2.m12
            && this.m20 == var2.m20
            && this.m21 == var2.m21
            && this.m22 == var2.m22;
      } catch (ClassCastException var3) {
    return false;
      } catch (NullPointerException var4) {
    return false;
      }
   }

    bool epsilonEquals(Matrix3d var1, double var2) {
    double var4 = this.m00 - var1.m00;
      if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
      } else {
         var4 = this.m01 - var1.m01;
         if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
         } else {
            var4 = this.m02 - var1.m02;
            if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
            } else {
               var4 = this.m10 - var1.m10;
               if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
               } else {
                  var4 = this.m11 - var1.m11;
                  if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
                  } else {
                     var4 = this.m12 - var1.m12;
                     if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
                     } else {
                        var4 = this.m20 - var1.m20;
                        if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
                        } else {
                           var4 = this.m21 - var1.m21;
                           if ((var4 < 0.0 ? -var4 : var4) > var2) {
    return false;
                           } else {
                              var4 = this.m22 - var1.m22;
                              return !((var4 < 0.0 ? -var4 : var4) > var2);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    int hashCode() {
    long var1 = 1L;
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m00);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m01);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m02);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m10);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m11);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m12);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m20);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m21);
      var1 = 31L * var1 + VecMathUtil.doubleToLongBits(this.m22);
      return (int)(var1 ^ var1 >> 32);
   }

    void setZero() {
      this.m00 = 0.0;
      this.m01 = 0.0;
      this.m02 = 0.0;
      this.m10 = 0.0;
      this.m11 = 0.0;
      this.m12 = 0.0;
      this.m20 = 0.0;
      this.m21 = 0.0;
      this.m22 = 0.0;
   }

    void negate() {
      this.m00 = -this.m00;
      this.m01 = -this.m01;
      this.m02 = -this.m02;
      this.m10 = -this.m10;
      this.m11 = -this.m11;
      this.m12 = -this.m12;
      this.m20 = -this.m20;
      this.m21 = -this.m21;
      this.m22 = -this.m22;
   }

    void negate(Matrix3d var1) {
      this.m00 = -var1.m00;
      this.m01 = -var1.m01;
      this.m02 = -var1.m02;
      this.m10 = -var1.m10;
      this.m11 = -var1.m11;
      this.m12 = -var1.m12;
      this.m20 = -var1.m20;
      this.m21 = -var1.m21;
      this.m22 = -var1.m22;
   }

    void transform(Tuple3d var1) {
    double var2 = this.m00 * var1.x + this.m01 * var1.y + this.m02 * var1.z;
    double var4 = this.m10 * var1.x + this.m11 * var1.y + this.m12 * var1.z;
    double var6 = this.m20 * var1.x + this.m21 * var1.y + this.m22 * var1.z;
      var1.set(var2, var4, var6);
   }

    void transform(Tuple3d var1, Tuple3d var2) {
    double var3 = this.m00 * var1.x + this.m01 * var1.y + this.m02 * var1.z;
    double var5 = this.m10 * var1.x + this.m11 * var1.y + this.m12 * var1.z;
      var2.z = this.m20 * var1.x + this.m21 * var1.y + this.m22 * var1.z;
      var2.x = var3;
      var2.y = var5;
   }

    void getScaleRotate(double[] var1, double[] var2) {
      double[] var3 = new double[]{this.m00, this.m01, this.m02, this.m10, this.m11, this.m12, this.m20, this.m21, this.m22};
      compute_svd(var3, var1, var2);
   }

    static void compute_svd(double[] var0, double[] var1, double[] var2) {
      double[] var9 = new double[9];
      double[] var10 = new double[9];
      double[] var11 = new double[9];
      double[] var12 = new double[9];
      double[] var15 = new double[9];
      double[] var16 = new double[3];
      double[] var17 = new double[3];
    int var19 = 0;

      for (int var3 = 0; var3 < 9; var3++) {
         var15[var3] = var0[var3];
      }

      if (var0[3] * var0[3] < 1.110223024E-16) {
         var9[0] = 1.0;
         var9[1] = 0.0;
         var9[2] = 0.0;
         var9[3] = 0.0;
         var9[4] = 1.0;
         var9[5] = 0.0;
         var9[6] = 0.0;
         var9[7] = 0.0;
         var9[8] = 1.0;
      } else if (var0[0] * var0[0] < 1.110223024E-16) {
         var11[0] = var0[0];
         var11[1] = var0[1];
         var11[2] = var0[2];
         var0[0] = var0[3];
         var0[1] = var0[4];
         var0[2] = var0[5];
         var0[3] = -var11[0];
         var0[4] = -var11[1];
         var0[5] = -var11[2];
         var9[0] = 0.0;
         var9[1] = 1.0;
         var9[2] = 0.0;
         var9[3] = -1.0;
         var9[4] = 0.0;
         var9[5] = 0.0;
         var9[6] = 0.0;
         var9[7] = 0.0;
         var9[8] = 1.0;
      } else {
    double var5 = 1.0 / Math.sqrt(var0[0] * var0[0] + var0[3] * var0[3]);
    double var24 = var0[0] * var5;
    double var32 = var0[3] * var5;
         var11[0] = var24 * var0[0] + var32 * var0[3];
         var11[1] = var24 * var0[1] + var32 * var0[4];
         var11[2] = var24 * var0[2] + var32 * var0[5];
         var0[3] = -var32 * var0[0] + var24 * var0[3];
         var0[4] = -var32 * var0[1] + var24 * var0[4];
         var0[5] = -var32 * var0[2] + var24 * var0[5];
         var0[0] = var11[0];
         var0[1] = var11[1];
         var0[2] = var11[2];
         var9[0] = var24;
         var9[1] = var32;
         var9[2] = 0.0;
         var9[3] = -var32;
         var9[4] = var24;
         var9[5] = 0.0;
         var9[6] = 0.0;
         var9[7] = 0.0;
         var9[8] = 1.0;
      }

      if (!(var0[6] * var0[6] < 1.110223024E-16)) {
         if (var0[0] * var0[0] < 1.110223024E-16) {
            var11[0] = var0[0];
            var11[1] = var0[1];
            var11[2] = var0[2];
            var0[0] = var0[6];
            var0[1] = var0[7];
            var0[2] = var0[8];
            var0[6] = -var11[0];
            var0[7] = -var11[1];
            var0[8] = -var11[2];
            var11[0] = var9[0];
            var11[1] = var9[1];
            var11[2] = var9[2];
            var9[0] = var9[6];
            var9[1] = var9[7];
            var9[2] = var9[8];
            var9[6] = -var11[0];
            var9[7] = -var11[1];
            var9[8] = -var11[2];
         } else {
    double var48 = 1.0 / Math.sqrt(var0[0] * var0[0] + var0[6] * var0[6]);
    double var26 = var0[0] * var48;
    double var34 = var0[6] * var48;
            var11[0] = var26 * var0[0] + var34 * var0[6];
            var11[1] = var26 * var0[1] + var34 * var0[7];
            var11[2] = var26 * var0[2] + var34 * var0[8];
            var0[6] = -var34 * var0[0] + var26 * var0[6];
            var0[7] = -var34 * var0[1] + var26 * var0[7];
            var0[8] = -var34 * var0[2] + var26 * var0[8];
            var0[0] = var11[0];
            var0[1] = var11[1];
            var0[2] = var11[2];
            var11[0] = var26 * var9[0];
            var11[1] = var26 * var9[1];
            var9[2] = var34;
            var11[6] = -var9[0] * var34;
            var11[7] = -var9[1] * var34;
            var9[8] = var26;
            var9[0] = var11[0];
            var9[1] = var11[1];
            var9[6] = var11[6];
            var9[7] = var11[7];
         }
      }

      if (var0[2] * var0[2] < 1.110223024E-16) {
         var10[0] = 1.0;
         var10[1] = 0.0;
         var10[2] = 0.0;
         var10[3] = 0.0;
         var10[4] = 1.0;
         var10[5] = 0.0;
         var10[6] = 0.0;
         var10[7] = 0.0;
         var10[8] = 1.0;
      } else if (var0[1] * var0[1] < 1.110223024E-16) {
         var11[2] = var0[2];
         var11[5] = var0[5];
         var11[8] = var0[8];
         var0[2] = -var0[1];
         var0[5] = -var0[4];
         var0[8] = -var0[7];
         var0[1] = var11[2];
         var0[4] = var11[5];
         var0[7] = var11[8];
         var10[0] = 1.0;
         var10[1] = 0.0;
         var10[2] = 0.0;
         var10[3] = 0.0;
         var10[4] = 0.0;
         var10[5] = -1.0;
         var10[6] = 0.0;
         var10[7] = 1.0;
         var10[8] = 0.0;
      } else {
    double var49 = 1.0 / Math.sqrt(var0[1] * var0[1] + var0[2] * var0[2]);
    double var28 = var0[1] * var49;
    double var36 = var0[2] * var49;
         var11[1] = var28 * var0[1] + var36 * var0[2];
         var0[2] = -var36 * var0[1] + var28 * var0[2];
         var0[1] = var11[1];
         var11[4] = var28 * var0[4] + var36 * var0[5];
         var0[5] = -var36 * var0[4] + var28 * var0[5];
         var0[4] = var11[4];
         var11[7] = var28 * var0[7] + var36 * var0[8];
         var0[8] = -var36 * var0[7] + var28 * var0[8];
         var0[7] = var11[7];
         var10[0] = 1.0;
         var10[1] = 0.0;
         var10[2] = 0.0;
         var10[3] = 0.0;
         var10[4] = var28;
         var10[5] = -var36;
         var10[6] = 0.0;
         var10[7] = var36;
         var10[8] = var28;
      }

      if (!(var0[7] * var0[7] < 1.110223024E-16)) {
         if (var0[4] * var0[4] < 1.110223024E-16) {
            var11[3] = var0[3];
            var11[4] = var0[4];
            var11[5] = var0[5];
            var0[3] = var0[6];
            var0[4] = var0[7];
            var0[5] = var0[8];
            var0[6] = -var11[3];
            var0[7] = -var11[4];
            var0[8] = -var11[5];
            var11[3] = var9[3];
            var11[4] = var9[4];
            var11[5] = var9[5];
            var9[3] = var9[6];
            var9[4] = var9[7];
            var9[5] = var9[8];
            var9[6] = -var11[3];
            var9[7] = -var11[4];
            var9[8] = -var11[5];
         } else {
    double var50 = 1.0 / Math.sqrt(var0[4] * var0[4] + var0[7] * var0[7]);
    double var30 = var0[4] * var50;
    double var38 = var0[7] * var50;
            var11[3] = var30 * var0[3] + var38 * var0[6];
            var0[6] = -var38 * var0[3] + var30 * var0[6];
            var0[3] = var11[3];
            var11[4] = var30 * var0[4] + var38 * var0[7];
            var0[7] = -var38 * var0[4] + var30 * var0[7];
            var0[4] = var11[4];
            var11[5] = var30 * var0[5] + var38 * var0[8];
            var0[8] = -var38 * var0[5] + var30 * var0[8];
            var0[5] = var11[5];
            var11[3] = var30 * var9[3] + var38 * var9[6];
            var9[6] = -var38 * var9[3] + var30 * var9[6];
            var9[3] = var11[3];
            var11[4] = var30 * var9[4] + var38 * var9[7];
            var9[7] = -var38 * var9[4] + var30 * var9[7];
            var9[4] = var11[4];
            var11[5] = var30 * var9[5] + var38 * var9[8];
            var9[8] = -var38 * var9[5] + var30 * var9[8];
            var9[5] = var11[5];
         }
      }

      var12[0] = var0[0];
      var12[1] = var0[4];
      var12[2] = var0[8];
      var16[0] = var0[1];
      var16[1] = var0[5];
      if (!(var16[0] * var16[0] < 1.110223024E-16) || !(var16[1] * var16[1] < 1.110223024E-16)) {
         compute_qr(var12, var16, var9, var10);
      }

      var17[0] = var12[0];
      var17[1] = var12[1];
      var17[2] = var12[2];
      if (almostEqual(Math.abs(var17[0]), 1.0) && almostEqual(Math.abs(var17[1]), 1.0) && almostEqual(Math.abs(var17[2]), 1.0)) {
         for (int var46 = 0; var46 < 3; var46++) {
            if (var17[var46] < 0.0) {
               var19++;
            }
         }

         if (var19 == 0 || var19 == 2) {
            var1[0] = var1[1] = var1[2] = 1.0;

            for (int var47 = 0; var47 < 9; var47++) {
               var2[var47] = var15[var47];
            }

            return;
         }
      }

      transpose_mat(var9, var11);
      transpose_mat(var10, var12);
      svdReorder(var0, var11, var12, var17, var2, var1);
   }

    static void svdReorder(double[] var0, double[] var1, double[] var2, double[] var3, double[] var4, double[] var5) {
      int[] var6 = new int[3];
      int[] var7 = new int[3];
      double[] var13 = new double[3];
      double[] var14 = new double[9];
      if (var3[0] < 0.0) {
         var3[0] = -var3[0];
         var2[0] = -var2[0];
         var2[1] = -var2[1];
         var2[2] = -var2[2];
      }

      if (var3[1] < 0.0) {
         var3[1] = -var3[1];
         var2[3] = -var2[3];
         var2[4] = -var2[4];
         var2[5] = -var2[5];
      }

      if (var3[2] < 0.0) {
         var3[2] = -var3[2];
         var2[6] = -var2[6];
         var2[7] = -var2[7];
         var2[8] = -var2[8];
      }

      mat_mul(var1, var2, var14);
      if (almostEqual(Math.abs(var3[0]), Math.abs(var3[1])) && almostEqual(Math.abs(var3[1]), Math.abs(var3[2]))) {
         for (int var12 = 0; var12 < 9; var12++) {
            var4[var12] = var14[var12];
         }

         for (int var26 = 0; var26 < 3; var26++) {
            var5[var26] = var3[var26];
         }
      } else {
         if (var3[0] > var3[1]) {
            if (var3[0] > var3[2]) {
               if (var3[2] > var3[1]) {
                  var6[0] = 0;
                  var6[1] = 2;
                  var6[2] = 1;
               } else {
                  var6[0] = 0;
                  var6[1] = 1;
                  var6[2] = 2;
               }
            } else {
               var6[0] = 2;
               var6[1] = 0;
               var6[2] = 1;
            }
         } else if (var3[1] > var3[2]) {
            if (var3[2] > var3[0]) {
               var6[0] = 1;
               var6[1] = 2;
               var6[2] = 0;
            } else {
               var6[0] = 1;
               var6[1] = 0;
               var6[2] = 2;
            }
         } else {
            var6[0] = 2;
            var6[1] = 1;
            var6[2] = 0;
         }

         var13[0] = var0[0] * var0[0] + var0[1] * var0[1] + var0[2] * var0[2];
         var13[1] = var0[3] * var0[3] + var0[4] * var0[4] + var0[5] * var0[5];
         var13[2] = var0[6] * var0[6] + var0[7] * var0[7] + var0[8] * var0[8];
    uint8_t var8;
    uint8_t var9;
    uint8_t var10;
         if (var13[0] > var13[1]) {
            if (var13[0] > var13[2]) {
               if (var13[2] > var13[1]) {
                  var8 = 0;
                  var10 = 1;
                  var9 = 2;
               } else {
                  var8 = 0;
                  var9 = 1;
                  var10 = 2;
               }
            } else {
               var10 = 0;
               var8 = 1;
               var9 = 2;
            }
         } else if (var13[1] > var13[2]) {
            if (var13[2] > var13[0]) {
               var9 = 0;
               var10 = 1;
               var8 = 2;
            } else {
               var9 = 0;
               var8 = 1;
               var10 = 2;
            }
         } else {
            var10 = 0;
            var9 = 1;
            var8 = 2;
         }

    int var11 = var6[var8];
         var5[0] = var3[var11];
         var11 = var6[var9];
         var5[1] = var3[var11];
         var11 = var6[var10];
         var5[2] = var3[var11];
         var11 = var6[var8];
         var4[0] = var14[var11];
         var11 = var6[var8] + 3;
         var4[3] = var14[var11];
         var11 = var6[var8] + 6;
         var4[6] = var14[var11];
         var11 = var6[var9];
         var4[1] = var14[var11];
         var11 = var6[var9] + 3;
         var4[4] = var14[var11];
         var11 = var6[var9] + 6;
         var4[7] = var14[var11];
         var11 = var6[var10];
         var4[2] = var14[var11];
         var11 = var6[var10] + 3;
         var4[5] = var14[var11];
         var11 = var6[var10] + 6;
         var4[8] = var14[var11];
      }
   }

    static int compute_qr(double[] var0, double[] var1, double[] var2, double[] var3) {
      double[] var16 = new double[2];
      double[] var17 = new double[2];
      double[] var18 = new double[2];
      double[] var19 = new double[2];
      double[] var20 = new double[9];
    double var29 = 1.0;
    double var31 = -1.0;
    bool var7 = false;
    uint8_t var33 = 1;
      if (Math.abs(var1[1]) < 4.89E-15 || Math.abs(var1[0]) < 4.89E-15) {
         var7 = true;
      }

      for (int var6 = 0; var6 < 10 && !var7; var6++) {
    double var8 = compute_shift(var0[1], var1[1], var0[2]);
    double var25 = (Math.abs(var0[0]) - var8) * (d_sign(var29, var0[0]) + var8 / var0[0]);
    double var27 = var1[0];
    double var14 = compute_rot(var25, var27, var19, var17, 0, var33);
         var25 = var17[0] * var0[0] + var19[0] * var1[0];
         var1[0] = var17[0] * var1[0] - var19[0] * var0[0];
         var27 = var19[0] * var0[1];
         var0[1] = var17[0] * var0[1];
         var14 = compute_rot(var25, var27, var18, var16, 0, var33);
         var33 = 0;
         var0[0] = var14;
         var25 = var16[0] * var1[0] + var18[0] * var0[1];
         var0[1] = var16[0] * var0[1] - var18[0] * var1[0];
         var27 = var18[0] * var1[1];
         var1[1] = var16[0] * var1[1];
         var14 = compute_rot(var25, var27, var19, var17, 1, var33);
         var1[0] = var14;
         var25 = var17[1] * var0[1] + var19[1] * var1[1];
         var1[1] = var17[1] * var1[1] - var19[1] * var0[1];
         var27 = var19[1] * var0[2];
         var0[2] = var17[1] * var0[2];
         var14 = compute_rot(var25, var27, var18, var16, 1, var33);
         var0[1] = var14;
         var25 = var16[1] * var1[1] + var18[1] * var0[2];
         var0[2] = var16[1] * var0[2] - var18[1] * var1[1];
         var1[1] = var25;
    double var21 = var2[0];
         var2[0] = var16[0] * var21 + var18[0] * var2[3];
         var2[3] = -var18[0] * var21 + var16[0] * var2[3];
         var21 = var2[1];
         var2[1] = var16[0] * var21 + var18[0] * var2[4];
         var2[4] = -var18[0] * var21 + var16[0] * var2[4];
         var21 = var2[2];
         var2[2] = var16[0] * var21 + var18[0] * var2[5];
         var2[5] = -var18[0] * var21 + var16[0] * var2[5];
         var21 = var2[3];
         var2[3] = var16[1] * var21 + var18[1] * var2[6];
         var2[6] = -var18[1] * var21 + var16[1] * var2[6];
         var21 = var2[4];
         var2[4] = var16[1] * var21 + var18[1] * var2[7];
         var2[7] = -var18[1] * var21 + var16[1] * var2[7];
         var21 = var2[5];
         var2[5] = var16[1] * var21 + var18[1] * var2[8];
         var2[8] = -var18[1] * var21 + var16[1] * var2[8];
    double var23 = var3[0];
         var3[0] = var17[0] * var23 + var19[0] * var3[1];
         var3[1] = -var19[0] * var23 + var17[0] * var3[1];
         var23 = var3[3];
         var3[3] = var17[0] * var23 + var19[0] * var3[4];
         var3[4] = -var19[0] * var23 + var17[0] * var3[4];
         var23 = var3[6];
         var3[6] = var17[0] * var23 + var19[0] * var3[7];
         var3[7] = -var19[0] * var23 + var17[0] * var3[7];
         var23 = var3[1];
         var3[1] = var17[1] * var23 + var19[1] * var3[2];
         var3[2] = -var19[1] * var23 + var17[1] * var3[2];
         var23 = var3[4];
         var3[4] = var17[1] * var23 + var19[1] * var3[5];
         var3[5] = -var19[1] * var23 + var17[1] * var3[5];
         var23 = var3[7];
         var3[7] = var17[1] * var23 + var19[1] * var3[8];
         var3[8] = -var19[1] * var23 + var17[1] * var3[8];
         var20[0] = var0[0];
         var20[1] = var1[0];
         var20[2] = 0.0;
         var20[3] = 0.0;
         var20[4] = var0[1];
         var20[5] = var1[1];
         var20[6] = 0.0;
         var20[7] = 0.0;
         var20[8] = var0[2];
         if (Math.abs(var1[1]) < 4.89E-15 || Math.abs(var1[0]) < 4.89E-15) {
            var7 = true;
         }
      }

      if (Math.abs(var1[1]) < 4.89E-15) {
         compute_2X2(var0[0], var1[0], var0[1], var0, var18, var16, var19, var17, 0);
    double var42 = var2[0];
         var2[0] = var16[0] * var42 + var18[0] * var2[3];
         var2[3] = -var18[0] * var42 + var16[0] * var2[3];
         var42 = var2[1];
         var2[1] = var16[0] * var42 + var18[0] * var2[4];
         var2[4] = -var18[0] * var42 + var16[0] * var2[4];
         var42 = var2[2];
         var2[2] = var16[0] * var42 + var18[0] * var2[5];
         var2[5] = -var18[0] * var42 + var16[0] * var2[5];
    double var53 = var3[0];
         var3[0] = var17[0] * var53 + var19[0] * var3[1];
         var3[1] = -var19[0] * var53 + var17[0] * var3[1];
         var53 = var3[3];
         var3[3] = var17[0] * var53 + var19[0] * var3[4];
         var3[4] = -var19[0] * var53 + var17[0] * var3[4];
         var53 = var3[6];
         var3[6] = var17[0] * var53 + var19[0] * var3[7];
         var3[7] = -var19[0] * var53 + var17[0] * var3[7];
      } else {
         compute_2X2(var0[1], var1[1], var0[2], var0, var18, var16, var19, var17, 1);
    double var45 = var2[3];
         var2[3] = var16[0] * var45 + var18[0] * var2[6];
         var2[6] = -var18[0] * var45 + var16[0] * var2[6];
         var45 = var2[4];
         var2[4] = var16[0] * var45 + var18[0] * var2[7];
         var2[7] = -var18[0] * var45 + var16[0] * var2[7];
         var45 = var2[5];
         var2[5] = var16[0] * var45 + var18[0] * var2[8];
         var2[8] = -var18[0] * var45 + var16[0] * var2[8];
    double var56 = var3[1];
         var3[1] = var17[0] * var56 + var19[0] * var3[2];
         var3[2] = -var19[0] * var56 + var17[0] * var3[2];
         var56 = var3[4];
         var3[4] = var17[0] * var56 + var19[0] * var3[5];
         var3[5] = -var19[0] * var56 + var17[0] * var3[5];
         var56 = var3[7];
         var3[7] = var17[0] * var56 + var19[0] * var3[8];
         var3[8] = -var19[0] * var56 + var17[0] * var3[8];
      }

    return 0;
   }

    static double max(double var0, double var2) {
      return var0 > var2 ? var0 : var2;
   }

    static double min(double var0, double var2) {
      return var0 < var2 ? var0 : var2;
   }

    static double d_sign(double var0, double var2) {
    double var4 = var0 >= 0.0 ? var0 : -var0;
      return var2 >= 0.0 ? var4 : -var4;
   }

    static double compute_shift(double var0, double var2, double var4) {
    double var16 = Math.abs(var0);
    double var18 = Math.abs(var2);
    double var20 = Math.abs(var4);
    double var10 = min(var16, var20);
    double var12 = max(var16, var20);
    double var28;
      if (var10 == 0.0) {
         var28 = 0.0;
         if (var12 != 0.0) {
    double var6 = min(var12, var18) / max(var12, var18);
         }
      } else if (var18 < var12) {
    double var22 = var10 / var12 + 1.0;
    double var24 = (var12 - var10) / var12;
    double var30 = var18 / var12;
    double var26 = var30 * var30;
    double var14 = 2.0 / (Math.sqrt(var22 * var22 + var26) + Math.sqrt(var24 * var24 + var26));
         var28 = var10 * var14;
      } else {
    double var35 = var12 / var18;
         if (var35 == 0.0) {
            var28 = var10 * var12 / var18;
         } else {
    double var33 = var10 / var12 + 1.0;
    double var34 = (var12 - var10) / var12;
    double var31 = var33 * var35;
    double var8 = var34 * var35;
    double var32 = 1.0 / (Math.sqrt(var31 * var31 + 1.0) + Math.sqrt(var8 * var8 + 1.0));
            var28 = var10 * var32 * var35;
            var28 += var28;
         }
      }

    return var28;
   }

    static int compute_2X2(double var0, double var2, double var4, double[] var6, double[] var7, double[] var8, double[] var9, double[] var10, int var11) {
    double var12 = 2.0;
    double var14 = 1.0;
    double var65 = var6[0];
    double var63 = var6[1];
    double var55 = 0.0;
    double var57 = 0.0;
    double var59 = 0.0;
    double var61 = 0.0;
    double var36 = 0.0;
    double var44 = var0;
    double var38 = Math.abs(var0);
    double var48 = var4;
    double var42 = Math.abs(var4);
    uint8_t var18 = 1;
    bool var21;
      if (var42 > var38) {
         var21 = true;
      } else {
         var21 = false;
      }

      if (var21) {
         var18 = 3;
         var44 = var4;
         var48 = var0;
    double var19 = var38;
         var38 = var42;
         var42 = var19;
      }

    double var40 = Math.abs(var2);
      if (var40 == 0.0) {
         var6[1] = var42;
         var6[0] = var38;
         var55 = 1.0;
         var57 = 1.0;
         var59 = 0.0;
         var61 = 0.0;
      } else {
    bool var52 = true;
         if (var40 > var38) {
            var18 = 2;
            if (var38 / var40 < 1.110223024E-16) {
               var52 = false;
               var65 = var40;
               if (var42 > 1.0) {
                  var63 = var38 / (var40 / var42);
               } else {
                  var63 = var38 / var40 * var42;
               }

               var55 = 1.0;
               var59 = var48 / var2;
               var61 = 1.0;
               var57 = var44 / var2;
            }
         }

         if (var52) {
    double var24 = var38 - var42;
    double var26;
            if (var24 == var38) {
               var26 = 1.0;
            } else {
               var26 = var24 / var38;
            }

    double var28 = var2 / var44;
    double var34 = 2.0 - var26;
    double var50 = var28 * var28;
    double var53 = var34 * var34;
    double var32 = Math.sqrt(var53 + var50);
    double var30;
            if (var26 == 0.0) {
               var30 = Math.abs(var28);
            } else {
               var30 = Math.sqrt(var26 * var26 + var50);
            }

    double var22 = (var32 + var30) * 0.5;
            if (var40 > var38) {
               var18 = 2;
               if (var38 / var40 < 1.110223024E-16) {
                  var52 = false;
                  var65 = var40;
                  if (var42 > 1.0) {
                     var63 = var38 / (var40 / var42);
                  } else {
                     var63 = var38 / var40 * var42;
                  }

                  var55 = 1.0;
                  var59 = var48 / var2;
                  var61 = 1.0;
                  var57 = var44 / var2;
               }
            }

            if (var52) {
               var24 = var38 - var42;
               if (var24 == var38) {
                  var26 = 1.0;
               } else {
                  var26 = var24 / var38;
               }

               var28 = var2 / var44;
               var34 = 2.0 - var26;
               var50 = var28 * var28;
               var53 = var34 * var34;
               var32 = Math.sqrt(var53 + var50);
               if (var26 == 0.0) {
                  var30 = Math.abs(var28);
               } else {
                  var30 = Math.sqrt(var26 * var26 + var50);
               }

               var22 = (var32 + var30) * 0.5;
               var63 = var42 / var22;
               var65 = var38 * var22;
               if (var50 == 0.0) {
                  if (var26 == 0.0) {
                     var34 = d_sign(var12, var44) * d_sign(var14, var2);
                  } else {
                     var34 = var2 / d_sign(var24, var44) + var28 / var34;
                  }
               } else {
                  var34 = (var28 / (var32 + var34) + var28 / (var30 + var26)) * (var22 + 1.0);
               }

               var26 = Math.sqrt(var34 * var34 + 4.0);
               var57 = 2.0 / var26;
               var61 = var34 / var26;
               var55 = (var57 + var61 * var28) / var22;
               var59 = var48 / var44 * var61 / var22;
            }
         }

         if (var21) {
            var8[0] = var61;
            var7[0] = var57;
            var10[0] = var59;
            var9[0] = var55;
         } else {
            var8[0] = var55;
            var7[0] = var59;
            var10[0] = var57;
            var9[0] = var61;
         }

         if (var18 == 1) {
            var36 = d_sign(var14, var10[0]) * d_sign(var14, var8[0]) * d_sign(var14, var0);
         }

         if (var18 == 2) {
            var36 = d_sign(var14, var9[0]) * d_sign(var14, var8[0]) * d_sign(var14, var2);
         }

         if (var18 == 3) {
            var36 = d_sign(var14, var9[0]) * d_sign(var14, var7[0]) * d_sign(var14, var4);
         }

         var6[var11] = d_sign(var65, var36);
    double var16 = var36 * d_sign(var14, var0) * d_sign(var14, var4);
         var6[var11 + 1] = d_sign(var63, var16);
      }

    return 0;
   }

    static double compute_rot(double var0, double var2, double[] var4, double[] var5, int var6, int var7) {
    double var13;
    double var15;
    double var25;
      if (var2 == 0.0) {
         var13 = 1.0;
         var15 = 0.0;
         var25 = var0;
      } else if (var0 == 0.0) {
         var13 = 0.0;
         var15 = 1.0;
         var25 = var2;
      } else {
    double var21 = var0;
    double var23 = var2;
    double var18 = max(Math.abs(var0), Math.abs(var2));
         if (var18 >= 4.994797680505588E145) {
    int var28;
            for (var28 = 0; var18 >= 4.994797680505588E145; var18 = max(Math.abs(var21), Math.abs(var23))) {
               var28++;
               var21 *= 2.002083095183101E-146;
               var23 *= 2.002083095183101E-146;
            }

            var25 = Math.sqrt(var21 * var21 + var23 * var23);
            var13 = var21 / var25;
            var15 = var23 / var25;

            for (int var27 = 1; var27 <= var28; var27++) {
               var25 *= 4.994797680505588E145;
            }
         } else if (!(var18 <= 2.002083095183101E-146)) {
            var25 = Math.sqrt(var0 * var0 + var2 * var2);
            var13 = var0 / var25;
            var15 = var2 / var25;
         } else {
    int var20;
            for (var20 = 0; var18 <= 2.002083095183101E-146; var18 = max(Math.abs(var21), Math.abs(var23))) {
               var20++;
               var21 *= 4.994797680505588E145;
               var23 *= 4.994797680505588E145;
            }

            var25 = Math.sqrt(var21 * var21 + var23 * var23);
            var13 = var21 / var25;
            var15 = var23 / var25;

            for (int var17 = 1; var17 <= var20; var17++) {
               var25 *= 2.002083095183101E-146;
            }
         }

         if (Math.abs(var0) > Math.abs(var2) && var13 < 0.0) {
            var13 = -var13;
            var15 = -var15;
            var25 = -var25;
         }
      }

      var4[var6] = var15;
      var5[var6] = var13;
    return var25;
   }

    static void print_mat(double[] var0) {
      for (int var1 = 0; var1 < 3; var1++) {
         System.out.println(var0[var1 * 3 + 0] + " " + var0[var1 * 3 + 1] + " " + var0[var1 * 3 + 2] + "\n");
      }
   }

    static void print_det(double[] var0) {
      double var1 = var0[0] * var0[4] * var0[8]
         + var0[1] * var0[5] * var0[6]
         + var0[2] * var0[3] * var0[7]
         - var0[2] * var0[4] * var0[6]
         - var0[0] * var0[5] * var0[7]
         - var0[1] * var0[3] * var0[8];
      System.out.println("det= " + var1);
   }

    static void mat_mul(double[] var0, double[] var1, double[] var2) {
      double[] var4 = new double[]{
         var0[0] * var1[0] + var0[1] * var1[3] + var0[2] * var1[6],
         var0[0] * var1[1] + var0[1] * var1[4] + var0[2] * var1[7],
         var0[0] * var1[2] + var0[1] * var1[5] + var0[2] * var1[8],
         var0[3] * var1[0] + var0[4] * var1[3] + var0[5] * var1[6],
         var0[3] * var1[1] + var0[4] * var1[4] + var0[5] * var1[7],
         var0[3] * var1[2] + var0[4] * var1[5] + var0[5] * var1[8],
         var0[6] * var1[0] + var0[7] * var1[3] + var0[8] * var1[6],
         var0[6] * var1[1] + var0[7] * var1[4] + var0[8] * var1[7],
         var0[6] * var1[2] + var0[7] * var1[5] + var0[8] * var1[8]
      };

      for (int var3 = 0; var3 < 9; var3++) {
         var2[var3] = var4[var3];
      }
   }

    static void transpose_mat(double[] var0, double[] var1) {
      var1[0] = var0[0];
      var1[1] = var0[3];
      var1[2] = var0[6];
      var1[3] = var0[1];
      var1[4] = var0[4];
      var1[5] = var0[7];
      var1[6] = var0[2];
      var1[7] = var0[5];
      var1[8] = var0[8];
   }

    static double max3(double[] var0) {
      if (var0[0] > var0[1]) {
         return var0[0] > var0[2] ? var0[0] : var0[2];
      } else {
         return var0[1] > var0[2] ? var0[1] : var0[2];
      }
   }

    static bool almostEqual(double var0, double var2) {
      if (var0 == var2) {
    return true;
      } else {
    double var4 = Math.abs(var0 - var2);
    double var6 = Math.abs(var0);
    double var8 = Math.abs(var2);
    double var10 = var6 >= var8 ? var6 : var8;
         return var4 < 1.0E-6 ? true : var4 / var10 < 1.0E-4;
      }
   }

    void* clone() {
    void* var1 = nullptr;

      try {
         return (Matrix3d)super.clone();
      } catch (CloneNotSupportedException var3) {
         throw std::make_unique<InternalError>();
      }
   }

    double getM00() {
      return this.m00;
   }

    void setM00(double var1) {
      this.m00 = var1;
   }

    double getM01() {
      return this.m01;
   }

    void setM01(double var1) {
      this.m01 = var1;
   }

    double getM02() {
      return this.m02;
   }

    void setM02(double var1) {
      this.m02 = var1;
   }

    double getM10() {
      return this.m10;
   }

    void setM10(double var1) {
      this.m10 = var1;
   }

    double getM11() {
      return this.m11;
   }

    void setM11(double var1) {
      this.m11 = var1;
   }

    double getM12() {
      return this.m12;
   }

    void setM12(double var1) {
      this.m12 = var1;
   }

    double getM20() {
      return this.m20;
   }

    void setM20(double var1) {
      this.m20 = var1;
   }

    double getM21() {
      return this.m21;
   }

    void setM21(double var1) {
      this.m21 = var1;
   }

    double getM22() {
      return this.m22;
   }

    void setM22(double var1) {
      this.m22 = var1;
   }
}
} // namespace vecmath
} // namespace javax
