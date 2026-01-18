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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Matrix4d {
public:
 static const long serialVersionUID = 8223903484171633710L;
 double m00;
 double m01;
 double m02;
 double m03;
 double m10;
 double m11;
 double m12;
 double m13;
 double m20;
 double m21;
 double m22;
 double m23;
 double m30;
 double m31;
 double m32;
 double m33;
 static const double EPS = 1.0E-10;

 public Matrix4d(
 double double0,
 double double1,
 double double2,
 double double3,
 double double4,
 double double5,
 double double6,
 double double7,
 double double8,
 double double9,
 double double10,
 double double11,
 double double12,
 double double13,
 double double14,
 double double15
 ) {
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }

 public Matrix4d(double[] doubles) {
 this->m00 = doubles[0];
 this->m01 = doubles[1];
 this->m02 = doubles[2];
 this->m03 = doubles[3];
 this->m10 = doubles[4];
 this->m11 = doubles[5];
 this->m12 = doubles[6];
 this->m13 = doubles[7];
 this->m20 = doubles[8];
 this->m21 = doubles[9];
 this->m22 = doubles[10];
 this->m23 = doubles[11];
 this->m30 = doubles[12];
 this->m31 = doubles[13];
 this->m32 = doubles[14];
 this->m33 = doubles[15];
 }

 public Matrix4d(Quat4d quat4d, Vector3d vector3d, double double0) {
 this->m00 = double0 * (1.0 - 2.0 * quat4d.y * quat4d.y - 2.0 * quat4d.z * quat4d.z);
 this->m10 = double0 * (2.0 * (quat4d.x * quat4d.y + quat4d.w * quat4d.z);
 this->m20 = double0 * (2.0 * (quat4d.x * quat4d.z - quat4d.w * quat4d.y);
 this->m01 = double0 * (2.0 * (quat4d.x * quat4d.y - quat4d.w * quat4d.z);
 this->m11 = double0 * (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.z * quat4d.z);
 this->m21 = double0 * (2.0 * (quat4d.y * quat4d.z + quat4d.w * quat4d.x);
 this->m02 = double0 * (2.0 * (quat4d.x * quat4d.z + quat4d.w * quat4d.y);
 this->m12 = double0 * (2.0 * (quat4d.y * quat4d.z - quat4d.w * quat4d.x);
 this->m22 = double0 * (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.y * quat4d.y);
 this->m03 = vector3d.x;
 this->m13 = vector3d.y;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 public Matrix4d(Quat4f quat4f, Vector3d vector3d, double double0) {
 this->m00 = double0 * (1.0 - 2.0 * quat4f.y * quat4f.y - 2.0 * quat4f.z * quat4f.z);
 this->m10 = double0 * (2.0 * (quat4f.x * quat4f.y + quat4f.w * quat4f.z);
 this->m20 = double0 * (2.0 * (quat4f.x * quat4f.z - quat4f.w * quat4f.y);
 this->m01 = double0 * (2.0 * (quat4f.x * quat4f.y - quat4f.w * quat4f.z);
 this->m11 = double0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.z * quat4f.z);
 this->m21 = double0 * (2.0 * (quat4f.y * quat4f.z + quat4f.w * quat4f.x);
 this->m02 = double0 * (2.0 * (quat4f.x * quat4f.z + quat4f.w * quat4f.y);
 this->m12 = double0 * (2.0 * (quat4f.y * quat4f.z - quat4f.w * quat4f.x);
 this->m22 = double0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.y * quat4f.y);
 this->m03 = vector3d.x;
 this->m13 = vector3d.y;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 public Matrix4d(Matrix4d matrix4d1) {
 this->m00 = matrix4d1.m00;
 this->m01 = matrix4d1.m01;
 this->m02 = matrix4d1.m02;
 this->m03 = matrix4d1.m03;
 this->m10 = matrix4d1.m10;
 this->m11 = matrix4d1.m11;
 this->m12 = matrix4d1.m12;
 this->m13 = matrix4d1.m13;
 this->m20 = matrix4d1.m20;
 this->m21 = matrix4d1.m21;
 this->m22 = matrix4d1.m22;
 this->m23 = matrix4d1.m23;
 this->m30 = matrix4d1.m30;
 this->m31 = matrix4d1.m31;
 this->m32 = matrix4d1.m32;
 this->m33 = matrix4d1.m33;
 }

 public Matrix4d(Matrix4f matrix4f) {
 this->m00 = matrix4f.m00;
 this->m01 = matrix4f.m01;
 this->m02 = matrix4f.m02;
 this->m03 = matrix4f.m03;
 this->m10 = matrix4f.m10;
 this->m11 = matrix4f.m11;
 this->m12 = matrix4f.m12;
 this->m13 = matrix4f.m13;
 this->m20 = matrix4f.m20;
 this->m21 = matrix4f.m21;
 this->m22 = matrix4f.m22;
 this->m23 = matrix4f.m23;
 this->m30 = matrix4f.m30;
 this->m31 = matrix4f.m31;
 this->m32 = matrix4f.m32;
 this->m33 = matrix4f.m33;
 }

 public Matrix4d(Matrix3f matrix3f, Vector3d vector3d, double double0) {
 this->m00 = matrix3f.m00 * double0;
 this->m01 = matrix3f.m01 * double0;
 this->m02 = matrix3f.m02 * double0;
 this->m03 = vector3d.x;
 this->m10 = matrix3f.m10 * double0;
 this->m11 = matrix3f.m11 * double0;
 this->m12 = matrix3f.m12 * double0;
 this->m13 = vector3d.y;
 this->m20 = matrix3f.m20 * double0;
 this->m21 = matrix3f.m21 * double0;
 this->m22 = matrix3f.m22 * double0;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 public Matrix4d(Matrix3d matrix3d, Vector3d vector3d, double double0) {
 this->m00 = matrix3d.m00 * double0;
 this->m01 = matrix3d.m01 * double0;
 this->m02 = matrix3d.m02 * double0;
 this->m03 = vector3d.x;
 this->m10 = matrix3d.m10 * double0;
 this->m11 = matrix3d.m11 * double0;
 this->m12 = matrix3d.m12 * double0;
 this->m13 = vector3d.y;
 this->m20 = matrix3d.m20 * double0;
 this->m21 = matrix3d.m21 * double0;
 this->m22 = matrix3d.m22 * double0;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 public Matrix4d() {
 this->m00 = 0.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = 0.0;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 0.0;
 }

 std::string toString() {
 return this->m00
 + ", "
 + this->m01
 + ", "
 + this->m02
 + ", "
 + this->m03
 + "\n"
 + this->m10
 + ", "
 + this->m11
 + ", "
 + this->m12
 + ", "
 + this->m13
 + "\n"
 + this->m20
 + ", "
 + this->m21
 + ", "
 + this->m22
 + ", "
 + this->m23
 + "\n"
 + this->m30
 + ", "
 + this->m31
 + ", "
 + this->m32
 + ", "
 + this->m33
 + "\n";
 }

 void setIdentity() {
 this->m00 = 1.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = 1.0;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 1.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void setElement(int int0, int int1, double double0) {
 switch (int0) {
 case 0:
 switch (int1) {
 case 0:
 this->m00 = double0;
 return;
 case 1:
 this->m01 = double0;
 return;
 case 2:
 this->m02 = double0;
 return;
 case 3:
 this->m03 = double0;
 return;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d0"));
 }
 case 1:
 switch (int1) {
 case 0:
 this->m10 = double0;
 return;
 case 1:
 this->m11 = double0;
 return;
 case 2:
 this->m12 = double0;
 return;
 case 3:
 this->m13 = double0;
 return;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d0"));
 }
 case 2:
 switch (int1) {
 case 0:
 this->m20 = double0;
 return;
 case 1:
 this->m21 = double0;
 return;
 case 2:
 this->m22 = double0;
 return;
 case 3:
 this->m23 = double0;
 return;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d0"));
 }
 case 3:
 switch (int1) {
 case 0:
 this->m30 = double0;
 return;
 case 1:
 this->m31 = double0;
 return;
 case 2:
 this->m32 = double0;
 return;
 case 3:
 this->m33 = double0;
 return;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d0"));
 }
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d0"));
 }
 }

 double getElement(int int0, int int1) {
 switch (int0) {
 case 0:
 switch (int1) {
 case 0:
 return this->m00;
 case 1:
 return this->m01;
 case 2:
 return this->m02;
 case 3:
 return this->m03;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d1"));
 }
 case 1:
 switch (int1) {
 case 0:
 return this->m10;
 case 1:
 return this->m11;
 case 2:
 return this->m12;
 case 3:
 return this->m13;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d1"));
 }
 case 2:
 switch (int1) {
 case 0:
 return this->m20;
 case 1:
 return this->m21;
 case 2:
 return this->m22;
 case 3:
 return this->m23;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d1"));
 }
 case 3:
 switch (int1) {
 case 0:
 return this->m30;
 case 1:
 return this->m31;
 case 2:
 return this->m32;
 case 3:
 return this->m33;
 }
 }

 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d1"));
 }

 void getRow(int int0, Vector4d vector4d) {
 if (int0 == 0) {
 vector4d.x = this->m00;
 vector4d.y = this->m01;
 vector4d.z = this->m02;
 vector4d.w = this->m03;
 } else if (int0 == 1) {
 vector4d.x = this->m10;
 vector4d.y = this->m11;
 vector4d.z = this->m12;
 vector4d.w = this->m13;
 } else if (int0 == 2) {
 vector4d.x = this->m20;
 vector4d.y = this->m21;
 vector4d.z = this->m22;
 vector4d.w = this->m23;
 } else {
 if (int0 != 3) {
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d2"));
 }

 vector4d.x = this->m30;
 vector4d.y = this->m31;
 vector4d.z = this->m32;
 vector4d.w = this->m33;
 }
 }

 void getRow(int int0, double[] doubles) {
 if (int0 == 0) {
 doubles[0] = this->m00;
 doubles[1] = this->m01;
 doubles[2] = this->m02;
 doubles[3] = this->m03;
 } else if (int0 == 1) {
 doubles[0] = this->m10;
 doubles[1] = this->m11;
 doubles[2] = this->m12;
 doubles[3] = this->m13;
 } else if (int0 == 2) {
 doubles[0] = this->m20;
 doubles[1] = this->m21;
 doubles[2] = this->m22;
 doubles[3] = this->m23;
 } else {
 if (int0 != 3) {
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d2"));
 }

 doubles[0] = this->m30;
 doubles[1] = this->m31;
 doubles[2] = this->m32;
 doubles[3] = this->m33;
 }
 }

 void getColumn(int int0, Vector4d vector4d) {
 if (int0 == 0) {
 vector4d.x = this->m00;
 vector4d.y = this->m10;
 vector4d.z = this->m20;
 vector4d.w = this->m30;
 } else if (int0 == 1) {
 vector4d.x = this->m01;
 vector4d.y = this->m11;
 vector4d.z = this->m21;
 vector4d.w = this->m31;
 } else if (int0 == 2) {
 vector4d.x = this->m02;
 vector4d.y = this->m12;
 vector4d.z = this->m22;
 vector4d.w = this->m32;
 } else {
 if (int0 != 3) {
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d3"));
 }

 vector4d.x = this->m03;
 vector4d.y = this->m13;
 vector4d.z = this->m23;
 vector4d.w = this->m33;
 }
 }

 void getColumn(int int0, double[] doubles) {
 if (int0 == 0) {
 doubles[0] = this->m00;
 doubles[1] = this->m10;
 doubles[2] = this->m20;
 doubles[3] = this->m30;
 } else if (int0 == 1) {
 doubles[0] = this->m01;
 doubles[1] = this->m11;
 doubles[2] = this->m21;
 doubles[3] = this->m31;
 } else if (int0 == 2) {
 doubles[0] = this->m02;
 doubles[1] = this->m12;
 doubles[2] = this->m22;
 doubles[3] = this->m32;
 } else {
 if (int0 != 3) {
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d3"));
 }

 doubles[0] = this->m03;
 doubles[1] = this->m13;
 doubles[2] = this->m23;
 doubles[3] = this->m33;
 }
 }

 void get(Matrix3d matrix3d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 matrix3d.m00 = doubles0[0];
 matrix3d.m01 = doubles0[1];
 matrix3d.m02 = doubles0[2];
 matrix3d.m10 = doubles0[3];
 matrix3d.m11 = doubles0[4];
 matrix3d.m12 = doubles0[5];
 matrix3d.m20 = doubles0[6];
 matrix3d.m21 = doubles0[7];
 matrix3d.m22 = doubles0[8];
 }

 void get(Matrix3f matrix3f) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 matrix3f.m00 = (float)doubles0[0];
 matrix3f.m01 = (float)doubles0[1];
 matrix3f.m02 = (float)doubles0[2];
 matrix3f.m10 = (float)doubles0[3];
 matrix3f.m11 = (float)doubles0[4];
 matrix3f.m12 = (float)doubles0[5];
 matrix3f.m20 = (float)doubles0[6];
 matrix3f.m21 = (float)doubles0[7];
 matrix3f.m22 = (float)doubles0[8];
 }

 double get(Matrix3d matrix3d, Vector3d vector3d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 matrix3d.m00 = doubles0[0];
 matrix3d.m01 = doubles0[1];
 matrix3d.m02 = doubles0[2];
 matrix3d.m10 = doubles0[3];
 matrix3d.m11 = doubles0[4];
 matrix3d.m12 = doubles0[5];
 matrix3d.m20 = doubles0[6];
 matrix3d.m21 = doubles0[7];
 matrix3d.m22 = doubles0[8];
 vector3d.x = this->m03;
 vector3d.y = this->m13;
 vector3d.z = this->m23;
 return Matrix3d.max3(doubles1);
 }

 double get(Matrix3f matrix3f, Vector3d vector3d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 matrix3f.m00 = (float)doubles0[0];
 matrix3f.m01 = (float)doubles0[1];
 matrix3f.m02 = (float)doubles0[2];
 matrix3f.m10 = (float)doubles0[3];
 matrix3f.m11 = (float)doubles0[4];
 matrix3f.m12 = (float)doubles0[5];
 matrix3f.m20 = (float)doubles0[6];
 matrix3f.m21 = (float)doubles0[7];
 matrix3f.m22 = (float)doubles0[8];
 vector3d.x = this->m03;
 vector3d.y = this->m13;
 vector3d.z = this->m23;
 return Matrix3d.max3(doubles1);
 }

 void get(Quat4f quat4f) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 double double0 = 0.25 * (1.0 + doubles0[0] + doubles0[4] + doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4f.w = (float)Math.sqrt(double0);
 double0 = 0.25 / quat4f.w;
 quat4f.x = (float)((doubles0[7] - doubles0[5]) * double0);
 quat4f.y = (float)((doubles0[2] - doubles0[6]) * double0);
 quat4f.z = (float)((doubles0[3] - doubles0[1]) * double0);
 } else {
 quat4f.w = 0.0F;
 double0 = -0.5 * (doubles0[4] + doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4f.x = (float)Math.sqrt(double0);
 double0 = 0.5 / quat4f.x;
 quat4f.y = (float)(doubles0[3] * double0);
 quat4f.z = (float)(doubles0[6] * double0);
 } else {
 quat4f.x = 0.0F;
 double0 = 0.5 * (1.0 - doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4f.y = (float)Math.sqrt(double0);
 quat4f.z = (float)(doubles0[7] / (2.0 * quat4f.y);
 } else {
 quat4f.y = 0.0F;
 quat4f.z = 1.0F;
 }
 }
 }
 }

 void get(Quat4d quat4d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 double double0 = 0.25 * (1.0 + doubles0[0] + doubles0[4] + doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4d.w = Math.sqrt(double0);
 double0 = 0.25 / quat4d.w;
 quat4d.x = (doubles0[7] - doubles0[5]) * double0;
 quat4d.y = (doubles0[2] - doubles0[6]) * double0;
 quat4d.z = (doubles0[3] - doubles0[1]) * double0;
 } else {
 quat4d.w = 0.0;
 double0 = -0.5 * (doubles0[4] + doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4d.x = Math.sqrt(double0);
 double0 = 0.5 / quat4d.x;
 quat4d.y = doubles0[3] * double0;
 quat4d.z = doubles0[6] * double0;
 } else {
 quat4d.x = 0.0;
 double0 = 0.5 * (1.0 - doubles0[8]);
 if (!((double0 < 0.0 ? -double0 : double0) < 1.0E-30) {
 quat4d.y = Math.sqrt(double0);
 quat4d.z = doubles0[7] / (2.0 * quat4d.y);
 } else {
 quat4d.y = 0.0;
 quat4d.z = 1.0;
 }
 }
 }
 }

 void get(Vector3d vector3d) {
 vector3d.x = this->m03;
 vector3d.y = this->m13;
 vector3d.z = this->m23;
 }

 void getRotationScale(Matrix3f matrix3f) {
 matrix3f.m00 = (float)this->m00;
 matrix3f.m01 = (float)this->m01;
 matrix3f.m02 = (float)this->m02;
 matrix3f.m10 = (float)this->m10;
 matrix3f.m11 = (float)this->m11;
 matrix3f.m12 = (float)this->m12;
 matrix3f.m20 = (float)this->m20;
 matrix3f.m21 = (float)this->m21;
 matrix3f.m22 = (float)this->m22;
 }

 void getRotationScale(Matrix3d matrix3d) {
 matrix3d.m00 = this->m00;
 matrix3d.m01 = this->m01;
 matrix3d.m02 = this->m02;
 matrix3d.m10 = this->m10;
 matrix3d.m11 = this->m11;
 matrix3d.m12 = this->m12;
 matrix3d.m20 = this->m20;
 matrix3d.m21 = this->m21;
 matrix3d.m22 = this->m22;
 }

 double getScale() {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 return Matrix3d.max3(doubles1);
 }

 void setRotationScale(Matrix3d matrix3d) {
 this->m00 = matrix3d.m00;
 this->m01 = matrix3d.m01;
 this->m02 = matrix3d.m02;
 this->m10 = matrix3d.m10;
 this->m11 = matrix3d.m11;
 this->m12 = matrix3d.m12;
 this->m20 = matrix3d.m20;
 this->m21 = matrix3d.m21;
 this->m22 = matrix3d.m22;
 }

 void setRotationScale(Matrix3f matrix3f) {
 this->m00 = matrix3f.m00;
 this->m01 = matrix3f.m01;
 this->m02 = matrix3f.m02;
 this->m10 = matrix3f.m10;
 this->m11 = matrix3f.m11;
 this->m12 = matrix3f.m12;
 this->m20 = matrix3f.m20;
 this->m21 = matrix3f.m21;
 this->m22 = matrix3f.m22;
 }

 void setScale(double double0) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 this->m00 = doubles0[0] * double0;
 this->m01 = doubles0[1] * double0;
 this->m02 = doubles0[2] * double0;
 this->m10 = doubles0[3] * double0;
 this->m11 = doubles0[4] * double0;
 this->m12 = doubles0[5] * double0;
 this->m20 = doubles0[6] * double0;
 this->m21 = doubles0[7] * double0;
 this->m22 = doubles0[8] * double0;
 }

 void setRow(int int0, double double0, double double1, double double2, double double3) {
 switch (int0) {
 case 0:
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 break;
 case 1:
 this->m10 = double0;
 this->m11 = double1;
 this->m12 = double2;
 this->m13 = double3;
 break;
 case 2:
 this->m20 = double0;
 this->m21 = double1;
 this->m22 = double2;
 this->m23 = double3;
 break;
 case 3:
 this->m30 = double0;
 this->m31 = double1;
 this->m32 = double2;
 this->m33 = double3;
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d4"));
 }
 }

 void setRow(int int0, Vector4d vector4d) {
 switch (int0) {
 case 0:
 this->m00 = vector4d.x;
 this->m01 = vector4d.y;
 this->m02 = vector4d.z;
 this->m03 = vector4d.w;
 break;
 case 1:
 this->m10 = vector4d.x;
 this->m11 = vector4d.y;
 this->m12 = vector4d.z;
 this->m13 = vector4d.w;
 break;
 case 2:
 this->m20 = vector4d.x;
 this->m21 = vector4d.y;
 this->m22 = vector4d.z;
 this->m23 = vector4d.w;
 break;
 case 3:
 this->m30 = vector4d.x;
 this->m31 = vector4d.y;
 this->m32 = vector4d.z;
 this->m33 = vector4d.w;
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d4"));
 }
 }

 void setRow(int int0, double[] doubles) {
 switch (int0) {
 case 0:
 this->m00 = doubles[0];
 this->m01 = doubles[1];
 this->m02 = doubles[2];
 this->m03 = doubles[3];
 break;
 case 1:
 this->m10 = doubles[0];
 this->m11 = doubles[1];
 this->m12 = doubles[2];
 this->m13 = doubles[3];
 break;
 case 2:
 this->m20 = doubles[0];
 this->m21 = doubles[1];
 this->m22 = doubles[2];
 this->m23 = doubles[3];
 break;
 case 3:
 this->m30 = doubles[0];
 this->m31 = doubles[1];
 this->m32 = doubles[2];
 this->m33 = doubles[3];
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d4"));
 }
 }

 void setColumn(int int0, double double0, double double1, double double2, double double3) {
 switch (int0) {
 case 0:
 this->m00 = double0;
 this->m10 = double1;
 this->m20 = double2;
 this->m30 = double3;
 break;
 case 1:
 this->m01 = double0;
 this->m11 = double1;
 this->m21 = double2;
 this->m31 = double3;
 break;
 case 2:
 this->m02 = double0;
 this->m12 = double1;
 this->m22 = double2;
 this->m32 = double3;
 break;
 case 3:
 this->m03 = double0;
 this->m13 = double1;
 this->m23 = double2;
 this->m33 = double3;
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d7"));
 }
 }

 void setColumn(int int0, Vector4d vector4d) {
 switch (int0) {
 case 0:
 this->m00 = vector4d.x;
 this->m10 = vector4d.y;
 this->m20 = vector4d.z;
 this->m30 = vector4d.w;
 break;
 case 1:
 this->m01 = vector4d.x;
 this->m11 = vector4d.y;
 this->m21 = vector4d.z;
 this->m31 = vector4d.w;
 break;
 case 2:
 this->m02 = vector4d.x;
 this->m12 = vector4d.y;
 this->m22 = vector4d.z;
 this->m32 = vector4d.w;
 break;
 case 3:
 this->m03 = vector4d.x;
 this->m13 = vector4d.y;
 this->m23 = vector4d.z;
 this->m33 = vector4d.w;
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d7"));
 }
 }

 void setColumn(int int0, double[] doubles) {
 switch (int0) {
 case 0:
 this->m00 = doubles[0];
 this->m10 = doubles[1];
 this->m20 = doubles[2];
 this->m30 = doubles[3];
 break;
 case 1:
 this->m01 = doubles[0];
 this->m11 = doubles[1];
 this->m21 = doubles[2];
 this->m31 = doubles[3];
 break;
 case 2:
 this->m02 = doubles[0];
 this->m12 = doubles[1];
 this->m22 = doubles[2];
 this->m32 = doubles[3];
 break;
 case 3:
 this->m03 = doubles[0];
 this->m13 = doubles[1];
 this->m23 = doubles[2];
 this->m33 = doubles[3];
 break;
 default:
 throw ArrayIndexOutOfBoundsException(VecMathI18N.getString("Matrix4d7"));
 }
 }

 void add(double double0) {
 this->m00 += double0;
 this->m01 += double0;
 this->m02 += double0;
 this->m03 += double0;
 this->m10 += double0;
 this->m11 += double0;
 this->m12 += double0;
 this->m13 += double0;
 this->m20 += double0;
 this->m21 += double0;
 this->m22 += double0;
 this->m23 += double0;
 this->m30 += double0;
 this->m31 += double0;
 this->m32 += double0;
 this->m33 += double0;
 }

 void add(double double0, Matrix4d matrix4d0) {
 this->m00 = matrix4d0.m00 + double0;
 this->m01 = matrix4d0.m01 + double0;
 this->m02 = matrix4d0.m02 + double0;
 this->m03 = matrix4d0.m03 + double0;
 this->m10 = matrix4d0.m10 + double0;
 this->m11 = matrix4d0.m11 + double0;
 this->m12 = matrix4d0.m12 + double0;
 this->m13 = matrix4d0.m13 + double0;
 this->m20 = matrix4d0.m20 + double0;
 this->m21 = matrix4d0.m21 + double0;
 this->m22 = matrix4d0.m22 + double0;
 this->m23 = matrix4d0.m23 + double0;
 this->m30 = matrix4d0.m30 + double0;
 this->m31 = matrix4d0.m31 + double0;
 this->m32 = matrix4d0.m32 + double0;
 this->m33 = matrix4d0.m33 + double0;
 }

 void add(Matrix4d matrix4d1, Matrix4d matrix4d0) {
 this->m00 = matrix4d1.m00 + matrix4d0.m00;
 this->m01 = matrix4d1.m01 + matrix4d0.m01;
 this->m02 = matrix4d1.m02 + matrix4d0.m02;
 this->m03 = matrix4d1.m03 + matrix4d0.m03;
 this->m10 = matrix4d1.m10 + matrix4d0.m10;
 this->m11 = matrix4d1.m11 + matrix4d0.m11;
 this->m12 = matrix4d1.m12 + matrix4d0.m12;
 this->m13 = matrix4d1.m13 + matrix4d0.m13;
 this->m20 = matrix4d1.m20 + matrix4d0.m20;
 this->m21 = matrix4d1.m21 + matrix4d0.m21;
 this->m22 = matrix4d1.m22 + matrix4d0.m22;
 this->m23 = matrix4d1.m23 + matrix4d0.m23;
 this->m30 = matrix4d1.m30 + matrix4d0.m30;
 this->m31 = matrix4d1.m31 + matrix4d0.m31;
 this->m32 = matrix4d1.m32 + matrix4d0.m32;
 this->m33 = matrix4d1.m33 + matrix4d0.m33;
 }

 void add(Matrix4d matrix4d0) {
 this->m00 = this->m00 + matrix4d0.m00;
 this->m01 = this->m01 + matrix4d0.m01;
 this->m02 = this->m02 + matrix4d0.m02;
 this->m03 = this->m03 + matrix4d0.m03;
 this->m10 = this->m10 + matrix4d0.m10;
 this->m11 = this->m11 + matrix4d0.m11;
 this->m12 = this->m12 + matrix4d0.m12;
 this->m13 = this->m13 + matrix4d0.m13;
 this->m20 = this->m20 + matrix4d0.m20;
 this->m21 = this->m21 + matrix4d0.m21;
 this->m22 = this->m22 + matrix4d0.m22;
 this->m23 = this->m23 + matrix4d0.m23;
 this->m30 = this->m30 + matrix4d0.m30;
 this->m31 = this->m31 + matrix4d0.m31;
 this->m32 = this->m32 + matrix4d0.m32;
 this->m33 = this->m33 + matrix4d0.m33;
 }

 void sub(Matrix4d matrix4d1, Matrix4d matrix4d0) {
 this->m00 = matrix4d1.m00 - matrix4d0.m00;
 this->m01 = matrix4d1.m01 - matrix4d0.m01;
 this->m02 = matrix4d1.m02 - matrix4d0.m02;
 this->m03 = matrix4d1.m03 - matrix4d0.m03;
 this->m10 = matrix4d1.m10 - matrix4d0.m10;
 this->m11 = matrix4d1.m11 - matrix4d0.m11;
 this->m12 = matrix4d1.m12 - matrix4d0.m12;
 this->m13 = matrix4d1.m13 - matrix4d0.m13;
 this->m20 = matrix4d1.m20 - matrix4d0.m20;
 this->m21 = matrix4d1.m21 - matrix4d0.m21;
 this->m22 = matrix4d1.m22 - matrix4d0.m22;
 this->m23 = matrix4d1.m23 - matrix4d0.m23;
 this->m30 = matrix4d1.m30 - matrix4d0.m30;
 this->m31 = matrix4d1.m31 - matrix4d0.m31;
 this->m32 = matrix4d1.m32 - matrix4d0.m32;
 this->m33 = matrix4d1.m33 - matrix4d0.m33;
 }

 void sub(Matrix4d matrix4d0) {
 this->m00 = this->m00 - matrix4d0.m00;
 this->m01 = this->m01 - matrix4d0.m01;
 this->m02 = this->m02 - matrix4d0.m02;
 this->m03 = this->m03 - matrix4d0.m03;
 this->m10 = this->m10 - matrix4d0.m10;
 this->m11 = this->m11 - matrix4d0.m11;
 this->m12 = this->m12 - matrix4d0.m12;
 this->m13 = this->m13 - matrix4d0.m13;
 this->m20 = this->m20 - matrix4d0.m20;
 this->m21 = this->m21 - matrix4d0.m21;
 this->m22 = this->m22 - matrix4d0.m22;
 this->m23 = this->m23 - matrix4d0.m23;
 this->m30 = this->m30 - matrix4d0.m30;
 this->m31 = this->m31 - matrix4d0.m31;
 this->m32 = this->m32 - matrix4d0.m32;
 this->m33 = this->m33 - matrix4d0.m33;
 }

 void transpose() {
 double double0 = this->m10;
 this->m10 = this->m01;
 this->m01 = double0;
 double0 = this->m20;
 this->m20 = this->m02;
 this->m02 = double0;
 double0 = this->m30;
 this->m30 = this->m03;
 this->m03 = double0;
 double0 = this->m21;
 this->m21 = this->m12;
 this->m12 = double0;
 double0 = this->m31;
 this->m31 = this->m13;
 this->m13 = double0;
 double0 = this->m32;
 this->m32 = this->m23;
 this->m23 = double0;
 }

 void transpose(Matrix4d matrix4d1) {
 if (this != matrix4d1) {
 this->m00 = matrix4d1.m00;
 this->m01 = matrix4d1.m10;
 this->m02 = matrix4d1.m20;
 this->m03 = matrix4d1.m30;
 this->m10 = matrix4d1.m01;
 this->m11 = matrix4d1.m11;
 this->m12 = matrix4d1.m21;
 this->m13 = matrix4d1.m31;
 this->m20 = matrix4d1.m02;
 this->m21 = matrix4d1.m12;
 this->m22 = matrix4d1.m22;
 this->m23 = matrix4d1.m32;
 this->m30 = matrix4d1.m03;
 this->m31 = matrix4d1.m13;
 this->m32 = matrix4d1.m23;
 this->m33 = matrix4d1.m33;
 } else {
 this->transpose();
 }
 }

 void set(double[] doubles) {
 this->m00 = doubles[0];
 this->m01 = doubles[1];
 this->m02 = doubles[2];
 this->m03 = doubles[3];
 this->m10 = doubles[4];
 this->m11 = doubles[5];
 this->m12 = doubles[6];
 this->m13 = doubles[7];
 this->m20 = doubles[8];
 this->m21 = doubles[9];
 this->m22 = doubles[10];
 this->m23 = doubles[11];
 this->m30 = doubles[12];
 this->m31 = doubles[13];
 this->m32 = doubles[14];
 this->m33 = doubles[15];
 }

 void set(Matrix3f matrix3f) {
 this->m00 = matrix3f.m00;
 this->m01 = matrix3f.m01;
 this->m02 = matrix3f.m02;
 this->m03 = 0.0;
 this->m10 = matrix3f.m10;
 this->m11 = matrix3f.m11;
 this->m12 = matrix3f.m12;
 this->m13 = 0.0;
 this->m20 = matrix3f.m20;
 this->m21 = matrix3f.m21;
 this->m22 = matrix3f.m22;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Matrix3d matrix3d) {
 this->m00 = matrix3d.m00;
 this->m01 = matrix3d.m01;
 this->m02 = matrix3d.m02;
 this->m03 = 0.0;
 this->m10 = matrix3d.m10;
 this->m11 = matrix3d.m11;
 this->m12 = matrix3d.m12;
 this->m13 = 0.0;
 this->m20 = matrix3d.m20;
 this->m21 = matrix3d.m21;
 this->m22 = matrix3d.m22;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Quat4d quat4d) {
 this->m00 = 1.0 - 2.0 * quat4d.y * quat4d.y - 2.0 * quat4d.z * quat4d.z;
 this->m10 = 2.0 * (quat4d.x * quat4d.y + quat4d.w * quat4d.z);
 this->m20 = 2.0 * (quat4d.x * quat4d.z - quat4d.w * quat4d.y);
 this->m01 = 2.0 * (quat4d.x * quat4d.y - quat4d.w * quat4d.z);
 this->m11 = 1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.z * quat4d.z;
 this->m21 = 2.0 * (quat4d.y * quat4d.z + quat4d.w * quat4d.x);
 this->m02 = 2.0 * (quat4d.x * quat4d.z + quat4d.w * quat4d.y);
 this->m12 = 2.0 * (quat4d.y * quat4d.z - quat4d.w * quat4d.x);
 this->m22 = 1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.y * quat4d.y;
 this->m03 = 0.0;
 this->m13 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(AxisAngle4d axisAngle4d) {
 double double0 = Math.sqrt(axisAngle4d.x * axisAngle4d.x + axisAngle4d.y * axisAngle4d.y + axisAngle4d.z * axisAngle4d.z);
 if (double0 < 1.0E-10) {
 this->m00 = 1.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m10 = 0.0;
 this->m11 = 1.0;
 this->m12 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 1.0;
 } else {
 double0 = 1.0 / double0;
 double double1 = axisAngle4d.x * double0;
 double double2 = axisAngle4d.y * double0;
 double double3 = axisAngle4d.z * double0;
 double double4 = Math.sin(axisAngle4d.angle);
 double double5 = Math.cos(axisAngle4d.angle);
 double double6 = 1.0 - double5;
 double double7 = double1 * double3;
 double double8 = double1 * double2;
 double double9 = double2 * double3;
 this->m00 = double6 * double1 * double1 + double5;
 this->m01 = double6 * double8 - double4 * double3;
 this->m02 = double6 * double7 + double4 * double2;
 this->m10 = double6 * double8 + double4 * double3;
 this->m11 = double6 * double2 * double2 + double5;
 this->m12 = double6 * double9 - double4 * double1;
 this->m20 = double6 * double7 - double4 * double2;
 this->m21 = double6 * double9 + double4 * double1;
 this->m22 = double6 * double3 * double3 + double5;
 }

 this->m03 = 0.0;
 this->m13 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Quat4f quat4f) {
 this->m00 = 1.0 - 2.0 * quat4f.y * quat4f.y - 2.0 * quat4f.z * quat4f.z;
 this->m10 = 2.0 * (quat4f.x * quat4f.y + quat4f.w * quat4f.z);
 this->m20 = 2.0 * (quat4f.x * quat4f.z - quat4f.w * quat4f.y);
 this->m01 = 2.0 * (quat4f.x * quat4f.y - quat4f.w * quat4f.z);
 this->m11 = 1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.z * quat4f.z;
 this->m21 = 2.0 * (quat4f.y * quat4f.z + quat4f.w * quat4f.x);
 this->m02 = 2.0 * (quat4f.x * quat4f.z + quat4f.w * quat4f.y);
 this->m12 = 2.0 * (quat4f.y * quat4f.z - quat4f.w * quat4f.x);
 this->m22 = 1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.y * quat4f.y;
 this->m03 = 0.0;
 this->m13 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(AxisAngle4f axisAngle4f) {
 double double0 = Math.sqrt(axisAngle4f.x * axisAngle4f.x + axisAngle4f.y * axisAngle4f.y + axisAngle4f.z * axisAngle4f.z);
 if (double0 < 1.0E-10) {
 this->m00 = 1.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m10 = 0.0;
 this->m11 = 1.0;
 this->m12 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 1.0;
 } else {
 double0 = 1.0 / double0;
 double double1 = axisAngle4f.x * double0;
 double double2 = axisAngle4f.y * double0;
 double double3 = axisAngle4f.z * double0;
 double double4 = Math.sin(axisAngle4f.angle);
 double double5 = Math.cos(axisAngle4f.angle);
 double double6 = 1.0 - double5;
 double double7 = double1 * double3;
 double double8 = double1 * double2;
 double double9 = double2 * double3;
 this->m00 = double6 * double1 * double1 + double5;
 this->m01 = double6 * double8 - double4 * double3;
 this->m02 = double6 * double7 + double4 * double2;
 this->m10 = double6 * double8 + double4 * double3;
 this->m11 = double6 * double2 * double2 + double5;
 this->m12 = double6 * double9 - double4 * double1;
 this->m20 = double6 * double7 - double4 * double2;
 this->m21 = double6 * double9 + double4 * double1;
 this->m22 = double6 * double3 * double3 + double5;
 }

 this->m03 = 0.0;
 this->m13 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Quat4d quat4d, Vector3d vector3d, double double0) {
 this->m00 = double0 * (1.0 - 2.0 * quat4d.y * quat4d.y - 2.0 * quat4d.z * quat4d.z);
 this->m10 = double0 * (2.0 * (quat4d.x * quat4d.y + quat4d.w * quat4d.z);
 this->m20 = double0 * (2.0 * (quat4d.x * quat4d.z - quat4d.w * quat4d.y);
 this->m01 = double0 * (2.0 * (quat4d.x * quat4d.y - quat4d.w * quat4d.z);
 this->m11 = double0 * (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.z * quat4d.z);
 this->m21 = double0 * (2.0 * (quat4d.y * quat4d.z + quat4d.w * quat4d.x);
 this->m02 = double0 * (2.0 * (quat4d.x * quat4d.z + quat4d.w * quat4d.y);
 this->m12 = double0 * (2.0 * (quat4d.y * quat4d.z - quat4d.w * quat4d.x);
 this->m22 = double0 * (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.y * quat4d.y);
 this->m03 = vector3d.x;
 this->m13 = vector3d.y;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Quat4f quat4f, Vector3d vector3d, double double0) {
 this->m00 = double0 * (1.0 - 2.0 * quat4f.y * quat4f.y - 2.0 * quat4f.z * quat4f.z);
 this->m10 = double0 * (2.0 * (quat4f.x * quat4f.y + quat4f.w * quat4f.z);
 this->m20 = double0 * (2.0 * (quat4f.x * quat4f.z - quat4f.w * quat4f.y);
 this->m01 = double0 * (2.0 * (quat4f.x * quat4f.y - quat4f.w * quat4f.z);
 this->m11 = double0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.z * quat4f.z);
 this->m21 = double0 * (2.0 * (quat4f.y * quat4f.z + quat4f.w * quat4f.x);
 this->m02 = double0 * (2.0 * (quat4f.x * quat4f.z + quat4f.w * quat4f.y);
 this->m12 = double0 * (2.0 * (quat4f.y * quat4f.z - quat4f.w * quat4f.x);
 this->m22 = double0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.y * quat4f.y);
 this->m03 = vector3d.x;
 this->m13 = vector3d.y;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Quat4f quat4f, Vector3f vector3f, float float0) {
 this->m00 = float0 * (1.0 - 2.0 * quat4f.y * quat4f.y - 2.0 * quat4f.z * quat4f.z);
 this->m10 = float0 * (2.0 * (quat4f.x * quat4f.y + quat4f.w * quat4f.z);
 this->m20 = float0 * (2.0 * (quat4f.x * quat4f.z - quat4f.w * quat4f.y);
 this->m01 = float0 * (2.0 * (quat4f.x * quat4f.y - quat4f.w * quat4f.z);
 this->m11 = float0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.z * quat4f.z);
 this->m21 = float0 * (2.0 * (quat4f.y * quat4f.z + quat4f.w * quat4f.x);
 this->m02 = float0 * (2.0 * (quat4f.x * quat4f.z + quat4f.w * quat4f.y);
 this->m12 = float0 * (2.0 * (quat4f.y * quat4f.z - quat4f.w * quat4f.x);
 this->m22 = float0 * (1.0 - 2.0 * quat4f.x * quat4f.x - 2.0 * quat4f.y * quat4f.y);
 this->m03 = vector3f.x;
 this->m13 = vector3f.y;
 this->m23 = vector3f.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Matrix4f matrix4f) {
 this->m00 = matrix4f.m00;
 this->m01 = matrix4f.m01;
 this->m02 = matrix4f.m02;
 this->m03 = matrix4f.m03;
 this->m10 = matrix4f.m10;
 this->m11 = matrix4f.m11;
 this->m12 = matrix4f.m12;
 this->m13 = matrix4f.m13;
 this->m20 = matrix4f.m20;
 this->m21 = matrix4f.m21;
 this->m22 = matrix4f.m22;
 this->m23 = matrix4f.m23;
 this->m30 = matrix4f.m30;
 this->m31 = matrix4f.m31;
 this->m32 = matrix4f.m32;
 this->m33 = matrix4f.m33;
 }

 void set(Matrix4d matrix4d0) {
 this->m00 = matrix4d0.m00;
 this->m01 = matrix4d0.m01;
 this->m02 = matrix4d0.m02;
 this->m03 = matrix4d0.m03;
 this->m10 = matrix4d0.m10;
 this->m11 = matrix4d0.m11;
 this->m12 = matrix4d0.m12;
 this->m13 = matrix4d0.m13;
 this->m20 = matrix4d0.m20;
 this->m21 = matrix4d0.m21;
 this->m22 = matrix4d0.m22;
 this->m23 = matrix4d0.m23;
 this->m30 = matrix4d0.m30;
 this->m31 = matrix4d0.m31;
 this->m32 = matrix4d0.m32;
 this->m33 = matrix4d0.m33;
 }

 void invert(Matrix4d matrix4d1) {
 this->invertGeneral(matrix4d1);
 }

 void invert() {
 this->invertGeneral(this);
 }

 void invertGeneral(Matrix4d matrix4d0) {
 double[] doubles0 = new double[16];
 int[] ints = new int[4];
 double[] doubles1 = new double[]{
 matrix4d0.m00,
 matrix4d0.m01,
 matrix4d0.m02,
 matrix4d0.m03,
 matrix4d0.m10,
 matrix4d0.m11,
 matrix4d0.m12,
 matrix4d0.m13,
 matrix4d0.m20,
 matrix4d0.m21,
 matrix4d0.m22,
 matrix4d0.m23,
 matrix4d0.m30,
 matrix4d0.m31,
 matrix4d0.m32,
 matrix4d0.m33
 };
 if (!luDecomposition(doubles1, ints) {
 throw SingularMatrixException(VecMathI18N.getString("Matrix4d10"));
 } else {
 for (int int0 = 0; int0 < 16; int0++) {
 doubles0[int0] = 0.0;
 }

 doubles0[0] = 1.0;
 doubles0[5] = 1.0;
 doubles0[10] = 1.0;
 doubles0[15] = 1.0;
 luBacksubstitution(doubles1, ints, doubles0);
 this->m00 = doubles0[0];
 this->m01 = doubles0[1];
 this->m02 = doubles0[2];
 this->m03 = doubles0[3];
 this->m10 = doubles0[4];
 this->m11 = doubles0[5];
 this->m12 = doubles0[6];
 this->m13 = doubles0[7];
 this->m20 = doubles0[8];
 this->m21 = doubles0[9];
 this->m22 = doubles0[10];
 this->m23 = doubles0[11];
 this->m30 = doubles0[12];
 this->m31 = doubles0[13];
 this->m32 = doubles0[14];
 this->m33 = doubles0[15];
 }
 }

 static bool luDecomposition(double[] doubles1, int[] ints) {
 double[] doubles0 = new double[4];
 int int0 = 0;
 int int1 = 0;
 int int2 = 4;

 while (int2-- != 0) {
 double double0 = 0.0;
 int int3 = 4;

 while (int3-- != 0) {
 double double1 = doubles1[int0++];
 double1 = Math.abs(double1);
 if (double1 > double0) {
 double0 = double1;
 }
 }

 if (double0 == 0.0) {
 return false;
 }

 doubles0[int1++] = 1.0 / double0;
 }

 uint8_t byte0 = 0;

 for (int int4 = 0; int4 < 4; int4++) {
 for (int int5 = 0; int5 < int4; int5++) {
 int int6 = byte0 + 4 * int5 + int4;
 double double2 = doubles1[int6];
 int int7 = int5;
 int int8 = byte0 + 4 * int5;

 for (int int9 = byte0 + int4; int7-- != 0; int9 += 4) {
 double2 -= doubles1[int8] * doubles1[int9];
 int8++;
 }

 doubles1[int6] = double2;
 }

 double double3 = 0.0;
 int1 = -1;

 for (int int10 = int4; int10 < 4; int10++) {
 int int11 = byte0 + 4 * int10 + int4;
 double double4 = doubles1[int11];
 int int12 = int4;
 int int13 = byte0 + 4 * int10;

 for (int int14 = byte0 + int4; int12-- != 0; int14 += 4) {
 double4 -= doubles1[int13] * doubles1[int14];
 int13++;
 }

 doubles1[int11] = double4;
 double double5;
 if ((double5 = doubles0[int10] * Math.abs(double4) >= double3) {
 double3 = double5;
 int1 = int10;
 }
 }

 if (int1 < 0) {
 throw RuntimeException(VecMathI18N.getString("Matrix4d11"));
 }

 if (int4 != int1) {
 int int15 = 4;
 int int16 = byte0 + 4 * int1;
 int int17 = byte0 + 4 * int4;

 while (int15-- != 0) {
 double double6 = doubles1[int16];
 doubles1[int16++] = doubles1[int17];
 doubles1[int17++] = double6;
 }

 doubles0[int1] = doubles0[int4];
 }

 ints[int4] = int1;
 if (doubles1[byte0 + 4 * int4 + int4] == 0.0) {
 return false;
 }

 if (int4 != 3) {
 double double7 = 1.0 / doubles1[byte0 + 4 * int4 + int4];
 int int18 = byte0 + 4 * (int4 + 1) + int4;

 for (int int19 = 3 - int4; int19-- != 0; int18 += 4) {
 doubles1[int18] *= double7;
 }
 }
 }

 return true;
 }

 static void luBacksubstitution(double[] doubles1, int[] ints, double[] doubles0) {
 uint8_t byte0 = 0;

 for (int int0 = 0; int0 < 4; int0++) {
 int int1 = int0;
 int int2 = -1;

 for (int int3 = 0; int3 < 4; int3++) {
 int int4 = ints[byte0 + int3];
 double double0 = doubles0[int1 + 4 * int4];
 doubles0[int1 + 4 * int4] = doubles0[int1 + 4 * int3];
 if (int2 >= 0) {
 int int5 = int3 * 4;

 for (int int6 = int2; int6 <= int3 - 1; int6++) {
 double0 -= doubles1[int5 + int6] * doubles0[int1 + 4 * int6];
 }
 } else if (double0 != 0.0) {
 int2 = int3;
 }

 doubles0[int1 + 4 * int3] = double0;
 }

 int int7 = 12;
 doubles0[int1 + 12] = doubles0[int1 + 12] / doubles1[int7 + 3];
 int7 -= 4;
 doubles0[int1 + 8] = (doubles0[int1 + 8] - doubles1[int7 + 3] * doubles0[int1 + 12]) / doubles1[int7 + 2];
 int7 -= 4;
 doubles0[int1 + 4] = (doubles0[int1 + 4] - doubles1[int7 + 2] * doubles0[int1 + 8] - doubles1[int7 + 3] * doubles0[int1 + 12]) / doubles1[int7 + 1];
 int7 -= 4;
 doubles0[int1 + 0] = (
 doubles0[int1 + 0]
 - doubles1[int7 + 1] * doubles0[int1 + 4]
 - doubles1[int7 + 2] * doubles0[int1 + 8]
 - doubles1[int7 + 3] * doubles0[int1 + 12]
 )
 / doubles1[int7 + 0];
 }
 }

 double determinant() {
 double double0 = this->m00
 * (
 this->m11 * this->m22 * this->m33
 + this->m12 * this->m23 * this->m31
 + this->m13 * this->m21 * this->m32
 - this->m13 * this->m22 * this->m31
 - this->m11 * this->m23 * this->m32
 - this->m12 * this->m21 * this->m33
 );
 double0 -= this->m01
 * (
 this->m10 * this->m22 * this->m33
 + this->m12 * this->m23 * this->m30
 + this->m13 * this->m20 * this->m32
 - this->m13 * this->m22 * this->m30
 - this->m10 * this->m23 * this->m32
 - this->m12 * this->m20 * this->m33
 );
 double0 += this->m02
 * (
 this->m10 * this->m21 * this->m33
 + this->m11 * this->m23 * this->m30
 + this->m13 * this->m20 * this->m31
 - this->m13 * this->m21 * this->m30
 - this->m10 * this->m23 * this->m31
 - this->m11 * this->m20 * this->m33
 );
 return double0
 - this->m03
 * (
 this->m10 * this->m21 * this->m32
 + this->m11 * this->m22 * this->m30
 + this->m12 * this->m20 * this->m31
 - this->m12 * this->m21 * this->m30
 - this->m10 * this->m22 * this->m31
 - this->m11 * this->m20 * this->m32
 );
 }

 void set(double double0) {
 this->m00 = double0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = double0;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = double0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Vector3d vector3d) {
 this->m00 = 1.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = vector3d.x;
 this->m10 = 0.0;
 this->m11 = 1.0;
 this->m12 = 0.0;
 this->m13 = vector3d.y;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 1.0;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(double double0, Vector3d vector3d) {
 this->m00 = double0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = vector3d.x;
 this->m10 = 0.0;
 this->m11 = double0;
 this->m12 = 0.0;
 this->m13 = vector3d.y;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = double0;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Vector3d vector3d, double double0) {
 this->m00 = double0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = double0 * vector3d.x;
 this->m10 = 0.0;
 this->m11 = double0;
 this->m12 = 0.0;
 this->m13 = double0 * vector3d.y;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = double0;
 this->m23 = double0 * vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Matrix3f matrix3f, Vector3f vector3f, float float0) {
 this->m00 = matrix3f.m00 * float0;
 this->m01 = matrix3f.m01 * float0;
 this->m02 = matrix3f.m02 * float0;
 this->m03 = vector3f.x;
 this->m10 = matrix3f.m10 * float0;
 this->m11 = matrix3f.m11 * float0;
 this->m12 = matrix3f.m12 * float0;
 this->m13 = vector3f.y;
 this->m20 = matrix3f.m20 * float0;
 this->m21 = matrix3f.m21 * float0;
 this->m22 = matrix3f.m22 * float0;
 this->m23 = vector3f.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void set(Matrix3d matrix3d, Vector3d vector3d, double double0) {
 this->m00 = matrix3d.m00 * double0;
 this->m01 = matrix3d.m01 * double0;
 this->m02 = matrix3d.m02 * double0;
 this->m03 = vector3d.x;
 this->m10 = matrix3d.m10 * double0;
 this->m11 = matrix3d.m11 * double0;
 this->m12 = matrix3d.m12 * double0;
 this->m13 = vector3d.y;
 this->m20 = matrix3d.m20 * double0;
 this->m21 = matrix3d.m21 * double0;
 this->m22 = matrix3d.m22 * double0;
 this->m23 = vector3d.z;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void setTranslation(Vector3d vector3d) {
 this->m03 = vector3d.x;
 this->m13 = vector3d.y;
 this->m23 = vector3d.z;
 }

 void rotX(double double1) {
 double double0 = Math.sin(double1);
 double double2 = Math.cos(double1);
 this->m00 = 1.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = double2;
 this->m12 = -double0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = double0;
 this->m22 = double2;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void rotY(double double1) {
 double double0 = Math.sin(double1);
 double double2 = Math.cos(double1);
 this->m00 = double2;
 this->m01 = 0.0;
 this->m02 = double0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = 1.0;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = -double0;
 this->m21 = 0.0;
 this->m22 = double2;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void rotZ(double double1) {
 double double0 = Math.sin(double1);
 double double2 = Math.cos(double1);
 this->m00 = double2;
 this->m01 = -double0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = double0;
 this->m11 = double2;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 1.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 1.0;
 }

 void mul(double double0) {
 this->m00 *= double0;
 this->m01 *= double0;
 this->m02 *= double0;
 this->m03 *= double0;
 this->m10 *= double0;
 this->m11 *= double0;
 this->m12 *= double0;
 this->m13 *= double0;
 this->m20 *= double0;
 this->m21 *= double0;
 this->m22 *= double0;
 this->m23 *= double0;
 this->m30 *= double0;
 this->m31 *= double0;
 this->m32 *= double0;
 this->m33 *= double0;
 }

 void mul(double double0, Matrix4d matrix4d0) {
 this->m00 = matrix4d0.m00 * double0;
 this->m01 = matrix4d0.m01 * double0;
 this->m02 = matrix4d0.m02 * double0;
 this->m03 = matrix4d0.m03 * double0;
 this->m10 = matrix4d0.m10 * double0;
 this->m11 = matrix4d0.m11 * double0;
 this->m12 = matrix4d0.m12 * double0;
 this->m13 = matrix4d0.m13 * double0;
 this->m20 = matrix4d0.m20 * double0;
 this->m21 = matrix4d0.m21 * double0;
 this->m22 = matrix4d0.m22 * double0;
 this->m23 = matrix4d0.m23 * double0;
 this->m30 = matrix4d0.m30 * double0;
 this->m31 = matrix4d0.m31 * double0;
 this->m32 = matrix4d0.m32 * double0;
 this->m33 = matrix4d0.m33 * double0;
 }

 void mul(Matrix4d matrix4d0) {
 double double0 = this->m00 * matrix4d0.m00 + this->m01 * matrix4d0.m10 + this->m02 * matrix4d0.m20 + this->m03 * matrix4d0.m30;
 double double1 = this->m00 * matrix4d0.m01 + this->m01 * matrix4d0.m11 + this->m02 * matrix4d0.m21 + this->m03 * matrix4d0.m31;
 double double2 = this->m00 * matrix4d0.m02 + this->m01 * matrix4d0.m12 + this->m02 * matrix4d0.m22 + this->m03 * matrix4d0.m32;
 double double3 = this->m00 * matrix4d0.m03 + this->m01 * matrix4d0.m13 + this->m02 * matrix4d0.m23 + this->m03 * matrix4d0.m33;
 double double4 = this->m10 * matrix4d0.m00 + this->m11 * matrix4d0.m10 + this->m12 * matrix4d0.m20 + this->m13 * matrix4d0.m30;
 double double5 = this->m10 * matrix4d0.m01 + this->m11 * matrix4d0.m11 + this->m12 * matrix4d0.m21 + this->m13 * matrix4d0.m31;
 double double6 = this->m10 * matrix4d0.m02 + this->m11 * matrix4d0.m12 + this->m12 * matrix4d0.m22 + this->m13 * matrix4d0.m32;
 double double7 = this->m10 * matrix4d0.m03 + this->m11 * matrix4d0.m13 + this->m12 * matrix4d0.m23 + this->m13 * matrix4d0.m33;
 double double8 = this->m20 * matrix4d0.m00 + this->m21 * matrix4d0.m10 + this->m22 * matrix4d0.m20 + this->m23 * matrix4d0.m30;
 double double9 = this->m20 * matrix4d0.m01 + this->m21 * matrix4d0.m11 + this->m22 * matrix4d0.m21 + this->m23 * matrix4d0.m31;
 double double10 = this->m20 * matrix4d0.m02 + this->m21 * matrix4d0.m12 + this->m22 * matrix4d0.m22 + this->m23 * matrix4d0.m32;
 double double11 = this->m20 * matrix4d0.m03 + this->m21 * matrix4d0.m13 + this->m22 * matrix4d0.m23 + this->m23 * matrix4d0.m33;
 double double12 = this->m30 * matrix4d0.m00 + this->m31 * matrix4d0.m10 + this->m32 * matrix4d0.m20 + this->m33 * matrix4d0.m30;
 double double13 = this->m30 * matrix4d0.m01 + this->m31 * matrix4d0.m11 + this->m32 * matrix4d0.m21 + this->m33 * matrix4d0.m31;
 double double14 = this->m30 * matrix4d0.m02 + this->m31 * matrix4d0.m12 + this->m32 * matrix4d0.m22 + this->m33 * matrix4d0.m32;
 double double15 = this->m30 * matrix4d0.m03 + this->m31 * matrix4d0.m13 + this->m32 * matrix4d0.m23 + this->m33 * matrix4d0.m33;
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }

 void mul(Matrix4d matrix4d2, Matrix4d matrix4d1) {
 if (this != matrix4d2 && this != matrix4d1) {
 this->m00 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m01 * matrix4d1.m10 + matrix4d2.m02 * matrix4d1.m20 + matrix4d2.m03 * matrix4d1.m30;
 this->m01 = matrix4d2.m00 * matrix4d1.m01 + matrix4d2.m01 * matrix4d1.m11 + matrix4d2.m02 * matrix4d1.m21 + matrix4d2.m03 * matrix4d1.m31;
 this->m02 = matrix4d2.m00 * matrix4d1.m02 + matrix4d2.m01 * matrix4d1.m12 + matrix4d2.m02 * matrix4d1.m22 + matrix4d2.m03 * matrix4d1.m32;
 this->m03 = matrix4d2.m00 * matrix4d1.m03 + matrix4d2.m01 * matrix4d1.m13 + matrix4d2.m02 * matrix4d1.m23 + matrix4d2.m03 * matrix4d1.m33;
 this->m10 = matrix4d2.m10 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m10 + matrix4d2.m12 * matrix4d1.m20 + matrix4d2.m13 * matrix4d1.m30;
 this->m11 = matrix4d2.m10 * matrix4d1.m01 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m12 * matrix4d1.m21 + matrix4d2.m13 * matrix4d1.m31;
 this->m12 = matrix4d2.m10 * matrix4d1.m02 + matrix4d2.m11 * matrix4d1.m12 + matrix4d2.m12 * matrix4d1.m22 + matrix4d2.m13 * matrix4d1.m32;
 this->m13 = matrix4d2.m10 * matrix4d1.m03 + matrix4d2.m11 * matrix4d1.m13 + matrix4d2.m12 * matrix4d1.m23 + matrix4d2.m13 * matrix4d1.m33;
 this->m20 = matrix4d2.m20 * matrix4d1.m00 + matrix4d2.m21 * matrix4d1.m10 + matrix4d2.m22 * matrix4d1.m20 + matrix4d2.m23 * matrix4d1.m30;
 this->m21 = matrix4d2.m20 * matrix4d1.m01 + matrix4d2.m21 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m21 + matrix4d2.m23 * matrix4d1.m31;
 this->m22 = matrix4d2.m20 * matrix4d1.m02 + matrix4d2.m21 * matrix4d1.m12 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m23 * matrix4d1.m32;
 this->m23 = matrix4d2.m20 * matrix4d1.m03 + matrix4d2.m21 * matrix4d1.m13 + matrix4d2.m22 * matrix4d1.m23 + matrix4d2.m23 * matrix4d1.m33;
 this->m30 = matrix4d2.m30 * matrix4d1.m00 + matrix4d2.m31 * matrix4d1.m10 + matrix4d2.m32 * matrix4d1.m20 + matrix4d2.m33 * matrix4d1.m30;
 this->m31 = matrix4d2.m30 * matrix4d1.m01 + matrix4d2.m31 * matrix4d1.m11 + matrix4d2.m32 * matrix4d1.m21 + matrix4d2.m33 * matrix4d1.m31;
 this->m32 = matrix4d2.m30 * matrix4d1.m02 + matrix4d2.m31 * matrix4d1.m12 + matrix4d2.m32 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m32;
 this->m33 = matrix4d2.m30 * matrix4d1.m03 + matrix4d2.m31 * matrix4d1.m13 + matrix4d2.m32 * matrix4d1.m23 + matrix4d2.m33 * matrix4d1.m33;
 } else {
 double double0 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m01 * matrix4d1.m10 + matrix4d2.m02 * matrix4d1.m20 + matrix4d2.m03 * matrix4d1.m30;
 double double1 = matrix4d2.m00 * matrix4d1.m01 + matrix4d2.m01 * matrix4d1.m11 + matrix4d2.m02 * matrix4d1.m21 + matrix4d2.m03 * matrix4d1.m31;
 double double2 = matrix4d2.m00 * matrix4d1.m02 + matrix4d2.m01 * matrix4d1.m12 + matrix4d2.m02 * matrix4d1.m22 + matrix4d2.m03 * matrix4d1.m32;
 double double3 = matrix4d2.m00 * matrix4d1.m03 + matrix4d2.m01 * matrix4d1.m13 + matrix4d2.m02 * matrix4d1.m23 + matrix4d2.m03 * matrix4d1.m33;
 double double4 = matrix4d2.m10 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m10 + matrix4d2.m12 * matrix4d1.m20 + matrix4d2.m13 * matrix4d1.m30;
 double double5 = matrix4d2.m10 * matrix4d1.m01 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m12 * matrix4d1.m21 + matrix4d2.m13 * matrix4d1.m31;
 double double6 = matrix4d2.m10 * matrix4d1.m02 + matrix4d2.m11 * matrix4d1.m12 + matrix4d2.m12 * matrix4d1.m22 + matrix4d2.m13 * matrix4d1.m32;
 double double7 = matrix4d2.m10 * matrix4d1.m03 + matrix4d2.m11 * matrix4d1.m13 + matrix4d2.m12 * matrix4d1.m23 + matrix4d2.m13 * matrix4d1.m33;
 double double8 = matrix4d2.m20 * matrix4d1.m00 + matrix4d2.m21 * matrix4d1.m10 + matrix4d2.m22 * matrix4d1.m20 + matrix4d2.m23 * matrix4d1.m30;
 double double9 = matrix4d2.m20 * matrix4d1.m01 + matrix4d2.m21 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m21 + matrix4d2.m23 * matrix4d1.m31;
 double double10 = matrix4d2.m20 * matrix4d1.m02 + matrix4d2.m21 * matrix4d1.m12 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m23 * matrix4d1.m32;
 double double11 = matrix4d2.m20 * matrix4d1.m03 + matrix4d2.m21 * matrix4d1.m13 + matrix4d2.m22 * matrix4d1.m23 + matrix4d2.m23 * matrix4d1.m33;
 double double12 = matrix4d2.m30 * matrix4d1.m00 + matrix4d2.m31 * matrix4d1.m10 + matrix4d2.m32 * matrix4d1.m20 + matrix4d2.m33 * matrix4d1.m30;
 double double13 = matrix4d2.m30 * matrix4d1.m01 + matrix4d2.m31 * matrix4d1.m11 + matrix4d2.m32 * matrix4d1.m21 + matrix4d2.m33 * matrix4d1.m31;
 double double14 = matrix4d2.m30 * matrix4d1.m02 + matrix4d2.m31 * matrix4d1.m12 + matrix4d2.m32 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m32;
 double double15 = matrix4d2.m30 * matrix4d1.m03 + matrix4d2.m31 * matrix4d1.m13 + matrix4d2.m32 * matrix4d1.m23 + matrix4d2.m33 * matrix4d1.m33;
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }
 }

 void mulTransposeBoth(Matrix4d matrix4d2, Matrix4d matrix4d1) {
 if (this != matrix4d2 && this != matrix4d1) {
 this->m00 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m10 * matrix4d1.m01 + matrix4d2.m20 * matrix4d1.m02 + matrix4d2.m30 * matrix4d1.m03;
 this->m01 = matrix4d2.m00 * matrix4d1.m10 + matrix4d2.m10 * matrix4d1.m11 + matrix4d2.m20 * matrix4d1.m12 + matrix4d2.m30 * matrix4d1.m13;
 this->m02 = matrix4d2.m00 * matrix4d1.m20 + matrix4d2.m10 * matrix4d1.m21 + matrix4d2.m20 * matrix4d1.m22 + matrix4d2.m30 * matrix4d1.m23;
 this->m03 = matrix4d2.m00 * matrix4d1.m30 + matrix4d2.m10 * matrix4d1.m31 + matrix4d2.m20 * matrix4d1.m32 + matrix4d2.m30 * matrix4d1.m33;
 this->m10 = matrix4d2.m01 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m01 + matrix4d2.m21 * matrix4d1.m02 + matrix4d2.m31 * matrix4d1.m03;
 this->m11 = matrix4d2.m01 * matrix4d1.m10 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m21 * matrix4d1.m12 + matrix4d2.m31 * matrix4d1.m13;
 this->m12 = matrix4d2.m01 * matrix4d1.m20 + matrix4d2.m11 * matrix4d1.m21 + matrix4d2.m21 * matrix4d1.m22 + matrix4d2.m31 * matrix4d1.m23;
 this->m13 = matrix4d2.m01 * matrix4d1.m30 + matrix4d2.m11 * matrix4d1.m31 + matrix4d2.m21 * matrix4d1.m32 + matrix4d2.m31 * matrix4d1.m33;
 this->m20 = matrix4d2.m02 * matrix4d1.m00 + matrix4d2.m12 * matrix4d1.m01 + matrix4d2.m22 * matrix4d1.m02 + matrix4d2.m32 * matrix4d1.m03;
 this->m21 = matrix4d2.m02 * matrix4d1.m10 + matrix4d2.m12 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m12 + matrix4d2.m32 * matrix4d1.m13;
 this->m22 = matrix4d2.m02 * matrix4d1.m20 + matrix4d2.m12 * matrix4d1.m21 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m32 * matrix4d1.m23;
 this->m23 = matrix4d2.m02 * matrix4d1.m30 + matrix4d2.m12 * matrix4d1.m31 + matrix4d2.m22 * matrix4d1.m32 + matrix4d2.m32 * matrix4d1.m33;
 this->m30 = matrix4d2.m03 * matrix4d1.m00 + matrix4d2.m13 * matrix4d1.m01 + matrix4d2.m23 * matrix4d1.m02 + matrix4d2.m33 * matrix4d1.m03;
 this->m31 = matrix4d2.m03 * matrix4d1.m10 + matrix4d2.m13 * matrix4d1.m11 + matrix4d2.m23 * matrix4d1.m12 + matrix4d2.m33 * matrix4d1.m13;
 this->m32 = matrix4d2.m03 * matrix4d1.m20 + matrix4d2.m13 * matrix4d1.m21 + matrix4d2.m23 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m23;
 this->m33 = matrix4d2.m03 * matrix4d1.m30 + matrix4d2.m13 * matrix4d1.m31 + matrix4d2.m23 * matrix4d1.m32 + matrix4d2.m33 * matrix4d1.m33;
 } else {
 double double0 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m10 * matrix4d1.m01 + matrix4d2.m20 * matrix4d1.m02 + matrix4d2.m30 * matrix4d1.m03;
 double double1 = matrix4d2.m00 * matrix4d1.m10 + matrix4d2.m10 * matrix4d1.m11 + matrix4d2.m20 * matrix4d1.m12 + matrix4d2.m30 * matrix4d1.m13;
 double double2 = matrix4d2.m00 * matrix4d1.m20 + matrix4d2.m10 * matrix4d1.m21 + matrix4d2.m20 * matrix4d1.m22 + matrix4d2.m30 * matrix4d1.m23;
 double double3 = matrix4d2.m00 * matrix4d1.m30 + matrix4d2.m10 * matrix4d1.m31 + matrix4d2.m20 * matrix4d1.m32 + matrix4d2.m30 * matrix4d1.m33;
 double double4 = matrix4d2.m01 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m01 + matrix4d2.m21 * matrix4d1.m02 + matrix4d2.m31 * matrix4d1.m03;
 double double5 = matrix4d2.m01 * matrix4d1.m10 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m21 * matrix4d1.m12 + matrix4d2.m31 * matrix4d1.m13;
 double double6 = matrix4d2.m01 * matrix4d1.m20 + matrix4d2.m11 * matrix4d1.m21 + matrix4d2.m21 * matrix4d1.m22 + matrix4d2.m31 * matrix4d1.m23;
 double double7 = matrix4d2.m01 * matrix4d1.m30 + matrix4d2.m11 * matrix4d1.m31 + matrix4d2.m21 * matrix4d1.m32 + matrix4d2.m31 * matrix4d1.m33;
 double double8 = matrix4d2.m02 * matrix4d1.m00 + matrix4d2.m12 * matrix4d1.m01 + matrix4d2.m22 * matrix4d1.m02 + matrix4d2.m32 * matrix4d1.m03;
 double double9 = matrix4d2.m02 * matrix4d1.m10 + matrix4d2.m12 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m12 + matrix4d2.m32 * matrix4d1.m13;
 double double10 = matrix4d2.m02 * matrix4d1.m20 + matrix4d2.m12 * matrix4d1.m21 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m32 * matrix4d1.m23;
 double double11 = matrix4d2.m02 * matrix4d1.m30 + matrix4d2.m12 * matrix4d1.m31 + matrix4d2.m22 * matrix4d1.m32 + matrix4d2.m32 * matrix4d1.m33;
 double double12 = matrix4d2.m03 * matrix4d1.m00 + matrix4d2.m13 * matrix4d1.m01 + matrix4d2.m23 * matrix4d1.m02 + matrix4d2.m33 * matrix4d1.m03;
 double double13 = matrix4d2.m03 * matrix4d1.m10 + matrix4d2.m13 * matrix4d1.m11 + matrix4d2.m23 * matrix4d1.m12 + matrix4d2.m33 * matrix4d1.m13;
 double double14 = matrix4d2.m03 * matrix4d1.m20 + matrix4d2.m13 * matrix4d1.m21 + matrix4d2.m23 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m23;
 double double15 = matrix4d2.m03 * matrix4d1.m30 + matrix4d2.m13 * matrix4d1.m31 + matrix4d2.m23 * matrix4d1.m32 + matrix4d2.m33 * matrix4d1.m33;
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }
 }

 void mulTransposeRight(Matrix4d matrix4d2, Matrix4d matrix4d1) {
 if (this != matrix4d2 && this != matrix4d1) {
 this->m00 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m01 * matrix4d1.m01 + matrix4d2.m02 * matrix4d1.m02 + matrix4d2.m03 * matrix4d1.m03;
 this->m01 = matrix4d2.m00 * matrix4d1.m10 + matrix4d2.m01 * matrix4d1.m11 + matrix4d2.m02 * matrix4d1.m12 + matrix4d2.m03 * matrix4d1.m13;
 this->m02 = matrix4d2.m00 * matrix4d1.m20 + matrix4d2.m01 * matrix4d1.m21 + matrix4d2.m02 * matrix4d1.m22 + matrix4d2.m03 * matrix4d1.m23;
 this->m03 = matrix4d2.m00 * matrix4d1.m30 + matrix4d2.m01 * matrix4d1.m31 + matrix4d2.m02 * matrix4d1.m32 + matrix4d2.m03 * matrix4d1.m33;
 this->m10 = matrix4d2.m10 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m01 + matrix4d2.m12 * matrix4d1.m02 + matrix4d2.m13 * matrix4d1.m03;
 this->m11 = matrix4d2.m10 * matrix4d1.m10 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m12 * matrix4d1.m12 + matrix4d2.m13 * matrix4d1.m13;
 this->m12 = matrix4d2.m10 * matrix4d1.m20 + matrix4d2.m11 * matrix4d1.m21 + matrix4d2.m12 * matrix4d1.m22 + matrix4d2.m13 * matrix4d1.m23;
 this->m13 = matrix4d2.m10 * matrix4d1.m30 + matrix4d2.m11 * matrix4d1.m31 + matrix4d2.m12 * matrix4d1.m32 + matrix4d2.m13 * matrix4d1.m33;
 this->m20 = matrix4d2.m20 * matrix4d1.m00 + matrix4d2.m21 * matrix4d1.m01 + matrix4d2.m22 * matrix4d1.m02 + matrix4d2.m23 * matrix4d1.m03;
 this->m21 = matrix4d2.m20 * matrix4d1.m10 + matrix4d2.m21 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m12 + matrix4d2.m23 * matrix4d1.m13;
 this->m22 = matrix4d2.m20 * matrix4d1.m20 + matrix4d2.m21 * matrix4d1.m21 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m23 * matrix4d1.m23;
 this->m23 = matrix4d2.m20 * matrix4d1.m30 + matrix4d2.m21 * matrix4d1.m31 + matrix4d2.m22 * matrix4d1.m32 + matrix4d2.m23 * matrix4d1.m33;
 this->m30 = matrix4d2.m30 * matrix4d1.m00 + matrix4d2.m31 * matrix4d1.m01 + matrix4d2.m32 * matrix4d1.m02 + matrix4d2.m33 * matrix4d1.m03;
 this->m31 = matrix4d2.m30 * matrix4d1.m10 + matrix4d2.m31 * matrix4d1.m11 + matrix4d2.m32 * matrix4d1.m12 + matrix4d2.m33 * matrix4d1.m13;
 this->m32 = matrix4d2.m30 * matrix4d1.m20 + matrix4d2.m31 * matrix4d1.m21 + matrix4d2.m32 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m23;
 this->m33 = matrix4d2.m30 * matrix4d1.m30 + matrix4d2.m31 * matrix4d1.m31 + matrix4d2.m32 * matrix4d1.m32 + matrix4d2.m33 * matrix4d1.m33;
 } else {
 double double0 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m01 * matrix4d1.m01 + matrix4d2.m02 * matrix4d1.m02 + matrix4d2.m03 * matrix4d1.m03;
 double double1 = matrix4d2.m00 * matrix4d1.m10 + matrix4d2.m01 * matrix4d1.m11 + matrix4d2.m02 * matrix4d1.m12 + matrix4d2.m03 * matrix4d1.m13;
 double double2 = matrix4d2.m00 * matrix4d1.m20 + matrix4d2.m01 * matrix4d1.m21 + matrix4d2.m02 * matrix4d1.m22 + matrix4d2.m03 * matrix4d1.m23;
 double double3 = matrix4d2.m00 * matrix4d1.m30 + matrix4d2.m01 * matrix4d1.m31 + matrix4d2.m02 * matrix4d1.m32 + matrix4d2.m03 * matrix4d1.m33;
 double double4 = matrix4d2.m10 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m01 + matrix4d2.m12 * matrix4d1.m02 + matrix4d2.m13 * matrix4d1.m03;
 double double5 = matrix4d2.m10 * matrix4d1.m10 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m12 * matrix4d1.m12 + matrix4d2.m13 * matrix4d1.m13;
 double double6 = matrix4d2.m10 * matrix4d1.m20 + matrix4d2.m11 * matrix4d1.m21 + matrix4d2.m12 * matrix4d1.m22 + matrix4d2.m13 * matrix4d1.m23;
 double double7 = matrix4d2.m10 * matrix4d1.m30 + matrix4d2.m11 * matrix4d1.m31 + matrix4d2.m12 * matrix4d1.m32 + matrix4d2.m13 * matrix4d1.m33;
 double double8 = matrix4d2.m20 * matrix4d1.m00 + matrix4d2.m21 * matrix4d1.m01 + matrix4d2.m22 * matrix4d1.m02 + matrix4d2.m23 * matrix4d1.m03;
 double double9 = matrix4d2.m20 * matrix4d1.m10 + matrix4d2.m21 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m12 + matrix4d2.m23 * matrix4d1.m13;
 double double10 = matrix4d2.m20 * matrix4d1.m20 + matrix4d2.m21 * matrix4d1.m21 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m23 * matrix4d1.m23;
 double double11 = matrix4d2.m20 * matrix4d1.m30 + matrix4d2.m21 * matrix4d1.m31 + matrix4d2.m22 * matrix4d1.m32 + matrix4d2.m23 * matrix4d1.m33;
 double double12 = matrix4d2.m30 * matrix4d1.m00 + matrix4d2.m31 * matrix4d1.m01 + matrix4d2.m32 * matrix4d1.m02 + matrix4d2.m33 * matrix4d1.m03;
 double double13 = matrix4d2.m30 * matrix4d1.m10 + matrix4d2.m31 * matrix4d1.m11 + matrix4d2.m32 * matrix4d1.m12 + matrix4d2.m33 * matrix4d1.m13;
 double double14 = matrix4d2.m30 * matrix4d1.m20 + matrix4d2.m31 * matrix4d1.m21 + matrix4d2.m32 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m23;
 double double15 = matrix4d2.m30 * matrix4d1.m30 + matrix4d2.m31 * matrix4d1.m31 + matrix4d2.m32 * matrix4d1.m32 + matrix4d2.m33 * matrix4d1.m33;
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }
 }

 void mulTransposeLeft(Matrix4d matrix4d2, Matrix4d matrix4d1) {
 if (this != matrix4d2 && this != matrix4d1) {
 this->m00 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m10 * matrix4d1.m10 + matrix4d2.m20 * matrix4d1.m20 + matrix4d2.m30 * matrix4d1.m30;
 this->m01 = matrix4d2.m00 * matrix4d1.m01 + matrix4d2.m10 * matrix4d1.m11 + matrix4d2.m20 * matrix4d1.m21 + matrix4d2.m30 * matrix4d1.m31;
 this->m02 = matrix4d2.m00 * matrix4d1.m02 + matrix4d2.m10 * matrix4d1.m12 + matrix4d2.m20 * matrix4d1.m22 + matrix4d2.m30 * matrix4d1.m32;
 this->m03 = matrix4d2.m00 * matrix4d1.m03 + matrix4d2.m10 * matrix4d1.m13 + matrix4d2.m20 * matrix4d1.m23 + matrix4d2.m30 * matrix4d1.m33;
 this->m10 = matrix4d2.m01 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m10 + matrix4d2.m21 * matrix4d1.m20 + matrix4d2.m31 * matrix4d1.m30;
 this->m11 = matrix4d2.m01 * matrix4d1.m01 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m21 * matrix4d1.m21 + matrix4d2.m31 * matrix4d1.m31;
 this->m12 = matrix4d2.m01 * matrix4d1.m02 + matrix4d2.m11 * matrix4d1.m12 + matrix4d2.m21 * matrix4d1.m22 + matrix4d2.m31 * matrix4d1.m32;
 this->m13 = matrix4d2.m01 * matrix4d1.m03 + matrix4d2.m11 * matrix4d1.m13 + matrix4d2.m21 * matrix4d1.m23 + matrix4d2.m31 * matrix4d1.m33;
 this->m20 = matrix4d2.m02 * matrix4d1.m00 + matrix4d2.m12 * matrix4d1.m10 + matrix4d2.m22 * matrix4d1.m20 + matrix4d2.m32 * matrix4d1.m30;
 this->m21 = matrix4d2.m02 * matrix4d1.m01 + matrix4d2.m12 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m21 + matrix4d2.m32 * matrix4d1.m31;
 this->m22 = matrix4d2.m02 * matrix4d1.m02 + matrix4d2.m12 * matrix4d1.m12 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m32 * matrix4d1.m32;
 this->m23 = matrix4d2.m02 * matrix4d1.m03 + matrix4d2.m12 * matrix4d1.m13 + matrix4d2.m22 * matrix4d1.m23 + matrix4d2.m32 * matrix4d1.m33;
 this->m30 = matrix4d2.m03 * matrix4d1.m00 + matrix4d2.m13 * matrix4d1.m10 + matrix4d2.m23 * matrix4d1.m20 + matrix4d2.m33 * matrix4d1.m30;
 this->m31 = matrix4d2.m03 * matrix4d1.m01 + matrix4d2.m13 * matrix4d1.m11 + matrix4d2.m23 * matrix4d1.m21 + matrix4d2.m33 * matrix4d1.m31;
 this->m32 = matrix4d2.m03 * matrix4d1.m02 + matrix4d2.m13 * matrix4d1.m12 + matrix4d2.m23 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m32;
 this->m33 = matrix4d2.m03 * matrix4d1.m03 + matrix4d2.m13 * matrix4d1.m13 + matrix4d2.m23 * matrix4d1.m23 + matrix4d2.m33 * matrix4d1.m33;
 } else {
 double double0 = matrix4d2.m00 * matrix4d1.m00 + matrix4d2.m10 * matrix4d1.m10 + matrix4d2.m20 * matrix4d1.m20 + matrix4d2.m30 * matrix4d1.m30;
 double double1 = matrix4d2.m00 * matrix4d1.m01 + matrix4d2.m10 * matrix4d1.m11 + matrix4d2.m20 * matrix4d1.m21 + matrix4d2.m30 * matrix4d1.m31;
 double double2 = matrix4d2.m00 * matrix4d1.m02 + matrix4d2.m10 * matrix4d1.m12 + matrix4d2.m20 * matrix4d1.m22 + matrix4d2.m30 * matrix4d1.m32;
 double double3 = matrix4d2.m00 * matrix4d1.m03 + matrix4d2.m10 * matrix4d1.m13 + matrix4d2.m20 * matrix4d1.m23 + matrix4d2.m30 * matrix4d1.m33;
 double double4 = matrix4d2.m01 * matrix4d1.m00 + matrix4d2.m11 * matrix4d1.m10 + matrix4d2.m21 * matrix4d1.m20 + matrix4d2.m31 * matrix4d1.m30;
 double double5 = matrix4d2.m01 * matrix4d1.m01 + matrix4d2.m11 * matrix4d1.m11 + matrix4d2.m21 * matrix4d1.m21 + matrix4d2.m31 * matrix4d1.m31;
 double double6 = matrix4d2.m01 * matrix4d1.m02 + matrix4d2.m11 * matrix4d1.m12 + matrix4d2.m21 * matrix4d1.m22 + matrix4d2.m31 * matrix4d1.m32;
 double double7 = matrix4d2.m01 * matrix4d1.m03 + matrix4d2.m11 * matrix4d1.m13 + matrix4d2.m21 * matrix4d1.m23 + matrix4d2.m31 * matrix4d1.m33;
 double double8 = matrix4d2.m02 * matrix4d1.m00 + matrix4d2.m12 * matrix4d1.m10 + matrix4d2.m22 * matrix4d1.m20 + matrix4d2.m32 * matrix4d1.m30;
 double double9 = matrix4d2.m02 * matrix4d1.m01 + matrix4d2.m12 * matrix4d1.m11 + matrix4d2.m22 * matrix4d1.m21 + matrix4d2.m32 * matrix4d1.m31;
 double double10 = matrix4d2.m02 * matrix4d1.m02 + matrix4d2.m12 * matrix4d1.m12 + matrix4d2.m22 * matrix4d1.m22 + matrix4d2.m32 * matrix4d1.m32;
 double double11 = matrix4d2.m02 * matrix4d1.m03 + matrix4d2.m12 * matrix4d1.m13 + matrix4d2.m22 * matrix4d1.m23 + matrix4d2.m32 * matrix4d1.m33;
 double double12 = matrix4d2.m03 * matrix4d1.m00 + matrix4d2.m13 * matrix4d1.m10 + matrix4d2.m23 * matrix4d1.m20 + matrix4d2.m33 * matrix4d1.m30;
 double double13 = matrix4d2.m03 * matrix4d1.m01 + matrix4d2.m13 * matrix4d1.m11 + matrix4d2.m23 * matrix4d1.m21 + matrix4d2.m33 * matrix4d1.m31;
 double double14 = matrix4d2.m03 * matrix4d1.m02 + matrix4d2.m13 * matrix4d1.m12 + matrix4d2.m23 * matrix4d1.m22 + matrix4d2.m33 * matrix4d1.m32;
 double double15 = matrix4d2.m03 * matrix4d1.m03 + matrix4d2.m13 * matrix4d1.m13 + matrix4d2.m23 * matrix4d1.m23 + matrix4d2.m33 * matrix4d1.m33;
 this->m00 = double0;
 this->m01 = double1;
 this->m02 = double2;
 this->m03 = double3;
 this->m10 = double4;
 this->m11 = double5;
 this->m12 = double6;
 this->m13 = double7;
 this->m20 = double8;
 this->m21 = double9;
 this->m22 = double10;
 this->m23 = double11;
 this->m30 = double12;
 this->m31 = double13;
 this->m32 = double14;
 this->m33 = double15;
 }
 }

 bool equals(Matrix4d matrix4d0) {
 try {
 return this->m00 == matrix4d0.m00
 && this->m01 == matrix4d0.m01
 && this->m02 == matrix4d0.m02
 && this->m03 == matrix4d0.m03
 && this->m10 == matrix4d0.m10
 && this->m11 == matrix4d0.m11
 && this->m12 == matrix4d0.m12
 && this->m13 == matrix4d0.m13
 && this->m20 == matrix4d0.m20
 && this->m21 == matrix4d0.m21
 && this->m22 == matrix4d0.m22
 && this->m23 == matrix4d0.m23
 && this->m30 == matrix4d0.m30
 && this->m31 == matrix4d0.m31
 && this->m32 == matrix4d0.m32
 && this->m33 == matrix4d0.m33;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 bool equals(void* object) {
 try {
 Matrix4d matrix4d0 = (Matrix4d)object;
 return this->m00 == matrix4d0.m00
 && this->m01 == matrix4d0.m01
 && this->m02 == matrix4d0.m02
 && this->m03 == matrix4d0.m03
 && this->m10 == matrix4d0.m10
 && this->m11 == matrix4d0.m11
 && this->m12 == matrix4d0.m12
 && this->m13 == matrix4d0.m13
 && this->m20 == matrix4d0.m20
 && this->m21 == matrix4d0.m21
 && this->m22 == matrix4d0.m22
 && this->m23 == matrix4d0.m23
 && this->m30 == matrix4d0.m30
 && this->m31 == matrix4d0.m31
 && this->m32 == matrix4d0.m32
 && this->m33 == matrix4d0.m33;
 } catch (ClassCastException classCastException) {
 return false;
 } catch (NullPointerException nullPointerException) {
 return false;
 }
 }

 /** @deprecated */
 bool epsilonEquals(Matrix4d matrix4d1, float float0) {
 return this->epsilonEquals(matrix4d1, (double)float0);
 }

 bool epsilonEquals(Matrix4d matrix4d0, double double1) {
 double double0 = this->m00 - matrix4d0.m00;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m01 - matrix4d0.m01;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m02 - matrix4d0.m02;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m03 - matrix4d0.m03;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m10 - matrix4d0.m10;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m11 - matrix4d0.m11;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m12 - matrix4d0.m12;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m13 - matrix4d0.m13;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m20 - matrix4d0.m20;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m21 - matrix4d0.m21;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m22 - matrix4d0.m22;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m23 - matrix4d0.m23;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m30 - matrix4d0.m30;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m31 - matrix4d0.m31;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m32 - matrix4d0.m32;
 if ((double0 < 0.0 ? -double0 : double0) > double1) {
 return false;
 } else {
 double0 = this->m33 - matrix4d0.m33;
 return !((double0 < 0.0 ? -double0 : double0) > double1);
 }
 }
 }
 }
 }
 }
 }
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
 long long0 = 1L;
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m00);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m01);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m02);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m03);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m10);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m11);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m12);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m13);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m20);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m21);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m22);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m23);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m30);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m31);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m32);
 long0 = 31L * long0 + VecMathUtil.doubleToLongBits(this->m33);
 return (int)(long0 ^ long0 >> 32);
 }

 void transform(Tuple4d tuple4d0, Tuple4d tuple4d1) {
 double double0 = this->m00 * tuple4d0.x + this->m01 * tuple4d0.y + this->m02 * tuple4d0.z + this->m03 * tuple4d0.w;
 double double1 = this->m10 * tuple4d0.x + this->m11 * tuple4d0.y + this->m12 * tuple4d0.z + this->m13 * tuple4d0.w;
 double double2 = this->m20 * tuple4d0.x + this->m21 * tuple4d0.y + this->m22 * tuple4d0.z + this->m23 * tuple4d0.w;
 tuple4d1.w = this->m30 * tuple4d0.x + this->m31 * tuple4d0.y + this->m32 * tuple4d0.z + this->m33 * tuple4d0.w;
 tuple4d1.x = double0;
 tuple4d1.y = double1;
 tuple4d1.z = double2;
 }

 void transform(Tuple4d tuple4d) {
 double double0 = this->m00 * tuple4d.x + this->m01 * tuple4d.y + this->m02 * tuple4d.z + this->m03 * tuple4d.w;
 double double1 = this->m10 * tuple4d.x + this->m11 * tuple4d.y + this->m12 * tuple4d.z + this->m13 * tuple4d.w;
 double double2 = this->m20 * tuple4d.x + this->m21 * tuple4d.y + this->m22 * tuple4d.z + this->m23 * tuple4d.w;
 tuple4d.w = this->m30 * tuple4d.x + this->m31 * tuple4d.y + this->m32 * tuple4d.z + this->m33 * tuple4d.w;
 tuple4d.x = double0;
 tuple4d.y = double1;
 tuple4d.z = double2;
 }

 void transform(Tuple4f tuple4f0, Tuple4f tuple4f1) {
 float float0 = (float)(this->m00 * tuple4f0.x + this->m01 * tuple4f0.y + this->m02 * tuple4f0.z + this->m03 * tuple4f0.w);
 float float1 = (float)(this->m10 * tuple4f0.x + this->m11 * tuple4f0.y + this->m12 * tuple4f0.z + this->m13 * tuple4f0.w);
 float float2 = (float)(this->m20 * tuple4f0.x + this->m21 * tuple4f0.y + this->m22 * tuple4f0.z + this->m23 * tuple4f0.w);
 tuple4f1.w = (float)(this->m30 * tuple4f0.x + this->m31 * tuple4f0.y + this->m32 * tuple4f0.z + this->m33 * tuple4f0.w);
 tuple4f1.x = float0;
 tuple4f1.y = float1;
 tuple4f1.z = float2;
 }

 void transform(Tuple4f tuple4f) {
 float float0 = (float)(this->m00 * tuple4f.x + this->m01 * tuple4f.y + this->m02 * tuple4f.z + this->m03 * tuple4f.w);
 float float1 = (float)(this->m10 * tuple4f.x + this->m11 * tuple4f.y + this->m12 * tuple4f.z + this->m13 * tuple4f.w);
 float float2 = (float)(this->m20 * tuple4f.x + this->m21 * tuple4f.y + this->m22 * tuple4f.z + this->m23 * tuple4f.w);
 tuple4f.w = (float)(this->m30 * tuple4f.x + this->m31 * tuple4f.y + this->m32 * tuple4f.z + this->m33 * tuple4f.w);
 tuple4f.x = float0;
 tuple4f.y = float1;
 tuple4f.z = float2;
 }

 void transform(Point3d point3d0, Point3d point3d1) {
 double double0 = this->m00 * point3d0.x + this->m01 * point3d0.y + this->m02 * point3d0.z + this->m03;
 double double1 = this->m10 * point3d0.x + this->m11 * point3d0.y + this->m12 * point3d0.z + this->m13;
 point3d1.z = this->m20 * point3d0.x + this->m21 * point3d0.y + this->m22 * point3d0.z + this->m23;
 point3d1.x = double0;
 point3d1.y = double1;
 }

 void transform(Point3d point3d) {
 double double0 = this->m00 * point3d.x + this->m01 * point3d.y + this->m02 * point3d.z + this->m03;
 double double1 = this->m10 * point3d.x + this->m11 * point3d.y + this->m12 * point3d.z + this->m13;
 point3d.z = this->m20 * point3d.x + this->m21 * point3d.y + this->m22 * point3d.z + this->m23;
 point3d.x = double0;
 point3d.y = double1;
 }

 void transform(Point3f point3f0, Point3f point3f1) {
 float float0 = (float)(this->m00 * point3f0.x + this->m01 * point3f0.y + this->m02 * point3f0.z + this->m03);
 float float1 = (float)(this->m10 * point3f0.x + this->m11 * point3f0.y + this->m12 * point3f0.z + this->m13);
 point3f1.z = (float)(this->m20 * point3f0.x + this->m21 * point3f0.y + this->m22 * point3f0.z + this->m23);
 point3f1.x = float0;
 point3f1.y = float1;
 }

 void transform(Point3f point3f) {
 float float0 = (float)(this->m00 * point3f.x + this->m01 * point3f.y + this->m02 * point3f.z + this->m03);
 float float1 = (float)(this->m10 * point3f.x + this->m11 * point3f.y + this->m12 * point3f.z + this->m13);
 point3f.z = (float)(this->m20 * point3f.x + this->m21 * point3f.y + this->m22 * point3f.z + this->m23);
 point3f.x = float0;
 point3f.y = float1;
 }

 void transform(Vector3d vector3d0, Vector3d vector3d1) {
 double double0 = this->m00 * vector3d0.x + this->m01 * vector3d0.y + this->m02 * vector3d0.z;
 double double1 = this->m10 * vector3d0.x + this->m11 * vector3d0.y + this->m12 * vector3d0.z;
 vector3d1.z = this->m20 * vector3d0.x + this->m21 * vector3d0.y + this->m22 * vector3d0.z;
 vector3d1.x = double0;
 vector3d1.y = double1;
 }

 void transform(Vector3d vector3d) {
 double double0 = this->m00 * vector3d.x + this->m01 * vector3d.y + this->m02 * vector3d.z;
 double double1 = this->m10 * vector3d.x + this->m11 * vector3d.y + this->m12 * vector3d.z;
 vector3d.z = this->m20 * vector3d.x + this->m21 * vector3d.y + this->m22 * vector3d.z;
 vector3d.x = double0;
 vector3d.y = double1;
 }

 void transform(Vector3f vector3f0, Vector3f vector3f1) {
 float float0 = (float)(this->m00 * vector3f0.x + this->m01 * vector3f0.y + this->m02 * vector3f0.z);
 float float1 = (float)(this->m10 * vector3f0.x + this->m11 * vector3f0.y + this->m12 * vector3f0.z);
 vector3f1.z = (float)(this->m20 * vector3f0.x + this->m21 * vector3f0.y + this->m22 * vector3f0.z);
 vector3f1.x = float0;
 vector3f1.y = float1;
 }

 void transform(Vector3f vector3f) {
 float float0 = (float)(this->m00 * vector3f.x + this->m01 * vector3f.y + this->m02 * vector3f.z);
 float float1 = (float)(this->m10 * vector3f.x + this->m11 * vector3f.y + this->m12 * vector3f.z);
 vector3f.z = (float)(this->m20 * vector3f.x + this->m21 * vector3f.y + this->m22 * vector3f.z);
 vector3f.x = float0;
 vector3f.y = float1;
 }

 void setRotation(Matrix3d matrix3d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 this->m00 = matrix3d.m00 * doubles1[0];
 this->m01 = matrix3d.m01 * doubles1[1];
 this->m02 = matrix3d.m02 * doubles1[2];
 this->m10 = matrix3d.m10 * doubles1[0];
 this->m11 = matrix3d.m11 * doubles1[1];
 this->m12 = matrix3d.m12 * doubles1[2];
 this->m20 = matrix3d.m20 * doubles1[0];
 this->m21 = matrix3d.m21 * doubles1[1];
 this->m22 = matrix3d.m22 * doubles1[2];
 }

 void setRotation(Matrix3f matrix3f) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 this->m00 = matrix3f.m00 * doubles1[0];
 this->m01 = matrix3f.m01 * doubles1[1];
 this->m02 = matrix3f.m02 * doubles1[2];
 this->m10 = matrix3f.m10 * doubles1[0];
 this->m11 = matrix3f.m11 * doubles1[1];
 this->m12 = matrix3f.m12 * doubles1[2];
 this->m20 = matrix3f.m20 * doubles1[0];
 this->m21 = matrix3f.m21 * doubles1[1];
 this->m22 = matrix3f.m22 * doubles1[2];
 }

 void setRotation(Quat4f quat4f) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 this->m00 = (1.0 - 2.0F * quat4f.y * quat4f.y - 2.0F * quat4f.z * quat4f.z) * doubles1[0];
 this->m10 = 2.0 * (quat4f.x * quat4f.y + quat4f.w * quat4f.z) * doubles1[0];
 this->m20 = 2.0 * (quat4f.x * quat4f.z - quat4f.w * quat4f.y) * doubles1[0];
 this->m01 = 2.0 * (quat4f.x * quat4f.y - quat4f.w * quat4f.z) * doubles1[1];
 this->m11 = (1.0 - 2.0F * quat4f.x * quat4f.x - 2.0F * quat4f.z * quat4f.z) * doubles1[1];
 this->m21 = 2.0 * (quat4f.y * quat4f.z + quat4f.w * quat4f.x) * doubles1[1];
 this->m02 = 2.0 * (quat4f.x * quat4f.z + quat4f.w * quat4f.y) * doubles1[2];
 this->m12 = 2.0 * (quat4f.y * quat4f.z - quat4f.w * quat4f.x) * doubles1[2];
 this->m22 = (1.0 - 2.0F * quat4f.x * quat4f.x - 2.0F * quat4f.y * quat4f.y) * doubles1[2];
 }

 void setRotation(Quat4d quat4d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 this->m00 = (1.0 - 2.0 * quat4d.y * quat4d.y - 2.0 * quat4d.z * quat4d.z) * doubles1[0];
 this->m10 = 2.0 * (quat4d.x * quat4d.y + quat4d.w * quat4d.z) * doubles1[0];
 this->m20 = 2.0 * (quat4d.x * quat4d.z - quat4d.w * quat4d.y) * doubles1[0];
 this->m01 = 2.0 * (quat4d.x * quat4d.y - quat4d.w * quat4d.z) * doubles1[1];
 this->m11 = (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.z * quat4d.z) * doubles1[1];
 this->m21 = 2.0 * (quat4d.y * quat4d.z + quat4d.w * quat4d.x) * doubles1[1];
 this->m02 = 2.0 * (quat4d.x * quat4d.z + quat4d.w * quat4d.y) * doubles1[2];
 this->m12 = 2.0 * (quat4d.y * quat4d.z - quat4d.w * quat4d.x) * doubles1[2];
 this->m22 = (1.0 - 2.0 * quat4d.x * quat4d.x - 2.0 * quat4d.y * quat4d.y) * doubles1[2];
 }

 void setRotation(AxisAngle4d axisAngle4d) {
 double[] doubles0 = new double[9];
 double[] doubles1 = new double[3];
 this->getScaleRotate(doubles1, doubles0);
 double double0 = 1.0 / Math.sqrt(axisAngle4d.x * axisAngle4d.x + axisAngle4d.y * axisAngle4d.y + axisAngle4d.z * axisAngle4d.z);
 double double1 = axisAngle4d.x * double0;
 double double2 = axisAngle4d.y * double0;
 double double3 = axisAngle4d.z * double0;
 double double4 = Math.sin(axisAngle4d.angle);
 double double5 = Math.cos(axisAngle4d.angle);
 double double6 = 1.0 - double5;
 double double7 = axisAngle4d.x * axisAngle4d.z;
 double double8 = axisAngle4d.x * axisAngle4d.y;
 double double9 = axisAngle4d.y * axisAngle4d.z;
 this->m00 = (double6 * double1 * double1 + double5) * doubles1[0];
 this->m01 = (double6 * double8 - double4 * double3) * doubles1[1];
 this->m02 = (double6 * double7 + double4 * double2) * doubles1[2];
 this->m10 = (double6 * double8 + double4 * double3) * doubles1[0];
 this->m11 = (double6 * double2 * double2 + double5) * doubles1[1];
 this->m12 = (double6 * double9 - double4 * double1) * doubles1[2];
 this->m20 = (double6 * double7 - double4 * double2) * doubles1[0];
 this->m21 = (double6 * double9 + double4 * double1) * doubles1[1];
 this->m22 = (double6 * double3 * double3 + double5) * doubles1[2];
 }

 void setZero() {
 this->m00 = 0.0;
 this->m01 = 0.0;
 this->m02 = 0.0;
 this->m03 = 0.0;
 this->m10 = 0.0;
 this->m11 = 0.0;
 this->m12 = 0.0;
 this->m13 = 0.0;
 this->m20 = 0.0;
 this->m21 = 0.0;
 this->m22 = 0.0;
 this->m23 = 0.0;
 this->m30 = 0.0;
 this->m31 = 0.0;
 this->m32 = 0.0;
 this->m33 = 0.0;
 }

 void negate() {
 this->m00 = -this->m00;
 this->m01 = -this->m01;
 this->m02 = -this->m02;
 this->m03 = -this->m03;
 this->m10 = -this->m10;
 this->m11 = -this->m11;
 this->m12 = -this->m12;
 this->m13 = -this->m13;
 this->m20 = -this->m20;
 this->m21 = -this->m21;
 this->m22 = -this->m22;
 this->m23 = -this->m23;
 this->m30 = -this->m30;
 this->m31 = -this->m31;
 this->m32 = -this->m32;
 this->m33 = -this->m33;
 }

 void negate(Matrix4d matrix4d0) {
 this->m00 = -matrix4d0.m00;
 this->m01 = -matrix4d0.m01;
 this->m02 = -matrix4d0.m02;
 this->m03 = -matrix4d0.m03;
 this->m10 = -matrix4d0.m10;
 this->m11 = -matrix4d0.m11;
 this->m12 = -matrix4d0.m12;
 this->m13 = -matrix4d0.m13;
 this->m20 = -matrix4d0.m20;
 this->m21 = -matrix4d0.m21;
 this->m22 = -matrix4d0.m22;
 this->m23 = -matrix4d0.m23;
 this->m30 = -matrix4d0.m30;
 this->m31 = -matrix4d0.m31;
 this->m32 = -matrix4d0.m32;
 this->m33 = -matrix4d0.m33;
 }

 void getScaleRotate(double[] doubles1, double[] doubles2) {
 double[] doubles0 = new double[]{this->m00, this->m01, this->m02, this->m10, this->m11, this->m12, this->m20, this->m21, this->m22};
 Matrix3d.compute_svd(doubles0, doubles1, doubles2);
 }

 void* clone() {
 void* object = nullptr;

 try {
 return (Matrix4d)super.clone();
 } catch (CloneNotSupportedException cloneNotSupportedException) {
 throw std::make_unique<InternalError>();
 }
 }

 double getM00() {
 return this->m00;
 }

 void setM00(double double0) {
 this->m00 = double0;
 }

 double getM01() {
 return this->m01;
 }

 void setM01(double double0) {
 this->m01 = double0;
 }

 double getM02() {
 return this->m02;
 }

 void setM02(double double0) {
 this->m02 = double0;
 }

 double getM10() {
 return this->m10;
 }

 void setM10(double double0) {
 this->m10 = double0;
 }

 double getM11() {
 return this->m11;
 }

 void setM11(double double0) {
 this->m11 = double0;
 }

 double getM12() {
 return this->m12;
 }

 void setM12(double double0) {
 this->m12 = double0;
 }

 double getM20() {
 return this->m20;
 }

 void setM20(double double0) {
 this->m20 = double0;
 }

 double getM21() {
 return this->m21;
 }

 void setM21(double double0) {
 this->m21 = double0;
 }

 double getM22() {
 return this->m22;
 }

 void setM22(double double0) {
 this->m22 = double0;
 }

 double getM03() {
 return this->m03;
 }

 void setM03(double double0) {
 this->m03 = double0;
 }

 double getM13() {
 return this->m13;
 }

 void setM13(double double0) {
 this->m13 = double0;
 }

 double getM23() {
 return this->m23;
 }

 void setM23(double double0) {
 this->m23 = double0;
 }

 double getM30() {
 return this->m30;
 }

 void setM30(double double0) {
 this->m30 = double0;
 }

 double getM31() {
 return this->m31;
 }

 void setM31(double double0) {
 this->m31 = double0;
 }

 double getM32() {
 return this->m32;
 }

 void setM32(double double0) {
 this->m32 = double0;
 }

 double getM33() {
 return this->m33;
 }

 void setM33(double double0) {
 this->m33 = double0;
 }
}
} // namespace vecmath
} // namespace javax
