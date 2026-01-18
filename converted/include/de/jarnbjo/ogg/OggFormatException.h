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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class OggFormatException : public IOException {
public:
 public OggFormatException() {
 }

 public OggFormatException(const std::string& string) {
 super(string);
 }
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
