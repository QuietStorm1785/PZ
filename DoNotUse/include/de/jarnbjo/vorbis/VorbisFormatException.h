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
namespace vorbis {


class VorbisFormatException : public IOException {
public:
    public VorbisFormatException() {
   }

    public VorbisFormatException(const std::string& var1) {
      super(var1);
   }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
