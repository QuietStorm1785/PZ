#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Math {
public:
 static const double PI = java.lang.Math.PI;
 static const double PI2 = java.lang.Math.PI * 2;
 static const float PI_f = (float)java.lang.Math.PI;
 static const float PI2_f = (float)(java.lang.Math.PI * 2);
 static const double PIHalf = java.lang.Math.PI / 2;
 static const float PIHalf_f = (float)(java.lang.Math.PI / 2);
 static const double PI_4 = java.lang.Math.PI / 4;
 static const double PI_INV = 0.3183098861837907;
 static const int lookupBits = Options.SIN_LOOKUP_BITS;
 static const int lookupTableSize = 1 << lookupBits;
 static const int lookupTableSizeMinus1 = lookupTableSize - 1;
 static const int lookupTableSizeWithMargin = lookupTableSize + 1;
 static const float pi2OverLookupSize =
 (float)(java.lang.Math.PI * 2) / lookupTableSize;
 static const float lookupSizeOverPi2 =
 lookupTableSize / (float)(java.lang.Math.PI * 2);
private
 static float[] sinTable;
 static const double c1;
 static const double c2;
 static const double c3;
 static const double c4;
 static const double c5;
 static const double c6;
 static const double c7;
 static const double s5;
 static const double s4;
 static const double s3;
 static const double s2;
 static const double s1;
 static const double k1;
 static const double k2;
 static const double k3;
 static const double k4;
 static const double k5;
 static const double k6;
 static const double k7;

 static double sin_theagentd_arith(double double1) {
 double double0 =
 floor((double1 + (java.lang.Math.PI / 4) * 0.3183098861837907);
 double double2 = double1 - double0 * java.lang.Math.PI;
 double double3 = ((int)double0 & 1) * -2 + 1;
 double double4 = double2 * double2;
 double double5 = double2 * double4;
 double double6 = double2 + double5 * c1;
 double5 *= double4;
 double6 += double5 * c2;
 double5 *= double4;
 double6 += double5 * c3;
 double5 *= double4;
 double6 += double5 * c4;
 double5 *= double4;
 double6 += double5 * c5;
 double5 *= double4;
 double6 += double5 * c6;
 double5 *= double4;
 double6 += double5 * c7;
 return double3 * double6;
 }

 static double sin_roquen_arith(double double1) {
 double double0 =
 floor((double1 + (java.lang.Math.PI / 4) * 0.3183098861837907);
 double double2 = double1 - double0 * java.lang.Math.PI;
 double double3 = ((int)double0 & 1) * -2 + 1;
 double double4 = double2 * double2;
 double2 = double3 * double2;
 double double5 = c7;
 double5 = double5 * double4 + c6;
 double5 = double5 * double4 + c5;
 double5 = double5 * double4 + c4;
 double5 = double5 * double4 + c3;
 double5 = double5 * double4 + c2;
 double5 = double5 * double4 + c1;
 return double2 + double2 * double4 * double5;
 }

 static double sin_roquen_9(double double1) {
 double double0 = java.lang.Math.rint(double1 * 0.3183098861837907);
 double double2 = double1 - double0 * java.lang.Math.PI;
 double double3 = 1 - 2 * ((int)double0 & 1);
 double double4 = double2 * double2;
 double2 = double3 * double2;
 double double5 = s5;
 double5 = double5 * double4 + s4;
 double5 = double5 * double4 + s3;
 double5 = double5 * double4 + s2;
 double5 = double5 * double4 + s1;
 return double2 * double5;
 }

 static double sin_roquen_newk(double double1) {
 double double0 = java.lang.Math.rint(double1 * 0.3183098861837907);
 double double2 = double1 - double0 * java.lang.Math.PI;
 double double3 = 1 - 2 * ((int)double0 & 1);
 double double4 = double2 * double2;
 double2 = double3 * double2;
 double double5 = k7;
 double5 = double5 * double4 + k6;
 double5 = double5 * double4 + k5;
 double5 = double5 * double4 + k4;
 double5 = double5 * double4 + k3;
 double5 = double5 * double4 + k2;
 double5 = double5 * double4 + k1;
 return double2 + double2 * double4 * double5;
 }

 static float sin_theagentd_lookup(float float1) {
 float float0 = float1 * lookupSizeOverPi2;
 int int0 = (int)java.lang.Math.floor(float0);
 float float2 = float0 - int0;
 int int1 = int0 & lookupTableSizeMinus1;
 float float3 = sinTable[int1];
 float float4 = sinTable[int1 + 1];
 return float3 + (float4 - float3) * float2;
 }

 static float sin(float float0) { return (float)java.lang.Math.sin(float0); }

 static double sin(double double0) {
 if (Options.FASTMATH) {
 return Options.SIN_LOOKUP ? sin_theagentd_lookup((float)double0)
 : sin_roquen_newk(double0);
 } else {
 return java.lang.Math.sin(double0);
 }
 }

 static float cos(float float0) {
 return Options.FASTMATH ? sin(float0 + (float)(java.lang.Math.PI / 2)
 : (float)java.lang.Math.cos(float0);
 }

 static double cos(double double0) {
 return Options.FASTMATH ? sin(double0 + (java.lang.Math.PI / 2)
 : java.lang.Math.cos(double0);
 }

 static float cosFromSin(float float0, float float1) {
 return Options.FASTMATH ? sin(float1 + (float)(java.lang.Math.PI / 2)
 : cosFromSinInternal(float0, float1);
 }

 static float cosFromSinInternal(float float1, float float3) {
 float float0 = sqrt(1.0F - float1 * float1);
 float float2 = float3 + (float)(java.lang.Math.PI / 2);
 float float4 = float2 - (int)(float2 / (float)(java.lang.Math.PI * 2) *
 (float)(java.lang.Math.PI * 2);
 if (float4 < 0.0) {
 float4 += (float)(java.lang.Math.PI * 2);
 }

 return float4 >= (float)java.lang.Math.PI ? -float0 : float0;
 }

 static double cosFromSin(double double2, double double0) {
 if (Options.FASTMATH) {
 return sin(double0 +);
 } else {
 double double1 = sqrt(1.0 - double2 * double2);
 double double3 = double0 + (java.lang.Math.PI / 2);
 double double4 = double3 - (int)(double3 / (java.lang.Math.PI * 2) *
 (java.lang.Math.PI * 2);
 if (double4 < 0.0) {
 double4 += java.lang.Math.PI * 2;
 }

 return double4 >= java.lang.Math.PI ? -double1 : double1;
 }
 }

 static float sqrt(float float0) { return (float)java.lang.Math.sqrt(float0); }

 static double sqrt(double double0) { return java.lang.Math.sqrt(double0); }

 static float invsqrt(float float0) {
 return 1.0F / (float)java.lang.Math.sqrt(float0);
 }

 static double invsqrt(double double0) {
 return 1.0 / java.lang.Math.sqrt(double0);
 }

 static float tan(float float0) { return (float)java.lang.Math.tan(float0); }

 static double tan(double double0) { return java.lang.Math.tan(double0); }

 static float acos(float float0) { return (float)java.lang.Math.acos(float0); }

 static double acos(double double0) { return java.lang.Math.acos(double0); }

 static float safeAcos(float float0) {
 if (float0 < -1.0F) {
 return (float)java.lang.Math.PI;
 } else {
 return float0 > 1.0F ? 0.0F : acos(float0);
 }
 }

 static double safeAcos(double double0) {
 if (double0 < -1.0) {
 return java.lang.Math.PI;
 } else {
 return double0 > 1.0 ? 0.0 : acos(double0);
 }
 }

 static double fastAtan2(double double3, double double1) {
 double double0 = double1 >= 0.0 ? double1 : -double1;
 double double2 = double3 >= 0.0 ? double3 : -double3;
 double double4 = min(double0, double2) / max(double0, double2);
 double double5 = double4 * double4;
 double double6 =
 ((-0.0464964749 * double5 + 0.15931422) * double5 - 0.327622764) *
 double5 * double4 +
 double4;
 if (double2 > double0) {
 double6 = 1.57079637 - double6;
 }

 if (double1 < 0.0) {
 double6 = 3.14159274 - double6;
 }

 return double3 >= 0.0 ? double6 : -double6;
 }

 static float atan2(float float1, float float0) {
 return (float)java.lang.Math.atan2(float1, float0);
 }

 static double atan2(double double0, double double1) {
 return Options.FASTMATH ? fastAtan2(double0, double1)
 : java.lang.Math.atan2(double0, double1);
 }

 static float asin(float float0) { return (float)java.lang.Math.asin(float0); }

 static double asin(double double0) { return java.lang.Math.asin(double0); }

 static float safeAsin(float float0) {
 return float0 <= -1.0F ? (float)(-java.lang.Math.PI / 2)
 : (float0 >= 1.0F ? (float)(java.lang.Math.PI / 2)
 : asin(float0);
 }

 static double safeAsin(double double0) {
 return double0 <= -1.0
 ? -java.lang.Math.PI / 2
 : (double0 >= 1.0 ? java.lang.Math.PI / 2 : asin(double0);
 }

 static float abs(float float0) { return java.lang.Math.abs(float0); }

 static double abs(double double0) { return java.lang.Math.abs(double0); }

 static bool absEqualsOne(float float0) {
 return (Float.floatToRawIntBits(float0) & 2147483647) == 1065353216;
 }

 static bool absEqualsOne(double double0) {
 return (Double.doubleToRawLongBits(double0) & Long.MAX_VALUE) ==
 4607182418800017408L;
 }

 static int abs(int int0) { return java.lang.Math.abs(int0); }

 static int max(int int0, int int1) { return java.lang.Math.max(int0, int1); }

 static int min(int int0, int int1) { return java.lang.Math.min(int0, int1); }

 static double min(double double0, double double1) {
 return double0 < double1 ? double0 : double1;
 }

 static float min(float float0, float float1) {
 return float0 < float1 ? float0 : float1;
 }

 static float max(float float0, float float1) {
 return float0 > float1 ? float0 : float1;
 }

 static double max(double double0, double double1) {
 return double0 > double1 ? double0 : double1;
 }

 static float clamp(float float0, float float1, float float2) { return max(); }

 static double clamp(double double0, double double1, double double2) {
 return max();
 }

 static int clamp(int int0, int int1, int int2) { return max(); }

 static float toRadians(float float0) {
 return (float)java.lang.Math.toRadians(float0);
 }

 static double toRadians(double double0) {
 return java.lang.Math.toRadians(double0);
 }

 static double toDegrees(double double0) {
 return java.lang.Math.toDegrees(double0);
 }

 static double floor(double double0) { return java.lang.Math.floor(double0); }

 static float floor(float float0) {
 return (float)java.lang.Math.floor(float0);
 }

 static double ceil(double double0) { return java.lang.Math.ceil(double0); }

 static float ceil(float float0) { return (float)java.lang.Math.ceil(float0); }

 static long round(double double0) { return java.lang.Math.round(double0); }

 static int round(float float0) { return java.lang.Math.round(float0); }

 static double exp(double double0) { return java.lang.Math.exp(double0); }

 static bool isFinite(double double0) { return abs(); }

 static bool isFinite(float float0) { return abs(); }

 static float fma(float float1, float float2, float float0) {
 return Runtime.HAS_Math_fma ? java.lang.Math.fma(float1, float2, float0)
 : float1 * float2 + float0;
 }

 static double fma(double double1, double double2, double double0) {
 return Runtime.HAS_Math_fma ? java.lang.Math.fma(double1, double2, double0)
 : double1 * double2 + double0;
 }

 static int roundUsing(float float0, int int0) {
 switch (int0) {
 case 0:
 return (int)float0;
 case 1:
 return (int)java.lang.Math.ceil(float0);
 case 2:
 return (int)java.lang.Math.floor(float0);
 case 3:
 return roundHalfEven();
 case 4:
 return roundHalfDown();
 case 5:
 return roundHalfUp();
 default:
 throw std::make_unique<UnsupportedOperationException>();
 }
 }

 static int roundUsing(double double0, int int0) {
 switch (int0) {
 case 0:
 return (int)double0;
 case 1:
 return (int)java.lang.Math.ceil(double0);
 case 2:
 return (int)java.lang.Math.floor(double0);
 case 3:
 return roundHalfEven();
 case 4:
 return roundHalfDown();
 case 5:
 return roundHalfUp();
 default:
 throw std::make_unique<UnsupportedOperationException>();
 }
 }

 static float lerp(float float1, float float2, float float0) {
 return fma(float2 -);
 }

 static double lerp(double double1, double double2, double double0) {
 return fma(double2 -);
 }

 static float biLerp(float float1, float float2, float float5, float float6,
 float float3, float float7) {
 float float0 = lerp(float1, float2, float3);
 float float4 = lerp(float5, float6, float3);
 return lerp();
 }

 static double biLerp(double double1, double double2, double double5,
 double double6, double double3, double double7) {
 double double0 = lerp(double1, double2, double3);
 double double4 = lerp(double5, double6, double3);
 return lerp();
 }

public
 static float triLerp(float float1, float float2, float float5, float float6,
 float float8, float float9, float float11, float float12,
 float float3, float float14, float float16) {
 float float0 = lerp(float1, float2, float3);
 float float4 = lerp(float5, float6, float3);
 float float7 = lerp(float8, float9, float3);
 float float10 = lerp(float11, float12, float3);
 float float13 = lerp(float0, float4, float14);
 float float15 = lerp(float7, float10, float14);
 return lerp();
 }

public
 static double triLerp(double double1, double double2, double double5,
 double double6, double double8, double double9,
 double double11, double double12, double double3,
 double double14, double double16) {
 double double0 = lerp(double1, double2, double3);
 double double4 = lerp(double5, double6, double3);
 double double7 = lerp(double8, double9, double3);
 double double10 = lerp(double11, double12, double3);
 double double13 = lerp(double0, double4, double14);
 double double15 = lerp(double7, double10, double14);
 return lerp();
 }

 static int roundHalfEven(float float0) {
 return (int)java.lang.Math.rint(float0);
 }

 static int roundHalfDown(float float0) {
 return float0 > 0.0F ? (int)java.lang.Math.ceil(float0 - 0.5)
 : (int)java.lang.Math.floor(float0 + 0.5);
 }

 static int roundHalfUp(float float0) {
 return float0 > 0.0F ? (int)java.lang.Math.floor(float0 + 0.5)
 : (int)java.lang.Math.ceil(float0 - 0.5);
 }

 static int roundHalfEven(double double0) {
 return (int)java.lang.Math.rint(double0);
 }

 static int roundHalfDown(double double0) {
 return double0 > 0.0 ? (int)java.lang.Math.ceil(double0 - 0.5)
 : (int)java.lang.Math.floor(double0 + 0.5);
 }

 static int roundHalfUp(double double0) {
 return double0 > 0.0 ? (int)java.lang.Math.floor(double0 + 0.5)
 : (int)java.lang.Math.ceil(double0 - 0.5);
 }

 static double random() { return java.lang.Math.random(); }

 static double signum(double double0) {
 return java.lang.Math.signum(double0);
 }

 static float signum(float float0) { return java.lang.Math.signum(float0); }

 static int signum(int int0) { return Integer.signum(int0); }

 static int signum(long long0) { return Long.signum(long0); }

 static {
 if (Options.FASTMATH && Options.SIN_LOOKUP) {
 sinTable = new float[lookupTableSizeWithMargin];

 for (int int0 = 0; int0 < lookupTableSizeWithMargin; int0++) {
 double double0 = int0 * pi2OverLookupSize;
 sinTable[int0] = (float)java.lang.Math.sin(double0);
 }
 } else {
 sinTable = nullptr;
 }

 c1 = Double.longBitsToDouble(-4628199217061079772L);
 c2 = Double.longBitsToDouble(4575957461383582011L);
 c3 = Double.longBitsToDouble(-4671919876300759001L);
 c4 = Double.longBitsToDouble(4523617214285661942L);
 c5 = Double.longBitsToDouble(-4730215272828025532L);
 c6 = Double.longBitsToDouble(4460272573143870633L);
 c7 = Double.longBitsToDouble(-4797767418267846529L);
 s5 = Double.longBitsToDouble(4523227044276562163L);
 s4 = Double.longBitsToDouble(-4671934770969572232L);
 s3 = Double.longBitsToDouble(4575957211482072852L);
 s2 = Double.longBitsToDouble(-4628199223918090387L);
 s1 = Double.longBitsToDouble(4607182418589157889L);
 k1 = Double.longBitsToDouble(-4628199217061079959L);
 k2 = Double.longBitsToDouble(4575957461383549981L);
 k3 = Double.longBitsToDouble(-4671919876307284301L);
 k4 = Double.longBitsToDouble(4523617213632129738L);
 k5 = Double.longBitsToDouble(-4730215344060517252L);
 k6 = Double.longBitsToDouble(4460268259291226124L);
 k7 = Double.longBitsToDouble(-4798040743777455072L);
 }
}
} // namespace joml
} // namespace org
