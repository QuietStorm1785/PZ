#pragma once
#include "java/text/NumberFormat.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Vector3f {
public:
  static const long serialVersionUID = 1L;
  float x;
  float y;
  float z;

public
  Vector3f() {}

public
  Vector3f(float arg0) {
    this.x = arg0;
    this.y = arg0;
    this.z = arg0;
  }

public
  Vector3f(float arg0, float arg1, float arg2) {
    this.x = arg0;
    this.y = arg1;
    this.z = arg2;
  }

public
  Vector3f(Vector3fc arg0) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg0.z();
  }

public
  Vector3f(Vector3ic arg0) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg0.z();
  }

public
  Vector3f(Vector2fc arg0, float arg1) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg1;
  }

public
  Vector3f(Vector2ic arg0, float arg1) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg1;
  }

public
  Vector3f(float[] arg0) {
    this.x = arg0[0];
    this.y = arg0[1];
    this.z = arg0[2];
  }

public
  Vector3f(ByteBuffer arg0) {
    MemUtil.INSTANCE.get(this, arg0.position(), arg0);
  }

public
  Vector3f(int arg0, ByteBuffer arg1) {
    MemUtil.INSTANCE.get(this, arg0, arg1);
  }

public
  Vector3f(FloatBuffer arg0) {
    MemUtil.INSTANCE.get(this, arg0.position(), arg0);
  }

