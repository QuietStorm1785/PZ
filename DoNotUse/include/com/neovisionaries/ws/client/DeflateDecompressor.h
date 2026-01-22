#pragma once
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

class DeflateDecompressor {
public:
    static void decompress(ByteArray input, ByteArray output) {
      decompress(input, 0, output);
   }

    static void decompress(ByteArray input, int index, ByteArray output) {
      int[] bitIndex = new int[]{index * 8};

      while (inflateBlock(input, bitIndex, output)) {
      }
   }

    static bool inflateBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    bool last = input.readBit(bitIndex);
    int type = input.readBits(bitIndex, 2);
      switch (type) {
         case 0:
            inflatePlainBlock(input, bitIndex, output);
            break;
         case 1:
            inflateFixedBlock(input, bitIndex, output);
            break;
         case 2:
            inflateDynamicBlock(input, bitIndex, output);
            break;
         default:
    std::string message = std::string.format("[%s] Bad compression type '11' at the bit index '%d'.", DeflateDecompressor.class.getSimpleName(), bitIndex[0]);
            throw FormatException(message);
      }

      if (input.length() <= bitIndex[0] / 8) {
         last = true;
      }

      return !last;
   }

    static void inflatePlainBlock(ByteArray input, int[] bitIndex, ByteArray output) {
    int bi = bitIndex[0] + 7 & -8;
    int index = bi / 8;
    int len = (input.get(index) & 255) + (input.get(index + 1) & 255) * 256;
      index += 4;
      output.put(input, index, len);
      bitIndex[0] = (index + len) * 8;
   }

    static void inflateFixedBlock(ByteArray input, int[] bitIndex, ByteArray output) {
      inflateData(input, bitIndex, output, FixedLiteralLengthHuffman.getInstance(), FixedDistanceHuffman.getInstance());
   }

    static void inflateDynamicBlock(ByteArray input, int[] bitIndex, ByteArray output) {
      Huffman[] tables = new Huffman[2];
      DeflateUtil.readDynamicTables(input, bitIndex, tables);
      inflateData(input, bitIndex, output, tables[0], tables[1]);
   }

    static void inflateData(ByteArray input, int[] bitIndex, ByteArray output, Huffman literalLengthHuffman, Huffman distanceHuffman) {
      while (true) {
    int literalLength = literalLengthHuffman.readSym(input, bitIndex);
         if (literalLength == 256) {
            return;
         }

         if (0 <= literalLength && literalLength <= 255) {
            output.put(literalLength);
         } else {
    int length = DeflateUtil.readLength(input, bitIndex, literalLength);
    int distance = DeflateUtil.readDistance(input, bitIndex, distanceHuffman);
            duplicate(length, distance, output);
         }
      }
   }

    static void duplicate(int length, int distance, ByteArray output) {
    int sourceLength = output.length();
      byte[] target = new byte[length];
    int initialPosition = sourceLength - distance;
    int sourceIndex = initialPosition;

      for (int targetIndex = 0; targetIndex < length; sourceIndex++) {
         if (sourceLength <= sourceIndex) {
            sourceIndex = initialPosition;
         }

         target[targetIndex] = output.get(sourceIndex);
         targetIndex++;
      }

      output.put(target);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
