#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace uncommons {
namespace maths {
namespace binary {

class BinaryUtils {
public:
    static const int BITWISE_BYTE_TO_INT = 255;
   private static const char[] HEX_CHARS = new char[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    private BinaryUtils() {
   }

    static std::string convertBytesToHexString(byte[] data) {
    std::stringstream buffer = new std::stringstream(data.length * 2);

    for (auto& b : data)         buffer.append(HEX_CHARS[b >>> 4 & 15]);
         buffer.append(HEX_CHARS[b & 15]);
      }

      return buffer;
   }

   public static byte[] convertHexStringToBytes(std::string hex) {
      if (hex.length() % 2 != 0) {
         throw IllegalArgumentException("Hex string must have even number of characters.");
      } else {
         byte[] seed = new byte[hex.length() / 2];

         for (int i = 0; i < seed.length; i++) {
    int index = i * 2;
            seed[i] = (byte)int.parseInt(hex.substr(index, index + 2), 16);
         }

    return seed;
      }
   }

    static int convertBytesToInt(byte[] bytes, int offset) {
      return 0xFF & bytes[offset + 3] | (0xFF & bytes[offset + 2]) << 8 | (0xFF & bytes[offset + 1]) << 16 | (0xFF & bytes[offset]) << 24;
   }

   public static int[] convertBytesToInts(byte[] bytes) {
      if (bytes.length % 4 != 0) {
         throw IllegalArgumentException("Number of input bytes must be a multiple of 4.");
      } else {
         int[] ints = new int[bytes.length / 4];

         for (int i = 0; i < ints.length; i++) {
            ints[i] = convertBytesToInt(bytes, i * 4);
         }

    return ints;
      }
   }

    static long convertBytesToLong(byte[] bytes, int offset) {
    long value = 0L;

      for (int i = offset; i < offset + 8; i++) {
    uint8_t b = bytes[i];
         value <<= 8;
         value |= b;
      }

    return value;
   }

    static BitString convertDoubleToFixedPointBits(double value) {
      if (!(value < 0.0) && !(value >= 1.0)) {
    std::stringstream bits = new std::stringstream(64);
    double bitValue = 0.5;

         for (double d = value; d > 0.0; bitValue /= 2.0) {
            if (d >= bitValue) {
               bits.append('1');
               d -= bitValue;
            } else {
               bits.append('0');
            }
         }

         return std::make_shared<BitString>(bits);
      } else {
         throw IllegalArgumentException("Value must be between 0 and 1.");
      }
   }
}
} // namespace binary
} // namespace maths
} // namespace uncommons
} // namespace org
