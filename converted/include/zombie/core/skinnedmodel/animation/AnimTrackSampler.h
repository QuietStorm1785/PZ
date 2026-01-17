#pragma once
#include "org/lwjgl/util/vector/Matrix4f.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace animation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimTrackSampler {
public:
  virtual ~AnimTrackSampler() = default;
  float getTotalTime();

  bool isLooped();

  void moveToTime(float time);

  float getCurrentTime();

  void getBoneMatrix(int boneIdx, Matrix4f out_matrix);

  int getNumBones();
}
} // namespace animation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
