#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace vector {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReadableVector2f {
public:
  virtual ~ReadableVector2f() = default;
  float getX();

  float getY();
}
} // namespace vector
} // namespace util
} // namespace lwjglx
} // namespace org
