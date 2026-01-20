#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/utils/Bits/CompareOption.h"

namespace zombie {
namespace core {
namespace utils {


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
    static thread_local std::ostringstream sb;

    static uint8_t packFloatUnitToByte(float var0) {
      if (var0 < 0.0F || var0 > 1.0F) {
         if (Core.bDebug) {
            throw RuntimeException("UtilsIO Cannot pack float units out of the range 0.0 to 1.0");
         }

         var0 = PZMath.clamp(var0, 0.0F, 1.0F);
      }

      return (byte)(var0 * 255.0F + -128.0F);
   }

    static float unpackByteToFloatUnit(uint8_t var0) {
      return (var0 - -128) / 255.0F;
   }

    static uint8_t addFlags(uint8_t var0, int var1) {
      if (var1 >= 0 && var1 <= 64) {
    uint8_t var2;
    return var2 = (byte)(var0 | var1);
      } else {
         throw RuntimeException("Cannot add flags, exceeding byte bounds or negative number flags. (" + var1 + ")");
      }
   }

    static uint8_t addFlags(uint8_t var0, long var1) {
      if (var1 >= 0L && var1 <= 64L) {
         return (byte)(var0 | var1);
      } else {
         throw RuntimeException("Cannot add flags, exceeding byte bounds or negative number flags. (" + var1 + ")");
      }
   }

    static short addFlags(short var0, int var1) {
      if (var1 >= 0 && var1 <= 16384) {
    short var2;
    return var2 = (short)(var0 | var1);
      } else {
         throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + var1 + ")");
      }
   }

    static short addFlags(short var0, long var1) {
      if (var1 >= 0L && var1 <= 16384L) {
         return (short)(var0 | var1);
      } else {
         throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + var1 + ")");
      }
   }

    static int addFlags(int var0, int var1) {
      if (var1 >= 0 && var1 <= 1073741824) {
    int var2;
    return var2 = var0 | var1;
      } else {
         throw RuntimeException("Cannot add flags, exceeding short bounds or negative number flags. (" + var1 + ")");
      }
   }

    static int addFlags(int var0, long var1) {
      if (var1 >= 0L && var1 <= 1073741824L) {
         return (int)(var0 | var1);
      } else {
         throw RuntimeException("Cannot add flags, exceeding integer bounds or negative number flags. (" + var1 + ")");
      }
   }

    static long addFlags(long var0, int var2) {
      if (var2 >= 0 && var2 <= 4611686018427387904L) {
    long var3;
    return var3 = var0 | var2;
      } else {
         throw RuntimeException("Cannot add flags, exceeding long bounds or negative number flags. (" + var2 + ")");
      }
   }

    static long addFlags(long var0, long var2) {
      if (var2 >= 0L && var2 <= 4611686018427387904L) {
    long var4;
    return var4 = var0 | var2;
      } else {
         throw RuntimeException("Cannot add flags, exceeding long bounds or negative number flags. (" + var2 + ")");
      }
   }

    static bool hasFlags(uint8_t var0, int var1) {
    return checkFlags();
   }

    static bool hasFlags(uint8_t var0, long var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(uint8_t var0, int var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(uint8_t var0, long var1) {
    return checkFlags();
   }

    static bool notHasFlags(uint8_t var0, int var1) {
    return checkFlags();
   }

    static bool notHasFlags(uint8_t var0, long var1) {
    return checkFlags();
   }

    static bool hasFlags(short var0, int var1) {
    return checkFlags();
   }

    static bool hasFlags(short var0, long var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(short var0, int var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(short var0, long var1) {
    return checkFlags();
   }

    static bool notHasFlags(short var0, int var1) {
    return checkFlags();
   }

    static bool notHasFlags(short var0, long var1) {
    return checkFlags();
   }

    static bool hasFlags(int var0, int var1) {
    return checkFlags();
   }

    static bool hasFlags(int var0, long var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(int var0, int var1) {
    return checkFlags();
   }

    static bool hasEitherFlags(int var0, long var1) {
    return checkFlags();
   }

    static bool notHasFlags(int var0, int var1) {
    return checkFlags();
   }

    static bool notHasFlags(int var0, long var1) {
    return checkFlags();
   }

    static bool hasFlags(long var0, int var2) {
    return checkFlags();
   }

    static bool hasFlags(long var0, long var2) {
    return checkFlags();
   }

    static bool hasEitherFlags(long var0, int var2) {
    return checkFlags();
   }

    static bool hasEitherFlags(long var0, long var2) {
    return checkFlags();
   }

    static bool notHasFlags(long var0, int var2) {
    return checkFlags();
   }

    static bool notHasFlags(long var0, long var2) {
    return checkFlags();
   }

    static bool checkFlags(int var0, int var1, int var2, CompareOption var3) {
      if (var1 < 0 || var1 > var2) {
         throw RuntimeException("Cannot check for flags, exceeding byte bounds or negative number flags. (" + var1 + ")");
      } else if (var3 == CompareOption.ContainsAll) {
         return (var0 & var1) == var1;
      } else if (var3 == CompareOption.HasEither) {
         return (var0 & var1) != 0;
      } else if (var3 == CompareOption.NotHas) {
         return (var0 & var1) == 0;
      } else {
         throw RuntimeException("No valid compare option.");
      }
   }

    static bool checkFlags(long var0, long var2, long var4, CompareOption var6) {
      if (var2 < 0L || var2 > var4) {
         throw RuntimeException("Cannot check for flags, exceeding byte bounds or negative number flags. (" + var2 + ")");
      } else if (var6 == CompareOption.ContainsAll) {
         return (var0 & var2) == var2;
      } else if (var6 == CompareOption.HasEither) {
         return (var0 & var2) != 0L;
      } else if (var6 == CompareOption.NotHas) {
         return (var0 & var2) == 0L;
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
      sb.str("");
      sb.clear();
   }

    static std::string getBitsString(uint8_t var0) {
    return getBitsString();
   }

    static std::string getBitsString(short var0) {
    return getBitsString();
   }

    static std::string getBitsString(int var0) {
    return getBitsString();
   }

    static std::string getBitsString(long var0) {
    return getBitsString();
   }

    static std::string getBitsString(long var0, int var2) {
      clearStringBuilder();
      if (var0 != 0L) {
         sb << "Bits(" << (var2 - 1) << "): ";
    long var3 = 1L;

         for (int var5 = 1; var5 < var2; var5++) {
            sb << "[" << var5 << "]";
            if ((var0 & var3) == var3) {
               sb << "1";
            } else {
               sb << "0";
            }

            if (var5 < var2 - 1) {
               sb << " ";
            }

            var3 *= 2L;
         }
      } else {
         sb << "No bits saved, 0x0.";
      }

      return sb.str();
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
