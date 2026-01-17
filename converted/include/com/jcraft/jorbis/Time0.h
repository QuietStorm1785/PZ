#pragma once
#include "com/jcraft/jogg/Buffer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Time0 : public FuncTime {
public:
  void free_info(void *var1) {}

  void free_look(void *var1) {}

  int inverse(Block var1, void *var2, float[] var3, float[] var4) { return 0; }

  void *look(DspState var1, InfoMode var2, void *var3) { return ""; }

  void pack(void *var1, Buffer var2) {}

  void *unpack(Info var1, Buffer var2) { return ""; }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
