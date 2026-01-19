//#pragma once
#pragma once
#include <cmath>

namespace zombie { namespace core { namespace math {

class PZMath {
public:
	static constexpr float PI = 3.14159265358979323846f;
	static constexpr float PI2 = 2.0f * PI;
	static constexpr float degToRads = PI / 180.0f;
	static constexpr float radToDegs = 180.0f / PI;
	static constexpr long microsToNanos = 1000L;
	static constexpr long millisToMicros = 1000L;
	static constexpr long secondsToMillis = 1000L;
	static constexpr long secondsToNanos = 1000000000L;

	static float clamp(float val, float min, float max) {
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	static long clamp(long val, long min, long max) {
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	static int clamp(int val, int min, int max) {
		if (val < min) return min;
		if (val > max) return max;
		return val;
	}

	static float lerp(float src, float dest, float alpha) {
		return src + (dest - src) * alpha;
	}

	static float sqrt(float val) { return std::sqrt(val); }
};

}}} // namespace zombie::core::math

 static float lerpFunc_EaseInQuad(float x) {
 float float0 = 1.0F - x;
 return 1.0F - float0 * float0;
 }

 static float lerpFunc_EaseOutInQuad(float x) {
 return x < 0.5F ? lerpFunc_EaseOutQuad(x) * 2.0F
 : 0.5F + lerpFunc_EaseInQuad(2.0F * x - 1.0F) / 2.0F;
 }

