#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix3f.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector4f.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoWaterFlow {
public:
 private static ArrayList<Vector4f> points = std::make_unique<ArrayList<>>();
 private static ArrayList<Matrix3f> zones = std::make_unique<ArrayList<>>();

 static void addFlow(float float1, float float2, float float0, float float3) {
 int int0 = (360 - (int)float0 - 45) % 360;
 if (int0 < 0) {
 int0 += 360;
 }

 float0 = (float)Math.toRadians(int0);
 points.add(new Vector4f(float1, float2, float0, float3);
 }

 static void addZone(float float3, float float1, float float4, float float2, float float0, float float5) {
 if (float3 > float4 || float1 > float2 || float0 > 1.0) {
 DebugLog.log("ERROR IsoWaterFlow: Invalid waterzone (" + float3 + ", " + float1 + ", " + float4 + ", " + float2 + ")");
 }

 zones.add(new Matrix3f(float3, float1, float4, float2, float0, float5, 0.0F, 0.0F, 0.0F);
 }

 static int getShore(int int2, int int1) {
 for (int int0 = 0; int0 < zones.size(); int0++) {
 Matrix3f matrix3f = zones.get(int0);
 if (matrix3f.m00 <= int2 && matrix3f.m02 >= int2 && matrix3f.m01 <= int1 && matrix3f.m10 >= int1) {
 return (int)matrix3f.m11;
 }
 }

 return 1;
 }

 static Vector2f getFlow(IsoGridSquare square0, int int2, int int1, Vector2f vector2f) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 Vector4f vector4f0 = nullptr;
 float float2 = Float.MAX_VALUE;
 Vector4f vector4f1 = nullptr;
 float float3 = Float.MAX_VALUE;
 Vector4f vector4f2 = nullptr;
 float float4 = Float.MAX_VALUE;
 if (points.size() == 0) {
 return vector2f.set(0.0F, 0.0F);
 } else {
 for (int int0 = 0; int0 < points.size(); int0++) {
 Vector4f vector4f3 = points.get(int0);
 double double0 = Math.pow(vector4f3.x - (square0.x + int2), 2.0) + Math.pow(vector4f3.y - (square0.y + int1), 2.0);
 if (double0 < float2) {
 float2 = (float)double0;
 vector4f0 = vector4f3;
 }
 }

 for (int int3 = 0; int3 < points.size(); int3++) {
 Vector4f vector4f4 = points.get(int3);
 double double1 = Math.pow(vector4f4.x - (square0.x + int2), 2.0) + Math.pow(vector4f4.y - (square0.y + int1), 2.0);
 if (double1 < float3 && vector4f4 != vector4f0) {
 float3 = (float)double1;
 vector4f1 = vector4f4;
 }
 }

 float2 = Math.max((float)Math.sqrt(float2), 0.1F);
 float3 = Math.max((float)Math.sqrt(float3), 0.1F);
 if (float2 > float3 * 10.0F) {
 float0 = vector4f0.z;
 float1 = vector4f0.w;
 } else {
 for (int int4 = 0; int4 < points.size(); int4++) {
 Vector4f vector4f5 = points.get(int4);
 double double2 = Math.pow(vector4f5.x - (square0.x + int2), 2.0) + Math.pow(vector4f5.y - (square0.y + int1), 2.0);
 if (double2 < float4 && vector4f5 != vector4f0 && vector4f5 != vector4f1) {
 float4 = (float)double2;
 vector4f2 = vector4f5;
 }
 }

 float4 = Math.max((float)Math.sqrt(float4), 0.1F);
 float float5 = vector4f1.z * (1.0F - float3 / (float3 + float4) + vector4f2.z * (1.0F - float4 / (float3 + float4);
 float float6 = vector4f1.w * (1.0F - float3 / (float3 + float4) + vector4f2.w * (1.0F - float4 / (float3 + float4);
 float float7 = float3 * (1.0F - float3 / (float3 + float4) + float4 * (1.0F - float4 / (float3 + float4);
 float0 = vector4f0.z * (1.0F - float2 / (float2 + float7) + float5 * (1.0F - float7 / (float2 + float7);
 float1 = vector4f0.w * (1.0F - float2 / (float2 + float7) + float6 * (1.0F - float7 / (float2 + float7);
 }

 float float8 = 1.0F;
 IsoCell cell = square0.getCell();

 for (int int5 = -5; int5 < 5; int5++) {
 for (int int6 = -5; int6 < 5; int6++) {
 IsoGridSquare square1 = cell.getGridSquare(square0.x + int2 + int5, square0.y + int1 + int6, 0);
 if (square1 == nullptr || !square1.getProperties().Is(IsoFlagType.water) {
 float8 = (float)Math.min((double)float8, Math.max(0.0, Math.sqrt(int5 * int5 + int6 * int6) / 4.0);
 }
 }
 }

 float1 *= float8;
 return vector2f.set(float0, float1);
 }
 }

 static void Reset() {
 points.clear();
 zones.clear();
 }
}
} // namespace iso
} // namespace zombie
