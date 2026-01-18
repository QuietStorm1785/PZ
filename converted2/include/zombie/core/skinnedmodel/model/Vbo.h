#pragma once
#include "org/lwjglx/BufferUtils.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMY on 3/17/2016.
 */
class Vbo {
public:
  IntBuffer b = BufferUtils.createIntBuffer(4);
  int VboID;
  int EboID;
  int NumElements;
  int VertexStride;
  bool FaceDataOnly;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
