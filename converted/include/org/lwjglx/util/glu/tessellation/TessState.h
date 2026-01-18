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
namespace glu {
namespace tessellation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TessState {
public:
  static const int T_DORMANT = 0;
  static const int T_IN_POLYGON = 1;
  static const int T_IN_CONTOUR = 2;
}
} // namespace tessellation
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
