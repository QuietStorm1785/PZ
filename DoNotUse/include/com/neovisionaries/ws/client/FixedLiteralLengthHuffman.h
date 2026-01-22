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

class FixedLiteralLengthHuffman : public Huffman {
public:
    static const FixedLiteralLengthHuffman INSTANCE = std::make_shared<FixedLiteralLengthHuffman>();

    private FixedLiteralLengthHuffman() {
      super(buildCodeLensFromSym());
   }

   private static int[] buildCodeLensFromSym() {
      int[] codeLengths = new int[288];

    int symbol;
      for (symbol = 0; symbol < 144; symbol++) {
         codeLengths[symbol] = 8;
      }

      while (symbol < 256) {
         codeLengths[symbol] = 9;
         symbol++;
      }

      while (symbol < 280) {
         codeLengths[symbol] = 7;
         symbol++;
      }

      while (symbol < 288) {
         codeLengths[symbol] = 8;
         symbol++;
      }

    return codeLengths;
   }

    static FixedLiteralLengthHuffman getInstance() {
    return INSTANCE;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
