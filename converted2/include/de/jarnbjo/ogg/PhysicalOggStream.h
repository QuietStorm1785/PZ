#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace ogg {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PhysicalOggStream {
public:
  virtual ~PhysicalOggStream() = default;
  Collection getLogicalStreams();

  OggPage getOggPage(int var1);

  bool isOpen();

  void close();

  void setTime(long var1);

  bool isSeekable();
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
