#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Bits {
public:
 static const bool ENABLED = true;
 static const int BIT_0 = 0;
 static const int BIT_1 = 1;
 static const int BIT_2 = 2;
 static const int BIT_3 = 4;
 static const int BIT_4 = 8;
 static const int BIT_5 = 16;
 static const int BIT_6 = 32;
 static const int BIT_7 = 64;
 static const int BIT_BYTE_MAX = 64;
 static const int BIT_8 = 128;
 static const int BIT_9 = 256;
 static const int BIT_10 = 512;
 static const int BIT_11 = 1024;
 static const int BIT_12 = 2048;
 static const int BIT_13 = 4096;
 static const int BIT_14 = 8192;
 static const int BIT_15 = 16384;
 static const int BIT_SHORT_MAX = 16384;
 static const int BIT_16 = 32768;
 static const int BIT_17 = 65536;
 static const int BIT_18 = 131072;
 static const int BIT_19 = 262144;
 static const int BIT_20 = 524288;
 static const int BIT_21 = 1048576;
 static const int BIT_22 = 2097152;
 static const int BIT_23 = 4194304;
 static const int BIT_24 = 8388608;
 static const int BIT_25 = 16777216;
 static const int BIT_26 = 33554432;
 static const int BIT_27 = 67108864;
 static const int BIT_28 = 134217728;
 static const int BIT_29 = 268435456;
 static const int BIT_30 = 536870912;
 static const int BIT_31 = 1073741824;
 static const int BIT_INT_MAX = 1073741824;
 static const long BIT_32 = 2147483648L;
 static const long BIT_33 = 4294967296L;
 static const long BIT_34 = 8589934592L;
 static const long BIT_35 = 17179869184L;
 static const long BIT_36 = 34359738368L;
 static const long BIT_37 = 68719476736L;
 static const long BIT_38 = 137438953472L;
 static const long BIT_39 = 274877906944L;
 static const long BIT_40 = 549755813888L;
 static const long BIT_41 = 1099511627776L;
 static const long BIT_42 = 2199023255552L;
 static const long BIT_43 = 4398046511104L;
 static const long BIT_44 = 8796093022208L;
 static const long BIT_45 = 17592186044416L;
 static const long BIT_46 = 35184372088832L;
 static const long BIT_47 = 70368744177664L;
 static const long BIT_48 = 140737488355328L;
 static const long BIT_49 = 281474976710656L;
 static const long BIT_50 = 562949953421312L;
 static const long BIT_51 = 1125899906842624L;
 static const long BIT_52 = 2251799813685248L;
 static const long BIT_53 = 4503599627370496L;
 static const long BIT_54 = 9007199254740992L;
 static const long BIT_55 = 18014398509481984L;
 static const long BIT_56 = 36028797018963968L;
 static const long BIT_57 = 72057594037927936L;
 static const long BIT_58 = 144115188075855872L;
 static const long BIT_59 = 288230376151711744L;
 static const long BIT_60 = 576460752303423488L;
 static const long BIT_61 = 1152921504606846976L;
 static const long BIT_62 = 2305843009213693952L;
 static const long BIT_63 = 4611686018427387904L;
 static const long BIT_LONG_MAX = 4611686018427387904L;
 static StringBuilder sb = new StringBuilder();

 static uint8_t packFloatUnitToByte(float float0) {
 if (float0 < 0.0F || float0 > 1.0F) {
 if (Core.bDebug) {
 throw RuntimeException("UtilsIO Cannot pack float units out of the range 0.0 to 1.0");
 }

 float0 = PZMath.clamp(float0, 0.0F, 1.0F);
 }

 return (byte)(float0 * 255.0F + -128.0F);
 }

 static float unpackByteToFloatUnit(uint8_t byte0) {
 return (byte0 - -128) / 255.0F;
 }

 static uint8_t addFlags(uint8_t byte1, int int0) {
 if (int0 >= 0 && int0 <= 64) {
 uint8_t byte0;
 return byte0 = (byte)(byte1 | int0);
 } else {
 throw RuntimeException("Cannot add flags, exceeding byte bounds or negative number flags. (" + int0 + ")");
 }
 }

 static uint8_t addFlags(uint8_t byte0, long long0) {
 if (long0 >= 0L && long0 <= 64L) {
 return (byte)(byte0 | long0);
 } else {
 throw RuntimeException("Cannot add flags, exceeding byte bounds or negative number flags. (" + long0 + ")");
 }
 }

 static short addFlags(short short1, int int0) {
 if (int0 >= 0 && int0 <= 16384) {
 short short0;
 return short0 = (short)(short1 | int0);
 } else {
 throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + int0 + ")");
 }
 }

 static short addFlags(short short0, long long0) {
 if (long0 >= 0L && long0 <= 16384L) {
 return (short)(short0 | long0);
 } else {
 throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + long0 + ")");
 }
 }

 static int addFlags(int int2, int int0) {
 if (int0 >= 0 && int0 <= 1073741824) {
 int int1;
 return int1 = int2 | int0;
 } else {
 throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + int0 + ")");
 }
 }

 static int addFlags(int int0, long long0) {
 if (long0 >= 0L && long0 <= 1073741824L) {
 return (int)(int0 | long0);
 } else {
 throw RuntimeException("Cannot add flags, exceeding integer bounds or negative number flags. (" + long0 + ")");
 }
 }

 static long addFlags(long long1, int int0) {
 if (int0 >= 0 && int0 <= 4611686018427387904L) {
 long long0;
 return long0 = long1 | int0;
 } else {
 throw RuntimeException("Cannot add flags, exceeding long bounds or negative number flags. (" + int0 + ")");
 }
 }

 static long addFlags(long long2, long long0) {
 if (long0 >= 0L && long0 <= 4611686018427387904L) {
 long long1;
 return long1 = long2 | long0;
 } else {
 throw RuntimeException("Cannot add flags, exceeding long bounds or negative number flags. (" + long0 + ")");
 }
 }

 static bool hasFlags(uint8_t byte0, int int0) {
 return checkFlags();
 }

 static bool hasFlags(uint8_t byte0, long long0) {
 return checkFlags();
 }

 static bool hasEitherFlags(uint8_t byte0, int int0) {
 return checkFlags();
 }

 static bool hasEitherFlags(uint8_t byte0, long long0) {
 return checkFlags();
 }

 static bool notHasFlags(uint8_t byte0, int int0) {
 return checkFlags();
 }

 static bool notHasFlags(uint8_t byte0, long long0) {
 return checkFlags();
 }

 static bool hasFlags(short short0, int int0) {
 return checkFlags();
 }

 static bool hasFlags(short short0, long long0) {
 return checkFlags();
 }

 static bool hasEitherFlags(short short0, int int0) {
 return checkFlags();
 }

 static bool hasEitherFlags(short short0, long long0) {
 return checkFlags();
 }

 static bool notHasFlags(short short0, int int0) {
 return checkFlags();
 }

 static bool notHasFlags(short short0, long long0) {
 return checkFlags();
 }

 static bool hasFlags(int int0, int int1) {
 return checkFlags();
 }

 static bool hasFlags(int int0, long long0) {
 return checkFlags();
 }

 static bool hasEitherFlags(int int0, int int1) {
 return checkFlags();
 }

 static bool hasEitherFlags(int int0, long long0) {
 return checkFlags();
 }

 static bool notHasFlags(int int0, int int1) {
 return checkFlags();
 }

 static bool notHasFlags(int int0, long long0) {
 return checkFlags();
 }

 static bool hasFlags(long long0, int int0) {
 return checkFlags();
 }

 static bool hasFlags(long long0, long long1) {
 return checkFlags();
 }

 static bool hasEitherFlags(long long0, int int0) {
 return checkFlags();
 }

 static bool hasEitherFlags(long long0, long long1) {
 return checkFlags();
 }

 static bool notHasFlags(long long0, int int0) {
 return checkFlags();
 }

 static bool notHasFlags(long long0, long long1) {
 return checkFlags();
 }

 static bool checkFlags(int int2, int int0, int int1, Bits.CompareOption compareOption) {
 if (int0 < 0 || int0 > int1) {
 throw RuntimeException("Cannot check for flags, exceeding byte bounds or negative number flags. (" + int0 + ")");
 } else if (compareOption == Bits.CompareOption.ContainsAll) {
 return (int2 & int0) == int0;
 } else if (compareOption == Bits.CompareOption.HasEither) {
 return (int2 & int0) != 0;
 } else if (compareOption == Bits.CompareOption.NotHas) {
 return (int2 & int0) == 0;
 } else {
 throw RuntimeException("No valid compare option.");
 }
 }

 static bool checkFlags(long long2, long long0, long long1, Bits.CompareOption compareOption) {
 if (long0 < 0L || long0 > long1) {
 throw RuntimeException("Cannot check for flags, exceeding byte bounds or negative number flags. (" + long0 + ")");
 } else if (compareOption == Bits.CompareOption.ContainsAll) {
 return (long2 & long0) == long0;
 } else if (compareOption == Bits.CompareOption.HasEither) {
 return (long2 & long0) != 0L;
 } else if (compareOption == Bits.CompareOption.NotHas) {
 return (long2 & long0) == 0L;
 } else {
 throw RuntimeException("No valid compare option.");
 }
 }

 static int getLen(uint8_t var0) {
 return 1;
 }

 static int getLen(short var0) {
 return 2;
 }

 static int getLen(int var0) {
 return 4;
 }

 static int getLen(long var0) {
 return 8;
 }

 static void clearStringBuilder() {
 if (sb.length() > 0) {
 sb.delete(0, sb.length());
 }
 }

 static std::string getBitsString(uint8_t byte0) {
 return getBitsString();
 }

 static std::string getBitsString(short short0) {
 return getBitsString();
 }

 static std::string getBitsString(int int0) {
 return getBitsString();
 }

 static std::string getBitsString(long long0) {
 return getBitsString();
 }

 static std::string getBitsString(long long0, int int0) {
 clearStringBuilder();
 if (long0 != 0L) {
 sb.append("Bits(" + (int0 - 1) + "): ");
 long long1 = 1L;

 for (int int1 = 1; int1 < int0; int1++) {
 sb.append("[" + int1 + "]");
 if ((long0 & long1) == long1) {
 sb.append("1");
 } else {
 sb.append("0");
 }

 if (int1 < int0 - 1) {
 sb.append(" ");
 }

 long1 *= 2L;
 }
 } else {
 sb.append("No bits saved, 0x0.");
 }

 return sb.toString();
 }

 public static enum CompareOption {
 ContainsAll,
 HasEither,
 NotHas;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
