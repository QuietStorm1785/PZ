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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLUtessellatorCallbackAdapter {
public:
  void begin(int var1) {}

  void edgeFlag(bool var1) {}

  void vertex(void *var1) {}

  void end() {}

  void error(int var1) {}

  void combine(double[] var1, Object[] var2, float[] var3, Object[] var4) {}

  void beginData(int var1, void *var2) {}

  void edgeFlagData(bool var1, void *var2) {}

  void vertexData(void *var1, void *var2) {}

  void endData(void *var1) {}

  void errorData(int var1, void *var2) {}

  void combineData(double[] var1, Object[] var2, float[] var3, Object[] var4,
                   void *var5) {}
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
