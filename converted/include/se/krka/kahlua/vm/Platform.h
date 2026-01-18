#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Platform {
public:
  virtual ~Platform() = default;
  double pow(double arg0, double arg1);

  KahluaTable newTable();

  KahluaTable newEnvironment();

  void setupEnvironment(KahluaTable arg0);
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
