#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"

namespace se {
namespace krka {
namespace kahlua {
namespace j2se {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MathLib {
public:
 static const int ABS = 0;
 static const int ACOS = 1;
 static const int ASIN = 2;
 static const int ATAN = 3;
 static const int ATAN2 = 4;
 static const int CEIL = 5;
 static const int COS = 6;
 static const int COSH = 7;
 static const int DEG = 8;
 static const int EXP = 9;
 static const int FLOOR = 10;
 static const int FMOD = 11;
 static const int FREXP = 12;
 static const int LDEXP = 13;
 static const int LOG = 14;
 static const int LOG10 = 15;
 static const int MODF = 16;
 static const int POW = 17;
 static const int RAD = 18;
 static const int SIN = 19;
 static const int SINH = 20;
 static const int SQRT = 21;
 static const int TAN = 22;
 static const int TANH = 23;
 static const int NUM_FUNCTIONS = 24;
 private static String[] names = new String[24];
 private static MathLib[] functions = new MathLib[24];
 const int index;
 static const double LN2_INV;

 public MathLib(int int0) {
 this->index = int0;
 }

 static void register(Platform platform, KahluaTable table1) {
 KahluaTable table0 = platform.newTable();
 table1.rawset("math", table0);
 table0.rawset("pi", KahluaUtil.toDouble(Math.PI);
 table0.rawset("huge", KahluaUtil.toDouble(Double.POSITIVE_INFINITY);

 for (int int0 = 0; int0 < 24; int0++) {
 table0.rawset(names[int0], functions[int0]);
 }
 }

 std::string toString() {
 return "math." + names[this->index];
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 switch (this->index) {
 case 0:
 return abs();
 case 1:
 return acos();
 case 2:
 return asin();
 case 3:
 return atan();
 case 4:
 return atan2();
 case 5:
 return ceil();
 case 6:
 return cos();
 case 7:
 return cosh();
 case 8:
 return deg();
 case 9:
 return exp();
 case 10:
 return floor();
 case 11:
 return fmod();
 case 12:
 return frexp();
 case 13:
 return ldexp();
 case 14:
 return log();
 case 15:
 return log10();
 case 16:
 return modf();
 case 17:
 return pow();
 case 18:
 return rad();
 case 19:
 return sin();
 case 20:
 return sinh();
 case 21:
 return sqrt();
 case 22:
 return tan();
 case 23:
 return tanh();
 default:
 return 0;
 }
 }

 static int abs(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[0]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.abs(double0);
 return 1;
 }

 static int ceil(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[5]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.ceil(double0);
 return 1;
 }

 static int floor(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[10]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.floor(double0);
 return 1;
 }

 static bool isNegative(double double0) {
 return Double.doubleToLongBits(double0) < 0L;
 }

 static double round(double double0) {
 if (double0 < 0.0) {
 return -round(-double0);
 } else {
 double0 += 0.5;
 double double1 = Math.floor(double0);
 return double1 = = double0 ? double1 - ((long)double1 & 1L) : double1;
 }
 }

 static int modf(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[16]);
 bool boolean0 = false;
 if (isNegative(double0) {
 boolean0 = true;
 double0 = -double0;
 }

 double double1 = Math.floor(double0);
 double double2;
 if (Double.isInfinite(double1) {
 double2 = 0.0;
 } else {
 double2 = double0 - double1;
 }

 if (boolean0) {
 double1 = -double1;
 double2 = -double2;
 }

 luaCallFrame.push(KahluaUtil.toDouble(double1), KahluaUtil.toDouble(double2);
 return 2;
 }

 static int fmod(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[11]);
 double double1 = KahluaUtil.getDoubleArg(luaCallFrame, 2, names[11]);
 double double2;
 if (Double.isInfinite(double0) || Double.isNaN(double0) {
 double2 = Double.NaN;
 } else if (Double.isInfinite(double1) {
 double2 = double0;
 } else {
 double1 = Math.abs(double1);
 bool boolean0 = false;
 if (isNegative(double0) {
 boolean0 = true;
 double0 = -double0;
 }

 double2 = double0 - Math.floor(double0 / double1) * double1;
 if (boolean0) {
 double2 = -double2;
 }
 }

 luaCallFrame.push(KahluaUtil.toDouble(double2);
 return 1;
 }

 static int cosh(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[7]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.cosh(double0);
 return 1;
 }

 static int sinh(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[20]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.sinh(double0);
 return 1;
 }

 static int tanh(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[23]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.tanh(double0);
 return 1;
 }

 static int deg(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[8]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.toDegrees(double0);
 return 1;
 }

 static int rad(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[18]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.toRadians(double0);
 return 1;
 }

 static int acos(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[1]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.acos(double0);
 return 1;
 }

 static int asin(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[2]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.asin(double0);
 return 1;
 }

 static int atan(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[3]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.atan(double0);
 return 1;
 }

 static int atan2(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[4]);
 double double1 = KahluaUtil.getDoubleArg(luaCallFrame, 2, names[4]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.atan2(double0, double1);
 return 1;
 }

 static int cos(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[6]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.cos(double0);
 return 1;
 }

 static int sin(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[19]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.sin(double0);
 return 1;
 }

 static int tan(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[22]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.tan(double0);
 return 1;
 }

 static int sqrt(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[21]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.sqrt(double0);
 return 1;
 }

 static int exp(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[9]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.exp(double0);
 return 1;
 }

 static int pow(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[17]);
 double double1 = KahluaUtil.getDoubleArg(luaCallFrame, 2, names[17]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.pow(double0, double1);
 return 1;
 }

 static int log(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[14]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.log(double0);
 return 1;
 }

 static int log10(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[15]);
 luaCallFrame.push(KahluaUtil.toDouble(Math.log10(double0);
 return 1;
 }

 static int frexp(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 1, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[12]);
 double double1;
 double double2;
 if (!Double.isInfinite(double0) && !Double.isNaN(double0) {
 double1 = Math.ceil(Math.log(double0) * LN2_INV);
 int int1 = 1 << (int)double1;
 double2 = double0 / int1;
 } else {
 double1 = 0.0;
 double2 = double0;
 }

 luaCallFrame.push(KahluaUtil.toDouble(double2), KahluaUtil.toDouble(double1);
 return 2;
 }

 static int ldexp(LuaCallFrame luaCallFrame, int int0) {
 KahluaUtil.luaAssert(int0 >= 2, "Not enough arguments");
 double double0 = KahluaUtil.getDoubleArg(luaCallFrame, 1, names[13]);
 double double1 = KahluaUtil.getDoubleArg(luaCallFrame, 2, names[13]);
 double double2 = double0 + double1;
 double double3;
 if (!Double.isInfinite(double2) && !Double.isNaN(double2) {
 int int1 = (int)double1;
 double3 = double0 * (1 << int1);
 } else {
 double3 = double0;
 }

 luaCallFrame.push(KahluaUtil.toDouble(double3);
 return 1;
 }

 static {
 names[0] = "abs";
 names[1] = "acos";
 names[2] = "asin";
 names[3] = "atan";
 names[4] = "atan2";
 names[5] = "ceil";
 names[6] = "cos";
 names[7] = "cosh";
 names[8] = "deg";
 names[9] = "exp";
 names[10] = "floor";
 names[11] = "fmod";
 names[12] = "frexp";
 names[13] = "ldexp";
 names[14] = "log";
 names[15] = "log10";
 names[16] = "modf";
 names[17] = "pow";
 names[18] = "rad";
 names[19] = "sin";
 names[20] = "sinh";
 names[21] = "sqrt";
 names[22] = "tan";
 names[23] = "tanh";

 for (int int0 = 0; int0 < 24; int0++) {
 functions[int0] = new MathLib(int0);
 }

 LN2_INV = 1.0 / Math.log(2.0);
 }
}
} // namespace j2se
} // namespace kahlua
} // namespace krka
} // namespace se
