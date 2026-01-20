#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


class OggFormatException : public IOException {
public:
    public OggFormatException() {
   }

    public OggFormatException(const std::string& var1) {
      super(var1);
   }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
