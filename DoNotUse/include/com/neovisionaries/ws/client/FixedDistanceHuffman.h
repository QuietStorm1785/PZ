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

class FixedDistanceHuffman : public Huffman {
public:
    static const FixedDistanceHuffman INSTANCE = std::make_shared<FixedDistanceHuffman>();

    private FixedDistanceHuffman() {
      super(buildCodeLensFromSym());
   }

   private static int[] buildCodeLensFromSym() {
      int[] codeLengths = new int[32];

      for (int symbol = 0; symbol < 32; symbol++) {
         codeLengths[symbol] = 5;
      }

    return codeLengths;
   }

    static FixedDistanceHuffman getInstance() {
    return INSTANCE;
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