public
  Vector3f(int arg0, FloatBuffer arg1) {
    MemUtil.INSTANCE.get(this, arg0, arg1);
  }

  float x() { return this.x; }

  float y() { return this.y; }

  float z() { return this.z; }

  Vector3f set(Vector3fc arg0) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg0.z();
    return this;
  }

  Vector3f set(Vector3dc arg0) {
    this.x = (float)arg0.x();
    this.y = (float)arg0.y();
    this.z = (float)arg0.z();
    return this;
  }

  Vector3f set(Vector3ic arg0) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg0.z();
    return this;
  }

  Vector3f set(Vector2fc arg0, float arg1) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg1;
    return this;
  }

  Vector3f set(Vector2dc arg0, float arg1) {
    this.x = (float)arg0.x();
    this.y = (float)arg0.y();
    this.z = arg1;
    return this;
  }

  Vector3f set(Vector2ic arg0, float arg1) {
    this.x = arg0.x();
    this.y = arg0.y();
    this.z = arg1;
    return this;
  }

  Vector3f set(float arg0) {
    this.x = arg0;
    this.y = arg0;
    this.z = arg0;
    return this;
  }

  Vector3f set(float arg0, float arg1, float arg2) {
    this.x = arg0;
    this.y = arg1;
    this.z = arg2;
    return this;
  }

  Vector3f set(double arg0) {
    this.x = (float)arg0;
    this.y = (float)arg0;
    this.z = (float)arg0;
    return this;
  }

  Vector3f set(double arg0, double arg1, double arg2) {
    this.x = (float)arg0;
    this.y = (float)arg1;
    this.z = (float)arg2;
    return this;
  }

  Vector3f set(float[] arg0) {
    this.x = arg0[0];
    this.y = arg0[1];
    this.z = arg0[2];
    return this;
  }

  Vector3f set(ByteBuffer arg0) {
    MemUtil.INSTANCE.get(this, arg0.position(), arg0);
    return this;
  }

  Vector3f set(int arg0, ByteBuffer arg1) {
    MemUtil.INSTANCE.get(this, arg0, arg1);
    return this;
  }

  Vector3f set(FloatBuffer arg0) {
    MemUtil.INSTANCE.get(this, arg0.position(), arg0);
    return this;
  }

  Vector3f set(int arg0, FloatBuffer arg1) {
    MemUtil.INSTANCE.get(this, arg0, arg1);
    return this;
  }

  Vector3f setFromAddress(long arg0) {
    if (Options.NO_UNSAFE) {
      throw new UnsupportedOperationException(
          "Not supported when using joml.nounsafe");
    } else {
      MemUtil.MemUtilUnsafe.get(this, arg0);
      return this;
    }
  }

  Vector3f setComponent(int arg0, float arg1) {
    switch (arg0) {
    case 0:
      this.x = arg1;
      break;
    case 1:
      this.y = arg1;
      break;
    case 2:
      this.z = arg1;
      break;
    default:
      throw std::make_unique<IllegalArgumentException>();
    }

    return this;
  }

  FloatBuffer get(FloatBuffer arg0) {
    MemUtil.INSTANCE.put(this, arg0.position(), arg0);
    return arg0;
  }

  FloatBuffer get(int arg0, FloatBuffer arg1) {
    MemUtil.INSTANCE.put(this, arg0, arg1);
    return arg1;
  }

  ByteBuffer get(ByteBuffer arg0) {
    MemUtil.INSTANCE.put(this, arg0.position(), arg0);
    return arg0;
  }

  ByteBuffer get(int arg0, ByteBuffer arg1) {
    MemUtil.INSTANCE.put(this, arg0, arg1);
    return arg1;
  }

  Vector3fc getToAddress(long arg0) {
    if (Options.NO_UNSAFE) {
      throw new UnsupportedOperationException(
          "Not supported when using joml.nounsafe");
    } else {
      MemUtil.MemUtilUnsafe.put(this, arg0);
      return this;
    }
  }

  Vector3f sub(Vector3fc arg0) {
    this.x = this.x - arg0.x();
    this.y = this.y - arg0.y();
    this.z = this.z - arg0.z();
    return this;
  }

  Vector3f sub(Vector3fc arg0, Vector3f arg1) {
    arg1.x = this.x - arg0.x();
    arg1.y = this.y - arg0.y();
    arg1.z = this.z - arg0.z();
    return arg1;
  }

  Vector3f sub(float arg0, float arg1, float arg2) {
    this.x -= arg0;
    this.y -= arg1;
    this.z -= arg2;
    return this;
  }

  Vector3f sub(float arg0, float arg1, float arg2, Vector3f arg3) {
    arg3.x = this.x - arg0;
    arg3.y = this.y - arg1;
    arg3.z = this.z - arg2;
    return arg3;
  }

  Vector3f add(Vector3fc arg0) {
    this.x = this.x + arg0.x();
    this.y = this.y + arg0.y();
    this.z = this.z + arg0.z();
    return this;
  }

  Vector3f add(Vector3fc arg0, Vector3f arg1) {
    arg1.x = this.x + arg0.x();
    arg1.y = this.y + arg0.y();
    arg1.z = this.z + arg0.z();
    return arg1;
  }

  Vector3f add(float arg0, float arg1, float arg2) {
    this.x += arg0;
    this.y += arg1;
    this.z += arg2;
    return this;
  }

  Vector3f add(float arg0, float arg1, float arg2, Vector3f arg3) {
    arg3.x = this.x + arg0;
    arg3.y = this.y + arg1;
    arg3.z = this.z + arg2;
    return arg3;
  }

  Vector3f fma(Vector3fc arg0, Vector3fc arg1) {
    this.x = Math.fma(arg0.x(), arg1.x(), this.x);
    this.y = Math.fma(arg0.y(), arg1.y(), this.y);
    this.z = Math.fma(arg0.z(), arg1.z(), this.z);
    return this;
  }

  Vector3f fma(float arg0, Vector3fc arg1) {
    this.x = Math.fma(arg0, arg1.x(), this.x);
    this.y = Math.fma(arg0, arg1.y(), this.y);
    this.z = Math.fma(arg0, arg1.z(), this.z);
    return this;
  }

  Vector3f fma(Vector3fc arg0, Vector3fc arg1, Vector3f arg2) {
    arg2.x = Math.fma(arg0.x(), arg1.x(), this.x);
    arg2.y = Math.fma(arg0.y(), arg1.y(), this.y);
    arg2.z = Math.fma(arg0.z(), arg1.z(), this.z);
    return arg2;
  }

  Vector3f fma(float arg0, Vector3fc arg1, Vector3f arg2) {
    arg2.x = Math.fma(arg0, arg1.x(), this.x);
    arg2.y = Math.fma(arg0, arg1.y(), this.y);
    arg2.z = Math.fma(arg0, arg1.z(), this.z);
    return arg2;
  }

  Vector3f mulAdd(Vector3fc arg0, Vector3fc arg1) {
    this.x = Math.fma(this.x, arg0.x(), arg1.x());
    this.y = Math.fma(this.y, arg0.y(), arg1.y());
    this.z = Math.fma(this.z, arg0.z(), arg1.z());
    return this;
  }

  Vector3f mulAdd(float arg0, Vector3fc arg1) {
    this.x = Math.fma(this.x, arg0, arg1.x());
    this.y = Math.fma(this.y, arg0, arg1.y());
    this.z = Math.fma(this.z, arg0, arg1.z());
    return this;
  }

  Vector3f mulAdd(Vector3fc arg0, Vector3fc arg1, Vector3f arg2) {
    arg2.x = Math.fma(this.x, arg0.x(), arg1.x());
    arg2.y = Math.fma(this.y, arg0.y(), arg1.y());
    arg2.z = Math.fma(this.z, arg0.z(), arg1.z());
    return arg2;
  }

  Vector3f mulAdd(float arg0, Vector3fc arg1, Vector3f arg2) {
    arg2.x = Math.fma(this.x, arg0, arg1.x());
    arg2.y = Math.fma(this.y, arg0, arg1.y());
    arg2.z = Math.fma(this.z, arg0, arg1.z());
    return arg2;
  }

  Vector3f mul(Vector3fc arg0) {
    this.x = this.x * arg0.x();
    this.y = this.y * arg0.y();
    this.z = this.z * arg0.z();
    return this;
  }

  Vector3f mul(Vector3fc arg0, Vector3f arg1) {
    arg1.x = this.x * arg0.x();
    arg1.y = this.y * arg0.y();
    arg1.z = this.z * arg0.z();
    return arg1;
  }

  Vector3f div(Vector3fc arg0) {
    this.x = this.x / arg0.x();
    this.y = this.y / arg0.y();
    this.z = this.z / arg0.z();
    return this;
  }

  Vector3f div(Vector3fc arg0, Vector3f arg1) {
    arg1.x = this.x / arg0.x();
    arg1.y = this.y / arg0.y();
    arg1.z = this.z / arg0.z();
    return arg1;
  }

  Vector3f mulProject(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 =
        1.0F / Math.fma(arg0.m03(), float0,
                        Math.fma(arg0.m13(), float1,
                                 Math.fma(arg0.m23(), float2, arg0.m33())));
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1,
                               Math.fma(arg0.m20(), float2, arg0.m30()))) *
             float3;
    arg1.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1,
                               Math.fma(arg0.m21(), float2, arg0.m31()))) *
             float3;
    arg1.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1,
                               Math.fma(arg0.m22(), float2, arg0.m32()))) *
             float3;
    return arg1;
  }

  Vector3f mulProject(Matrix4fc arg0, float arg1, Vector3f arg2) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 =
        1.0F /
        Math.fma(arg0.m03(), float0,
                 Math.fma(arg0.m13(), float1,
                          Math.fma(arg0.m23(), float2, arg0.m33() * arg1)));
    arg2.x =
        Math.fma(arg0.m00(), float0,
                 Math.fma(arg0.m10(), float1,
                          Math.fma(arg0.m20(), float2, arg0.m30() * arg1))) *
        float3;
    arg2.y =
        Math.fma(arg0.m01(), float0,
                 Math.fma(arg0.m11(), float1,
                          Math.fma(arg0.m21(), float2, arg0.m31() * arg1))) *
        float3;
    arg2.z =
        Math.fma(arg0.m02(), float0,
                 Math.fma(arg0.m12(), float1,
                          Math.fma(arg0.m22(), float2, arg0.m32() * arg1))) *
        float3;
    return arg2;
  }

  Vector3f mulProject(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 =
        1.0F / Math.fma(arg0.m03(), float0,
                        Math.fma(arg0.m13(), float1,
                                 Math.fma(arg0.m23(), float2, arg0.m33())));
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1,
                               Math.fma(arg0.m20(), float2, arg0.m30()))) *
             float3;
    this.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1,
                               Math.fma(arg0.m21(), float2, arg0.m31()))) *
             float3;
    this.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1,
                               Math.fma(arg0.m22(), float2, arg0.m32()))) *
             float3;
    return this;
  }

  Vector3f mul(Matrix3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    this.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    this.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mul(Matrix3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    arg1.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    arg1.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mul(Matrix3dc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = (float)Math.fma(
        arg0.m00(), (double)float0,
        Math.fma(arg0.m10(), (double)float1, arg0.m20() * float2));
    this.y = (float)Math.fma(
        arg0.m01(), (double)float0,
        Math.fma(arg0.m11(), (double)float1, arg0.m21() * float2));
    this.z = (float)Math.fma(
        arg0.m02(), (double)float0,
        Math.fma(arg0.m12(), (double)float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mul(Matrix3dc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = (float)Math.fma(
        arg0.m00(), (double)float0,
        Math.fma(arg0.m10(), (double)float1, arg0.m20() * float2));
    arg1.y = (float)Math.fma(
        arg0.m01(), (double)float0,
        Math.fma(arg0.m11(), (double)float1, arg0.m21() * float2));
    arg1.z = (float)Math.fma(
        arg0.m02(), (double)float0,
        Math.fma(arg0.m12(), (double)float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mul(Matrix3x2fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    this.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    this.z = float2;
    return this;
  }

  Vector3f mul(Matrix3x2fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    arg1.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    arg1.z = float2;
    return arg1;
  }

  Vector3f mulTranspose(Matrix3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m01(), float1, arg0.m02() * float2));
    this.y = Math.fma(arg0.m10(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m12() * float2));
    this.z = Math.fma(arg0.m20(), float0,
                      Math.fma(arg0.m21(), float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mulTranspose(Matrix3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m01(), float1, arg0.m02() * float2));
    arg1.y = Math.fma(arg0.m10(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m12() * float2));
    arg1.z = Math.fma(arg0.m20(), float0,
                      Math.fma(arg0.m21(), float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mulPosition(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    this.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    this.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return this;
  }

  Vector3f mulPosition(Matrix4x3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    this.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    this.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return this;
  }

  Vector3f mulPosition(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    arg1.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    arg1.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return arg1;
  }

  Vector3f mulPosition(Matrix4x3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    arg1.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    arg1.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return arg1;
  }

  Vector3f mulTransposePosition(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m01(), float1, Math.fma(arg0.m02(), float2, arg0.m03())));
    this.y = Math.fma(
        arg0.m10(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m12(), float2, arg0.m13())));
    this.z = Math.fma(
        arg0.m20(), float0,
        Math.fma(arg0.m21(), float1, Math.fma(arg0.m22(), float2, arg0.m23())));
    return this;
  }

  Vector3f mulTransposePosition(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m01(), float1, Math.fma(arg0.m02(), float2, arg0.m03())));
    arg1.y = Math.fma(
        arg0.m10(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m12(), float2, arg0.m13())));
    arg1.z = Math.fma(
        arg0.m20(), float0,
        Math.fma(arg0.m21(), float1, Math.fma(arg0.m22(), float2, arg0.m23())));
    return arg1;
  }

  float mulPositionW(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 = Math.fma(
        arg0.m03(), float0,
        Math.fma(arg0.m13(), float1, Math.fma(arg0.m23(), float2, arg0.m33())));
    this.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    this.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    this.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return float3;
  }

  float mulPositionW(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 = Math.fma(
        arg0.m03(), float0,
        Math.fma(arg0.m13(), float1, Math.fma(arg0.m23(), float2, arg0.m33())));
    arg1.x = Math.fma(
        arg0.m00(), float0,
        Math.fma(arg0.m10(), float1, Math.fma(arg0.m20(), float2, arg0.m30())));
    arg1.y = Math.fma(
        arg0.m01(), float0,
        Math.fma(arg0.m11(), float1, Math.fma(arg0.m21(), float2, arg0.m31())));
    arg1.z = Math.fma(
        arg0.m02(), float0,
        Math.fma(arg0.m12(), float1, Math.fma(arg0.m22(), float2, arg0.m32())));
    return float3;
  }

  Vector3f mulDirection(Matrix4dc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = (float)Math.fma(
        arg0.m00(), (double)float0,
        Math.fma(arg0.m10(), (double)float1, arg0.m20() * float2));
    this.y = (float)Math.fma(
        arg0.m01(), (double)float0,
        Math.fma(arg0.m11(), (double)float1, arg0.m21() * float2));
    this.z = (float)Math.fma(
        arg0.m02(), (double)float0,
        Math.fma(arg0.m12(), (double)float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mulDirection(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    this.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    this.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mulDirection(Matrix4x3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    this.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    this.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mulDirection(Matrix4dc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = (float)Math.fma(
        arg0.m00(), (double)float0,
        Math.fma(arg0.m10(), (double)float1, arg0.m20() * float2));
    arg1.y = (float)Math.fma(
        arg0.m01(), (double)float0,
        Math.fma(arg0.m11(), (double)float1, arg0.m21() * float2));
    arg1.z = (float)Math.fma(
        arg0.m02(), (double)float0,
        Math.fma(arg0.m12(), (double)float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mulDirection(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    arg1.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    arg1.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mulDirection(Matrix4x3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m10(), float1, arg0.m20() * float2));
    arg1.y = Math.fma(arg0.m01(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m21() * float2));
    arg1.z = Math.fma(arg0.m02(), float0,
                      Math.fma(arg0.m12(), float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mulTransposeDirection(Matrix4fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m01(), float1, arg0.m02() * float2));
    this.y = Math.fma(arg0.m10(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m12() * float2));
    this.z = Math.fma(arg0.m20(), float0,
                      Math.fma(arg0.m21(), float1, arg0.m22() * float2));
    return this;
  }

  Vector3f mulTransposeDirection(Matrix4fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = Math.fma(arg0.m00(), float0,
                      Math.fma(arg0.m01(), float1, arg0.m02() * float2));
    arg1.y = Math.fma(arg0.m10(), float0,
                      Math.fma(arg0.m11(), float1, arg0.m12() * float2));
    arg1.z = Math.fma(arg0.m20(), float0,
                      Math.fma(arg0.m21(), float1, arg0.m22() * float2));
    return arg1;
  }

  Vector3f mul(float arg0) {
    this.x *= arg0;
    this.y *= arg0;
    this.z *= arg0;
    return this;
  }

  Vector3f mul(float arg0, Vector3f arg1) {
    arg1.x = this.x * arg0;
    arg1.y = this.y * arg0;
    arg1.z = this.z * arg0;
    return arg1;
  }

  Vector3f mul(float arg0, float arg1, float arg2) {
    this.x *= arg0;
    this.y *= arg1;
    this.z *= arg2;
    return this;
  }

  Vector3f mul(float arg0, float arg1, float arg2, Vector3f arg3) {
    arg3.x = this.x * arg0;
    arg3.y = this.y * arg1;
    arg3.z = this.z * arg2;
    return arg3;
  }

  Vector3f div(float arg0) {
    float float0 = 1.0F / arg0;
    this.x *= float0;
    this.y *= float0;
    this.z *= float0;
    return this;
  }

  Vector3f div(float arg0, Vector3f arg1) {
    float float0 = 1.0F / arg0;
    arg1.x = this.x * float0;
    arg1.y = this.y * float0;
    arg1.z = this.z * float0;
    return arg1;
  }

  Vector3f div(float arg0, float arg1, float arg2) {
    this.x /= arg0;
    this.y /= arg1;
    this.z /= arg2;
    return this;
  }

  Vector3f div(float arg0, float arg1, float arg2, Vector3f arg3) {
    arg3.x = this.x / arg0;
    arg3.y = this.y / arg1;
    arg3.z = this.z / arg2;
    return arg3;
  }

  Vector3f rotate(Quaternionfc arg0) { return arg0.transform(this, this); }

  Vector3f rotate(Quaternionfc arg0, Vector3f arg1) {
    return arg0.transform(this, arg1);
  }

  Quaternionf rotationTo(Vector3fc arg0, Quaternionf arg1) {
    return arg1.rotationTo(this, arg0);
  }

  Quaternionf rotationTo(float arg0, float arg1, float arg2, Quaternionf arg3) {
    return arg3.rotationTo(this.x, this.y, this.z, arg0, arg1, arg2);
  }

  Vector3f rotateAxis(float arg0, float arg1, float arg2, float arg3) {
    if (arg2 == 0.0F && arg3 == 0.0F && Math.absEqualsOne(arg1)) {
      return this.rotateX(arg1 * arg0, this);
    } else if (arg1 == 0.0F && arg3 == 0.0F && Math.absEqualsOne(arg2)) {
      return this.rotateY(arg2 * arg0, this);
    } else {
      return arg1 == 0.0F && arg2 == 0.0F && Math.absEqualsOne(arg3)
                 ? this.rotateZ(arg3 * arg0, this)
                 : this.rotateAxisInternal(arg0, arg1, arg2, arg3, this);
    }
  }

  Vector3f rotateAxis(float arg0, float arg1, float arg2, float arg3,
                      Vector3f arg4) {
    if (arg2 == 0.0F && arg3 == 0.0F && Math.absEqualsOne(arg1)) {
      return this.rotateX(arg1 * arg0, arg4);
    } else if (arg1 == 0.0F && arg3 == 0.0F && Math.absEqualsOne(arg2)) {
      return this.rotateY(arg2 * arg0, arg4);
    } else {
      return arg1 == 0.0F && arg2 == 0.0F && Math.absEqualsOne(arg3)
                 ? this.rotateZ(arg3 * arg0, arg4)
                 : this.rotateAxisInternal(arg0, arg1, arg2, arg3, arg4);
    }
  }

  Vector3f rotateAxisInternal(float float1, float float4, float float6,
                              float float8, Vector3f vector3f1) {
    float float0 = float1 * 0.5F;
    float float2 = Math.sin(float0);
    float float3 = float4 * float2;
    float float5 = float6 * float2;
    float float7 = float8 * float2;
    float float9 = Math.cosFromSin(float2, float0);
    float float10 = float9 * float9;
    float float11 = float3 * float3;
    float float12 = float5 * float5;
    float float13 = float7 * float7;
    float float14 = float7 * float9;
    float float15 = float3 * float5;
    float float16 = float3 * float7;
    float float17 = float5 * float9;
    float float18 = float5 * float7;
    float float19 = float3 * float9;
    float float20 = this.x;
    float float21 = this.y;
    float float22 = this.z;
    vector3f1.x = (float10 + float11 - float13 - float12) * float20 +
                  (-float14 + float15 - float14 + float15) * float21 +
                  (float17 + float16 + float16 + float17) * float22;
    vector3f1.y = (float15 + float14 + float14 + float15) * float20 +
                  (float12 - float13 + float10 - float11) * float21 +
                  (float18 + float18 - float19 - float19) * float22;
    vector3f1.z = (float16 - float17 + float16 - float17) * float20 +
                  (float18 + float18 + float19 + float19) * float21 +
                  (float13 - float12 - float11 + float10) * float22;
    return vector3f1;
  }

  Vector3f rotateX(float arg0) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.y * float1 - this.z * float0;
    float float3 = this.y * float0 + this.z * float1;
    this.y = float2;
    this.z = float3;
    return this;
  }

  Vector3f rotateX(float arg0, Vector3f arg1) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.y * float1 - this.z * float0;
    float float3 = this.y * float0 + this.z * float1;
    arg1.x = this.x;
    arg1.y = float2;
    arg1.z = float3;
    return arg1;
  }

  Vector3f rotateY(float arg0) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.x * float1 + this.z * float0;
    float float3 = -this.x * float0 + this.z * float1;
    this.x = float2;
    this.z = float3;
    return this;
  }

  Vector3f rotateY(float arg0, Vector3f arg1) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.x * float1 + this.z * float0;
    float float3 = -this.x * float0 + this.z * float1;
    arg1.x = float2;
    arg1.y = this.y;
    arg1.z = float3;
    return arg1;
  }

  Vector3f rotateZ(float arg0) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.x * float1 - this.y * float0;
    float float3 = this.x * float0 + this.y * float1;
    this.x = float2;
    this.y = float3;
    return this;
  }

  Vector3f rotateZ(float arg0, Vector3f arg1) {
    float float0 = Math.sin(arg0);
    float float1 = Math.cosFromSin(float0, arg0);
    float float2 = this.x * float1 - this.y * float0;
    float float3 = this.x * float0 + this.y * float1;
    arg1.x = float2;
    arg1.y = float3;
    arg1.z = this.z;
    return arg1;
  }

  float lengthSquared() {
    return Math.fma(this.x, this.x, Math.fma(this.y, this.y, this.z * this.z));
  }

  static float lengthSquared(float arg0, float arg1, float arg2) {
    return Math.fma(arg0, arg0, Math.fma(arg1, arg1, arg2 * arg2));
  }

  float length() {
    return Math.sqrt(
        Math.fma(this.x, this.x, Math.fma(this.y, this.y, this.z * this.z)));
  }

  static float length(float arg0, float arg1, float arg2) {
    return Math.sqrt(Math.fma(arg0, arg0, Math.fma(arg1, arg1, arg2 * arg2)));
  }

  Vector3f normalize() {
    float float0 = Math.invsqrt(
        Math.fma(this.x, this.x, Math.fma(this.y, this.y, this.z * this.z)));
    this.x *= float0;
    this.y *= float0;
    this.z *= float0;
    return this;
  }

  Vector3f normalize(Vector3f arg0) {
    float float0 = Math.invsqrt(
        Math.fma(this.x, this.x, Math.fma(this.y, this.y, this.z * this.z)));
    arg0.x = this.x * float0;
    arg0.y = this.y * float0;
    arg0.z = this.z * float0;
    return arg0;
  }

  Vector3f normalize(float arg0) {
    float float0 =
        Math.invsqrt(Math.fma(this.x, this.x,
                              Math.fma(this.y, this.y, this.z * this.z))) *
        arg0;
    this.x *= float0;
    this.y *= float0;
    this.z *= float0;
    return this;
  }

  Vector3f normalize(float arg0, Vector3f arg1) {
    float float0 =
        Math.invsqrt(Math.fma(this.x, this.x,
                              Math.fma(this.y, this.y, this.z * this.z))) *
        arg0;
    arg1.x = this.x * float0;
    arg1.y = this.y * float0;
    arg1.z = this.z * float0;
    return arg1;
  }

  Vector3f cross(Vector3fc arg0) {
    float float0 = Math.fma(this.y, arg0.z(), -this.z * arg0.y());
    float float1 = Math.fma(this.z, arg0.x(), -this.x * arg0.z());
    float float2 = Math.fma(this.x, arg0.y(), -this.y * arg0.x());
    this.x = float0;
    this.y = float1;
    this.z = float2;
    return this;
  }

  Vector3f cross(float arg0, float arg1, float arg2) {
    float float0 = Math.fma(this.y, arg2, -this.z * arg1);
    float float1 = Math.fma(this.z, arg0, -this.x * arg2);
    float float2 = Math.fma(this.x, arg1, -this.y * arg0);
    this.x = float0;
    this.y = float1;
    this.z = float2;
    return this;
  }

  Vector3f cross(Vector3fc arg0, Vector3f arg1) {
    float float0 = Math.fma(this.y, arg0.z(), -this.z * arg0.y());
    float float1 = Math.fma(this.z, arg0.x(), -this.x * arg0.z());
    float float2 = Math.fma(this.x, arg0.y(), -this.y * arg0.x());
    arg1.x = float0;
    arg1.y = float1;
    arg1.z = float2;
    return arg1;
  }

  Vector3f cross(float arg0, float arg1, float arg2, Vector3f arg3) {
    float float0 = Math.fma(this.y, arg2, -this.z * arg1);
    float float1 = Math.fma(this.z, arg0, -this.x * arg2);
    float float2 = Math.fma(this.x, arg1, -this.y * arg0);
    arg3.x = float0;
    arg3.y = float1;
    arg3.z = float2;
    return arg3;
  }

  float distance(Vector3fc arg0) {
    float float0 = this.x - arg0.x();
    float float1 = this.y - arg0.y();
    float float2 = this.z - arg0.z();
    return Math.sqrt(
        Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2)));
  }

  float distance(float arg0, float arg1, float arg2) {
    float float0 = this.x - arg0;
    float float1 = this.y - arg1;
    float float2 = this.z - arg2;
    return Math.sqrt(
        Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2)));
  }

  float distanceSquared(Vector3fc arg0) {
    float float0 = this.x - arg0.x();
    float float1 = this.y - arg0.y();
    float float2 = this.z - arg0.z();
    return Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2));
  }

  float distanceSquared(float arg0, float arg1, float arg2) {
    float float0 = this.x - arg0;
    float float1 = this.y - arg1;
    float float2 = this.z - arg2;
    return Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2));
  }

  static float distance(float arg0, float arg1, float arg2, float arg3,
                        float arg4, float arg5) {
    return Math.sqrt(distanceSquared(arg0, arg1, arg2, arg3, arg4, arg5));
  }

  static float distanceSquared(float arg0, float arg1, float arg2, float arg3,
                               float arg4, float arg5) {
    float float0 = arg0 - arg3;
    float float1 = arg1 - arg4;
    float float2 = arg2 - arg5;
    return Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2));
  }

  float dot(Vector3fc arg0) {
    return Math.fma(this.x, arg0.x(),
                    Math.fma(this.y, arg0.y(), this.z * arg0.z()));
  }

  float dot(float arg0, float arg1, float arg2) {
    return Math.fma(this.x, arg0, Math.fma(this.y, arg1, this.z * arg2));
  }

  float angleCos(Vector3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 =
        Math.fma(float0, float0, Math.fma(float1, float1, float2 * float2));
    float float4 = Math.fma(arg0.x(), arg0.x(),
                            Math.fma(arg0.y(), arg0.y(), arg0.z() * arg0.z()));
    float float5 = Math.fma(float0, arg0.x(),
                            Math.fma(float1, arg0.y(), float2 * arg0.z()));
    return float5 / Math.sqrt(float3 * float4);
  }

  float angle(Vector3fc arg0) {
    float float0 = this.angleCos(arg0);
    float0 = float0 < 1.0F ? float0 : 1.0F;
    float0 = float0 > -1.0F ? float0 : -1.0F;
    return Math.acos(float0);
  }

  float angleSigned(Vector3fc arg0, Vector3fc arg1) {
    return this.angleSigned(arg0.x(), arg0.y(), arg0.z(), arg1.x(), arg1.y(),
                            arg1.z());
  }

  float angleSigned(float arg0, float arg1, float arg2, float arg3, float arg4,
                    float arg5) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    return Math.atan2((float1 * arg2 - float2 * arg1) * arg3 +
                          (float2 * arg0 - float0 * arg2) * arg4 +
                          (float0 * arg1 - float1 * arg0) * arg5,
                      float0 * arg0 + float1 * arg1 + float2 * arg2);
  }

  Vector3f min(Vector3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = float0 < arg0.x() ? float0 : arg0.x();
    this.y = float1 < arg0.y() ? float1 : arg0.y();
    this.z = float2 < arg0.z() ? float2 : arg0.z();
    return this;
  }

  Vector3f min(Vector3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = float0 < arg0.x() ? float0 : arg0.x();
    arg1.y = float1 < arg0.y() ? float1 : arg0.y();
    arg1.z = float2 < arg0.z() ? float2 : arg0.z();
    return arg1;
  }

  Vector3f max(Vector3fc arg0) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    this.x = float0 > arg0.x() ? float0 : arg0.x();
    this.y = float1 > arg0.y() ? float1 : arg0.y();
    this.z = float2 > arg0.z() ? float2 : arg0.z();
    return this;
  }

  Vector3f max(Vector3fc arg0, Vector3f arg1) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    arg1.x = float0 > arg0.x() ? float0 : arg0.x();
    arg1.y = float1 > arg0.y() ? float1 : arg0.y();
    arg1.z = float2 > arg0.z() ? float2 : arg0.z();
    return arg1;
  }

  Vector3f zero() {
    this.x = 0.0F;
    this.y = 0.0F;
    this.z = 0.0F;
    return this;
  }

  std::string toString() {
    return Runtime.formatNumbers(this.toString(Options.NUMBER_FORMAT));
  }

  std::string toString(NumberFormat numberFormat) {
    return "(" + Runtime.format(this.x, numberFormat) + " " +
           Runtime.format(this.y, numberFormat) + " " +
           Runtime.format(this.z, numberFormat) + ")";
  }

  void writeExternal(ObjectOutput arg0) {
    arg0.writeFloat(this.x);
    arg0.writeFloat(this.y);
    arg0.writeFloat(this.z);
  }

  void readExternal(ObjectInput arg0) {
    this.set(arg0.readFloat(), arg0.readFloat(), arg0.readFloat());
  }

  Vector3f negate() {
    this.x = -this.x;
    this.y = -this.y;
    this.z = -this.z;
    return this;
  }

  Vector3f negate(Vector3f arg0) {
    arg0.x = -this.x;
    arg0.y = -this.y;
    arg0.z = -this.z;
    return arg0;
  }

  Vector3f absolute() {
    this.x = Math.abs(this.x);
    this.y = Math.abs(this.y);
    this.z = Math.abs(this.z);
    return this;
  }

  Vector3f absolute(Vector3f arg0) {
    arg0.x = Math.abs(this.x);
    arg0.y = Math.abs(this.y);
    arg0.z = Math.abs(this.z);
    return arg0;
  }

  int hashCode() {
    int int0 = 1;
    int0 = 31 * int0 + Float.floatToIntBits(this.x);
    int0 = 31 * int0 + Float.floatToIntBits(this.y);
    return 31 * int0 + Float.floatToIntBits(this.z);
  }

  bool equals(void *arg0) {
    if (this == arg0) {
      return true;
    } else if (arg0 == nullptr) {
      return false;
    } else if (this.getClass() != arg0.getClass()) {
      return false;
    } else {
      Vector3f vector3f = (Vector3f)arg0;
      if (Float.floatToIntBits(this.x) != Float.floatToIntBits(vector3f.x)) {
        return false;
      } else {
        return Float.floatToIntBits(this.y) != Float.floatToIntBits(vector3f.y)
                   ? false
                   : Float.floatToIntBits(this.z) ==
                         Float.floatToIntBits(vector3f.z);
      }
    }
  }

  bool equals(Vector3fc arg0, float arg1) {
    if (this == arg0) {
      return true;
    } else if (arg0 == nullptr) {
      return false;
    } else if (!(arg0 instanceof Vector3fc)) {
      return false;
    } else if (!Runtime == this.x, arg0.x(), arg1)) {
    return false;
        }
    else {
            return !Runtime == this.y, arg0.y(), arg1) ? false : Runtime == this.z, arg0.z(), arg1);
    }
  }

  bool equals(float arg0, float arg1, float arg2) {
    if (Float.floatToIntBits(this.x) != Float.floatToIntBits(arg0)) {
      return false;
    } else {
      return Float.floatToIntBits(this.y) != Float.floatToIntBits(arg1)
                 ? false
                 : Float.floatToIntBits(this.z) == Float.floatToIntBits(arg2);
    }
  }

  Vector3f reflect(Vector3fc arg0) {
    float float0 = arg0.x();
    float float1 = arg0.y();
    float float2 = arg0.z();
    float float3 =
        Math.fma(this.x, float0, Math.fma(this.y, float1, this.z * float2));
    this.x -= (float3 + float3) * float0;
    this.y -= (float3 + float3) * float1;
    this.z -= (float3 + float3) * float2;
    return this;
  }

  Vector3f reflect(float arg0, float arg1, float arg2) {
    float float0 =
        Math.fma(this.x, arg0, Math.fma(this.y, arg1, this.z * arg2));
    this.x -= (float0 + float0) * arg0;
    this.y -= (float0 + float0) * arg1;
    this.z -= (float0 + float0) * arg2;
    return this;
  }

  Vector3f reflect(Vector3fc arg0, Vector3f arg1) {
    return this.reflect(arg0.x(), arg0.y(), arg0.z(), arg1);
  }

  Vector3f reflect(float arg0, float arg1, float arg2, Vector3f arg3) {
    float float0 = this.dot(arg0, arg1, arg2);
    arg3.x = this.x - (float0 + float0) * arg0;
    arg3.y = this.y - (float0 + float0) * arg1;
    arg3.z = this.z - (float0 + float0) * arg2;
    return arg3;
  }

  Vector3f half(Vector3fc arg0) {
    return this.set(this).add(arg0.x(), arg0.y(), arg0.z()).normalize();
  }

  Vector3f half(float arg0, float arg1, float arg2) {
    return this.half(arg0, arg1, arg2, this);
  }

  Vector3f half(Vector3fc arg0, Vector3f arg1) {
    return this.half(arg0.x(), arg0.y(), arg0.z(), arg1);
  }

  Vector3f half(float arg0, float arg1, float arg2, Vector3f arg3) {
    return arg3.set(this).add(arg0, arg1, arg2).normalize();
  }

  Vector3f smoothStep(Vector3fc arg0, float arg1, Vector3f arg2) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 = arg1 * arg1;
    float float4 = float3 * arg1;
    arg2.x = (float0 + float0 - arg0.x() - arg0.x()) * float4 +
             (3.0F * arg0.x() - 3.0F * float0) * float3 + float0 * arg1 +
             float0;
    arg2.y = (float1 + float1 - arg0.y() - arg0.y()) * float4 +
             (3.0F * arg0.y() - 3.0F * float1) * float3 + float1 * arg1 +
             float1;
    arg2.z = (float2 + float2 - arg0.z() - arg0.z()) * float4 +
             (3.0F * arg0.z() - 3.0F * float2) * float3 + float2 * arg1 +
             float2;
    return arg2;
  }

  Vector3f hermite(Vector3fc arg0, Vector3fc arg1, Vector3fc arg2, float arg3,
                   Vector3f arg4) {
    float float0 = this.x;
    float float1 = this.y;
    float float2 = this.z;
    float float3 = arg3 * arg3;
    float float4 = float3 * arg3;
    arg4.x =
        (float0 + float0 - arg1.x() - arg1.x() + arg2.x() + arg0.x()) * float4 +
        (3.0F * arg1.x() - 3.0F * float0 - arg0.x() - arg0.x() - arg2.x()) *
            float3 +
        float0 * arg3 + float0;
    arg4.y =
        (float1 + float1 - arg1.y() - arg1.y() + arg2.y() + arg0.y()) * float4 +
        (3.0F * arg1.y() - 3.0F * float1 - arg0.y() - arg0.y() - arg2.y()) *
            float3 +
        float1 * arg3 + float1;
    arg4.z =
        (float2 + float2 - arg1.z() - arg1.z() + arg2.z() + arg0.z()) * float4 +
        (3.0F * arg1.z() - 3.0F * float2 - arg0.z() - arg0.z() - arg2.z()) *
            float3 +
        float2 * arg3 + float2;
    return arg4;
  }

  Vector3f lerp(Vector3fc arg0, float arg1) {
    return this.lerp(arg0, arg1, this);
  }

  Vector3f lerp(Vector3fc arg0, float arg1, Vector3f arg2) {
    arg2.x = Math.fma(arg0.x() - this.x, arg1, this.x);
    arg2.y = Math.fma(arg0.y() - this.y, arg1, this.y);
    arg2.z = Math.fma(arg0.z() - this.z, arg1, this.z);
    return arg2;
  }

  float get(int arg0) {
    switch (arg0) {
    case 0:
      return this.x;
    case 1:
      return this.y;
    case 2:
      return this.z;
    default:
      throw std::make_unique<IllegalArgumentException>();
    }
  }

  Vector3i get(int arg0, Vector3i arg1) {
    arg1.x = Math.roundUsing(this.x(), arg0);
    arg1.y = Math.roundUsing(this.y(), arg0);
    arg1.z = Math.roundUsing(this.z(), arg0);
    return arg1;
  }

  Vector3f get(Vector3f arg0) {
    arg0.x = this.x();
    arg0.y = this.y();
    arg0.z = this.z();
    return arg0;
  }

  Vector3d get(Vector3d arg0) {
    arg0.x = this.x();
    arg0.y = this.y();
    arg0.z = this.z();
    return arg0;
  }

  int maxComponent() {
    float float0 = Math.abs(this.x);
    float float1 = Math.abs(this.y);
    float float2 = Math.abs(this.z);
    if (float0 >= float1 && float0 >= float2) {
      return 0;
    } else {
      return float1 >= float2 ? 1 : 2;
    }
  }

  int minComponent() {
    float float0 = Math.abs(this.x);
    float float1 = Math.abs(this.y);
    float float2 = Math.abs(this.z);
    if (float0 < float1 && float0 < float2) {
      return 0;
    } else {
      return float1 < float2 ? 1 : 2;
    }
  }

  Vector3f orthogonalize(Vector3fc arg0, Vector3f arg1) {
    float float0;
    float float1;
    float float2;
    if (Math.abs(arg0.x()) > Math.abs(arg0.z())) {
      float0 = -arg0.y();
      float1 = arg0.x();
      float2 = 0.0F;
    } else {
      float0 = 0.0F;
      float1 = -arg0.z();
      float2 = arg0.y();
    }

    float float3 =
        Math.invsqrt(float0 * float0 + float1 * float1 + float2 * float2);
    arg1.x = float0 * float3;
    arg1.y = float1 * float3;
    arg1.z = float2 * float3;
    return arg1;
  }

  Vector3f orthogonalize(Vector3fc arg0) {
    return this.orthogonalize(arg0, this);
  }

  Vector3f orthogonalizeUnit(Vector3fc arg0, Vector3f arg1) {
    return this.orthogonalize(arg0, arg1);
  }

  Vector3f orthogonalizeUnit(Vector3fc arg0) {
    return this.orthogonalizeUnit(arg0, this);
  }

  Vector3f floor() { return this.floor(this); }

  Vector3f floor(Vector3f arg0) {
    arg0.x = Math.floor(this.x);
    arg0.y = Math.floor(this.y);
    arg0.z = Math.floor(this.z);
    return arg0;
  }

  Vector3f ceil() { return this.ceil(this); }

  Vector3f ceil(Vector3f arg0) {
    arg0.x = Math.ceil(this.x);
    arg0.y = Math.ceil(this.y);
    arg0.z = Math.ceil(this.z);
    return arg0;
  }

  Vector3f round() { return this.round(this); }

  Vector3f round(Vector3f arg0) {
    arg0.x = Math.round(this.x);
    arg0.y = Math.round(this.y);
    arg0.z = Math.round(this.z);
    return arg0;
  }

  bool isFinite() {
    return Math.isFinite(this.x) && Math.isFinite(this.y) &&
           Math.isFinite(this.z);
  }
}
} // namespace joml
} // namespace org
