#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/NumberFormat.h"

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Runtime {
public:
 static const bool HAS_floatToRawIntBits = hasFloatToRawIntBits();
 static const bool HAS_doubleToRawLongBits = hasDoubleToRawLongBits();
 static const bool HAS_Long_rotateLeft = hasLongRotateLeft();
 static const bool HAS_Math_fma = Options.USE_MATH_FMA && hasMathFma();

 static bool hasMathFma() {
 try {
 java.lang.Math.class.getDeclaredMethod("fma", float.class, float.class, float.class);
 return true;
 } catch (NoSuchMethodException noSuchMethodException) {
 return false;
 }
 }

 private Runtime() {
 }

 static bool hasFloatToRawIntBits() {
 try {
 Float.class.getDeclaredMethod("floatToRawIntBits", float.class);
 return true;
 } catch (NoSuchMethodException noSuchMethodException) {
 return false;
 }
 }

 static bool hasDoubleToRawLongBits() {
 try {
 Double.class.getDeclaredMethod("doubleToRawLongBits", double.class);
 return true;
 } catch (NoSuchMethodException noSuchMethodException) {
 return false;
 }
 }

 static bool hasLongRotateLeft() {
 try {
 Long.class.getDeclaredMethod("rotateLeft", long.class, int.class);
 return true;
 } catch (NoSuchMethodException noSuchMethodException) {
 return false;
 }
 }

 static int floatToIntBits(float float0) {
 return HAS_floatToRawIntBits ? floatToIntBits1_3(float0) : floatToIntBits1_2(float0);
 }

 static int floatToIntBits1_3(float float0) {
 return Float.floatToRawIntBits(float0);
 }

 static int floatToIntBits1_2(float float0) {
 return Float.floatToIntBits(float0);
 }

 static long doubleToLongBits(double double0) {
 return HAS_doubleToRawLongBits ? doubleToLongBits1_3(double0) : doubleToLongBits1_2(double0);
 }

 static long doubleToLongBits1_3(double double0) {
 return Double.doubleToRawLongBits(double0);
 }

 static long doubleToLongBits1_2(double double0) {
 return Double.doubleToLongBits(double0);
 }

 static std::string formatNumbers(const std::string& string) {
 StringBuffer stringBuffer = new StringBuffer();
 int int0 = Integer.MIN_VALUE;

 for (int int1 = 0; int1 < string.length(); int1++) {
 char char0 = string.charAt(int1);
 if (char0 == 'E') {
 int0 = int1;
 } else {
 if (char0 == ' ' && int0 == int1 - 1) {
 stringBuffer.append('+');
 continue;
 }

 if (Character.isDigit(char0) && int0 == int1 - 1) {
 stringBuffer.append('+');
 }
 }

 stringBuffer.append(char0);
 }

 return stringBuffer.toString();
 }

 static std::string format(double double0, NumberFormat numberFormat) {
 if (Double.isNaN(double0) {
 return padLeft(" NaN");
 } else {
 return Double.isInfinite(double0) ? padLeft(numberFormat, double0 > 0.0 ? " +Inf" : " -Inf") : numberFormat.format(double0);
 }
 }

 static std::string padLeft(NumberFormat numberFormat, const std::string& string) {
 int int0 = numberFormat.format(0.0).length();
 StringBuffer stringBuffer = new StringBuffer();

 for (int int1 = 0; int1 < int0 - string.length() + 1; int1++) {
 stringBuffer.append(" ");
 }

 return stringBuffer.append(string).toString();
 }

 static bool equals(float float1, float float2, float float0) {
 return Float.floatToIntBits(float1) == Float.floatToIntBits(float2) || Math.abs(float1 - float2) <= float0;
 }

 static bool equals(double double1, double double2, double double0) {
 return Double.doubleToLongBits(double1) == Double.doubleToLongBits(double2) || Math.abs(double1 - double2) <= double0;
 }
}
} // namespace joml
} // namespace org
