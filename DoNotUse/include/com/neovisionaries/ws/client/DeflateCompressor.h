#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {


class DeflateCompressor {
public:
   public static byte[] compress(byte[] input) throws IOException {
    ByteArrayOutputStream baos = std::make_shared<ByteArrayOutputStream>();
    Deflater deflater = createDeflater();
    DeflaterOutputStream dos = std::make_shared<DeflaterOutputStream>(baos, deflater);
      dos.write(input, 0, input.length);
      dos.close();
      deflater.end();
      return baos.toByteArray();
   }

    static Deflater createDeflater() {
      return std::make_shared<Deflater>(-1, true);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