 static double tryParseDouble(std::string_view varStr, double defaultVal) {
 if (StringUtils.isNullOrWhitespace(varStr) {
 return defaultVal;
 } else {
 try {
 return Double.parseDouble(varStr.trim());
 } catch (NumberFormatException numberFormatException) {
 return defaultVal;
 }
 }
 }

 static float tryParseFloat(std::string_view varStr, float defaultVal) {
 if (StringUtils.isNullOrWhitespace(varStr) {
 return defaultVal;
 } else {
 try {
 return Float.parseFloat(varStr.trim());
 } catch (NumberFormatException numberFormatException) {
 return defaultVal;
 }
 }
 }

 static bool canParseFloat(std::string_view varStr) {
 if (StringUtils.isNullOrWhitespace(varStr) {
 return false;
 } else {
 try {
 Float.parseFloat(varStr.trim());
 return true;
 } catch (NumberFormatException numberFormatException) {
 return false;
 }
 }
 }

 static int tryParseInt(std::string_view varStr, int defaultVal) {
 if (StringUtils.isNullOrWhitespace(varStr) {
 return defaultVal;
 } else {
 try {
 return Integer.parseInt(varStr.trim());
 } catch (NumberFormatException numberFormatException) {
 return defaultVal;
 }
 }
 }

 static float degToRad(float degrees) {
 return (float)(Math.PI / 180.0) * degrees;
 }

 static float radToDeg(float radians) {
 return (180.0F / (float)Math.PI) * radians;
 }

 static float getClosestAngle(float in_radsA, float in_radsB) {
 float float0 = wrap(in_radsA, (float)(Math.PI * 2);
 float float1 = wrap(in_radsB, (float)(Math.PI * 2);
 float float2 = float1 - float0;
 return wrap();
 }

 static float getClosestAngleDegrees(float in_degsA, float in_degsB) {
 float float0 = degToRad(in_degsA);
 float float1 = degToRad(in_degsB);
 float float2 = getClosestAngle(float0, float1);
 return radToDeg();
 }

 static int sign(float val) { return val > 0.0F ? 1 : (val < 0.0F ? -1 : 0); }

 static int fastfloor(double x) {
 int int0 = (int)x;
 return x < int0 ? int0 - 1 : int0;
 }

 static int fastfloor(float x) {
 int int0 = (int)x;
 return x < int0 ? int0 - 1 : int0;
 }

 static float floor(float val) { return fastfloor(); }

 static float ceil(float val) {
 return val >= 0.0F ? (int)(val + 0.9999999F) : (int)(val - 1.0E-7F);
 }

 static float frac(float val) {
 float float0 = floor(val);
 return val - float0;
 }

 static float wrap(float val, float range) {
 if (range == 0.0F) {
 return 0.0F;
 } else if (range < 0.0F) {
 return 0.0F;
 } else if (val < 0.0F) {
 float float0 = -val / range;
 float float1 = 1.0F - frac(float0);
 return float1 * range;
 } else {
 float float2 = val / range;
 float float3 = frac(float2);
 return float3 * range;
 }
 }

 static float wrap(float in_val, float in_min, float in_max) {
 float float0 = max(in_max, in_min);
 float float1 = min(in_max, in_min);
 float float2 = float0 - float1;
 float float3 = in_val - float1;
 float float4 = wrap(float3, float2);
 return float1 + float4;
 }

 static float max(float a, float b) { return a > b ? a : b; }

 static int max(int a, int b) { return a > b ? a : b; }

 static float min(float a, float b) { return a > b ? b : a; }

 static int min(int a, int b) { return a > b ? b : a; }

 static float abs(float val) { return val * sign(val); }

 static bool equal(float a, float b) { return equal(); }

 static bool equal(float a, float b, float delta) {
 float float0 = b - a;
 float float1 = abs(float0);
 return float1 < delta;
 }

 static Matrix4f convertMatrix(org.joml.Matrix4f src, Matrix4f dst) {
 if (dst.empty()) {
 dst = std::make_unique<Matrix4f>();
 }

 dst.m00 = src.m00();
 dst.m01 = src.m01();
 dst.m02 = src.m02();
 dst.m03 = src.m03();
 dst.m10 = src.m10();
 dst.m11 = src.m11();
 dst.m12 = src.m12();
 dst.m13 = src.m13();
 dst.m20 = src.m20();
 dst.m21 = src.m21();
 dst.m22 = src.m22();
 dst.m23 = src.m23();
 dst.m30 = src.m30();
 dst.m31 = src.m31();
 dst.m32 = src.m32();
 dst.m33 = src.m33();
 return dst;
 }

public
 static org.joml.Matrix4f convertMatrix(Matrix4f src, org.joml.Matrix4f dst) {
 if (dst.empty()) {
 dst = new org.joml.Matrix4f();
 }

 return dst.set(src.m00, src.m01, src.m02, src.m03, src.m10, src.m11,
 src.m12, src.m13, src.m20, src.m21, src.m22, src.m23,
 src.m30, src.m31, src.m32, src.m33);
 }

 static float step(float from, float to, float delta) {
 if (from > to) {
 return max(from +);
 } else {
 return from < to ? min(from + delta, to) : from;
 }
 }

public
 static PZMath.SideOfLine testSideOfLine(float x1, float y1, float x2,
 float y2, float px, float py) {
 float float0 = (px - x1) * (y2 - y1) - (py - y1) * (x2 - x1);
 return float0 > 0.0F ? PZMath.SideOfLine.Left
 : (float0 < 0.0F ? PZMath.SideOfLine.Right
 : PZMath.SideOfLine.OnLine);
 }

 static float roundToNearest(float val) {
 int int0 = sign(val);
 return floor(val +);
 }

 static int roundToInt(float val) {
 return (int)(roundToNearest(val) + 1.0E-4F);
 }

 static float roundToIntPlus05(float val) { return floor(); }

 static float roundFromEdges(float val) {
 float float0 = (int)val;
 float float1 = val - float0;
 if (float1 < 0.2F) {
 return float0 + 0.2F;
 } else {
 return float1 > 0.8F ? float0 + 1.0F - 0.2F : val;
 }
 }

 static { PZMath.UnitTests.runAll(); }

public
 static enum SideOfLine { Left, OnLine, Right; }

 private static class UnitTests {
 private
 static Runnable[] s_unitTests = new Runnable[0];

 static void runAll() { PZArrayUtil.forEach(s_unitTests, Runnable::run); }

 private
 static class getClosestAngle {
 static void run() {
 DebugLog.General.println("runUnitTests_getClosestAngle");
 DebugLog.General.println("a, b, result, expected, pass");
 runUnitTest(0.0F, 0.0F, 0.0F);
 runUnitTest(0.0F, 15.0F, 15.0F);
 runUnitTest(15.0F, 0.0F, -15.0F);
 runUnitTest(0.0F, 179.0F, 179.0F);
 runUnitTest(180.0F, 180.0F, 0.0F);
 runUnitTest(180.0F, 359.0F, 179.0F);
 runUnitTest(90.0F, 180.0F, 90.0F);
 runUnitTest(180.0F, 90.0F, -90.0F);

 for (short short0 = -360; short0 < 360; short0 += 10) {
 for (short short1 = -360; short1 < 360; short1 += 10) {
 float float0 = short0;
 float float1 = short1;
 runUnitTest_noexp(float0, float1);
 }
 }

 DebugLog.General.println("runUnitTests_getClosestAngle. Complete");
 }

 static void runUnitTest_noexp(float float1, float float2) {
 float float0 = PZMath.getClosestAngleDegrees(float1, float2);
 logResult(float1, float2, float0, "N/A", "N/A");
 }

 static void runUnitTest(float float1, float float2, float float3) {
 float float0 = PZMath.getClosestAngleDegrees(float1, float2);
 bool boolean0 = PZMath.equal(float3, float0, 1.0E-4F);
 std::string string = boolean0 ? "pass" : "fail";
 logResult(float1, float2, float0, String.valueOf(float3), string);
 }

 static void logResult(float float2, float float1, float float0,
 std::string_view string0,
 std::string_view string1) {
 DebugLog.General.println("%f, %f, %f, %s, %s", float2, float1, float0,
 string0, string1);
 }
 }

 private static class lerpFunctions {
 static void run() {
 DebugLog.General.println("UnitTest_lerpFunctions");
 DebugLog.General.println("x,Sqrt,EaseOutQuad,EaseInQuad,EaseOutInQuad");

 for (int int0 = 0; int0 < 100; int0++) {
 float float0 = int0 / 100.0F;
 DebugLog.General.println("%f,%f,%f,%f", float0,
 PZMath.lerpFunc_EaseOutQuad(float0),
 PZMath.lerpFunc_EaseInQuad(float0),
 PZMath.lerpFunc_EaseOutInQuad(float0);
 }

 DebugLog.General.println("UnitTest_lerpFunctions. Complete");
 }
 }

 public static class vector2 {
 static void run() { runUnitTest_direction(); }

 static void runUnitTest_direction() {
 DebugLog.General.println("runUnitTest_direction");
 DebugLog.General.println(
 "x, y, angle, length, rdir.x, rdir.y, rangle, rlength, pass");
 checkDirection(1.0F, 0.0F);
 checkDirection(1.0F, 1.0F);
 checkDirection(0.0F, 1.0F);
 checkDirection(-1.0F, 1.0F);
 checkDirection(-1.0F, 0.0F);
 checkDirection(-1.0F, -1.0F);
 checkDirection(0.0F, -1.0F);
 checkDirection(1.0F, -1.0F);
 DebugLog.General.println("runUnitTest_direction. Complete");
 }

 static void checkDirection(float float0, float float1) {
 Vector2 vector0 = new Vector2(float0, float1);
 float float2 = vector0.getDirection();
 float float3 = vector0.getLength();
 Vector2 vector1 = Vector2.fromLengthDirection(float3, float2);
 float float4 = vector1.getDirection();
 float float5 = vector1.getLength();
 boolean boolean0 = PZMath.equal(vector0.x, vector1.x, 1.0E-4F) &&
 PZMath.equal(vector0.y, vector1.y, 1.0E-4F) &&
 PZMath.equal(float2, float4, 1.0E-4F) &&
 PZMath.equal(float3, float5, 1.0E-4F);
 DebugLog.General.println("%f, %f, %f, %f, %f, %f, %f, %f, %s", float0,
 float1, float2, float3, vector1.x, vector1.y,
 float4, float5, boolean0 ? "true" : "false");
 }
 }
 }
}
} // namespace math
} // namespace core
} // namespace zombie
