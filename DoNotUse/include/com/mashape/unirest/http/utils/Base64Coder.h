#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace mashape {
namespace unirest {
namespace http {
namespace utils {

class Base64Coder {
public:
    static const std::string systemLineSeparator = System.getProperty("line.separator");
   private static const char[] map1 = new char[64];
   private static const byte[] map2;

    static std::string encodeString(const std::string& s) {
      return new std::string(encode(s.getBytes()));
   }

    static std::string encodeLines(byte[] in) {
    return encodeLines();
   }

    static std::string encodeLines(byte[] in, int iOff, int iLen, int lineLen, const std::string& lineSeparator) {
    int blockLen = lineLen * 3 / 4;
      if (blockLen <= 0) {
         throw std::make_unique<IllegalArgumentException>();
      } else {
    int lines = (iLen + blockLen - 1) / blockLen;
    int bufLen = (iLen + 2) / 3 * 4 + lines * lineSeparator.length();
    std::stringstream buf = new std::stringstream(bufLen);
    int ip = 0;

         while (ip < iLen) {
    int l = Math.min(iLen - ip, blockLen);
            buf.append(encode(in, iOff + ip, l));
            buf.append(lineSeparator);
            ip += l;
         }

         return buf;
      }
   }

   public static char[] encode(byte[] in) {
    return encode();
   }

   public static char[] encode(byte[] in, int iLen) {
    return encode();
   }

   public static char[] encode(byte[] in, int iOff, int iLen) {
    int oDataLen = (iLen * 4 + 2) / 3;
    int oLen = (iLen + 2) / 3 * 4;
      char[] out = new char[oLen];
    int ip = iOff;
    int iEnd = iOff + iLen;

      for (int op = 0; ip < iEnd; op++) {
    int i0 = in[ip++] & 255;
    int i1 = ip < iEnd ? in[ip++] & 255 : 0;
    int i2 = ip < iEnd ? in[ip++] & 255 : 0;
    int o0 = i0 >>> 2;
    int o1 = (i0 & 3) << 4 | i1 >>> 4;
    int o2 = (i1 & 15) << 2 | i2 >>> 6;
    int o3 = i2 & 63;
         out[op++] = map1[o0];
         out[op++] = map1[o1];
         out[op] = op < oDataLen ? map1[o2] : 61;
         out[++op] = op < oDataLen ? map1[o3] : 61;
      }

    return out;
   }

    static std::string decodeString(const std::string& s) {
      return new std::string(decode(s));
   }

   public static byte[] decodeLines(std::string s) {
      char[] buf = new char[s.length()];
    int p = 0;

      for (int ip = 0; ip < s.length(); ip++) {
    char c = s.charAt(ip);
         if (c != ' ' && c != '\r' && c != '\n' && c != '\t') {
            buf[p++] = c;
         }
      }

    return decode();
   }

   public static byte[] decode(std::string s) {
    return decode();
   }

   public static byte[] decode(char[] in) {
    return decode();
   }

   public static byte[] decode(char[] in, int iOff, int iLen) {
      if (iLen % 4 != 0) {
         throw IllegalArgumentException("Length of Base64 encoded input string is not a multiple of 4.");
      } else {
         while (iLen > 0 && in[iOff + iLen - 1] == '=') {
            iLen--;
         }

    int oLen = iLen * 3 / 4;
         byte[] out = new byte[oLen];
    int ip = iOff;
    int iEnd = iOff + iLen;
    int op = 0;

         while (ip < iEnd) {
    int i0 = in[ip++];
    int i1 = in[ip++];
    int i2 = ip < iEnd ? in[ip++] : 65;
    int i3 = ip < iEnd ? in[ip++] : 65;
            if (i0 <= 127 && i1 <= 127 && i2 <= 127 && i3 <= 127) {
    int b0 = map2[i0];
    int b1 = map2[i1];
    int b2 = map2[i2];
    int b3 = map2[i3];
               if (b0 >= 0 && b1 >= 0 && b2 >= 0 && b3 >= 0) {
    int o0 = b0 << 2 | b1 >>> 4;
    int o1 = (b1 & 15) << 4 | b2 >>> 2;
    int o2 = (b2 & 3) << 6 | b3;
                  out[op++] = (byte)o0;
                  if (op < oLen) {
                     out[op++] = (byte)o1;
                  }

                  if (op < oLen) {
                     out[op++] = (byte)o2;
                  }
                  continue;
               }

               throw IllegalArgumentException("Illegal character in Base64 encoded data.");
            }

            throw IllegalArgumentException("Illegal character in Base64 encoded data.");
         }

    return out;
      }
   }

    private Base64Coder() {
   }

   static {
    int i = 0;
    char c = 'A';

      while (c <= 'Z') {
         map1[i++] = c++;
      }

      c = 'a';

      while (c <= 'z') {
         map1[i++] = c++;
      }

      c = '0';

      while (c <= '9') {
         map1[i++] = c++;
      }

      map1[i++] = '+';
      map1[i++] = '/';
      map2 = new byte[128];

      for (int ix = 0; ix < map2.length; ix++) {
         map2[ix] = -1;
      }

      for (int ix = 0; ix < 64; ix++) {
         map2[map1[ix]] = (byte)ix;
      }
   }
}
} // namespace utils
} // namespace http
} // namespace unirest
} // namespace mashape
} // namespace com
