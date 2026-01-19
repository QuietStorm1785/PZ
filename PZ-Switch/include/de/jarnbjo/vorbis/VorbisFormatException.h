#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace vorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VorbisFormatException : public IOException {
public:
public
 VorbisFormatException() {}

public
 VorbisFormatException(std::string_view string) { super(string); }
}
} // namespace vorbis
} // namespace jarnbjo
} // namespace de
