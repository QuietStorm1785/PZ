#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace sixlegs {
namespace png {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextChunk {
public:
  virtual ~TextChunk() = default;
  std::string getKeyword();

  std::string getTranslatedKeyword();

  std::string getLanguage();

  std::string getText();

  int getType();
}
} // namespace png
} // namespace sixlegs
} // namespace com
