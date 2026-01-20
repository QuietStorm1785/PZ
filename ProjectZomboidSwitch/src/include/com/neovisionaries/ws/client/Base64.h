#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class Base64 {
public:
   private static const byte[] INDEX_TABLE = new byte[]{
      65,
      66,
      67,
      68,
      69,
      70,
      71,
      72,
      73,
      74,
      75,
      76,
      77,
      78,
      79,
      80,
      81,
      82,
      83,
      84,
      85,
      86,
      87,
      88,
      89,
      90,
      97,
      98,
      99,
      100,
      101,
      102,
      103,
      104,
      105,
      106,
      107,
      108,
      109,
      110,
      111,
      112,
      113,
      114,
      115,
      116,
      117,
      118,
      119,
      120,
      121,
      122,
      48,
      49,
      50,
      51,
      52,
      53,
      54,
      55,
      56,
      57,
      43,
      47
   };

    static std::string encode(const std::string& data) {
    return data = = nullptr ? nullptr : encode(Misc.getBytesUTF8(data));
   }

    static std::string encode(byte[] data) {
      if (data == nullptr) {
    return nullptr;
      } else {
    int capacity = ((data.length * 8 + 5) / 6 + 3) / 4 * 4;
    std::stringstream builder = new std::stringstream(capacity);
    int bitIndex = 0;

         while (true) {
    int bits = extractBits(data, bitIndex);
            if (bits < 0) {
               for (int i = builder.length(); i < capacity; i++) {
                  builder.append('=');
               }

               return builder;
            }

            builder.append((char)INDEX_TABLE[bits]);
            bitIndex += 6;
         }
      }
   }

    static int extractBits(byte[] data, int bitIndex) {
    int byteIndex = bitIndex / 8;
      if (data.length <= byteIndex) {
         return -1;
      } else {
    uint8_t nextByte;
         if (data.length - 1 == byteIndex) {
            nextByte = 0;
         } else {
            nextByte = data[byteIndex + 1];
         }

         switch (bitIndex % 24 / 6) {
            case 0:
               return data[byteIndex] >> 2 & 63;
            case 1:
               return data[byteIndex] << 4 & 48 | nextByte >> 4 & 15;
            case 2:
               return data[byteIndex] << 2 & 60 | nextByte >> 6 & 3;
            case 3:
               return data[byteIndex] & 63;
            default:
    return 0;
         }
      }
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
